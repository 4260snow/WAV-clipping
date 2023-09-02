#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>

void read(WaveRIFF* , WaveFormat* , WaveData* , int16_t**, FILE*);
void write(WaveRIFF, WaveFormat, WaveData, int16_t*, FILE*);
void clip(int16_t**, int);
void unclip(int16_t**, int, int);

#endif
