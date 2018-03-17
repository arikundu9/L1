#ifndef _CUI_INTERFACE
#define _CUI_INTERFACE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "L1.h"

void printh(){
	printf("\nL1 Code Interpreter   v%s\n\nUsage:\tL1 [-OPTIONS] [INPUT_L1_SOURCE]\n\n[-OPTIONS]\n    -v\t\tDisplay compiled versions.\n    -help\tPrint this help message.\n\n",VERSION);
}


void parse_arg(int argc,char **argv){
	char *ctmp;
	for(int i=1; i<argc; i++){
		ctmp=*(argv+i);
		if(strcmp(ctmp,"-help")==0)
			printh();
		else if(strcmp(ctmp,"-v")==0)
			printf("\n%s\n",VERSION);
		else if(i+1 == argc){}
			//source=ctmp;
		else{
			//cout<<"\nERROR :: Unknown argument:"<<i+1<<" "<<ctmp<<endl;
			exit;
		}
	}
}

#endif