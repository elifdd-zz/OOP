#ifndef CS540_VALUE_HPP
#define CS540_VALUE_HPP



#include <typeinfo>
#include <string>



namespace cs540 {

class Value {
    public:
        virtual ~Value() {}
        const std::type_info &type() const { return typeid(*this); }
        virtual void print() const = 0;
        virtual const Value *addition(const Value *) const = 0;

	
	//virtual const Value *multiplication(const Value *) const;
    private:
};



class IntegerValue : public Value {
    public:
        IntegerValue(int v):i_val(v) {}
        int value() const { return i_val; };
        virtual void print() const;
        virtual const IntegerValue *addition(const Value *) const;
	virtual const IntegerValue *multiplication(const Value *) const;
	virtual const IntegerValue *negation() const;
    private:
	const int i_val;
	const IntegerValue *add_res;
};



class StringValue : public Value {
    public:
        StringValue(const std::string &v){ s_val = v; }
        std::string value() const { return s_val; }
        virtual void print() const;
        // Note the co-variance.
        virtual const StringValue *addition(const Value *) const;
    private:
	std::string s_val;
};


/**********************************************/

class ObjPtrValue : public Value {
    public:
        virtual void print() const;
        // Note the co-variance.  This function should cause
        // an error, since it doesn't have any meaning.
        virtual const ObjPtrValue *addition(const Value *) const;
	 std::string class_name;// = "A";
    private:
	const ObjPtrValue *optr;
	//std::string class_name;
};



}



#endif
