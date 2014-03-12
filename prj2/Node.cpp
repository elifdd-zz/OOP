#include <dlfcn.h>
#include "Node.hpp"
#include <assert.h>
#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <stdio.h>
#include "Value.hpp"
#include "Token.hpp"
#include "Reflection.hpp"
#include <stdlib.h>

using namespace std;



namespace cs540 {

//dl_lookup
///////////////////////////////////
void *
dl_lookup(void *h, const char *sym) {
    dlerror(); // Clear old error.

    void *vp = dlsym(h, sym);
    const char *ec = dlerror(); // Get error if any.
    if (ec != 0) {
        printf("dlsym error: %s.\n", ec);
        assert(false);
    }
    return vp;
}
///////////////////////////////////

namespace {
    
}

//class name to object name
map<const std::string, std::string >clobmap;

//class name to factory map
map<const std::string, const CFactory **>classmap;

//var_name to value* map
map<const std::string, const Value *>varmap;

/****************************************************************************/

// Actual type: const IdentToken *id
// The node is just an expression.
AssignmentNode::AssignmentNode(const Token *id, const Node *e) {
    // FILL IN.
	//cout<<"AssignmentNode - AssignmentNode() "<<endl;
	//const IdentToken *idtok = (const IdentToken *)id;
	const IdentToken *idtok = dynamic_cast<const IdentToken *>(id);
	if(idtok == 0){
		cout<<"AssignmentNode - AssignmentNode() IdentToken cast error.."<<endl;
		abort();
	}
	vname = idtok->ident();
	//cout<<"vname : "<<vname<<endl;
	exp = e;

	//const Value *
	vptr = exp->execute();
        assert(vptr != 0);
        varmap[vname] = vptr;

}

const Value *
AssignmentNode::execute() const {

    // FILL IN.
    //assert(false);
	
	//cout<<"AssignmentNode - exec() "<<endl;
	//varmap[vname] = exp->execute();
//	const Value *vptr = exp->execute();
//	assert(vptr != 0);
//	varmap[vname] = vptr; 
	//exp->execute()->print();

    return vptr;//exp->execute();
}

/****************************************************************************/

// Actual type: const IdentToken *t
VarNode::VarNode(const Token *t) {
	//cout<<"VarNode - VarNode() "<<endl;
        //const IdentToken *idtok = (const IdentToken *)t;
	const IdentToken *idtok = dynamic_cast<const IdentToken *>(t);
	assert(idtok != 0);
        vname = idtok->ident();
        //cout<<"vname : "<<vname<<endl;
}

const Value *
VarNode::execute() const {

	//cout<<"VarNode - exec() "<<endl;
	const Value *vptr = varmap.find(vname)->second;
	//assert(vptr != 0);
	if(vptr == 0){
		cout<<"VarNode - exec() : variable value not found..."<<endl;
		abort();
	}
	return  vptr;
}


/********************************************************************************/


// Actual type: const IntegerToken *t
IntegerNode::IntegerNode(const Token *t) {

	//const IntegerToken *it = (const IntegerToken *)t;
	const IntegerToken *it = dynamic_cast<const IntegerToken *>(t);
	assert(it != 0);
	//cout <<"IntegerNode - IntegerNode() : "<<it->value().value()<<endl;
	iptr = new IntegerValue(it->value());
}

const Value *
IntegerNode::execute() const {
	//cout<<"IntegerNode - exec() : "<<iptr->value()<<endl;
	return iptr;
}


/********************************************************************************/


// Actual type: const StringToken *t
StringNode::StringNode(const Token *t) {
	//const StringToken *st = (const StringToken *)t;
	const StringToken *st = dynamic_cast<const StringToken *>(t);
	assert(st != 0);
	//cout <<"StringNode - StringNode() :"<<endl;
	const StringValue sval = st->value();
	std::string ss = sval.value();
	//cout<<"string value :: "<<ss<<endl;

	sptr = new StringValue(ss);
}

const Value *
StringNode::execute() const {
    //assert(false);
	//cout <<"StringNode - exec() : "<<sptr->value()<<endl;
    	return sptr;
}

/********************************************************************************/

AdditionNode::AdditionNode(const Node *l, const Node *r){

	lchild = l;
	rchild = r;
}
const Value *
AdditionNode::execute() const {
//    assert(false);
	 //cout<<"AdditionNode - exec() : "<<endl;
	const Value *l_cval = lchild->execute();
	const Value *r_cval = rchild->execute();
	//(r_cval->addition(l_cval))->print();	
	return r_cval->addition(l_cval);
}


/********************************************************************************/

MultiplicationNode::MultiplicationNode(const Node *l, const Node *r){

        lchild = l;
        rchild = r;
}

//no multiplication for strings so IntegerValue is used
const Value *
MultiplicationNode::execute() const {
//    assert(false);
        //cout<<"MultiplicationNode - exec() : "<<endl;
        const IntegerValue *l_cval = dynamic_cast<const IntegerValue *>(lchild->execute());
        const IntegerValue *r_cval = dynamic_cast<const IntegerValue *>(rchild->execute());
	if((l_cval ==0) || (r_cval==0)){
		cout<<"MultiplicationNode - execute() : no multiplication for non-integers..."<<endl;
		abort();
	}

        //(r_cval->multiplication(l_cval))->print();    
        return r_cval->multiplication(l_cval);
}


/********************************************************************************/

//no multiplication for strings so IntegerValue is used
NegationNode::NegationNode(const Node *e){

	nnode = e;
}


const Value *
NegationNode::execute() const {

         //cout<<"NegationNode - exec() : "<<endl;
        const IntegerValue *n_val = dynamic_cast<const IntegerValue *>(nnode->execute());
	if(n_val ==0){
		cout<<"NegationNode - execute() : no negation for strings..."<<endl;
		abort();
	}
        //(n_val->negation())->print();    
        return n_val->negation();
}
/********************************************************************************/
// Actual type: const IdentToken *t
NewNode::NewNode(const Token *t) {

	const IdentToken *idtok = (const IdentToken *)t;
	cname = idtok->ident();
	//cout<<"NewNode - NewNode() : "<<endl;
	//cout<<"**** Object class :: "<<cname<<endl;
	so_name = "class_"+cname+".so";
	//cout<<"**** Object .so :: "<<so_name<<endl;

}
////////////////////////////////////FACTORY!!!!!!!!!!!!!!!!!!!!!
const Value *
NewNode::execute() const {
	//cout<<"NewNode - exec() : "<<endl;
	//load the .so file

	void *vp =  dlopen(("./" + so_name ).c_str(), RTLD_LAZY|RTLD_LOCAL);//GLOBAL);
	if(vp == 0){
		cerr << dlerror() << endl; 
		cout<<"Loading .so file - "<<so_name<<" failed."<<endl;
		abort();
	}//else
	//	 cout<<"Loading .so file - "<<so_name<<" done."<<endl;

/***/
		std::string ff = "factory" + cname;
	
/***/
	//call to dl_look up
	const CFactory **cf = (const CFactory **)dl_lookup(vp,ff.c_str());// "factory");

	classmap[cname] = cf;

	//map the class name to the obj name
	//clobmap[cname] = cf;

	ObjPtrValue *ref = (*cf)->create();
	if(ref == 0){
                cout<<"NewNode - exec() : no ObjValurPtr found !!!"<<endl;
                abort();
        }
	ref->class_name = cname;
	//clobmap[cname] = ref;

    	return ref;
}


/********************************************************************************/
// Node is some epression.
PrintNode::PrintNode(const Node *n) { 
	//cout<<"PrintNode - PrintNode() "<<endl;
	nptr = n;
}

const Value *
PrintNode::execute() const {
    //assert(false);
	//cout<<"PrintNode - exec() "<<endl;
	nptr->execute()->print();
	return 0;//nptr->execute()->print();
    //return 0;
}


/********************************************************************************/

// Actual types: const IdentToken *obj, const IdentToken *method
// Each node in the deque is some expression.
InvocationNode::InvocationNode(const Token *obj, const Token *method, 
 const deque<const Node *> *al) {

	//cout<<"InvocationNode - InvocationNode() "<<endl;
	const IdentToken *o_it = dynamic_cast<const IdentToken *>(obj);
	assert(o_it != 0);

	oname = o_it->ident();
	//cout<<"InvocationNode - InvocationNode() :  object name "<<oname<<endl;
	const IdentToken *m_it = dynamic_cast<const IdentToken *>(method);
	 assert(m_it != 0);
        
	mname = m_it->ident();  

	//cout<<"InvocationNode - InvocationNode() :  method name "<<mname<<endl;
	
	for(size_t i =0; i<(al->size()); i++){
		//cout<<"function args : "<<i<<" : ";
		const Node *e = al->at(i); //  (al[i]->execute())->print();///<<endl;
		//e->execute()->print();
		const Value *pnt = e->execute();
		params.push_back(pnt);
	//	params[i]->print();
	}
}

const Value *
InvocationNode::execute() const {
	//cout<<"InvocationNode - exec() "<<endl;

	const ObjPtrValue *iobj = (ObjPtrValue *)varmap.find(oname)->second;
	if(iobj ==0){
                cout<<"InvocationNode - exec() : no ObjValuePtr for this variable..."<<endl;
                abort();
        }

	
	//map object name and class name
	clobmap[oname] = iobj->class_name;
	std::string cname = iobj->class_name;

	//cout<<"!!!!!!!!!!!!!!!!!!!!!!!!     "<<cname<<endl;

	const CFactory **fptr = classmap.find(cname)->second;
	if(fptr ==0){
		cout<<"InvocationNode - exec() : maping class_name and class_factory failed..."<<endl;
		abort();
	}
	//Reflection::Invoke(iobj, mname, params);
	
	const Value *vptr = (*fptr)->invoke(iobj, mname, params);
	if(vptr ==0){
                cout<<"InvocationNode - exec() : invoke return value failed..."<<endl;
                abort();
        }

	
    return vptr;
}



}

