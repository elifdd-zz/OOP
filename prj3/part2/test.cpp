#include "List.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cs540;

void doit();


class A {
        friend void doit();
    private:
        A(int i_) : i(i_) {}
        A(const A &);
        A &operator=(const A &);
        int i;
    private:
        Link<A> link1;
        Link<A> link2;
    public:
        //public: typedef List<A> list1_t;
        //public: typedef List<A> list2_t;


	public: typedef List<A, &A::link1> list1_t;
        public: typedef List<A, &A::link2> list2_t;

};

int
main() {
    doit();
}

void
doit() {

    A::list1_t list1_1;
    A::list1_t list1_2;
    A::list2_t list2;

    A *ap1 = new A(1);
    A *ap2 = new A(2);
    A *ap3 = new A(3);
    A *ap4 = new A(4);

    list1_1.push_back(ap1);
    list1_1.push_back(ap2);
    list1_1.push_back(ap3);
    list1_1.push_back(ap4);
    A::list1_t::Iterator it;
    list1_1.remove(ap1);

   

 // Should print nothing.
    printf("Nothing.\n");
    for (A::list1_t::Iterator it = list1_2.begin(); !(it == list1_2.end()); ++it) 
	{
	cout << (*it)->i << endl;
 //       cout << (*it)->i << endl;
//	cout << (it.currentLink)->i << endl;
    }
    list1_2.push_back(ap1);

    // Should print 2, 3, 4.
    printf("Should print 2, 3, 4.\n");
    for (A::list1_t::Iterator it = list1_1.begin(); !(it == list1_1.end()); ++it) {
        cout << (*it)->i << endl;
    }

    // Should print 1.
    printf("Should print 1.\n");
    for (A::list1_t::Iterator it = list1_2.begin(); !(it == list1_2.end()); ++it) {
        cout << (*it)->i << endl;
    }

    list2.push_back(ap3);
    list2.push_back(ap4);

    // Should print 3, 4.
    printf("Should print 3, 4.\n");
    for (A::list2_t::Iterator it = list2.begin(); !(it == list2.end()); ++it) {
        cout << (*it)->i << endl;
    }

    delete ap1;
    delete ap2;
    delete ap3;
    delete ap4;
}

