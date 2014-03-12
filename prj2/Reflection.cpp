#include "Reflection.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include "Value.hpp"
#include <assert.h>

using namespace std;



class AA {
    public:
        int f() { cout<<"@@@@@@@@@@@@@@@@@@@@@ heyyyyyyyyy"<<endl; return 1234; }

};

namespace cs540 {


template <typename T>
class ObjPtrValue_tmpl : public ObjPtrValue {
    public:
        ObjPtrValue_tmpl(T *t) : m_obj(t) {}
        virtual void print() const;
    private:
        T *const m_obj;
	///
	std::string clname;
};

template <typename T>
void
ObjPtrValue_tmpl<T>::print() const {
//	cout<<"ObjPtrValue_tmpl - print() : printing the object address ... ";
    cout << m_obj << endl;
}



void
Reflection::Load(const string &so_file) {
   // void *
	void *h =  dlopen(("./" + so_file).c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if (h == 0) {
     //if(Reflection::dop == 0 ){
        cerr << dlerror() << endl;
	cout<<"Reflection - Load() - failed... "<<endl;
        abort();
    }
	cout<<"Reflection - Load() - load successful... "<<endl;


///////////////
///////////
}

const ObjPtrValue *
Reflection::New(const string &type_name) {
    cout << "Instantiation of type " << type_name << " requested." << endl;
    cout << "CHANGE THIS: " << " currently hard-code to type AA." << endl;
    return new ObjPtrValue_tmpl<AA>(new AA);
}

const Value *
Reflection::Invoke(const ObjPtrValue *obj, const string &method_name,
 const vector<const Value *> &args) {
    printf("Invoke:\n");
    cout << typeid(*obj).name() << endl;
    cout << method_name << endl;
    for (size_t i = 0; i < args.size(); i++) {
        args[i]->print();
    }

    return 0;
}



}
