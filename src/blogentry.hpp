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
#include "lines.hpp"
#include "comments.hpp"

using namespace std;


const string DEFAULT_COMMENT_AUTHOR=string("Anonymous");

const string COMMENT_AUTHOR_SETTER=string("#AUTHOR=");
const string VERBATIM_AREA_START=string("#START_VERBATIM");
const string VERBATIM_AREA_END=string("#END_VERBATIM");


///For creation from file:
const string ID_SETTER="ID";
const string HEADING_SETTER="heading";
const string CONTENT_FILE_SETTER="content_file";
const string COMMENTS_FILE_SETTER="comment_file";
const string DISPLAY_DATE_SETTER="display_date";
const string ISO_DATE_SETTER="iso_date";
const string TAGS_SETTER="tags";
const string HIDDEN_SETTER="hidden";

///This class represents a blogentry.
class blogentry{
	public:
		blogentry(string file,settings &S, bool with_content=false);
		~blogentry();
		//void create_from_line(string line);
		void create_from_file(string filename,settings &S);
		void read_content();
		void read_comments();
		void set_content(LINES content);
		void new_comment(string filename);
		LINES content();
		LINES get_comments(settings &S);
		LINES rss(settings &S);
		string get_iso_date();
		string get_dynamic_date(settings &S);
		string get_display_date();
		string get_display_date(settings &S);
		string get_heading();
		string get_id();
		string get_filename();
		string get_comments_filename();
		string get_url(settings &S);
		string get_rel_url(settings &S);
		string get_conf_file();
		deque<string> &get_tags();
		ID id();
		
		bool operator>(blogentry b);
		bool operator<(blogentry b);
		
		bool hidden(){return m_hidden;}
		
	private:
		
		string m_heading;
		string m_display_date;
		string m_iso_date;
		string m_content_file;
		string m_comments_file;
		string m_conf_file;
		
		bool m_content_loaded;
		bool m_comments_loaded;
		bool m_hidden;
		
		ID m_id;
		LINES m_content;
		//LINES m_comments;
		comments m_comments;
		
		deque<string> m_tags;
};

//deque<blogentry> read_entries(string filename, bool with_content=false);
void read_entries(settings &S, bool with_content=false);

blogentry* select(list<blogentry*> &blogentries,ID id);

bool comp(blogentry *b1, blogentry *b2);

#endif /* BLOGENTRY_H */ 
