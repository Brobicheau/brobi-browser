#include <iostream>
#include "HtmlNode.h"
#include "HtmlParser.h"
#include "ElementData.h"

int main() {
    HtmlParser parser("<html><body><h1>Title</h1><div id=\"main\"class=\"test\"><p>Hello<em>world</em>!</p></div></body></html>");
    HtmlNode document = parser.parse();
    parser.consume_whitespace();
    return 0;
}