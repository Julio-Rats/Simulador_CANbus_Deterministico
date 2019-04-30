# Simulador_CANbus_deterministico

Codigo que implementa um simulador deterministico de um barramento CAN 2.0A
com entrada de um aquivo padrão de frames descrito abaixo, exemplo aquivo input.txt.

arquivo entrada:
"separar apenas por um espaço os valores"

<ID> <CYCLE_TIME> <DELAY_START_TIME>

Entrada do programa:

./simulador <PATH> <TIME> [DEBUG_MODE]

PATH: Caminho com o arquivo descrevendo os quadros CAN.

TIME: Tempo de simulação de milissegundos (ms)

DEBUG_MODE: 0 para falso, 1 para mostrar estado das mensagens a cada escrita.
