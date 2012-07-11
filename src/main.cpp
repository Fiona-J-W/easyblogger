//      easyblogger V 2.0
//      
//      Copyright 2011 Florian Weber <florian.weber@sfz-bw.de>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU Affero General Public License as published by
//      the Free Software Foundation; either version 3 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU Affero General Public License for more details.
//      
//      You should have received a copy of the GNU Affero General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <getopt.h>
#include <stdexcept>

#include "settings.hpp"
#include "help.hpp"
#include "actions.hpp"
#include "config.hpp"

using namespace std;

char parse_command(string input){
	static const map<string,char> arguments={
		pair<string,char>("create",'c'),
		pair<string,char>("configure",'C'),
		pair<string,char>("import",'i'),
		pair<string,char>("edit",'e'),
		pair<string,char>("edit-comment",'E'),
		pair<string,char>("search",'s'),
		pair<string,char>("html-search",'S'),
		pair<string,char>("list-entries",'l'),
		pair<string,char>("help",'h'),
		pair<string,char>("comment",'o'), //'o' for "opinion" as 'c' is already in use
		pair<string,char>("about",'a')
	};
	int pos=0;
	while(input[pos]=='-'){
		++pos;
	}
	input.erase(0,pos);
	if(input.size()==0){
		throw runtime_error("invalid argument");
	}
	else if(input.size()==1){
		return input[0];
	}
	map<string,char>::const_iterator it=arguments.find(input);
	if(it==arguments.end()){
		throw runtime_error("invalid argument");
	}
	return (*it).second;
}

int main(int argc, char **argv){
	settings S;
	//if there are no parameters: quit
	if(argc==1){
		print_help();
		return 1;
	}
	//put parameters into a std::vector
	vector<string> args;
	args.resize(argc-1);
	for(int i=1;i<argc;++i){
		args[i-1]=string(argv[i]);
	}
	//choose which blog to take:
	if(args[0][0]=='-'){
		S=get_blog_by_name();
	}
	else{
		try{
			S=get_blog_by_name(args[0]);
		}
		catch(std::logic_error &e){
			if(e.what()==string("does not exist")){
				cerr<<"blog does not exist"<<endl;
				return 1;
			}
			else throw e;
		}
		args.erase(args.begin());
		//again: if there are no parameters: quit
		if(args.size()==0){
			print_help();
			return 1;
		}
	}
	//get identifier for command:
	char cmd;
	try{
		cmd=parse_command(args[0]);
	}
	catch(runtime_error &e){
		cerr<<"Error: "<<e.what()<<endl;
		print_help();
		return 1;
	}
	//make args just contain the left parameters:
	args.erase(args.begin());
	int n_parameters=args.size();
	//choose command to execute:
	try{
		switch(cmd){
			case 'h': print_help(); return 0; break;
			case 'c': return create_all(S); break;
			case 'i': return import(S,args.at(0)); break;
			case 'e': return edit(S,ID(args.at(0))); break;
			case 'E': return edit_comment(S,ID(args.at(0))); break;
			case 's': return print_search(S,args.at(0)); break;
			case 'S': return print_html_search(S,args.at(0)); break;
			case 'l': return list_entries(S); break;
			case 'o': return comment(S,ID(args.at(0)),args.at(1)); break;
			case 'C': 
				if(n_parameters==0){
					return configure_blog(S);
				}
				else{
					return configure_post(S,ID(args[0]));
				}
				break;
				
			default:
				cerr<<"Error: invalid arguments"<<endl;
				print_help();
				return 1;
		}
	}
	catch(out_of_range &e){
		//this might not allways be true:
		cerr<<"Error: invalid number of arguments"<<endl;
		return 1;
	}
	//you should never get here (except an exception is thrown)
}
