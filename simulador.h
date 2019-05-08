#ifndef SIMULADOR
#define  SIMULADOR

#include "get_candb.h" // include to structs.h, fifo.h

double wcrt;
double end_time_queue;
double time_min_queue;
double time_max_queue;
double time_mean_queue;
double start_time_queue;
double busload_simulated;
double time_current_simulation;
u_int32_t frames_write;
u_int16_t wcrt_id;
u_int16_t length_queue;
u_int16_t msg_deadline;
u_int16_t number_of_queue;
u_int16_t max_length_queue;
u_int16_t min_length_queue;
u_int16_t acumul_length_queue;
u_int16_t current_length_queue;

int    main_simulated(char* path, double time_simulation);
fifo_t* get_priority_frame();
double small_time(double time);
double get_mean_wcrt();
void   get_wcrt();
void   start_simulation(double time_of_simulation);
void   add_time_lost_arbitrage(double time);
void   realloc_event(fifo_t* event);
void   verific_queue();
void   verific_deadlines();
void   verific_wcrt();
void   check_time();


#endif
