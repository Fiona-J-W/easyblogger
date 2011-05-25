#include "help.hpp"

#include <iostream>

using namespace std;

void print_info(){
	cout
		<<"easyblogger 2.0.0\n"
		<<"Copyright (c) 2011 \n"
		<<"Florian Weber <florian.weber@sfz-bw.de>\n"
		<<"\n"
		<<"This programm is a small and fast CMS.\n"
		<<"\n"
		<<"This Programm is free Software under the Terms of the GNU GPL\n"
		<<"For more information look up the GPL.\n"
		<<endl;
}

void print_help(){
	cout
		<<"easyblogger [blog] <command> <blogentry>\n"
		<<"\t--create / -c: recreate all entries\n"
		<<"\t--import / -i <file>: create new post from <file>\n"
		<<"\t--edit / -e <ID>: edit Post with the id <ID>\n"
		<<"\t--configure: configure settings\n"
		<<"\t--comment <ID> <file>: comment POST <ID> with content from <file>\n"
		<<"\t--about: print a copyright-note \n"
		<<"\t--help / -h: show this help\n"
		<<endl;
}
