#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Animals.hpp"

//////////////////////////
int Poodle_type_check(const char *str)
{
	if ((strcmp(str, "Dog") == 0) || (strcmp(str, "Poodle")) == 0){
   		return 1; 
	}else { return 0;}
}  

int Dog_type_check(const char *str)
{
	if (strcmp(str, "Dog") == 0) {
   		return 1; 
	 }else { return 0;}
}

int Fish_type_check(const char *str)
{
	if (strcmp(str, "Fish") == 0) {
   		return 1;  
	}else { return 0;}
}

////////////////////////////
void my_fetch(struct Dog *a)
{
printf ("Fetching...\n");
}

void dog_talk (struct Animal * a)
{
printf ("Woof!\n");
}

void poodle_talk (struct Animal * a)
{
printf ("Yap!\n");
}

void my_primp (struct Poodle * a)
{
printf("primping...\n");
}

///////////////////////////////////////animal delete
void ani_delet(Animal * ani){
}

/////////////////////////////////////////Dog delete
void dog_delet(Animal *dog){
// printf("in dog_delete %p\n", (char *) dog->type_name);
	free((char *)dog->type_name);
	free((char *)((Dog *)dog)->name);
	free((Dog *)dog);
}
/*
void poo_delet(Animal *poodle) {
 dog_delet(poodle);
 free((char *)((Poodle *)poodle)->groomer);
 free((Poodle *) poodle);
} 
*/
////////////////////////////////////////Poodle delete
void pood_delet(Animal *poodle){
//printf("pooooddddddddddddddddd\n");
	free((char *)poodle->type_name);
	free((char *)((Dog *)poodle)->name);
	free((char *)((Poodle *)poodle)->groomer);
	free((Poodle *) poodle);
}

///////////////////////////////////////fish delete
void fish_delet(Animal *fish){
	free((char *)(fish->type_name));
	free((Fish *)fish);
}


/////////////////////////////////////////////////////////////////???????????????????????????????????
//void my_delet (struct Animal * a)
//{
//printf("my_deletttttttttttttttt\n");

//free(a);
//delete a;
//a = NULL;
//free(a);
//}

////////////////////////////////////////////////////////////////////////

struct Dog *Dog_new(const char *name, int tag) /* Dog "constructor" */
{
// creating a dog to be returned

	struct Dog *a_dog;

	a_dog = (struct Dog*)malloc(sizeof(struct Dog));

//	char *tmp = (char *) malloc(strlen(name));

//	strcpy(tmp,name);

///

char *tmp = (char *) malloc(strlen(name) + 1);
	strcpy(tmp, name);
	a_dog->name = tmp;

//a_dog->name = (char *)malloc(strlen(name));
//strcpy((a_dog->name), name);
//a_dog->name = name;
///

//	a_dog->name = tmp;

	a_dog->dog_tag_number = tag;

	a_dog->animal.talk = dog_talk;

	a_dog->animal.delet = dog_delet;

	a_dog->animal.type_check = Dog_type_check;

	a_dog->fetch = my_fetch;

	a_dog->animal.number_of_legs = 4;

/////
char *tmp2 = (char *) malloc(strlen("Dog") + 1);
	strcpy(tmp2, "Dog");
	a_dog->animal.type_name = tmp2;

//	printf("in dog_new %p\n",  a_dog->animal.type_name);
////

//	a_dog->animal.type_name = "Dog";

	return a_dog;
}

/////////////////////////////////////////////////////////////////////////////
struct Poodle *Dog_downcast_Poodle(struct Dog *d) /* Casting a dog down to poodle */
{
 	if(d->animal.type_check("Poodle")){
		return (Poodle *)d;
	}else
		return NULL;
}

/////////////////////////////////////////////////////////////////////////////

struct Dog *Animal_downcast_Dog(struct Animal *a) /* Casting a dog down to animal */
{
	if(a->type_check("Dog")){
		return (Dog *)a;
	}else 
		return NULL;
}
////////////////////////////////////////////////////////////////////////////

struct Poodle *Poodle_new(const char *name, int tag, const char *groomer) /* Poodle "constructor" */
{
	// creating a dog to be returned

	struct Poodle *a_poodle;

	a_poodle = (struct Poodle*)malloc(sizeof(struct Poodle));


	char *tmp = (char *) malloc(strlen(name) + 1);
        strcpy(tmp, name);
        a_poodle->dog.name = tmp;


//	a_poodle->dog.name = name;

	a_poodle->dog.dog_tag_number = tag;

//	a_poodle->groomer = groomer;

	char *tmp3 = (char *) malloc(strlen(groomer) + 1);
        strcpy(tmp3, groomer);
        a_poodle->groomer = tmp3;

	a_poodle->primp = my_primp;


	char *tmp2 = (char *) malloc(strlen("Poodle") + 1);
        strcpy(tmp2, "Poodle");
        a_poodle->dog.animal.type_name = tmp2;


//	a_poodle->dog.animal.type_name = "Poodle";

	a_poodle->dog.animal.number_of_legs = 4;

	a_poodle->dog.animal.delet = pood_delet;

	a_poodle->dog.animal.type_check = Poodle_type_check;

	a_poodle->dog.animal.talk = poodle_talk;

	a_poodle->dog.fetch = my_fetch;

	return a_poodle;
}

/////////////////////////////////////////////////////////////////////////////////

struct Poodle *Animal_downcast_Poodle(struct Animal *a) /* Casting a Poodle down to animal */
{
	if(a->type_check("Poodle")){
		return (Poodle *)a;
	}else 
		return NULL;

}

//////////////////////////////////////////////////////////////////////////////////


void my_swim (struct Fish * f)
{
	printf("Swimming...\n");
}

void fish_talk (Animal * a)
{
	printf ("Gurgle!\n");
}

////////////////////////////////////////////////////////////////////////////////

struct Fish *Fish_new() /* Fish "constructor" */
{
	// creating fish to be returned
	struct Fish *_fish;
	_fish = (struct Fish*)malloc(sizeof(struct Fish));

	_fish->swim = my_swim;

	_fish->animal.number_of_legs = 0;


	char *tmp3 = (char *)malloc( strlen("Fish")+1 );
        strcpy(tmp3, "Fish");
        _fish->animal.type_name = tmp3;

	_fish->animal.talk = fish_talk;
	_fish->animal.delet = fish_delet;

	_fish->animal.type_check = Fish_type_check;

	return _fish;
}
/////////////////////////////////////////////////////////////////////////////////

struct Fish *Animal_downcast_Fish(struct Animal *a) /* Casting an animal down to fish*/
{

	if(a->type_check("Fish")){
		return (Fish *)a;
	}else 
		return NULL;

}



