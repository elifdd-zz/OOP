#include "CachingNew.hpp"
#include <ctime>
using namespace std;
//using namespace cs540;

class A : public CachingNew<A> {
	public:
	int f;
	A(){}
};
class B : public A {
	public:
	int k, j;
	B(){}
};

class C{
	public:
	int ff;	
};

int main()
{

 A *a = new A; // Use free list if not empty.
//      a->f = 3;
//      cout<<a->f<<endl;
        delete a; // Put memory block on free list.

//cached time
clock_t start_cached = clock();
for(int i=0; i<10000000; i++)
{
	A *a = new A; // Use free list if not empty.
 	delete a; // Put memory block on free list.

// 	B *b = new B; // Should give run-time error.
//	b->k = 8;
//	 cout<<b->k<<endl;
}
cout<<"cached time : "<< ( ( std::clock() - start_cached ) / (double)CLOCKS_PER_SEC ) <<'\n';

//non cached time
clock_t start = clock();
for(int i=0; i<10000000; i++)
{
	C  *c = new C;
	delete c;
}	

cout<<"non-cached time: "<< ( ( std::clock() - start ) / (double)CLOCKS_PER_SEC ) <<'\n';
}
