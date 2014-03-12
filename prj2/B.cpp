#include "B.hpp"
#include <iostream>

using namespace std;

//B::B() {
//    cout << "new B()" << endl;
//}



const char *
B::foo(int a, const char *b) {
    cout << "B::foo() called." << endl;
    return "Hello";
}

int
B::goo(int a, const char *b, int d, int c) {
    cout << "B::goo() called." << endl;

	int ret = a + d + c;
    //return 1234;
	return ret;
}
