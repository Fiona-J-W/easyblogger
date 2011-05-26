/**
 * get_localdate.cpp
 * 
 * Copyright 2010 Florian Weber <florian.weber@sfz-bw.de>
 * 
 * This program is free software; you can redistribute it and/or modify
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
**/

#include "date.hpp"

#include <cstdio>
#include <ctime>
#include <clocale>
#include <cstring>



std::string get_localdate(){
	time_t TIME;
	char timestring_1[21],timestring_2[11],timestring_3[21];
	struct tm *timeinfo;
	std::string returnstring;

	setlocale(LC_ALL, "");
	time(&TIME);
	timeinfo=localtime(&TIME);
	strftime(timestring_1,20,"%A, ",timeinfo);
	strftime(timestring_2,10,"%d",timeinfo);
	strftime(timestring_3,20,". %B %Y",timeinfo);
	
	timestring_1[20]=0;
	timestring_2[10]=0;
	timestring_3[20]=0;
	
	if(timestring_2[0]=='0'){
		char *pointer;
		pointer=timestring_2;
		++pointer;
		strcpy(timestring_2,pointer);
	}
	returnstring=timestring_1;
	returnstring+=timestring_2;
	returnstring+=timestring_3;
	
	return returnstring;
}
