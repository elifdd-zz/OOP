#include "Value.hpp"
#include <typeinfo>
#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;



namespace cs540 {


void
IntegerValue::print() const {
//    assert(false);
	//cout<<"IntegerValue - print() : "<<i_val<<endl;
	cout<<i_val<<endl;

}

/**********************************************/
const IntegerValue *
IntegerValue::addition(const Value *aval) const {
	//const IntegerValue *add_val = (const IntegerValue *)aval;
	const IntegerValue *add_val = dynamic_cast<const IntegerValue *>(aval);
        if(add_val == 0){
                cout<<"IntegerValue - addition() : integer - invalid type addition..."<<endl;
                abort();
        }

	int res = i_val + add_val->value();
	const IntegerValue * add_res = new IntegerValue(res);
	return add_res;
}

/**********************************************/


const IntegerValue *
IntegerValue::multiplication(const Value *aval) const {
       // const IntegerValue *add_val = (const IntegerValue *)aval;
	const IntegerValue *add_val = dynamic_cast<const IntegerValue *>(aval);
        if(add_val == 0){
                cout<<"IntegerValue - multiplication() : integer - invalid type multiplication..."<<endl;
                abort();
        }

        int res = i_val * add_val->value();
        const IntegerValue * add_res = new IntegerValue(res);
        return add_res;
}
/**********************************************/

const IntegerValue *
IntegerValue::negation() const {
        int res = i_val - (i_val*2);
        const IntegerValue * add_res = new IntegerValue(res);
        return add_res;
}
/**********************************************/

void
StringValue::print() const {
	//cout<<"StringValue - print() : "<<s_val<<endl;
	cout<<s_val<<endl;
//    assert(false);
}

/**********************************************/
const StringValue *
StringValue::addition(const Value *aval) const {
	//const StringValue *add_val = (const StringValue *)aval;
	const StringValue *add_val = dynamic_cast<const StringValue *>(aval);
	if(add_val == 0){
		cout<<"StringValue - addition() : string - invalid type addition..."<<endl;
		abort();
	}
		
	std::string res =  add_val->value(); //s_val;
	res.append(s_val);
	
	const StringValue *add_res = new StringValue(res);
	return add_res;

//    assert(false);


}

/**********************************************/
void
ObjPtrValue::print() const {
	cout<<"ObjPtrValue - print() : printing the object address ... ";
	cout<<optr<<endl;
    //assert(false);
}

const ObjPtrValue *
ObjPtrValue::addition(const Value *) const {
	cout<<"ObjPtrValue - addition() : addition on objects not allowed ..."<<endl;
    assert(false);
	//return 0;
}



}
