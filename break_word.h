#ifndef _L1_BREAK_WORD_H
#define _L1_BREAK_WORD_H
#include<cstdio>
#include<cstring>

typedef struct{
	bool accepted;
	int nosubstr;
	int map[30][2];
} line_string;

bool isBlankSpace(const char *c){
	return (*c==' ') ? true : false ;
}
bool isQuote(const char *c){
	return (*c=='\\' and *(c+1)=='\"') ? true : false ;
}
bool isLastChar(const char *c){
	return(*c=='\0');
}
bool isOtherChar(const char *c){
	return (!isBlankSpace(c) and !isQuote(c) and !isLastChar(c)) ? true : false ;
}
void increment(const char **c,int *i){
	if(isQuote(*c))
		(*c)+=2,(*i)+=2;
	else
		(*c)++,(*i)++;
}


line_string break_into_words(const char *st){
	int state=0,count=0,i=0;
	line_string l;
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
				l.map[count][0]=i+2;
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
				l.map[count][0]=i+2;
				state=2;
			}
		}
		else if(state==2){
			if(isBlankSpace(st))
				state=2;
			if(isOtherChar(st))
				state=2;
			if(isQuote(st)){
				l.map[count][1]=i-1;
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
		l.nosubstr=count+1;
	}
	return l;
}

char** get_words(const char *st,line_string l){
	char **r;
	int i,j,k;
	if(l.accepted==1){
		r=(char**)malloc(sizeof(char*)*(l.nosubstr+1));
		for(i=0;i<l.nosubstr;i++){
			//cout<<endl<<i+1<<". ";
			*(r+i) = (char*) malloc( sizeof(char)*(l.map[i][1]-l.map[i][0]+2) );
			for(k=0,j=l.map[i][0]; j<=l.map[i][1]; j++,k++){
				//printf("%c",*(st+j));
				*(*(r+i)+k)=*(st+j);
			}
			*(*(r+i)+k)='\0';
		}
		r[i]=(char*)malloc(2);
		*(*(r+i)+0)='\0';
		*(*(r+i)+1)='\0';
	}
	return r;
}
#endif