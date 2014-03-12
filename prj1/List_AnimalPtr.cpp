//Basic double linked list fragment
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "List_AnimalPtr.hpp"

void my_dtor(List_AnimalPtr *list){
////
//free(list->tail->next);
//while(list->head->next->next != 0){

//while(list->head->next != 0){
while(list->head->next != 0){
	struct dllist *temp = list->head;
	list->head = list->head->next;
	free(temp);
//printf("llllll\n");
}

//printf("endddd\n");
struct dllist *temp1 = list->tail; 
free(temp1);
//free(list);

}
//////////////////


void my_push_back(struct List_AnimalPtr *list, Animal *ani ) {  // re

///////////////////////
struct dllist *lnode =  (struct dllist *)malloc(sizeof(struct dllist));
lnode->animal = ani;


if(list->head == 0) { // NULL
  list->head = lnode;
  lnode->prev = 0; //NULL

  list->tail->prev = lnode;
  lnode->next =list->tail;
 } 
else{
lnode->prev = list->tail->prev;
lnode->next = list->tail;
list->tail->prev->next = lnode;
list->tail->prev = lnode;

}

////////////////////////////////////
//list->tail->next = lnode;
//lnode->prev = list-> tail;
//lnode->prev = list->tail->next->prev;
//lnode->next = list->tail->next;
//list->tail->next->prev = lnode;
//list->tail = lnode;


/*
/////////////////////////////////////////////////////////
/////////////////////////
if(list->head == 0) { // NULL
  list->head = lnode;
  lnode->prev = 0; //NULL
 } else {
 // list->tail->next = lnode;
 // lnode->prev = list->tail;
 }
///////////////////////

 list->tail = lnode;


list->tail->next = (struct dllist *)malloc(sizeof(struct dllist));
list->tail->next->prev = list->tail;
list->tail->next->next == 0;

// lnode->next = 0; //NULL
*/

} // push_back


void my_insert(struct List_AnimalPtr *list, struct List_AnimalPtr_Iterator node, Animal *ani ) {
///////////////////

struct dllist *lnode =  (struct dllist *)malloc(sizeof(struct dllist));
lnode->animal = ani;

/////////////////
if(list->head->next != 0  ){ //not empty
printf("noooooootttttt hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");


	if(node.element->next == 0){  //end

	lnode->prev = list->tail->prev;
	lnode->next = list->tail;
	list->tail->prev->next = lnode;
	list->tail->prev = lnode;
	//list->tail->next = lnode;
	//lnode->prev  = list->tail;
	//lnode->next = node.element;
	//node.element->prev = lnode;
	//list->tail = lnode;

	}else {

	  if(node.element->prev == 0){  //begining
	    node.element->prev = lnode;
	    lnode->next = node.element; 
	    list->head = lnode;  	
  	  }else{                         //regular
	    lnode->next = node.element;
	    lnode->prev = node.element->prev;
	    node.element->prev->next = lnode;
	    node.element->prev = lnode;
  	  }
	}
}else{//empty
printf("hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");

 if(node.element->next == 0){  //end
printf("   empty insert enddd \n");
 	lnode->next = node.element;
            //lnode->prev = node.element->prev;
           // node.element->prev->next = lnode;
            node.element->prev = lnode;       

//	lnode->next = node.element;
//        node.element->prev = lnode;
//        list->tail = lnode;
	lnode->prev = 0;
	list->head = lnode;
 }else{ //begin
printf("   empty insert toppp \n");
/*	    lnode->next = node.element;
            //lnode->prev = node.element->prev;
	    lnode->prev = 0;
            node.element->prev = lnode;
          //  node.element->prev = lnode;
	list->head = list->tail = lnode;
*/

	lnode->next = node.element;
            lnode->prev = node.element->prev;
            node.element->prev->next = lnode;
            node.element->prev = lnode;
}
/*
	/////////////////////////
	if(list->head == 0) { // NULL
  		list->head = lnode;
  		lnode->prev = 0; //NULL
 	}else {
  		list->tail->next = lnode;
  		lnode->prev = list->tail;
 	}

 	list->tail = lnode;

	list->tail->next = (struct dllist *)malloc(sizeof(struct dllist));
	list->tail->next->prev = list->tail;
	list->tail->next->next == 0;



*/
// lnode->next = 0; //NULL

}

}


void my_erase(struct List_AnimalPtr *list,struct  List_AnimalPtr_Iterator lnode) {

 if(lnode.element->prev == 0){	  /// NEW head
///////////////
//	if(lnode.element->next->next = 0){ //only one element
	if(list->tail->prev == lnode.element){
//	printf("onlyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n");
		list->head = list->tail;;
		free(lnode.element);
		return;
 	}//////////////
 	else{
  	list->head = lnode.element->next;
  	lnode.element->next->prev = 0;
  	free(lnode.element);
 	return;
 	}
//return;
	
 }else if(lnode.element->next->next == 0 ){ // new tail
//}else if(lnode.element->next  == 0 ){
  //printf(" taillll \n");
  //list->tail = lnode.element->prev;
  lnode.element->prev->next  = lnode.element->next;
  //lnode.element->next->prev = lnode.element->prev;
  list->tail->prev = lnode.element->prev;  
  free(lnode.element);

 }else{			// regular
  lnode.element->prev->next = lnode.element->next;
  lnode.element->next->prev = lnode.element->prev;
  free(lnode.element);
  }

}



void my_inc(struct List_AnimalPtr_Iterator *it){

it->element = it->element->next;

//if(it->element->next->next == 0 )
//	it->element = 0; 
}

void my_dec(List_AnimalPtr_Iterator *it){

it->element = it->element->prev;

}

/****************************************************/

Animal *my_deref(List_AnimalPtr_Iterator *it){

//if(it->element == 0)
//return NULL;

Animal * anima = it->element->animal;
return anima;


}


List_AnimalPtr_Iterator my_begin(struct List_AnimalPtr *list){

//struct List_AnimalPtr_Iterator *L_A_iterator;
struct List_AnimalPtr_Iterator L_A_iterator;
L_A_iterator.inc = my_inc;
L_A_iterator.dec = my_dec;
L_A_iterator.deref = my_deref;

//L_A_iterator = (struct List_AnimalPtr_Iterator*)malloc(sizeof(L_A_iterator));

L_A_iterator.element = list->head;

//printf("begin: list head number %d\n",list->head->number);

return L_A_iterator;

// to do

}

List_AnimalPtr_Iterator my_end(struct List_AnimalPtr *list){

struct List_AnimalPtr_Iterator L_A_iterator;
L_A_iterator.inc = my_inc;
L_A_iterator.dec = my_dec;


//L_A_iterator = (struct List_AnimalPtr_Iterator*)malloc(sizeof(L_A_iterator));

L_A_iterator.element = list->tail;

//L_A_iterator.element = list->tail->next;

//printf("end: list tail number %d\n",list->tail->next->number);

return L_A_iterator;


// to do


}

int List_AnimalPtr_Iterator_equal(List_AnimalPtr_Iterator it1, List_AnimalPtr_Iterator it2){

if (it1.element == it2.element)
return 1;
else
return 0;

}



void List_AnimalPtr_ctor(List_AnimalPtr *list)
{
list->head = 0;
//list->tail = 0;

////////////
//list->tail-next = (struct dllist *)malloc(sizeof(struct dllist));
//list->tail->next->prev = list->tail;
//list->tail->next->next == 0;
////////////
list->tail = (struct dllist *)malloc(sizeof(struct dllist));
//list->tail->next->prev = list->tail;
list->tail->next = 0;


/////////////
list->push_back = my_push_back;
list->insert = my_insert;
list->erase = my_erase;
list->begin = my_begin;
list->end   = my_end;
list->dtor = my_dtor;

}

//////////////////

 


