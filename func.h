#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>

void read(WaveRIFF* , WaveFormat* , WaveData* , int16_t**, FILE*);
void write(WaveRIFF, WaveFormat, WaveData, int16_t*, FILE*);
void new_data(int16_t**, int);
void nd(int16_t**, int, int);

#endif
