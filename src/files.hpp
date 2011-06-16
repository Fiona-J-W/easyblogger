
#ifndef __files_hpp__
#define __files_hpp__

#include <string>
#include <deque>

using std::string;
using std::deque;

typedef deque<string> LINES;

LINES read_file(string filename);
LINES read_config_file(string filename);

int write_file(string filename, LINES data);
int write_file(string filename, string data);

int insert_into_file(string filename, string line,int pos=0);

int insert_to_begin_of_file(string filename, string line);

#endif 
