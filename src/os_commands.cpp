//      os_commands.cpp
//      
//      Copyright 2011 Florian Weber <florian@mars>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU Affero General Public License as published by
//      the Free Software Foundation; either version 3 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      


#include "os_commands.hpp"
#include <cstdlib>

#if defined(unix)


int change_rights(string filename,string rights){
	return system(("chmod "+rights+" "+filename).c_str());
}

#else
#warning "unknown system"
int change_rights(string filename,string rights){
	return -1;
}

#endif
