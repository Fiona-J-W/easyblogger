
#ifndef __files_hpp__
#define __files_hpp__

#include <string>
#include <deque>
#include "lines.hpp"
#include <list>

using std::string;
using std::deque;
using std::list;

LINES read_file(string filename);
list<string> read_file_to_list(string filename);
LINES read_config_file(string filename);


int write_file(string filename, LINES data);
int write_file(string filename, list<string> data);
int write_file(string filename, string data);

int insert_into_file(string filename, string line,int pos=0);

int insert_to_begin_of_file(string filename, string line);

#endif 
