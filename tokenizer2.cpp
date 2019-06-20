/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

//#ifndef _L1_TOKENIZER_H
//#define _L1_TOKENIZER_H
#include<iostream>
#include<utility>
#include<cstring>
#include<forward_list>
#include<vector>
#include<regex> 
#include<cstdio>
#include "lexer.hpp"
#include "linkedlist.hpp"
/*|---char** getWords(const char *);
 *|---char** explode(const char *,char);
 *+---bool isValidIdentifier(const char *);
 */
using namespace std;

#define IDENTIFIER_RGX "([a-zA-Z_][a-zA-Z0-9_]*)(.([a-zA-Z_][a-zA-Z0-9_]*))*" /*bug :: allows white space and = symbol*/
#define INT_RGX "[0-9]+"
#define FLOAT_RGX "([0-9]+).([0-9]+)"

char keywords[][12]={ "let","var","if","for","fun","void","int","float","string","and","or","not","this","class",
					  "public","private","protected"};
char operators[][3]={"+=","-=","*=","/=","%=",
					 ">=","<=","==","!=",
					 "++","--",
					 "+","-","*","/","%","=",
					 ">","<",
					 ",",":",";"
					 };

typedef enum tokens {Tnull,Tkeyword,Tidentifier,Toperator,Tinteger,Tfloatpoint,Tstring,Tchar} tokens;
typedef std::pair<tokens,const char *> tokenizedWord;
typedef container::LinkedList<tokenizedWord> tokenizedLine;
typedef std::vector<tokenizedLine> tokenizedProg;

/*Function Declerations*/

tokenizedLine getTokenozedLine(const char *);
bool __cmp(tokenizedWord,tokenizedWord);
bool isUnknownWordExists(tokenizedLine &);
void resolveUnknownWords(tokenizedLine &);

/*Function Definations*/

tokenizedLine getTokenozedLine(const char *w){
	tokenizedLine tL;
	tokenizedLine::iterator it;
	tokenizedWord tW;
	tokens tk=Tnull;
	it=tL.head;
	for(const char *kw : keywords){
		if(strcmp(kw,w)==0){
			tk=Tkeyword;
			tW.first=tk;
			tW.second=w;
			it=tL.insertAfter(it,tW);
			//cout<<w<<" is a keyword\n";
			return tL;
		}
	}
	for(const char *op : operators){
		if(strcmp(op,w)==0){
			tk=Toperator;
			tW.first=tk;
			tW.second=w;
			it=tL.insertAfter(it,tW);
			//cout<<w<<" is an operator\n";
			return tL;
		}
	}
	if(isValidIdentifier(w)){
		tk=Tidentifier;
		tW.first=tk;
		tW.second=w;
		it=tL.insertAfter(it,tW);
		//cout<<w<<" is an identifier\n";
		return tL;
	}
	if(regex_match(w,std::regex(INT_RGX))){
		tk=Tinteger;
		tW.first=tk;
		tW.second=w;
		it=tL.insertAfter(it,tW);
		//cout<<w<<" is an integer\n";
		return tL;
	}
	if(regex_match(w,std::regex(FLOAT_RGX))){
		tk=Tfloatpoint;
		tW.first=tk;
		tW.second=w;
		it=tL.insertAfter(it,tW);
		//cout<<w<<" is an floating point number\n";
		return tL;
	}
	if(*w=='\"'){/*TODO: add last char chk*/
		tk=Tstring;
		tW.first=tk;
		tW.second=w;
		it=tL.insertAfter(it,tW);
		//cout<<w<<" is a string\n";
		return tL;
	}
	if(*w=='\''){/*TODO: add last char chk*/
		tk=Tchar;
		tW.first=tk;
		tW.second=w;
		it=tL.insertAfter(it,tW);
		//cout<<w<<" is a char\n";
		return tL;
	}
	
	tW.first=tk;
	tW.second=w;
	it=tL.insertAfter(it,tW);
	
	/* cout<<w<<"  ::  is a unknown word\n";
	char **words;
	words=explode(w,';');
	char **w2;
	for(int i=0;!(words[i][0]=='\0' and words[i][1]=='\0');i++){
		//cout<<words[i]<<endl;
		w2=explode(words[i],',');
		for(int j=0;!(w2[j][0]=='\0' and w2[j][1]=='\0');j++){
			cout<<w2[j]<<endl;
		}
	} */
	
	/* while(isUnknownWordExists(tL)){
		//resolveUnknownWords(tL);
	} */
	return tL;
}
bool __cmp(tokenizedWord,tokenizedWord){
	return false;
}
bool isUnknownWordExists(tokenizedLine &tL){
	bool r=false;
	tokenizedLine::iterator it=tL.head;
	for(it=tL.head; it!=nullptr; it=it->next){
		if(it->data.first==Tnull){
			r=true;
			break;
		}
	}
	return r;
}
void removeUnknownWord(tokenizedLine &tL){
	tokenizedLine::iterator it=tL.head;
	for(it=tL.head; it!=nullptr; it=it->next){
		if(it->data.first==Tnull){
			tL.eraseAfter(it);
		}
	}
}
void resolveUnknownWords(tokenizedLine &tL){
	const char *s;
	int i;
	tokenizedLine::iterator it,tmpIt;
	tokenizedWord tW;
	it=tL.head;
	for(it=tL.head; it!=nullptr; it=it->next){
		tmpIt=it;
		//tW=*it;
		if(it->data.first==Tnull){
			s=it->data.second;
			while(!lexer::isLastChar(s)){
				for(const char *op : operators){
					i=0;
					while(!lexer::isLastChar(op+i)){
						if(*(op+i)!=*(s+i)){
							break;
						}
						i++;
					}
					if(lexer::isLastChar(op+i)){
						cout<<"Operator: "<<op<<endl;
						s+=i;
						tW.first=Toperator;
						tW.second=op;
						//tmpIt=it;
						it=tL.insertAfter(it,/* tokenizedWord(Toperator,op) */tW);
						//it=tL.emplace_after(it,Toperator,op);
						cout<<"1st: "<<tmpIt->data.first<<" , 2nd: "<<tmpIt->data.second<<endl;
						//cout<<"1st: "<<it->data.first<<" , 2nd: "<<it->data.second<<endl;
						//if()
						//tL.eraseAfter(tmpIt);//tmp::
						goto jmp;
					}
				}
				s++;
				jmp:;
			}
		}
	}
}
void insert(tokenizedLine &tL){
	tokenizedLine::iterator it=tL.head;
	it=it->next;
	it=tL.insertAfter(it,tokenizedWord(Tkeyword,"the"));
}
int main(){
	char str1[]="let x = 5.0 , TVal = 7 , person._age = TVal";
	char str2[]="let x=5.0,TVal=7,person._age=TVal";
	char str3[]="let x = \"jjkl as \\\" asljlf\" ,y== 3 ,m*= 'K'";
	char str4[]="for   ;i=0,j%=((i+2)/3),m='v';;;i<=noofdata;j=++i";
	char **words;
	tokenizedLine tL;
	words=getWords(str3);
	for(int i=0;!(words[i][0]=='\0' and words[i][1]=='\0');i++){
		//cout<<words[i]<<endl;
		
		tL.merge(getTokenozedLine(words[i]));
	}
	free(words);
	resolveUnknownWords(tL);
	removeUnknownWord(tL);
	insert(tL);
	//removeUnknownWord(tL);
	tokenizedLine::iterator it=tL.head;
	for(it=tL.head; it!=nullptr; it=it->next){
		cout<<"\nType: "<<it->data.first<<", String: "<<it->data.second;
	}
	return 0;
}

//#endif
