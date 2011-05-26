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
		//cerr<<raw_data.size()<<"\t"<<line<<endl;
		//for(int i=0;i<=raw_data.size();++i){
		//	cout<<raw_data[i]<<endl;
		//}
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
	
}

void blogentry::read_content(){
	m_content=read_file(m_content_file);
}

void blogentry::read_comments(){
	m_comments=read_file(m_comments_file);
}

LINES blogentry::content(){
	bool p_open=false;
	string line;
	LINES data;
	for(LINES::iterator it=m_content.begin();it!=m_content.end();++it){
		line=*it;
		line=clean_whitespace(line);
		if(!line.empty()){
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
	if(p_open){
		p_open=false;
		data.push_back(string("</p>"));
	}
	return data;
}

void blogentry::new_comment(string filename){
	read_comments();
	if(filename=="")return;
	LINES comment=read_file(filename);
	string author="Anonymous";
	bool p_open=false;
	if(comment[0].find("#AUTHOR=")==0){
		author=cut(comment[0]).second;
		comment.erase(comment.begin());
	}
	m_comments.push_back("<li class=\"comment\">");
	m_comments.push_back("<p><strong>"+author+"</strong> ("+get_localdate()+"):</p>");
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
	LINES data=read_file(filename);
	deque<blogentry> returndata;
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		returndata.push_back(blogentry(*it,with_content));
		
	}
	return returndata;
}
/*
map<ID,blogentry*> create map(deque<blogentry>& data){
	map<ID,blogentry*> returndata;
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		returndata[it->id()]=&(*it);
		
	}
	return returndata;
}
//*/
