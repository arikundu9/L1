#ifndef _L1_H
#define _L1_H
#include<stdio.h>
#define VERSION "0.2"
typedef struct pinput{
	char *source_path,*target_path;
} pinput;
/*Function Declerations*/

void interprete_file(pinput *);

/*Function Definations*/

void interprete_file(pinput *input){
	printf("PATH:%s  OUT:",input->source_path);
}

#endif