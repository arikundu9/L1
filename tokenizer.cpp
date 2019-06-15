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
#include<string>
#include<forward_list>
#include<vector>
#include<regex> 
#include "lexer.hpp"
/*└───char **getWords(const char *);
 */
//using namespace std;

#define IDENTIFIER_RGX "([a-zA-Z_][a-zA-Z0-9_]*)(.([a-zA-Z_][a-zA-Z0-9_]*))*"
#define INT_RGX "[0-9]+"
#define FLOAT_RGX "([0-9]+).([0-9]+)"

std::string keywords[]={ "let","var","if","for","fun","void","int","float","string","and","or","not","this","class","public","private","protected"
					};
std::string operators[]={"+","-","*","/","%","=",
					 ">","<",">=","<=","==","!=",
					 ",",":",";",
					 "+=","-=","*=","/=","%="};
typedef enum tokens {Tnull,Tkeyword,Tidentifier,Toperator,Tinteger,Tfloatpoint,Tstring,Tchar} tokens;
typedef std::pair<tokens,std::string> tokenizedWord;
typedef std::forward_list<tokenizedWord> tokenizedLine;
typedef std::vector<tokenizedLine> tokenizedProg;

/*Function Declerations*/

void getTokenozedLine(const char *);

/*Function Definations*/

void getTokenozedLine(const char *w){
	tokens tk=Tnull;
	for(std::string kw : keywords){
		if(kw==w){
			tk=Tkeyword;
			std::cout<<w<<" is a keyword\n";
			return;
		}
	}
	for(std::string op : operators){
		if(op==w){
			tk=Toperator;
			std::cout<<w<<" is an operator\n";
			return;
		}
	}
	if(regex_match(w,std::regex(IDENTIFIER_RGX))){
		tk=Tidentifier;
		std::cout<<w<<" is an identifier\n";
		return;
	}
	else if(regex_match(w,std::regex(INT_RGX))){
		tk=Tinteger;
		std::cout<<w<<" is an integer\n";
		return;
	}
	else if(regex_match(w,std::regex(FLOAT_RGX))){
		tk=Tfloatpoint;
		std::cout<<w<<" is an floating point number\n";
		return;
	}
}

int main(){
	//char str[]="let x = 5.0 , TVal = 7 , person._age = TVal";
	//char str[]="let x=5.0,TVal=7,person._age=TVal";
	char str[]="let x = \"9 asasljlf\" , y = 3";
	char **words;
	words=getWords(str);
	for(int i=0;!(words[i][0]=='\0' and words[i][1]=='\0');i++){
		//std::cout<<words[i]<<std::endl;
		getTokenozedLine(words[i]);
	}
	free(words);
	return 0;
}

//#endif