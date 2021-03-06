/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

#ifndef _L1_LEXER_H
#define _L1_LEXER_H
#include<cstdlib>
#include<cstring>
char** getWords(const char *);
char** explode(const char *,char);
bool isValidIdentifier(const char *);
namespace lexer{
	typedef struct{
		bool accepted;
		int nosubstr;
		int map[30][2];
	} FsmLine;

	/*Function Declerations*/
	inline bool isBlankSpace(const char *);
	inline bool isEscQuote(const char *);
	inline bool isQuote(const char *);
	inline bool isLastChar(const char *);
	inline bool isOtherChar(const char *);
	inline bool is_AZ(const char *);
	inline bool is_az(const char *);
	inline bool is_09(const char *);
	void increment(const char **,int *);
	FsmLine word_parser_fsm(const char *);
	char** get_words(const char *,FsmLine);

	/*Function Definations*/

	inline bool isBlankSpace(const char *c){
		return (*c==' ');
	}
	inline bool isEscQuote(const char *c){
		return (*c=='\\' and *(c+1)=='\"');
	}
	inline bool isQuote(const char *c){
		return (*c=='\"' and !isEscQuote(c-1));
	}
	inline bool isLastChar(const char *c){
		return(*c=='\0');
	}
	inline bool isOtherChar(const char *c){
		return (!isBlankSpace(c) and !isQuote(c) and !isLastChar(c));
	}
	inline bool is_AZ(const char *c){
		return (*c>=65 and *c<=90);
	}
	inline bool is_az(const char *c){
		return (*c>=97 and *c<=122);
	}
	inline bool is_09(const char *c){
		return (*c>=48 and *c<=57);
	}
	void increment(const char **c,int *i){
		if(isEscQuote(*c))
			(*c)+=2,(*i)+=2;
		else
			(*c)++,(*i)++;
	}

	FsmLine word_parser_fsm(const char *st){
		int state=0,count=0,i=0;
		FsmLine l;
		while(true){
			if(state==0){
				if(isBlankSpace(st))
					state=0;
				if(isOtherChar(st)){
					l.map[count][0]=i;
					state=1;
				}
				if(isLastChar(st))
					break;
				if(isQuote(st)){
					l.map[count][0]=i/* i+1 */;
					state=2;
				}
			}
			else if(state==1){
				if(isBlankSpace(st)){
					l.map[count][1]=i-1;
					state=0;
					count++;
				}
				if(isLastChar(st)){
					l.map[count][1]=i-1;
					count++;
					break;
				}
				if(isOtherChar(st))
					state=1;
				if(isQuote(st)){
					l.map[count][1]=i-1;
					count++;
					l.map[count][0]=i/* i+1 */;
					state=2;
				}
			}
			else if(state==2){
				if(isBlankSpace(st))
					state=2;
				if(isOtherChar(st))
					state=2;
				if(isQuote(st)){
					l.map[count][1]=i/* i-1 */;
					state=0;
					count++;
				}
				if(isLastChar(st))
					break;
			}
		increment(&st,&i);
		}
		if(state==0 or state==1){
			l.accepted=true;
			l.nosubstr=count;
		}
		else{
			l.accepted=false;
			//l.nosubstr=count+1;
		}
		return l;
	}

	char** get_words(const char *st,FsmLine l){
		char **r;
		int i,j,k;
		if(l.accepted==1){
			r=(char**)malloc(sizeof(char*)*(l.nosubstr+1));
			for(i=0;i<l.nosubstr;i++){
				*(r+i) = (char*) malloc( sizeof(char)*(l.map[i][1]-l.map[i][0])+1);
				for(k=0,j=l.map[i][0]; j<=l.map[i][1]; j++,k++)
					*(*(r+i)+k)=*(st+j);
				*(*(r+i)+k)='\0';
			}
			r[i]=(char*)malloc(2);
			*(*(r+i)+0)='\0';
			*(*(r+i)+1)='\0';
		}
		return r;
	}
}

char** getWords(const char *s){
	using namespace lexer;
	FsmLine l;
	char **words;
	l=word_parser_fsm(s);
	words=get_words(s,l);
	return words;
}

char** explode(const char *s,char z){
	using namespace lexer;
	char **r;
	int count=0;
	int start=0,end=0,i=0;
	int map[30][2];
	while(true){
		if(*s==z){
			end=i-1;
			if(i!=start){
				map[count][0]=start;
				map[count][1]=end;
				count++;
			}
			start=i+1;
		}
		if(isLastChar(s)){
			end=i-1;
			if(i!=start){
				map[count][0]=start;
				map[count][1]=end;
				count++;
			}
			break;
		}
		s++;
		i++;
	}
	s-=i;
	r=(char**)malloc(sizeof(char*)*(count+1));
	int j,k;
	for(i=0;i<count;i++){
		*(r+i) = (char*) malloc( sizeof(char)*(map[i][1]-map[i][0]+1) );
		for(k=0,j=map[i][0]; j<=map[i][1]; j++,k++)
			*(*(r+i)+k)=*(s+j);
		*(*(r+i)+k)='\0';
	}
	r[i]=(char*)malloc(2);
	*(*(r+i)+0)='\0';
	*(*(r+i)+1)='\0';
	return r;
}

bool isValidIdentifier(const char *s){
	using namespace lexer;
	int state=0;
	while(!isLastChar(s)){
		if(state==0){
			if(*s=='_' or is_AZ(s) or is_az(s))
				state=1;
			else if(*s=='.' or *s==' ' or is_09(s))
				state=2;
		}
		else if(state==1){
			if(*s=='_' or is_AZ(s) or is_az(s) or is_09(s))
				state=1;
			else if(*s=='.')
				state=0;
			else
				state=2;
		}
		s++;
	}
	return state==1;
}
#endif