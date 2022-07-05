#include <stdio.h>
#include <math.h>
#include "wave.h"
#include "func.h"


int main(int argc, char** argv)
{
	// Чтение файла
	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL)
	{
		printf("ERROR1");
		return 1;
	}	
	
	WaveRIFF header;
	WaveFormat info;
	WaveData dataHeader;
	
	int16_t *data;
	
	read(&header, &info, &dataHeader, &data, fin);
	
	// Обработка
	new_data(&data, dataHeader.subchunkSize2 / info.blockAlign);

	// Запись в новый файл
	FILE* fout = fopen(argv[2], "w");
	if (fout == NULL)
	{
		printf("ERROR2");
		return 2;
	}
	
	write(header, info, dataHeader, data, fout);
	
	// Очистка памяти
	delete[] data;
	fclose(fin);
	fclose(fout);
}



















/*
	printf("%c%c%c%c\t", header.chunkID, header.chunkID >> 8, header.chunkID >> 16, header.chunkID >> 24);
	printf("%d\t", header.chunkSize);
	printf("%c%c%c%c\n", header.format, header.format >> 8, header.format >> 16, header.format >> 24);
	
	printf("%c%c%c\t", info.subchunkID, info.subchunkID >> 8, info.subchunkID >> 16);
	printf("%d\n", info.subchunkSize);
	printf("%d\n", info.audioFormat);
	printf("%d\n", info.nChannels);
	printf("%d\n", info.sampleRate);
	printf("%d\n", info.byteRate);
	printf("%d\n", info.blockAlign);
	printf("%d\n", info.bitsPerSample);
	
	printf("%c%c%c%c\t", dataHeader.subchunkID2, dataHeader.subchunkID2 >> 8, dataHeader.subchunkID2 >> 16, dataHeader.subchunkID2 >> 24);
	printf("%d\n", dataHeader.subchunkSize2 / (info.nChannels * info.bitsPerSample / 8));
*/


















