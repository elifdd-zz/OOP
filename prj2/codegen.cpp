#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "Emitter.hpp"
#include <sstream>
#include <vector>
using namespace std;



/*
 * These are the type codes:
 *   _135: void			...not used
 *   _126: int			..._143
 *   _139: const char *		..._139
 */

/*
 * Simple example to parse a file given as a single argument, walk
 * down the DOM, and emit a file named after the input file name.
 */

void print_element_names(xmlNode *, Emitter &, Emitter &);
void print_arguments(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em);

string base_name(const std::string &fn);
int argcount = 0;				//num of args
std::vector<string> params;		//arg list
int
main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./cg_xml input_xml_file\n");
        exit(1);
    }

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

   // int argcount = 0;

    /*
     * This initializes the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    // Probably will not actually need anything in the .hpp file.
    string bn = base_name(argv[1]) + "_meta";

    ofstream hpp_file((bn + ".hpp").c_str());
    assert(hpp_file.good());
    Emitter hpp_emitter(&hpp_file);
    hpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    hpp_emitter.emitLine("");

    ofstream cpp_file((bn + ".cpp").c_str());
    assert(cpp_file.good());
    Emitter cpp_emitter(&cpp_file);
    cpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    cpp_emitter.emitLine("");

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, hpp_emitter, cpp_emitter);
    cpp_emitter.emitLine("return 0;");
    cpp_emitter.emitLine(-1, "}");
    cpp_emitter.emitLine(-1, "};");
 
    cpp_emitter.emitLine("");
    cpp_emitter.emitLineF(-1,"CFactory_%s theFactory;", base_name(argv[1]).c_str() );
    cpp_emitter.emitLine("extern \"C\" {");
    cpp_emitter.emitLineF("CFactory *factory%s = &theFactory;", base_name(argv[1]).c_str() );
    cpp_emitter.emitLine("}");
    cpp_emitter.emitLine(-1, "}");


    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}

void
print_element_names(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em) {

    xmlNode *cur_node = NULL;
    xmlAttr * aptr;
	string cname;
//     int argcount = 0;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
		
            // Look for elements named "Class".
            if (!strcmp((const char *) cur_node->name, "Class")) {
                printf("Class Name: ");
                // The name of the class is in the attribute named
                // "name", so look through the attributes.
                aptr = cur_node->properties;
                while (aptr) {
                    if (!strcmp((const char *) aptr->name, "name")) {
                        // The value of the attribute is here.
                        string class_name((const char *) aptr->children->content);
                        printf("%s\n", class_name.c_str());
			cname.assign( class_name);
                        // Make $$ in the emitted text get replaced
                        // with the class name, for convenience.
                        cpp_em.setReplacement(class_name + "_meta");
                        cpp_em.emitLine("#include \"MetaInfo.hpp\"");
                        cpp_em.emitLine("#include <assert.h>");
                        cpp_em.emitLine("#include <iostream>");
                        cpp_em.emitLine("#include <string>");

	                cpp_em.emitLine("#include \"Reflection.cpp\"");
                        cpp_em.emitLine("#include \"Node.hpp\"");
                        cpp_em.emitLine("#include \"Value.hpp\"");
                        cpp_em.emitLineF("#include \"%s.hpp\"",class_name.c_str() );
			cpp_em.emitLine(" ");
                        cpp_em.emitLine("namespace cs540{"); //1
                        cpp_em.emitLine(" ");
                        cpp_em.emitLineF(1, "class CFactory_%s : public CFactory {", class_name.c_str()); //2
                        cpp_em.emitLine(" ");
                        cpp_em.emitLine(1, "public :");
                        cpp_em.emitLine(1, "virtual ObjPtrValue *create() const { ");//3
                        cpp_em.emitLine(1," ");
                        cpp_em.emitLineF("return new ObjPtrValue_tmpl<%s>(new %s);", class_name.c_str(), class_name.c_str());
                        cpp_em.emitLine(-1,"}");                //3
                        
                        cpp_em.emitLine("virtual Value *invoke(const ObjPtrValue *obj, const std::string &method_name, const std::vector<const Value *> &args) const {");//4
                        cpp_em.emitLine(1," ");

                        //cpp_em.emitLine("");
                        //cpp_em.emitLine("using namespace std;");
                        //cpp_em.emitLine("using namespace cs540;");
                        //cpp_em.emitLine("");
                        //cpp_em.emitLine("class $$ : public MetaInfo {");
                        //cpp_em.emitLine(1, "public:");
                        //cpp_em.emitLine(1, "virtual string className() const;");
                        //cpp_em.emitLine(-2, "};");
                        //cpp_em.emitLine("");


                    }
                    aptr = aptr->next;
                }
                printf("Fields\n");
            }

            // Look for elements named Method.
            if (!strcmp((const char *) cur_node->name, "Method")) {
                printf("Method Name: ");
		argcount = 0;
                // The return type is in an attribute.
		string ret;
		string mname;
		params.clear();		//args
		string retval;
                aptr = cur_node->properties;
                while (aptr) {
                    if (!strcmp((const char *) aptr->name, "returns")) {
                        printf("Returns: ");
                        printf("%s\n",aptr->children->content);

			cpp_em.emitLine(1," ");
                        if(!strcmp((const char *) aptr->children->content, "_139")){     //const char *
                                ret = "const char *ret;";
                                        cpp_em.emitLineF("%s", ret.c_str());
				retval = "return  new StringValue(ret); ";
                        }else if(!strcmp((const char *) aptr->children->content, "_143")){
                                ret = "int ret;";
                                        cpp_em.emitLineF("%s", ret.c_str());
					retval = "return new IntegerValue(ret); ";
                        }

                    }
                    // The name of the method is also an attribute.
                    if (!strcmp((const char *) aptr->name,"name")) {
                        printf("%s\n",aptr->children->content);
                        cpp_em.emitLineF("/* Method: %s */", aptr->children->content);
			cpp_em.emitLineF("if(method_name == \"%s\"){", aptr->children->content);
			mname.assign(((const char *)aptr->children->content));
                    }
                    aptr = aptr->next;
                }
                printf("Method Arguments\n");
		print_arguments(cur_node->children, hpp_em, cpp_em);
		cpp_em.emitLineF("%s *ap = (%s *)obj;", cname.c_str(), cname.c_str());

		string argpass;
		for (size_t i = 0; i < params.size(); i++)
		{
		   argpass += params[i]; //+ "->value(),";
		  if((i+1) != params.size())
			argpass += ", ";
		}
		string oo = "ret = ap->"+mname+"("+argpass+");";
		cpp_em.emitLineF("%s", oo.c_str());
		cpp_em.emitLineF("%s", retval.c_str()); 
		cpp_em.emitLine(-1,"}");		//end if foo

            }
        }
        print_element_names(cur_node->children, hpp_em, cpp_em);
	//cpp_em.emitLine("}");
    }
//	cpp_em.emitLine("}");
}


void
print_arguments(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em) {
    xmlNode *cur_node = NULL;
    xmlAttr * aptr;
    printf("Method Arguments\n");

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
	if(cur_node->type == XML_ELEMENT_NODE) {

	    // Method Arguments
            if (!strcmp((const char *) cur_node->name,"Argument")) {

		// The name and type are both attributes.
                aptr = cur_node->properties;
		while(aptr) {
		    if (!strcmp((const char *) aptr->name,"name")) {
                        printf("Name: ");
                        printf("%s\n",aptr->children->content);
                    }
		    if (!strcmp((const char *) aptr->name,"type")) {
                        printf("Type: ");
                        printf("%s\n",aptr->children->content);
			if(!strcmp((const char *) aptr->children->content, "_143")){
                           string s;                       //int to string
                           stringstream out;
                           out<<argcount;
                           s = out.str();
			   string argn = "ar"+s+"->value()";
                           params.push_back(argn);
                           string oret = "const IntegerValue *ar"+s+" = dynamic_cast<const IntegerValue *>(args.at(" + s +"));";
                           cpp_em.emitLineF("%s", oret.c_str());
			   //arg type check
			   string check1 = "if( ar"+s+" == 0){  std::cout<<\"Invalid function argument... \"<<endl; abort(); }";
			   cpp_em.emitLineF("%s", check1.c_str());
			   cpp_em.emitLine(" ");
			}
			else if(!strcmp((const char *) aptr->children->content, "_139")){
                           string s;                       //int to string
                           stringstream out;
                           out<<argcount;
                           s = out.str();
			   string argn = "(ar"+s+"->value()).c_str()";
			   params.push_back(argn);
                           string oret = "const StringValue *ar"+s+" = dynamic_cast<const StringValue *>(args.at(" + s +"));";
                           cpp_em.emitLineF("%s", oret.c_str());
		           ///arg type check
			   string check1 = "if( ar"+s+" == 0){  std::cout<<\"Invalid function argument... \"<<endl; abort(); }";
                           cpp_em.emitLineF("%s", check1.c_str());
                           cpp_em.emitLine(" ");

                        }
			argcount++;
                    }
                    aptr = aptr->next;
		}
	    }
	}
    }
}



string
base_name(const std::string &fn) {
    string base = fn;
    // Search for . to find the file extension.
    string::size_type pos = base.find('.');
    if (pos == string::npos) {
        fprintf(stderr, "File name %s not in right form.\n", base.c_str());
        exit(1);
    }
    // Truncate the file extension.
    base.erase(pos);
    cerr << "base: " << base << endl;
    return base;
}
