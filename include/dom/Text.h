#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <map>
#include "HtmlNode.h"


class Text : public HtmlNode {
    private: 
        std::string _data;
    public:
        Text(std::string data);
        std::string getText(){ return _data; }
};



#endif // TEXT_H