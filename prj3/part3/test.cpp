
#include "Array.hpp"
//#include <string>

using namespace cs540;
using namespace std;
int main(){

// Define a 2X3X4 array of integers.  Elements are uninitialized.
size_t dims[3] = {3, 4, 5};

Array<3, int> a(dims);
//a[0];
// Range-checked indexing.
a[0][0][0] = 1234;
cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<<a[0][0][0]<<endl;
a[1][1][1] = a[0][0][0];
cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<<a[1][1][1]<<endl;

a[0][2][3] = 5678; // Set the element in the first plane, 3rd row, and 4th column.
cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<<a[0][2][3]<<endl;

try{
	a[0][5][0] = 1; // Out of range, throws.
}catch(OutOfRange e){
	cerr<<e.what()<<endl;
}

try{
  a[0][0][6] = 1; // Out of range, throws.
}catch(OutOfRange e){
  cerr<<e.what()<<endl;
}

try{
  a[4][0][0] = 1; // Out of range, throws.
}catch(OutOfRange e){
  cerr<<e.what()<<endl;
}

a = a; // Self-assignment must be a no-op.

const Array<3, int> &const_ref(a);

a[1][3][3] =1;
int i = const_ref[1][3][3]; // Okay.

cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<<i<<endl;
//const_ref[0][0][0] = 1; // Syntax error.

Array<3, float> c1(dims);
Array<3, float> &c2(c1);

//c1[1][1][1] = 99999;
//cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<<c1[1][1][1]<<endl;
return 0;
}
