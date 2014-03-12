#include<iostream>
#include<malloc.h>

using namespace std;

//namespace cs540{

///////////////////////////
template<typename T>
class Node
{

public:

 T *data;

  Node* next;


Node<T>() 
{
    data = NULL;
    next = NULL;
}

~Node<T>()
{
}


 /**
   * explicit paramater constructor
   */

Node<T>(T *dataIn, Node* nextIn) 
{
    data = dataIn;
    next = nextIn;
}

};

////////////////////////////////////
template <typename T>
class LinkedList
{

public:

Node<T>* first;
Node<T>* last;
	LinkedList()
	{
  		first = NULL;
		last  = NULL;
	}

~LinkedList()
        {
        }

 /**
   * inserts a node into a linked list
   * @param a pointer to an object of templated type
   * @return void
   */


void insertLastNode(T *recordIn)
{

    // initially set the next of this node to NULL
    Node<T> *newNode = new Node<T>(recordIn, NULL);

    // FIXME: Add rest of the code to insert the node

        if( first == NULL)
        {
                first = newNode;
		last  = newNode;
        }
        else
        {

		//Node<T> * temp = last;
		last->next = newNode;
		last = newNode;

           //     Node<T> * temp = first;
           //     while( temp->next != NULL)
            //    {
            //            temp = temp->next;
            //    }
             //   temp->next = newNode;
        }

}


 /**
   * removes the first node in a linked list
   * @param no parameters
   * @return void
   */
void removeFirstNode()
{
    // FIXME: Add rest of the code to remove the first node
    // FIXME: check for the boundary condition that the linked list may
    // be empty, in which case just print a warning message and continue.

        if ( first == NULL)
        {
                cout << "The List is empty, could not remove the first node." << endl;
        }
        else
        {
                //Node<T> *temp = first;
                first = first->next;
                //delete temp;
        }
}

};

////////////////////////////////////
template<typename T>
class CachingNew {

private:

	static LinkedList<T> *freelist;
public:


	//CachingNew():next(0) {}

	~CachingNew() {
	}


	void *operator new(size_t size) 
	{
		 if(size != sizeof(T)) {
			//should give a run-time error
			cout << "************* ERROR ***********" <<endl;
			//exit(1);
		}

		if (freelist->first == NULL) {
			T* tmp = (T *) malloc(size);
			//cout << "new at " << tmp << endl;
			return tmp;
		} else {
			T* tmp = (freelist->first)->data;
			//freelist->removeFirstNode();
			
			(freelist->first) = (freelist->first)->next;
			//cout << "using caching new at " << tmp << endl;
			return tmp;
		}
	}

	void operator delete(void * p) 	
	{
		T* tmp = (T *) p;
	
		//Node<T> *a_node = new Node<T>(tmp,NULL);
		freelist->insertLastNode(tmp);
		//Node<T> *a_n = new Node<T>(tmp,NULL);
		//a_n->next = freelist->first;
		//freelist->first->data = tmp;
		//cout << "delete " << p << endl;
	}


};

/////////////////////////////////////////////

template<typename T>
LinkedList<T>* CachingNew<T>::freelist = new LinkedList<T>();


