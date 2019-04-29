#include "simulador.h"
#define DEBUG 0

void start_simulation(double time_end_simulation){
    state_current = RUNNING;
    fifo_t* aux    = NULL;
    time_current_simulation = list_event->first->event.time_current;
    u_int32_t frames_write = 0;
    while(time_current_simulation < time_end_simulation){
      if (state_current == RUNNING){
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
          time_current_simulation = small_time(time_end_simulation);
          state_current = WAIT;
      }else if (state_current == WAIT){ // ARB
          verific_queue();
          verific_give_up();
          verific_wcrt();
          state_current = RUNNING;
      }
    } // while

    if (length_queue!=0){
      list_event->first = NULL;
      verific_queue();
    }
    printf("frames total %ld\n", frames_write);
    printf("tamanho max da fila = %d\n", max_length_queue);
    printf("tempo max da fila = %lf\n", time_max_queue);
    printf("numero de give = %d\n", msg_give_up);
    printf("wcrt ID: %d temp: %lf\n", wcrt_id, wcrt);
    printf("tempo simulação = %lf\n", time_current_simulation);

}

fifo_t* get_priority_frame(){
    u_int16_t high_priority  = 2048;
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
    if ((event->event.time_current + event->event.frame.cycle_time)>=time_current_simulation){
        event->event.time_happen += event->event.frame.cycle_time;
    }else{
        event->event.time_happen = time_current_simulation;
    }
    event->event.time_current = event->event.time_happen;
    add_list(event->event);
}

void verific_queue(){
    u_int16_t cont=0;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
        if (aux->event.time_current != aux->event.time_happen)
            cont += 1;

    if (cont!=0){
        if (length_queue==0)
            start_time_queue = time_current_simulation;

        if (max_length_queue < cont)
            max_length_queue = cont;

    }else if (length_queue!=0){
        length_queue = 0;
        end_time_queue = time_current_simulation;
        if ((end_time_queue-start_time_queue) > time_max_queue)
            time_max_queue = (double)(end_time_queue-start_time_queue);
    }
    length_queue = cont;
}

void verific_give_up(){
    u_int16_t cont=0;
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
        if (aux->event.time_happen >= (aux->event.frame.cycle_time+aux->event.time_current)){
            cont += 1;
            realloc_event(aux);
        }

    if (msg_give_up < cont)
        msg_give_up = cont;

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
      if (wcrt<(aux->event.time_happen-aux->event.time_current)) {
          wcrt = aux->event.time_happen-aux->event.time_current;
          wcrt_id = aux->event.frame.id;
      }
}

void check_time(double time){
    for(fifo_t* aux=list_event->first; aux; aux=aux->next_event)
        if (aux->event.time_current < time_current_simulation+time)
            aux->event.time_happen = time_current_simulation+time;
}
