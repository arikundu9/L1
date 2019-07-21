/* Project L1 - A new programming language for noobs
 *
 * Copyright (C) 2018-2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * This file belongs to the Project L1.
 * Any commercial use of this file is prohibited.
 */

#ifndef _L1_LL_H
#define _L1_LL_H
#include<functional>
namespace container{
	template<typename V>
	class node{
		public:
			V data;
			node<V> *next;
			node(){
				next=nullptr;
				// data=NULL;
			}
			node(V v,node<V> *p=nullptr){
				next=p;
				data=v;
			}
			
	};
	
	template<typename V>
	class LinkedList{
		public:
			typedef node<V>* iterator;
			node<V> *head;
			LinkedList(){
				head=nullptr;
			}
			bool isEmpty(){
				return (head==nullptr);
			}
			node<V>* insertTop(V d){
				node<V> *tmp=new node<V>(d);
				tmp->next=head;
				head=tmp;
				return head;
			}
			void eraseAfter(iterator id){
				iterator tmp;
				if(id!=nullptr){
					if(id->next!=nullptr){
						tmp=id->next;
						id->next=id->next->next;
						delete tmp;
					}
				}
			}
			node<V>* insertAfter(iterator id,V d){
				if(head==nullptr)
					return insertTop(d);
				else{
					node<V> *tmp=new node<V>(d,id->next);
					id->next=tmp;
					return tmp;
				}
			}
			void forEach(std::function<void(V)> f){
				iterator it=head;
				while(it!=nullptr){
					f(it->data);
					it=it->next;
				}
			}
			void forEachIterator(std::function<void(iterator)> f){
				iterator it=head;
				while(it!=nullptr){
					f(it);
					it=it->next;
				}
			}
			void merge(LinkedList<V> ll){
				iterator it=head;
				if(head==nullptr)
					head=ll.head;
				else{
					while(it->next!=nullptr)
						it=it->next;
					it->next=ll.head;
				}
			}
			V &operator[](iterator i){
				return i->data;
			}
	};
}
#endif