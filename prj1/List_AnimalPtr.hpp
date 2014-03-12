#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Animals.hpp"

#ifndef LIST_ANIMALPTR_H
#define LIST_ANIMALPTR_H

/* structs */

struct dllist {
 //int number;
 Animal *animal;
 struct dllist *next;
 struct dllist *prev;
};


struct List_AnimalPtr_Iterator { 
struct dllist *element;
void (*inc)(List_AnimalPtr_Iterator *);
void (*dec)(List_AnimalPtr_Iterator *);
Animal* (*deref)(List_AnimalPtr_Iterator *);

};


struct List_AnimalPtr {

struct dllist *head, *tail;

void (*push_back)(List_AnimalPtr *,Animal *);
void (*insert)(List_AnimalPtr *,List_AnimalPtr_Iterator, Animal *);
void (*erase)(List_AnimalPtr *, List_AnimalPtr_Iterator);
List_AnimalPtr_Iterator (*begin)(List_AnimalPtr *);
List_AnimalPtr_Iterator (*end)(List_AnimalPtr *);
void (*dtor)(List_AnimalPtr *);
};


//protos
void my_dtor(List_AnimalPtr *list);
void my_push_back(struct List_AnimalPtr *list, Animal *ani );

void my_insert(struct List_AnimalPtr *list, struct List_AnimalPtr_Iterator node, Animal *ani ) ;
void my_erase(struct List_AnimalPtr *list,struct  List_AnimalPtr_Iterator lnode);

void my_inc(struct List_AnimalPtr_Iterator *it);
void my_dec(struct List_AnimalPtr_Iterator *it);

Animal *my_deref(List_AnimalPtr_Iterator *it);

List_AnimalPtr_Iterator my_begin(struct List_AnimalPtr *list);
List_AnimalPtr_Iterator my_end(struct List_AnimalPtr *list);

int List_AnimalPtr_Iterator_equal(List_AnimalPtr_Iterator it1, List_AnimalPtr_Iterator it2);

void List_AnimalPtr_ctor(List_AnimalPtr *list);


#endif

