#ifndef __lines_hpp__
#define __lines_hpp__

#include <string>
#include <utility>
#include <deque>
#include <list>

using std::string;
using std::pair;
using std::deque;
using std::list;

typedef deque<string> LINES;

string clean_whitespace(string str);
string clean_whitespace_both_sides(string str);
pair<string,string> cut(string line,string divider="=");
deque<string> cut_words(string line);
deque<string> cut_fields(string line,string divider="\t");

string replace(string old_str,string old_phrase,string new_phrase);
string remove_double_spaces(string str);

LINES operator+(LINES L1, LINES L2);
LINES operator+=(LINES &L1, LINES L2);
LINES operator+=(LINES &L1,list<string> L2);

list<string> operator+=(list<string> &L1,LINES L2);
list<string> operator+=(list<string> &L1,deque<string> L2);
list<string> operator+=(list<string> &L1,list<string>  L2);

LINES push_string_to_front_of_every_line(LINES L, string str);

void replace(LINES &L, string old_phrase, string new_phrase);


template <typename T>
deque<T> list_to_deque(list<T> LIST){
	deque<T> DEQUE;
	DEQUE.resize(LIST.size());
	int i=0;
	for(typename list<T>::iterator it=LIST.begin();it!=LIST.end();++it){
		DEQUE[i]=*it;
		++i;
	}
	return DEQUE;
}

#endif
