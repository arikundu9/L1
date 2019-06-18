/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

#include<stdio.h>
#include<cui_interface.h>
/*|---void printh();
 *+---void parse_arg(int,char**);
 */
int main(int argc, char **argv){
	
	if(argc<2){
		printh();
	}
	parse_arg(argc,argv);
	return 0;
}