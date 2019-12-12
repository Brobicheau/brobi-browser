#include "ElementData.h"
#include "HtmlNode.h"

ElementData::ElementData(std::string tag_name, std::map<std::string, std::string> attributes, std::vector<HtmlNode> children) : 
    HtmlNode (children), _tag_name(tag_name), _attributes(attributes) {}