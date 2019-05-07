#include "simulador.h"

int main(int argc, char *argv[]) {

  u_int8_t debug = 0;

  if (argc < 3 || argc > 4){

        printf("\nSimulador CANbus 2.0A\n\n");
        printf("Utilize a sintaxe:\n\n\t%s <Arq> <Time> [DEBUG]\n", argv[0]);
        printf("\n   Arq: Arquivo descritivo com os frames (path)\n");
        printf("  Time: Tempo da simulação (ms)\n");
        printf("  DEBUG: Debug em tempo de execução (0->False; 1->True)\n\n");
        exit(14);

    }else if (argc == 4){
        debug = atoi(argv[3]);
  }


  main_simulated(argv[1], atol(argv[2]), debug);
  main_simulated("input2.txt", atol(argv[2]), debug);
  return 0;

}
