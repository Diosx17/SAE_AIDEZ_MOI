#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GrayScale(FILE*, FILE*);
void Invert(FILE*, FILE*);
void Mono(FILE*, FILE *);
void Contours(FILE*, FILE*);
void Superposition(FILE*, FILE*, FILE*);

#endif // HEADER_H_INCLUDED
