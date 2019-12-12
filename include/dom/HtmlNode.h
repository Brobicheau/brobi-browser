#ifndef HTML_NODE_H
#define HTML_NODE_H

#include <iostream>
#include <vector>


class HtmlNode {
    private: 
       std::vector<HtmlNode> _children; 
    public:

        HtmlNode();
        HtmlNode(std::vector<HtmlNode> children);

        void addChild(HtmlNode child);

        std::vector<HtmlNode> getChildren(){
            return _children;
        }
};


#endif // HTML_NODE_H