//      config.cpp
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
//      


#include "config.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include "actions.hpp"

using namespace std;

int configure_blog(settings &S, string name){
	if(S.editor.empty()){
		cerr<<"Error: No editor has been specified; choosing vi as fallback."<<endl;
		S.editor="vi";
	}
	string command=S.editor+" "+get_blog_conf_file(name);
	system(command.c_str());
	create_all(S);
	return 0;
}
