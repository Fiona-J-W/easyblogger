//      page.hpp
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


#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include <deque>

#include "blogentry.hpp"
#include "settings.hpp"

using namespace std;

int write_page(deque<blogentry> entries, settings S,string filename,bool comments=false);

int write_page(blogentry entry, settings S,string filename,bool comments=true);

#endif /* PAGE_HPP */ 
