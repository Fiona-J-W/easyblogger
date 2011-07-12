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

#include "lines.hpp"

#include <cstdio>
#include <ctime>
#include <clocale>
#include <cstring>

using namespace std;




std::string get_localdate(std::string format,std::string locale, int max_date_size){
	time_t TIME;
	char *timestring=new char[max_date_size+1];
	struct tm *timeinfo;
	string returnstr;
	setlocale(LC_TIME, locale.c_str());
	time(&TIME);
	timeinfo=localtime(&TIME);
	strftime(timestring,max_date_size,format.c_str(),timeinfo);
	timestring[max_date_size]='\0';
	returnstr=remove_double_spaces(string(timestring));
	delete timestring;
	return returnstr;
}

std::string get_localdate(settings &S){
	string format=DEFAULT_TIME_FORMAT,locale=DEFAULT_LOCALE;
	int max_date_size=DEFAULT_MAX_DATE_SIZE;
	if(!S.time_format.empty()){
		format=S.time_format;
	}
	if(!S.locale.empty()){
		locale=S.locale;
	}
	if(S.max_date_size>0){
		max_date_size=S.max_date_size;
	}
	return get_localdate(format, locale, max_date_size);
}


std::string get_isodate(){
	return
get_localdate("%a, %d %b %Y %X %Z","en_US",40);
}
