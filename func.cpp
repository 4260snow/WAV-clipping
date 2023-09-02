#include <math.h>
#include "wave.h"
#include "func.h"

void read(WaveRIFF* header, WaveFormat* info, WaveData* dataHeader, int16_t **data, FILE* fin)
{
	// Чтение заголовка файла
	fread( &header->chunkID, sizeof(header->chunkID), 1, fin );
	fread( &header->chunkSize, sizeof(header->chunkSize), 1, fin );
	fread( &header->format, sizeof(header->format), 1, fin );
	
	//Чтение информации о данных
	fread( &info->subchunkID, sizeof(info->subchunkID), 1, fin );
	fread( &info->subchunkSize, sizeof(info->subchunkSize), 1, fin );
	fread( &info->audioFormat, sizeof(info->audioFormat), 1, fin );
	fread( &info->nChannels, sizeof(info->nChannels), 1, fin );
	fread( &info->sampleRate, sizeof(info->sampleRate), 1, fin );
	fread( &info->byteRate, sizeof(info->byteRate), 1, fin );
	fread( &info->blockAlign, sizeof(info->blockAlign), 1, fin );
	fread( &info->bitsPerSample, sizeof(info->bitsPerSample), 1, fin );
		
	// Чтение данных и пропуск лишней информации
	fread( &dataHeader->subchunkID2, sizeof(dataHeader->subchunkID2), 1, fin );

	if (dataHeader->subchunkID2 == 0x5453494c)
	{
		int shift; // Размер лишней информации
		fread(&shift, sizeof(shift), 1, fin);
		fseek(fin, shift, SEEK_CUR);
		
		fread( &dataHeader->subchunkID2, sizeof(dataHeader->subchunkID2), 1, fin );
		fread( &dataHeader->subchunkSize2, sizeof(dataHeader->subchunkSize2), 1, fin );
	}
	else
	{
		fread( &dataHeader->subchunkSize2, sizeof(dataHeader->subchunkSize2), 1, fin );
	}
	
	*data = new int16_t[header->chunkSize];
	for (int i = 0; i < dataHeader->subchunkSize2 / info->blockAlign; i++)
	{
		fread( &(*data)[i], info->blockAlign, 1, fin );
	}
}

void write(WaveRIFF header, WaveFormat info, WaveData dataHeader, int16_t *data, FILE* fout)
{
		fwrite( &header.chunkID, sizeof(header.chunkID), 1, fout );
	fwrite( &header.chunkSize, sizeof(header.chunkSize), 1, fout );
	fwrite( &header.format, sizeof(header.format), 1, fout );
	
	fwrite( &info.subchunkID, sizeof(info.subchunkID), 1, fout );
	fwrite( &info.subchunkSize, sizeof(info.subchunkSize), 1, fout );
	fwrite( &info.audioFormat, sizeof(info.audioFormat), 1, fout );
	fwrite( &info.nChannels, sizeof(info.nChannels), 1, fout );
	fwrite( &info.sampleRate, sizeof(info.sampleRate), 1, fout );
	fwrite( &info.byteRate, sizeof(info.byteRate), 1, fout );
	fwrite( &info.blockAlign, sizeof(info.blockAlign), 1, fout );
	fwrite( &info.bitsPerSample, sizeof(info.bitsPerSample), 1, fout );
	
	fwrite( &dataHeader.subchunkID2, sizeof(dataHeader.subchunkID2), 1, fout );
	fwrite( &dataHeader.subchunkSize2, sizeof(dataHeader.subchunkSize2), 1, fout );
	
	for (int i = 0; i < dataHeader.subchunkSize2 / info.blockAlign; i++)
	{
		fwrite( &data[i], info.blockAlign, 1, fout );
	}
}

// клиппирование wav файла
void clip(int16_t** data, int size)
{
	for (int i = 2; i < size - 1; i++)
	{
		if (abs((*data)[i] - (*data)[i - 1]) < 10 && abs((*data)[i]) > 10)
		{				
			nd(data, i, size);
		}		
	}
}

// восстановление клиппированного wav файла
void unclip(int16_t** data, int i, int size)
{
	int d = (*data)[i - 1] - (*data)[i - 2];

	int j = i + 1;
	while (abs((*data)[i] - (*data)[j]) < 10 && j < size - 1)
		j++;
	j--;
	
	double k = 1;
	while( i <= j)
	{
		(*data)[i] += d * k;
		(*data)[j] += d * k;
		k *= 1.12;
		i++; j--;
	}
	
}





























