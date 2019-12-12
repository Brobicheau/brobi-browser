
#include "HtmlNode.h"
#include <vector>

using namespace std;

HtmlNode::HtmlNode() {
    _children = vector<HtmlNode>();
}

HtmlNode::HtmlNode(vector<HtmlNode> children){
    _children = vector<HtmlNode>(children);
}

void HtmlNode::addChild(HtmlNode child){
    _children.push_back(child);
}