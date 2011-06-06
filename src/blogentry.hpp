//      blogentry.h
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


#ifndef BLOGENTRY_H
#define BLOGENTRY_H

#include <string>
#include <deque>
#include <map>

#include "id.hpp"
#include "settings.hpp"

using namespace std;

typedef deque<string> LINES;

const string DEFAULT_COMMENT_AUTHOR=string("Anonymous");


class blogentry{
	public:
		blogentry(string line, bool with_content=false);
		void create_from_line(string line);
		void read_content();
		void read_comments();
		void set_content(LINES content);
		void new_comment(string filename,settings S);
		LINES content();
		LINES comments();
		string get_date();
		string get_heading();
		string get_id();
		string get_filename();
		string get_comments_filename();
		ID id();
	private:
		
		string m_heading;
		string m_date;
		string m_content_file;
		string m_comments_file;
		ID m_id;
		LINES m_content;
		LINES m_comments;
};

deque<blogentry> read_entries(string filename, bool with_content=false);



#endif /* BLOGENTRY_H */ 
