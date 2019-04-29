#ifndef CANDB
#define  CANDB

#include "fifo.h"
#include <math.h>

#define  BITS_FRAMES   76  // BITS
#define  PAYLOAD_FRAME 64  // BITS
#define  SPEED_BIT   (double)(pow(2,20)/1000)

void   input_file(u_int8_t* path);
double get_duration_frame(u_int8_t payload);

#endif
