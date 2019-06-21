/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

// #ifndef _L1_LL_H
// #define _L1_LL_H
#include<iostream>
#include "linkedlist.hpp"
using namespace std;

int main(){
	container::LinkedList<int> list;
	container::LinkedList<int>::iterator it;
	it=list.head;
	it=list.insertAfter(it,1);
	it=list.insertAfter(it,2);
	it=list.insertAfter(it,3);
	it=list.insertAfter(it,4);
	it=list.insertAfter(it,5);
	it=list.insertAfter(it,6);
	// list.insertTop(1);
	// list.insertTop(2);
	// list.insertTop(3);
	// list.insertTop(4);
	for(it=list.head; it!=nullptr; it=it->next){
		// if(it->data==2)
			// /* it= */list.insertAfter(it,9);
		// if(it->data==6)
			// /* it= */list.eraseAfter(it);
		cout<<it->data<<endl;
	}
	// list.forEach([&](int i){
		// cout<<i<<endl;
	// });
	list.forEachIterator([&](container::LinkedList<int>::iterator i){
		cout<<i->data<<endl;
	});
	// for(it=list.head; it!=nullptr; it=it->next){
		
		// cout<<it->data<<endl;
	// }
	return 0;
}
// #endif