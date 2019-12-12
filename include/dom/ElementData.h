#ifndef ELEMENT_DATA_H
#define ELEMENT_DATA_H

#include <map>
#include "HtmlNode.h"


class ElementData : public HtmlNode {
    private: 
        std::string _tag_name;
        std::map<std::string, std::string> _attributes;
    public:
        ElementData(std::string tag_name, std::map<std::string, std::string> attributes, std::vector<HtmlNode> children);
        std::string getTagName(){ return _tag_name; };
        std::map<std::string, std::string> getAttributes(){ return _attributes; };
};



#endif // ELEMENT_DATA_H