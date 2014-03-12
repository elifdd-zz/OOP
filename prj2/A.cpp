#include "A.hpp"
#include <iostream>

using namespace std;

//A::A() {
//    cout << "new A()" << endl;
//}



//void
int
A::foo(int a , const char *b) {
    cout << "A::foo() called." << endl;
    cout<<"arg1 : "<<a<<endl;
    cout<<"arg2 : "<<b<<endl;
    return 1234;
}


const char *
A::goo(int a) {
    cout << "A::goo() called." << endl;
    cout<<"arg1 : "<<a<<endl;
    return "hi yibo!";
}
