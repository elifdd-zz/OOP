#include <iostream>

namespace cs540{


template <class T> class Link {

public:
//private:

T * next;
T * prev;

public:

Link() {

        prev = NULL;
        next = NULL;

}

T* getNext() {
    return next;
}

void setNext(T* nextn) {
    next = nextn;
}

T* getPrev() {
    return prev;
}


void setPrev(T* prevn) {
    prev = prevn;
}

};


template <class T, Link<T> T::*A_LINK>
class List {

//////////// Inner class Iterator ////
public:

class Iterator {

public:

T * currentLink;


Iterator() {

        currentLink = NULL;

}

Iterator(T* A_A){

currentLink = A_A;

}

T* operator*() const { return currentLink; }

Iterator& operator++(int)
{


	T* temp = currentLink;
	Iterator thisIterator = new Iterator(temp);
        if(currentLink!=NULL) {
            currentLink = (currentLink->*A_LINK).getNext(); //increment this.
        }
        return thisIterator;


}
Iterator& operator++()
{

if(currentLink!=NULL) {
            currentLink = (currentLink->*A_LINK).getNext();
        }
        return *this;
}

friend bool operator== (const Iterator &first, const Iterator &other)
{
        return (first.currentLink == other.currentLink);
}
};


List(){

first = NULL;
last  = NULL;
}

Iterator begin() {

return (Iterator(first));
}

Iterator end() {

return (Iterator(NULL));
}

void push_back(T *A_A)
{




        if( first == NULL)
        {
		(A_A->*A_LINK).setPrev(NULL);
		(A_A->*A_LINK).setNext(NULL);
                first = A_A;
        }
        else
        {

                (last->*A_LINK).setNext(A_A);
		(A_A->*A_LINK).setPrev(last);
                (A_A->*A_LINK).setNext(NULL);

        }

                last = A_A;

}

void remove(T *A_A)
{


        if(first == last)
        {
                        first = NULL;
                        last = NULL;



        }else if((A_A->*A_LINK).next == NULL){

                last = (A_A->*A_LINK).prev;
                (last->*A_LINK).next = NULL;
                (A_A->*A_LINK).prev = NULL;


        }
        else if((A_A->*A_LINK).prev == NULL) // if first
        {


                        first = (A_A->*A_LINK).next;
			(first->*A_LINK).prev = NULL;
                        (A_A->*A_LINK).next = NULL;
        }
        else{



                        ((A_A->*A_LINK).prev->*A_LINK).next  = (A_A->*A_LINK).next;
                        ((A_A->*A_LINK).next->*A_LINK).prev = (A_A->*A_LINK).prev;


        }

(A_A->*A_LINK).prev = NULL; (A_A->*A_LINK).next = NULL;
}


T* first;
T* last;

private:

List(const List&){}            // No copy construction allowed

List& operator=(const List&){} // No assignment allowed

};

}//ednd namespace

//#endif
