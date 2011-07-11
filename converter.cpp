/***
 *  
 *  This is some small code to convert data saved in the old way
 *  to the new modell. after you have compiled the main programm, 
 *  compile this by.
 *  
 *  g++ -O3 -c converter.cpp
 *  
 *  And link it against files.o and lines.o:
 *  
 *  g++ -o converter converter.o build/files.o build/lines.o 
 *  
 *  or write it as one command:
 *  
 *  g++ -O3 -c converter.cpp ; g++ -o converter converter.o build/files.o build/lines.o
 *  
**/

#include "src/lines.hpp"
#include "src/files.hpp"

#include <string>
#include <deque>

using namespace std;

int main(int argc, char **argv){
	deque<string> args;
	for(int i=0;i<argc;++i){
		args.push_back(string(argv[i]));
	}
	if(argc<3) return 1;
	string filename=args[1];
	LINES old_data=read_file(filename), conf_file_list, conf_file;
	deque<string> post_data;
	string new_file;
	for(LINES::iterator it=old_data.begin();it!=old_data.end();++it){
		try{
		post_data=cut_fields(*it);
		new_file=replace(post_data.at(0),".html","")+".conf";
		conf_file_list.push_back(new_file);
		conf_file.push_back("ID="+post_data.at(3));
		conf_file.push_back("heading="+post_data.at(2));
		conf_file.push_back("content_file="+post_data.at(0));
		conf_file.push_back("comment_file="+post_data.at(4));
		conf_file.push_back("display_date="+post_data.at(1));
		write_file(new_file,conf_file);
		conf_file.clear();
		}
		catch(...){
			continue;
		}
	}
	write_file(args[2],conf_file_list);
	return 0;
}
