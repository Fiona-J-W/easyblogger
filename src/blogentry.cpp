//      blogentry.cpp
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


#include "blogentry.hpp"
#include "lines.hpp"
#include "files.hpp"
#include "date.hpp"

#include <utility>
#include <exception>
#include <iostream>

using namespace std;

blogentry::blogentry(string file, bool with_content){
	m_content_loaded=false;
	m_comments_loaded=false;
	create_from_file(file);
	if(with_content){
		read_content();
		read_comments();
	}
}


void blogentry::create_from_file(string filename){
	LINES raw_data=read_config_file(filename);
	pair<string,string> temp_pair;
	string key;
	for(LINES::iterator it=raw_data.begin();it!=raw_data.end();++it){
		temp_pair=cut(*it);
		key=temp_pair.first;
		if(key==CONTENT_FILE_SETTER){
			m_content_file=temp_pair.second;
		}
		else if(key==COMMENTS_FILE_SETTER){
			m_comments_file=temp_pair.second;
		}
		else if(key==DISPLAY_DATE_SETTER){
			m_display_date=temp_pair.second;
		}
		else if(key==ISO_DATE_SETTER){
			m_iso_date=temp_pair.second;
		}
		else if(key==HEADING_SETTER){
			m_heading=temp_pair.second;
		}
		else if(key==ID_SETTER){
			try{
				m_id=ID(temp_pair.second);
			}
			catch(...){
				throw string("invalid ID");
			}
		}
		else if(key==TAGS_SETTER){
			m_tags=cut_fields(temp_pair.second,",");
		}
		else{
			cerr<<"Unknown key: \""<<key<<"\" with value \""<<temp_pair.second<<"\""<<endl;
		}
	}
	
}

void blogentry::set_content(LINES content){
	m_content=content;
	m_content_loaded=true;
}

void blogentry::read_content(){
	m_content=read_file(m_content_file);
	m_content_loaded=true;
}

void blogentry::read_comments(){
	m_comments=read_file(m_comments_file);
	m_comments_loaded=true;
}

LINES blogentry::content(){
	if(!m_content_loaded){
		read_content();
	}
	bool p_open=false, verbatim_mode=false;
	string line;
	LINES data;
	for(LINES::iterator it=m_content.begin();it!=m_content.end();++it){
		line=*it;
		line=clean_whitespace(line);
		if(verbatim_mode){
			if(line==VERBATIM_AREA_END){
				verbatim_mode=false;
			}
			else{
				data.push_back(line);
			}
		}
		else{
			if(!line.empty()){
				if(line==VERBATIM_AREA_START){
					verbatim_mode=true;
					continue;
				}
				if(!p_open){
					p_open=true;
					data.push_back(string("<p>"));
				}
				data.push_back(line);
			}
			else{
				if(p_open){
					p_open=false;
					data.push_back(string("</p>"));
				}
			}
		}
	}
	if(p_open){
		p_open=false;
		data.push_back(string("</p>"));
	}
	return data;
}

void blogentry::new_comment(string filename,settings &S){
	if(!m_comments_loaded){
		read_comments();
	}
	if(filename=="")return;
	LINES comment=read_file(filename);
	string author=DEFAULT_COMMENT_AUTHOR;
	bool p_open=false;
	if(comment[0].find(COMMENT_AUTHOR_SETTER)==0){
		author=cut(comment[0]).second;
		comment.erase(comment.begin());
	}
	m_comments.push_back("<li class=\"comment\">");
	m_comments.push_back("<p><strong>"+author+"</strong> ("+get_localdate(S)+"):</p>");
	for(LINES::iterator it=comment.begin();it!=comment.end();++it){
		*it=clean_whitespace(*it);
		
		if(!it->empty()){
			if(!p_open){
				p_open=true;
				m_comments.push_back("<p>");
			}
			m_comments.push_back(*it);
		}
		else{
			if(p_open){
				p_open=false;
				m_comments.push_back("</p>");
			}
		}
	}
	if(p_open){
		p_open=false;
		m_comments.push_back(string("</p>"));
	}
	m_comments.push_back("</li>");
	write_file(m_comments_file,m_comments);
}

LINES blogentry::comments(){
	if(!m_comments_loaded){
		read_comments();
	}
	return m_comments;
}

string blogentry::get_display_date(){
	return m_display_date;
}

string blogentry::get_display_date(settings &S){
	if(m_iso_date.empty()){
		return get_display_date();
	}
	else return get_dynamic_date(S);
}

string blogentry::get_iso_date(){
	return m_iso_date;
}

string blogentry::get_dynamic_date(settings &S){
	if(m_iso_date.empty()){
		return "";
	}
	return iso_to_custom_date(m_iso_date,S);
}

string blogentry::get_heading(){
	return m_heading;
}

string blogentry::get_id(){
	return m_id.get();
}

string blogentry::get_filename(){
	return m_content_file;
}

ID blogentry::id(){
	return m_id;
}


string blogentry::get_comments_filename(){
	return m_comments_file;
}

string blogentry::get_url(settings &S){
	return S.url+S.single_entries_dir_rel+get_id();
}

///Non-member-functions:

deque<blogentry> read_entries(string filename, bool with_content){
	LINES data=read_config_file(filename);
	deque<blogentry> returndata;
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		returndata.push_back(blogentry(*it,with_content));
	}
	return returndata;
}
