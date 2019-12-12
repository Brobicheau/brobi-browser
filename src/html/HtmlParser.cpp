#include "HtmlParser.h"
#include "HtmlNode.h"
#include "Text.h"
#include "ElementData.h"
#include <iostream>

HtmlParser::HtmlParser(std::string input) : _input(input), _pos(0) {} 

std::string HtmlParser::consume_while(bool (*test)(char)){
    std::string result;
    while (!eof() && test(next_char())){
        result.push_back(consume_char());
    } 
    return result;
}

bool is_whitespace(char c){
    return isspace(c) != 0;
}

bool is_tag_char(char c){
    return isalpha(c) || isdigit(c) || c == '!';
}

bool is_not_tag(char c){
    return c != '<';
}

bool is_not_closing_quote(char c){
    return c != '\'' && c != '\"';
}

void HtmlParser::consume_whitespace(){
    consume_while(is_whitespace);
}

std::string HtmlParser::parse_tag_name(){
    return consume_while(is_tag_char);
}

bool HtmlParser::starts_with(std::string s){
    return s.compare(_input.substr(_pos, _pos + s.size())) != 0;
}

char HtmlParser::next_char(){
    return _input[_pos];
}

bool HtmlParser::eof(){
    return _pos >= _input.size();
}

char HtmlParser::consume_char() {
    char current_char = _input[_pos];
    _pos = _pos + 1;
     return current_char;
}

HtmlNode HtmlParser::parse_node(){
    if(next_char() == '<'){
        return parse_element();
    }
    else{
        return parse_text();
    }
}

HtmlNode HtmlParser::parse_text(){
    std::string text = consume_while(is_not_tag);
    return Text(text);
}

HtmlNode HtmlParser::parse_element(){
    bool error;
    error = consume_char() != '<';
    if(error){
        std::cout << "Error parsing opening tag. Expected '<' found " << _input[_pos -1 ] << std::endl;
        exit(1);
    }
    std::string tag_name = parse_tag_name();

    std::map<std::string, std::string> attrs = parse_attributes();
    error = consume_char() != '>';
    if(error){
        std::cout << "Error parsing closing tag. Expected '>' found " << _input[_pos -1 ] << std::endl;
        exit(1);
    }
    std::vector<HtmlNode> children = parse_nodes();
    error = (consume_char() != '<' || consume_char() != '/' || parse_tag_name() != tag_name || consume_char() != '>');
    if(error){
        std::cout << "Error parsing tag at " << _input[_pos -1 ] << std::endl;
        exit(1);
    }
    return ElementData(tag_name, attrs, children);
}

HtmlParser::attribute HtmlParser::parse_attr(){
    bool error;
    std::string name = parse_tag_name();
    error = consume_char() != '=';
    if(error){
        std::cout << "Error parsing attribute" << std::endl;
        exit(1);
    }
    std::string value = parse_attr_value();
    HtmlParser::attribute attr;
    attr.attr_name = name;
    attr.value = value;
    return attr;
}

std::string HtmlParser::parse_attr_value(){
    consume_char();
    //TODO error check open quote
    std::string value = consume_while(is_not_closing_quote);
    consume_char();
    return value;
}

std::map<std::string, std::string> HtmlParser::parse_attributes() {
    std::map<std::string, std::string> attributes;
    consume_whitespace();
    while(next_char() != '>'){
        HtmlParser::attribute attr = parse_attr();
        attributes.insert(std::pair<std::string, std::string> (attr.attr_name, attr.value));
        consume_whitespace();
    }
    return attributes;
}

std::vector<HtmlNode> HtmlParser::parse_nodes(){
    std::vector<HtmlNode> nodes;
    consume_whitespace();
    while(!eof() && _input.substr(_pos, 2).compare("</") != 0){
        nodes.push_back(parse_node());
        consume_whitespace();
    }
    return nodes;
}

HtmlNode HtmlParser::parse(){
    std::vector<HtmlNode> nodes = parse_nodes();
    if(nodes.size() == 1){
        nodes.erase(nodes.begin());
    }
    else {
        HtmlNode(nodes);
    }
    return nodes;
}