#ifndef _L1_H
#define _L1_H
#include<stdio.h>
#include<stdlib.h>
#define VERSION "0.2"
#define LINE_MAX 100
typedef struct pinput{
	char *source_path,*target_path;
} pinput;
/*Function Declerations*/

void interprete_file(pinput *);

/*Function Definations*/

void interprete_file(pinput *input){
	FILE *fs,*ft;
	char line[LINE_MAX];
	fs=fopen(input->source_path ,"rb");
	if(fs==NULL){
		fprintf(stderr,"\nERROR::Failed to open source file.\n");
		exit(1);
	}
	else{
		ft=fopen(input->target_path,"wb");
		if(ft==NULL){
			fprintf(stderr,"\nERROR::Failed to open target file.\n");
			exit(1);
		}
		else{
			while(fgets(line,LINE_MAX,fs)){
				fprintf(ft,line);
			}
			//fprintf(ft,"bin");
			fclose(ft);
		}
		fclose(fs);
	}
}

#endif