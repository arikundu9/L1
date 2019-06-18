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
#include "lexer.hpp"
/*|---char** getWords(const char *);
 *+---char** explode(const char *,char);
 */
using namespace std;

#define IDENTIFIER_RGX "([a-zA-Z_][a-zA-Z0-9_]*)(.([a-zA-Z_][a-zA-Z0-9_]*))*" /*bug :: allows white space and = symbol*/
#define INT_RGX "[0-9]+"
#define FLOAT_RGX "([0-9]+).([0-9]+)"

char keywords[][12]={ "let","var","if","for","fun","void","int","float","string","and","or","not","this","class","public","private","protected"
					};
char operators[][3]={"+","-","*","/","%","=",
					 ">","<",">=","<=","==","!=",
					 ",",":",";",
					 "+=","-=","*=","/=","%=",
					 "++","--"};

typedef enum tokens {Tnull,Tkeyword,Tidentifier,Toperator,Tinteger,Tfloatpoint,Tstring,Tchar} tokens;
typedef std::pair<tokens,const char *> tokenizedWord;
typedef std::forward_list<tokenizedWord> tokenizedLine;
typedef std::vector<tokenizedLine> tokenizedProg;

/*Function Declerations*/

tokenizedLine getTokenozedLine(const char *);
bool __cmp(tokenizedWord,tokenizedWord);

/*Function Definations*/

tokenizedLine getTokenozedLine(const char *w){
	tokenizedLine tL;
	tokenizedLine::iterator it;
	tokenizedWord tW;
	tokens tk=Tnull;
	it=tL.before_begin();
	for(const char *kw : keywords){
		if(strcmp(kw,w)==0){
			tk=Tkeyword;
			tW.first=tk;
			tW.second=w;
			it=tL.insert_after(it,tW);
			//cout<<w<<" is a keyword\n";
			return tL;
		}
	}
	for(const char *op : operators){
		if(strcmp(op,w)==0){
			tk=Toperator;
			tW.first=tk;
			tW.second=w;
			it=tL.insert_after(it,tW);
			//cout<<w<<" is an operator\n";
			return tL;
		}
	}
	if(regex_match(w,std::regex(IDENTIFIER_RGX))){
		tk=Tidentifier;
		tW.first=tk;
		tW.second=w;
		it=tL.insert_after(it,tW);
		//cout<<w<<" is an identifier\n";
		return tL;
	}
	if(regex_match(w,std::regex(INT_RGX))){
		tk=Tinteger;
		tW.first=tk;
		tW.second=w;
		it=tL.insert_after(it,tW);
		//cout<<w<<" is an integer\n";
		return tL;
	}
	if(regex_match(w,std::regex(FLOAT_RGX))){
		tk=Tfloatpoint;
		tW.first=tk;
		tW.second=w;
		it=tL.insert_after(it,tW);
		//cout<<w<<" is an floating point number\n";
		return tL;
	}
	if(*w=='\"'){/*TODO: add last char chk*/
		tk=Tstring;
		tW.first=tk;
		tW.second=w;
		it=tL.insert_after(it,tW);
		//cout<<w<<" is a string\n";
		return tL;
	}
	if(*w=='\''){/*TODO: add last char chk*/
		tk=Tchar;
		tW.first=tk;
		tW.second=w;
		it=tL.insert_after(it,tW);
		//cout<<w<<" is a char\n";
		return tL;
	}
	
	tW.first=tk;
	tW.second=w;
	it=tL.insert_after(it,tW);
	
	cout<<w<<"  ::  is a unknown word\n";
	char **words;
	words=explode(w,';');
	char **w2;
	for(int i=0;!(words[i][0]=='\0' and words[i][1]=='\0');i++){
		//cout<<words[i]<<endl;
		w2=explode(words[i],',');
		for(int j=0;!(w2[j][0]=='\0' and w2[j][1]=='\0');j++){
			cout<<w2[j]<<endl;
		}
	}
	return tL;
}
bool __cmp(tokenizedWord,tokenizedWord){
	return false;
}

int main(){
	char str1[]="let x = 5.0 , TVal = 7 , person._age = TVal";
	char str2[]="let x=5.0,TVal=7,person._age=TVal";
	char str3[]="let x = \"jjkl as \\\" asljlf\" , y= 3 , m = 'K'";
	char str4[]="for   ;i=0,j=9,m='v';;i<=noofdata;i++,j+=2";
	char **words;
	tokenizedLine tL;
	words=getWords(str4);
	for(int i=0;!(words[i][0]=='\0' and words[i][1]=='\0');i++){
		//cout<<words[i]<<endl;
		tL.merge(getTokenozedLine(words[i]),__cmp);
	}
	free(words);
	for(tokenizedWord tW : tL){
		cout<<"\nType: "<<tW.first<<", String: "<<tW.second;
	}
	return 0;
}

//#endif