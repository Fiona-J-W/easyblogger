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
#include <exception>

#include <iostream>

using namespace std;

blogentry::blogentry(string line, bool with_content){
	m_content_loaded=false;
	m_comments_loaded=false;
	create_from_line(line);
	if(with_content){
		read_content();
		read_comments();
	}
}


void blogentry::create_from_line(string line){
	deque<string> raw_data;
	raw_data=cut_fields(line,"\t");
	if(raw_data.size()<4){
		throw string("invalid field_count");
	}
	m_content_file=raw_data[0];
	m_date=raw_data[1];
	m_heading=raw_data[2];
	try{
		m_id=ID(raw_data[3]);
	}
	catch(...){
		throw string("invalid ID");
	}
	if(raw_data.size()>=5){
		m_comments_file=raw_data[4];
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

void blogentry::new_comment(string filename,settings S){
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

string blogentry::get_date(){
	return m_date;
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

///Non-member-functions:

deque<blogentry> read_entries(string filename, bool with_content){
	LINES data=read_config_file(filename);
	deque<blogentry> returndata;
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		returndata.push_back(blogentry(*it,with_content));
	}
	return returndata;
}
