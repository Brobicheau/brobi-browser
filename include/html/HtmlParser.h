#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <string>
#include <map>
#include "HtmlNode.h"


class HtmlParser {
    private: 
        std::string _input;
        size_t _pos;
    public:
        struct attribute {
            std::string attr_name;
            std::string value;
        };
        HtmlParser(std::string);
        std::string getInput(){ return _input; }
        int getPos(){ return _pos; } 
        void consume_whitespace();
        bool eof();        
        bool starts_with(std::string s);
        char next_char();
        char consume_char();
        std::string consume_while(bool (*test)(char));
        std::string parse_tag_name();
        HtmlNode parse_node();
        HtmlNode parse_text();
        HtmlNode parse_element();
        HtmlNode parse();
        HtmlParser::attribute parse_attr();
        std::string parse_attr_value();
        std::map<std::string, std::string> parse_attributes();
        std::vector<HtmlNode> parse_nodes();

};



#endif // HTML_PARSER_H