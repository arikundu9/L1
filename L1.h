/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

#ifndef _L1_H
#define _L1_H
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<regex>
#include "break_word.h"
#define VERSION "0.2"

#define LINE_MAX 100

#define LT_VAR_DEC 1
#define LT_FOR_LOOP 2
#define LT_FUN_DEC 4
#define LT_IF_STMT 8
#define LT_ELSE_STMT 16
#define LT_RET_STMT 32


typedef struct pinput{
	char *source_path,*target_path;
} pinput;
typedef struct line{
	//int type;
	char type[30];
	int indent;
} line;

/*Function Declerations*/

void interprete_file(pinput *);
void parsel(const char *,line *);

/*Function Definations*/

void interprete_file(pinput *input){
	FILE *fs,*ft;
	char ln[LINE_MAX];
	fs=fopen(input->source_path ,"rb");
	line rl;
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
			int l1=1;
			while(fgets(ln,LINE_MAX,fs)){
				parsel(ln,&rl);
				printf("%d: Indent: %d, Type: %s\n",l1++,rl.indent,rl.type);
				fprintf(ft,"%d: Indent: %d, Type: %s\n",l1++,rl.indent,rl.type);
			}
			fclose(ft);
		}
		fclose(fs);
	}
}

void parsel(const char *l,line *ret_l){
	FsmLine ls;
	char **words;
	ret_l->indent=0;
	//ret_l->type=0;
	const char *L=l;
	bool indent_end=false;
	while(!indent_end){
		if(*L==32 or *L==9){
			ret_l->indent+=*L;
			L++;
		}
		else
			indent_end=true;
	}
	ls=break_into_words(L);
	words=get_words(L,ls);
	strcpy(ret_l->type,words[0]);
}
#endif