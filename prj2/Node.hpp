#ifndef CS540_NODE_HPP
#define CS540_NODE_HPP


#include <string>
#include <deque>
#include "Value.hpp"
#include <vector>


namespace cs540 {

class IntegerToken;
class IdentToken;
class StringToken;
class Token;

//factoryclass
/*********************************************/
class CFactory{
    public:
	virtual ~CFactory() {}
        virtual ObjPtrValue *create() const = 0;
	//virtual Value *invoke(const ObjPtrValue *opv, 
	//		const std::string &metname, 
	//		const std::vector<Value *> &args) const = 0;

	virtual Value *invoke(const ObjPtrValue *obj, const std::string &method_name, const std::vector<const Value *> &args) const = 0;
};

/**********************************************/

class Node {
    public:
        virtual ~Node() {}
        virtual const Value *execute() const = 0;
};

class VoidNode : public Node {
    public:
        virtual const Value *execute() const { return 0; }
};

/**********************************************/

class AssignmentNode : public Node {
    public:
        AssignmentNode(const Token *, const Node *);
        virtual const Value *execute() const;
	//~AssignmentNode() { delete exp; }
    private:
	const Node *exp;
	std::string vname;
	const Value *vptr;
};

/**********************************************/

class VarNode : public Node {
    public:
        VarNode(const Token *);
        virtual const Value *execute() const;
    private:
	std::string vname;
};


/**********************************************/

class IntegerNode : public Node {
    public:
        IntegerNode(const Token *);
        virtual const Value *execute() const;
	//~IntegerNode(){ delete iptr; }
    private:
	const IntegerValue *iptr;

};

/**********************************************/


class StringNode : public Node {
    public:
        StringNode(const Token *);
        virtual const Value *execute() const;
	~StringNode(){ delete sptr; }
    private:
	const StringValue *sptr;
};

/**********************************************/
class AdditionNode : public Node {
    public:
        AdditionNode(const Node *l, const Node *r);// {}
        virtual const Value *execute() const;
	~AdditionNode(){ delete lchild; delete rchild; delete result; }
    private:
	const Node *lchild;
	const Node *rchild;
	const Value *result;
};


/**********************************************/



class MultiplicationNode : public Node {
    public:
        MultiplicationNode(const Node *l, const Node *r); //{}
        virtual const Value *execute() const;// { return 0; }
	~MultiplicationNode(){ delete lchild; delete rchild; delete result; }
    private:
	const Node *lchild;
        const Node *rchild;
        const Value *result;
};


/**********************************************/

class NegationNode : public Node {
    public:
        NegationNode(const Node *e);// { nnode = e; }
        virtual const Value *execute() const;// { return 0; }
	~NegationNode(){ delete nnode; }
    private:
	const Node *nnode;
};


/**********************************************/

class NewNode : public Node {
    public:
        NewNode(const Token *);
        virtual const Value *execute() const;
    private:
	const Node *obj;
	std::string cname;
	std::string so_name;
	const CFactory *cf;
};


/**********************************************/

class PrintNode : public Node {
    public:
        PrintNode(const Node *n);
        virtual const Value *execute() const;
	 ~PrintNode(){ delete nptr; }
    private:
	const Node* nptr;
};

/**********************************************/

class ArgList;

class InvocationNode : public Node {
    public:
        InvocationNode(const Token *, const Token *, const std::deque<const Node *> *);
        virtual const Value *execute() const;
    private:
	std::string oname;
	std::string mname;
	std::vector<const Value *> params;
	//ObjPtrValue *iobj;
};



}



#endif
