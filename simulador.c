#include "simulador.h"
//#define DEBUG 0
#define VERBOSE 1

int main_simulated(char* path, double time_simulation, u_int8_t debug) {

  input_file(path);
  start_simulation(time_simulation, debug);

  return 0;
}

void start_simulation(double time_end_simulation, u_int8_t DEBUG){
    min_length_queue = 65535;
    time_min_queue   = 2147483647;
    wcrt             = 0;
    number_of_queue  = 0;
    time_mean_queue  = 0;
    msg_deadline     = 0;
    frames_write     = 0;
    time_max_queue   = 0;
    length_queue     = 0;
    msg_deadline     = 0;
    max_length_queue = 0;
    fifo_t* aux       = NULL;
    acumul_length_queue = 0;
    time_current_simulation = list_event->first->event.time_current;

    while(time_current_simulation < time_end_simulation){
          frames_write++;
          aux = get_priority_frame();

          if (DEBUG){
              for(fifo_t* aux=list_event->first;aux;aux=aux->next_event){
                  printf("ID = %lu  ", aux->event.frame.id);
                  printf("cycle = %lf  ", aux->event.frame.cycle_time);
                  printf("Current time: %lf\n", aux->event.time_current);
                  printf("Happen time: %lf\n", aux->event.time_happen);
              }
              printf("\nWRITE ID %d -- ", aux->event.frame.id);
              printf("%lf\n", time_current_simulation);
              printf("wcrt ID: %d temp: %lf\n", wcrt_id, wcrt);
              printf("tamanho da fila = %d\n", length_queue);
              printf("tamanho max fila = %d\n", max_length_queue);
              printf("tempo max da fila = %lf\n", time_max_queue);
              getchar();
          }

          add_time_lost_arbitrage(aux->event.duration);
          realloc_event(aux);
          check_time(aux->event.duration);
          verific_queue();
          verific_give_up();
          verific_wcrt();

      time_current_simulation = small_time(time_end_simulation);
    } // while

    get_wcrt();
    double mean_wcrt = get_mean_wcrt();
    list_event->first = NULL;
    verific_queue();

    double print_mean_queue_length = 0;
    double print_mean_queue_time   = 0;

    busload_simulated = (((frames_write*(BITS_FRAMES+PAYLOAD_FRAME))/SPEED_BIT)/10)*(1000/time_current_simulation);

    if (number_of_queue == 0){
       min_length_queue = 0;
       time_min_queue   = 0;
    }else{
       print_mean_queue_length = ((double)acumul_length_queue/number_of_queue);
       print_mean_queue_time   = ((double)time_mean_queue/number_of_queue);
    }

    if (VERBOSE){
        printf("\nFrames escritos        = %ld (Frames)\n", frames_write);
        printf("Numero de deadlines    = %d (Frames)\n\n", msg_deadline);

        printf("Numero de filas        = %d (Unid.)\n", number_of_queue);
        printf("Frames em fila acumul. = %d (Unid.)\n\n", acumul_length_queue);

        printf("Tamanho min de fila    = %d (Frames)\n", min_length_queue);
        printf("Tamanho medio de filas = %lf (Frames)\n", print_mean_queue_length);
        printf("Tamanho max de fila    = %d (Frames)\n\n", max_length_queue);

        printf("Tempo min de fila      = %lf (ms)\n", time_min_queue);
        printf("Tempo medio de filas   = %lf (ms)\n", print_mean_queue_time);
        printf("Tempo max de fila      = %lf (ms)\n\n", time_max_queue);

        printf("WCRT ID: %d WRCT Time: %lf (ms)\n", wcrt_id, wcrt);
        printf("Media WCRT             = %lf (ms)\n\n", mean_wcrt);

        printf("Busload                = %lf (%)\n", busload_simulated);
        printf("Tempo de simulação     = %lf (ms)\n\n", time_current_simulation);
    }

}

fifo_t* get_priority_frame(){
    u_int16_t high_priority  = pow(2,16)-1;
    fifo_t*    event_priority = NULL;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
         if ((aux->event.frame.id < high_priority) && (aux->event.time_happen <= time_current_simulation)){
              high_priority  = aux->event.frame.id;
              event_priority = aux;
         }
    return event_priority;
}

void add_time_lost_arbitrage(double time){
  for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
    if (aux->event.time_happen <= time_current_simulation){
       aux->event.time_happen += time;
    }
}

void realloc_event(fifo_t* event){
    rem_list(event);
    if (event->event.frame.cycle_time < 0){
        free(event);
        return;
    }
    if ((event->event.time_current + event->event.frame.cycle_time)>=time_current_simulation){
        event->event.time_happen += event->event.frame.cycle_time;
    }else{
        event->event.time_happen = time_current_simulation;
    }
    event->event.time_current = event->event.time_happen;
    add_list(event->event);
}

void verific_queue(){
    u_int16_t count=0;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
        if (aux->event.time_current != aux->event.time_happen)
            count += 1;

    if (count!=0){
        if (length_queue==0)
            start_time_queue = time_current_simulation;

        if (max_length_queue < count)
            max_length_queue = count;

        if (current_length_queue < count)
            current_length_queue = count;

    }else if (length_queue!=0){
        end_time_queue = time_current_simulation;
        if ((end_time_queue-start_time_queue) > time_max_queue)
            time_max_queue = ((double)end_time_queue-start_time_queue);

        if ((end_time_queue-start_time_queue) < time_min_queue)
            time_min_queue = ((double)end_time_queue-start_time_queue);

        if (min_length_queue > current_length_queue)
        min_length_queue = current_length_queue;

        number_of_queue++;
        acumul_length_queue += current_length_queue;
        time_mean_queue     += ((double)end_time_queue-start_time_queue);

        current_length_queue = 0;
    }
    length_queue = count;
}

void verific_give_up(){
    u_int16_t count=0;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
       if (aux->event.time_happen >= (aux->event.frame.cycle_time+aux->event.time_current)){
          count += 1;
          realloc_event(aux);
       }

    if (msg_deadline < count)
       msg_deadline = count;
}

double small_time(double time){
    double menor = time;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
      if (aux->event.time_happen < menor)
          menor = aux->event.time_happen;
    return menor;
}

void verific_wcrt(){
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
      if (aux->event.frame.wcrt < (aux->event.time_happen-aux->event.time_current))
         aux->event.frame.wcrt = aux->event.time_happen-aux->event.time_current;

}

void check_time(double time){
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
        if (aux->event.time_current < time_current_simulation+time)
           aux->event.time_happen = time_current_simulation+time;
}

void get_wcrt(){
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
      if (wcrt<aux->event.frame.wcrt){
          wcrt    = aux->event.frame.wcrt;
          wcrt_id = aux->event.frame.id;
      }
}

double get_mean_wcrt(){
    u_int16_t count = 0;
    double    media = 0;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event){
        count++;
        media += aux->event.frame.wcrt;
    }
    return (double)(media/(double)count);
}
