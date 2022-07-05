#ifndef WAVE_H
#define WAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

typedef struct
{
	uint32_t chunkID;	// "RIFF"
	uint32_t chunkSize;	// Размер файла в байтах
	uint32_t format;	// "WAVE"
} WaveRIFF;

typedef struct
{
	uint32_t	subchunkID;		// "fmt"
	uint32_t	subchunkSize;	//
	uint16_t	audioFormat;	// PCM == 1 (без сжатия)
	uint16_t	nChannels;		// Количесвто каналов
	uint32_t	sampleRate;		// Частота дискретизации
	uint32_t	byteRate;		// sampleRate * nChannels * bitsPerSample / 8
	uint16_t	blockAlign;		// nChannels * bitsPerSample / 8 - количество байт в sample'е
	uint16_t	bitsPerSample;	// 
} WaveFormat;

typedef struct
{
	uint32_t	subchunkID2;	// "data"
	uint32_t	subchunkSize2;	// nSamples * nChannels * bitsPerSample / 8
} WaveData;

#endif
