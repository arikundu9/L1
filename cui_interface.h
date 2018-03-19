#ifndef _CUI_INTERFACE
#define _CUI_INTERFACE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "L1.h"

void printh(){
	printf("\nL1 Code Interpreter   v%s\n",VERSION);
	printf("\nUsage:\tL1 [-OPTIONS] [INPUT_L1_SOURCE]\n");
	printf("\n[-OPTIONS]\n");
	printf("\t-o:path\t\tSet output file path.\n");
	printf("\t-v\t\tDisplay compiled versions.\n");
	printf("\t-help\t\tPrint this help message.\n");
	printf("\nExample:\tL1 -o:outputfile.ext source.lone\n\n");
}


void parse_arg(int argc,char **argv){
	char *ctmp;
	pinput in;
	for(int i=1; i<argc; i++){
		ctmp=*(argv+i);
		if(strcmp(ctmp,"-help")==0)
			printh();
		else if(strcmp(ctmp,"-v")==0)
			printf("\n%s\n",VERSION);
		else if( (*ctmp=='-') and (*(ctmp+1)=='o') ){
			in.target_path=ctmp+3;
		}
		else if(i+1 == argc){
			in.source_path=ctmp;
			interprete_file(&in);
		}
		else{
			exit;
		}
	}
}

#endif