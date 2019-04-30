#include <stdio.h>
#include "simulador.h"

int main(int argc, char const *argv[]) {

  u_int8_t debug = 0;
  if (argc < 3){
      printf("\nSimulador CANbus 2.0A\n\n");
      printf("Utilize a sintaxe:\n\n\t%s <Arq> <Time> [DEBUG]\n", argv[0]);
      printf("\n   Arq: Arquivo descritivo com os frames (path)\n");
      printf("  Time: Tempo da simulação (ms)\n");
      printf("  DEBUG: Debug em tempo de execução (0->False; 1->True)\n\n");
      exit(14);

  }else if (argc == 4){
      debug = atoi(argv[3]);
  }

  input_file((u_int8_t*)argv[1]);
  start_simulation((double)atoll(argv[2]), debug);

  return 0;
}
