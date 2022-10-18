// Pre processor directive
#ifndef PPM_CONVERT_MAIN_H
#define PPM_CONVERT_MAIN_H

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>


// Function Prototypes:
void readP3Data( char* name, uint8_t **pixmap,
	int width, int height, int channels );

void readP6Data( char* name, uint8_t **pixmap,
	int width, int height, int channels );

void writeP3Data( char* name, uint8_t *pixmap, 
	int width, int height, int channels );

void writeP6Data( char* name, uint8_t *pixmap, 
	int width, int height, int channels );

#endif // PPM_CONVERT_H