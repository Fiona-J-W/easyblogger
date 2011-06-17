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

#include "settings.hpp"
#include "help.hpp"
#include "sites.hpp"
#include "config.hpp"

using namespace std;

int main(int argc, char **argv){
	///bring parameters into a reasonable form:
	vector<string> args;
	args.resize(argc);
	for(int i=0;i<argc;++i){
		args[i]=(string(argv[i]));
	}
	settings S;
	if(argc==1){
		print_help();
		return 0;
	}
	else if(argc==2){
		if(args[1]=="-h"||args[1]=="--help"){
			print_help();
			return 0;
		}
		else if(args[1]=="--about"){
			print_info();
			return 0;
		}
		else if(args[1]=="--create"||args[1]=="-c"){
			S=get_blog_by_name();
			create_all(S);
		}
		else if(args[1]=="--list-entries"||args[1]=="-l"){
			S=get_blog_by_name();
			return list_entries(S);
		}
		else if(args[1]=="--configure"){
			S=get_blog_by_name();
			return configure_blog(S);
		}
		else{
			print_help();
			return 1;
		}
	}
	else if(argc==3){
		if(args[2]=="--create"||args[2]=="-c"){
			S=get_blog_by_name(args[1]);
			return create_all(S);
		}
		else if(args[1]=="--import"||args[1]=="-i"){
			S=get_blog_by_name();
			return import(S,args[2]);
		}
		else if(args[1]=="--edit"||args[1]=="-e"){
			S=get_blog_by_name();
			return edit(S,ID(args[2]));
		}
		else if(args[1]=="--edit-comment"||args[1]=="-E"){
			S=get_blog_by_name();
			return edit_comment(S,ID(args[2]));
		}
		else if(args[2]=="--configure"){
			S=get_blog_by_name(args[1]);
			return configure_blog(S,args[1]);
		}
		else if(args[2]=="--list-entries"||args[2]=="-l"){
			S=get_blog_by_name(args[1]);
			return list_entries(S);
		}
		else{
			print_help();
			return 1;
		}
	}
	else if(argc==4){
		if(args[2]=="--import"||args[2]=="-i"){
			S=get_blog_by_name(args[1]);
			return import(S,args[3]);
		}
		else if(args[2]=="--edit"||args[2]=="-e"){
			S=get_blog_by_name(args[1]);
			return edit(S,ID(args[3]));
		}
		else if(args[2]=="--edit-comment"||args[2]=="-E"){
			S=get_blog_by_name(args[1]);
			return edit_comment(S,ID(args[3]));
		}
		else if(args[1]=="--comment"){
			S=get_blog_by_name();
			comment(S,ID(args[2]),args[3]);
		}
		else{
			print_help();
			return 1;
		}
	}
	else if(argc==5){
		if(args[2]=="--comment"){
			S=get_blog_by_name(args[1]);
			comment(S,ID(args[3]),args[4]);
		}
		else{
			print_help();
			return 1;
		}
	}
	else{
		print_help();
		return 1;
	}
	return 0;
}
