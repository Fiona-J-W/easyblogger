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
		<<"This Programm is free Software under the Terms of the GNU AGPL\n"
		<<"For more information look up the AGPL.\n"
		<<endl;
}

void print_help(){
	cout
		<<"easyblogger [blog] <command> <further parameters>\n"
		<<"\t--create / -c: recreate all entries\n"
		<<"\t--import / -i <file>: create new post from <file>\n"
		<<"\t--edit / -e <ID>: edit post with the id <ID>\n"
		<<"\t--edit-comments / -E <ID>: edit comments of the choosen post\n"
		<<"\t--configure / -C: configure settings\n"
		<<"\t--configure / -C <ID>: configure settings of the post with the id <ID>\n"
		<<"\t--comment <ID> <file>: comment POST <ID> with content from <file>\n"
		<<"\t--list-comments / -l: list all posts (id and title)\n"
		<<"\t--search / -s <phrase>: print a list of all entries, that contain <phrase>.\n"
		<<"\t--html-search / -S <phrase>: same as search, but format the output as html.\n"
		<<"\t--about: print a copyright-note \n"
		<<"\t--help / -h: show this help\n"
		<<endl;
}
