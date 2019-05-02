# Simulador_CANbus_Deterministico

Codigo que implementa um simulador deterministico de um barramento CAN 2.0A
com entrada de um arquivo padrão de frames descrito abaixo, exemplo arquivo input.txt.

arquivo entrada:
"separar apenas por um espaço os valores"

< ID > < CYCLE_TIME > < DELAY_START_TIME >

ID: ID do quadro CAN2.0A [0..2047]

CYCLE_TIME: Tempo de ciclo da mensagem [1..2147483647] (ms)

DELAY_START_TIME: Tempo de espera para primeiro acesso ao barramento, 0 para imediato [0..2147483647] (ms)

Entrada do programa:

./simulador < PATH > < TIME > [DEBUG_MODE]

PATH: Caminho com o arquivo descrevendo os quadros CAN.

TIME: Tempo de simulação de milissegundos [0..2147483646] (ms)

DEBUG_MODE: 0 para falso, 1 para mostrar estado das mensagens a cada escrita.
