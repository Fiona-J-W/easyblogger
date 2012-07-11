/**
 * get_localdate.hpp
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

#ifndef _get_localdate_
#define _get_localdate_

#include <string>
#include <ctime>

#include "settings.hpp"

const string DEFAULT_TIME_FORMAT=string("%A, %e. %B %Y");
const string DEFAULT_LOCALE=string("");
const int DEFAULT_MAX_DATE_SIZE=200;

string get_localdate(
	string format=DEFAULT_TIME_FORMAT,
	string locale=DEFAULT_LOCALE, 
	int max_date_size=DEFAULT_MAX_DATE_SIZE
);

string format_time(
	tm TIME,
	string format=DEFAULT_TIME_FORMAT,
	string locale=DEFAULT_LOCALE,
	int max_date_size=DEFAULT_MAX_DATE_SIZE
);
string get_localdate(settings &S);

string get_isodate();

string iso_to_custom_date(
	string isodate,
	string format=DEFAULT_TIME_FORMAT,
	string locale=DEFAULT_LOCALE, 
	int max_date_size=DEFAULT_MAX_DATE_SIZE
);
string iso_to_custom_date(string isodate,settings &S);

tm str_to_time(string isodate);
string time_to_str(tm time);
tm get_time();



#endif
