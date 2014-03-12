#ifndef CS540_META_INFO_HPP
#define CS540_META_INFO_HPP



#include <string>



namespace cs540 {



class MetaInfo {
    public:
        virtual ~MetaInfo() {}
        virtual std::string className() const = 0;
};

class MetaInfoRegisterer {
    public:
        MetaInfoRegisterer(const MetaInfo *);
};



}



#endif
