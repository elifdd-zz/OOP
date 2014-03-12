#ifndef REFLECTION_HPP
#define REFLECTION_HPP



#include <string>
#include <vector>



namespace cs540 {



class ObjPtrValue;
class Value;



class Reflection {
    public:
        static void Load(const std::string &);
        static const ObjPtrValue *New(const std::string &type_name);
        static const Value *Invoke(const ObjPtrValue *, const std::string &method_name, const std::vector<const Value *> &args);
        // Other things can go here of course.
        // ...
   private: 
	//static void *dop;

};



}



#endif
