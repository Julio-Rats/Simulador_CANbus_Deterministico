#ifndef SIMULADOR
#define  SIMULADOR

#include "get_candb.h" // include to structs.h, fifo.h

double time_current_simulation;
double next_time_event;
double start_time_queue;
double end_time_queue;
double time_max_queue;
double wcrt;
u_int16_t wcrt_id;
u_int16_t length_queue;
u_int16_t max_length_queue;
u_int16_t msg_give_up;


typedef enum{
    RUNNING=0, WAIT, GNC, /*get no cycle*/
}states_e;

states_e state_current;

fifo_t* get_priority_frame();
double small_time(double time);
double get_mean_wcrt();
void   get_wcrt();
void   start_simulation(double time_of_simulation,  u_int8_t DEBUG);
void   add_time_lost_arbitrage(double time);
void   realloc_event(fifo_t* event);
void   verific_queue();
void   verific_give_up();
void   verific_wcrt();
void   check_time(double time);


#endif
