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
#include <cstdlib>

using namespace std;


string format_time(tm TIME,string format,string locale,int max_date_size){
	string returnstr;
	char *timestring=new char[max_date_size+1];
	
	if(!locale.empty()){
		setlocale(LC_TIME, locale.c_str());
	}
	
	strftime(timestring,max_date_size,format.c_str(),&TIME);
	timestring[max_date_size]='\0';
	returnstr=remove_double_spaces(timestring);
	
	delete timestring;
	return returnstr;
}


tm get_time(){
	time_t TIME;
	tm *timeinfo;
//	setlocale(LC_TIME, locale.c_str());
	time(&TIME);
	timeinfo=localtime(&TIME);
	return *timeinfo;
}

std::string get_localdate(std::string format,std::string locale, int max_date_size){
	time_t TIME;
	char *timestring=new char[max_date_size+1];
	tm *timeinfo;
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
get_localdate("%a, %d %b %Y %H:%M:%S %z","en_US",40);
}

const string weeknames[]={
	"Sun","Mon","Tue","Wed",
	"Thu","Fri","Sat",
};


const string monthnames[]={
	"Jan","Feb","Mar",
	"Apr","May","Jun",
	"Jul","Aug","Sep",
	"Oct","Nov","Dec"
};


std::string iso_to_custom_date(
	string isodate,
	string format,
	string locale, int max_date_size
){
	tm time=str_to_time(isodate);
	
	setlocale(LC_TIME, locale.c_str());
	char *timestring=new char[max_date_size+1];
	strftime(timestring,max_date_size,format.c_str(),&time);
	timestring[max_date_size]='\0';
	string returnstr=remove_double_spaces(string(timestring));
	
	delete timestring;
	return returnstr;
}

string iso_to_custom_date(std::string isodate,settings &S){
	return iso_to_custom_date(isodate,S.time_format,S.locale,S.max_date_size);
}


tm str_to_time(string isodate){
	tm time;
	if(isodate.empty()){
		return time;
	}
	string temp="";
	pair<string,string> temp_pair;
	
	temp_pair=cut(isodate,",");
	temp=temp_pair.first;
	isodate=temp_pair.second;
	for(int i=0;i<=6;++i){
		if(temp==weeknames[i]){
			time.tm_wday=i;
		}
	}
	
	isodate=clean_whitespace(isodate);
	temp_pair=cut(isodate," ");
	temp=temp_pair.first;
	isodate=temp_pair.second;
	time.tm_mday=atoi(temp.c_str());
	
	isodate=clean_whitespace(isodate);
	temp_pair=cut(isodate," ");
	temp=temp_pair.first;
	isodate=temp_pair.second;
	for(int i=0;i<=11;++i){
		if(temp==monthnames[i]){
			time.tm_mon=i;
			break;
		}
	}
	
	isodate=clean_whitespace(isodate);
	temp_pair=cut(isodate," ");
	isodate=temp_pair.second;
	time.tm_year=atoi(temp_pair.first.c_str()-1900);
	
	isodate=clean_whitespace(isodate);
	temp_pair=cut(isodate,":");
	isodate=temp_pair.second;
	time.tm_hour=atoi(temp_pair.first.c_str());
	
	temp_pair=cut(isodate,":");
	isodate=temp_pair.second;
	time.tm_min=atoi(temp_pair.first.c_str());
	
	temp_pair=cut(isodate," ");
	isodate=clean_whitespace(temp_pair.second);
	time.tm_sec=atoi(temp_pair.first.c_str());
	return time;
}


