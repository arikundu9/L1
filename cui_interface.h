/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

#ifndef _CUI_INTERFACE
#define _CUI_INTERFACE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "L1.hpp"
/*|---pInput{char *source_path,*target_path;}
 *+---void interprete_file(pInput *);
 */

/*Function Declerations*/

void printh();
void parse_arg(int,char**);

/*Function Definations*/

void printh(){
	printf("\nL1 Code Interpreter   v%s\n",VERSION);
	printf("\nUsage:\tL1 [-OPTIONS]\n");
	printf("\n[-OPTIONS]\n");
	printf("\t-i PATH\t\tSet L1 source file path.\n");
	printf("\t-o PATH\t\tSet output file path.\n");
	printf("\t-v\t\tDisplay compiled versions.\n");
	printf("\t-help\t\tPrint this help message.\n");
	printf("\nExample:\tL1 -i source.lone -o outputfile.ext\n\n");
}


void parse_arg(int argc,char **argv){
	char *ctmp;
	pInput in;
	int i;
	for(i=1; i<argc; i++){
		ctmp=*(argv+i);
		if(strcmp(ctmp,"-help")==0)
			printh();
		else if((*ctmp=='-')){
			if(*(ctmp+1)=='v' and *(ctmp+2)=='\0'){
				printf("%s\n",VERSION);
				exit(3);
			}
			else if(*(ctmp+1)=='o' and *(ctmp+2)=='\0')
				in.target_path=*(argv+(++i));
			else if(*(ctmp+1)=='i' and *(ctmp+2)=='\0')
				in.source_path=*(argv+(++i));
			else{
				fprintf(stderr,"ERROR::Invalid Option : %s\n",ctmp);
				exit(1);
			}
		}
		else{
			fprintf(stderr,"ERROR::Invalid Argument : %s\n",ctmp);
			exit(2);
		}
	}
	if(i==argc){
		interprete_file(&in);
	}
}

#endif