#include<stdio.h>
#include "cui_interface.h"

int main(int argc, char **argv){
	
	if(argc<2){
		printh();
	}
	parse_arg(argc,argv);
	return 0;
}