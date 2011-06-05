#ifndef __lines_hpp__
#define __lines_hpp__

#include <string>
#include <utility>
#include <deque>

using std::string;
using std::pair;
using std::deque;

typedef deque<string> LINES;

string clean_whitespace(string str);
pair<string,string> cut(string line,string divider="=");
deque<string> cut_words(string line);
deque<string> cut_fields(string line,string divider="\t");

string replace(string old_str,string old_phrase,string new_phrase);
string remove_double_spaces(string str);

#endif
