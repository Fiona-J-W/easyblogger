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

#include "settings.hpp"

const std::string DEFAULT_TIME_FORMAT=std::string("%A, %e. %B %Y");
const std::string DEFAULT_LOCALE=std::string("");
const int DEFAULT_MAX_DATE_SIZE=200;

std::string get_localdate(std::string format=DEFAULT_TIME_FORMAT,std::string locale=DEFAULT_LOCALE, int max_date_size=DEFAULT_MAX_DATE_SIZE);
std::string get_localdate(settings &S);



#endif
