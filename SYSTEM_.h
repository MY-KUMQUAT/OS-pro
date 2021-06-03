#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

void format();
void allocation(int length);
void recycling(int lenghth);
void clearADDRbuffer();

void read_system(FILE* fp, char* filename);
void write_system(FILE* fp, char* filename);