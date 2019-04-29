#include <stdio.h>
#include "simulador.h"

int main(int argc, char const *argv[]) {

  if (argc < 3){
      printf("\nSimulador CANbus 2.0A\n\n");
      printf("Utilize a sintaxe:\n\n\t%s <Arq> <Time>\n", argv[0]);
      printf("\n   Arq: Arquivo descritivo com os frames\n");
      printf("  Time: Tempo da simulação\n\n");
      exit(0);
  }

  input_file((u_int8_t*)argv[1]);
  start_simulation((double)atoll(argv[2]));
  //
  //
  // fifo_t* temp = get_priority_frame();
  // time_current_simulation = 100;
  // printf("%d\n", temp->event.frame.id);
  // realloc_event(temp);
  // add_time_lost_arbitrage(temp->event.duration);
  // next_time_event = time_current_simulation + temp->event.duration;
  // verific_queue();
  // verific_give_up();
  // printf("tamanho da fila = %d\n", length_queue);
  // printf("numero de give = %d\n", msg_give_up);
  // // temp = get_priority_frame();
  // printf("%d\n", list_event->first->event.frame.id);
  // //
  // for(fifo_t* aux=list_event->first;aux;aux=aux->next_event){
  //     printf("ID = %lu  ", aux->event.frame.id);
  //     printf("cycle = %lf  ", aux->event.frame.cycle_time);
  //     printf("Payload = %lu  ", aux->event.frame.payload);
  //     printf("Current time: %lf\n", aux->event.time_happen);
  // }

  return 0;
}
