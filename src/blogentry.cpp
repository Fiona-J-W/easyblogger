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

blogentry::blogentry(string file,settings &S, bool with_content){
	m_content_loaded=false;
	m_comments_loaded=false;
	m_hidden=false;
	m_conf_file=file;
	create_from_file(m_conf_file,S);
	if(with_content){
		read_content();
		read_comments();
		m_content_loaded=true;
		m_comments_loaded=true;
	}
}

blogentry::~blogentry(){
}

void blogentry::create_from_file(string filename,settings &S){
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
			if(m_tags.empty()){
				m_tags=cut_fields(temp_pair.second,",");
			}
			else{
				m_tags+=cut_fields(temp_pair.second,",");
			}
		}
		else if(key==HIDDEN_SETTER){
			if(temp_pair.second=="true"){
				m_hidden=true;
			}
			else{
				m_hidden=false;
			}
		}
		else{
			cerr<<"Unknown key: \""<<key<<"\" with value \""<<temp_pair.second<<"\""<<endl;
		}
	}
	for(deque<string>::iterator it=m_tags.begin();it!=m_tags.end();++it){
		*it=clean_whitespace_both_sides(*it);
		S.tags[*it].push_back(this);
	}
}

void blogentry::set_content(LINES content){
	m_content=content;
	m_content_loaded=true;
}

void blogentry::read_content(){
	if(!m_content_loaded){
		m_content=read_file(m_content_file);
		m_content_loaded=true;
	}
}

void blogentry::read_comments(){
	if(!m_comments_loaded){
		m_comments=read_file(m_comments_file);
		m_comments_loaded=true;
	}
}

LINES blogentry::content(){
	read_content();
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
	m_comments.push_back("<!-- DATE: "+get_iso_date()+" -->");
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
	return S.url+S.single_entries_dir_rel+get_id()+S.filename_extension;
}

string blogentry::get_rel_url(settings &S){
	return S.single_entries_dir_rel+get_id()+S.filename_extension;
}


string blogentry::get_conf_file(){
	return m_conf_file;
}

deque<string>& blogentry::get_tags(){
	return m_tags;
}

LINES blogentry::rss(settings &S){
	LINES data,content_=content();
	data.push_back("<item>");
	
	data.push_back("\t<title>"+get_heading()+"</title>");
	data.push_back("\t<link>"+get_url(S)+"</link>");
	
	data.push_back("\t<description><![CDATA[");
	replace(content_,"href=\"/","href=\""+S.url+"/");
	replace(content_,"src=\"/","src=\""+S.url+"/");
	data+=push_string_to_front_of_every_line(content_,"\t\t");		
	data.push_back("\t]]></description>");
	
	data.push_back("\t<guid>"+get_url(S)+"</guid>");
	
	if(!m_iso_date.empty()){
		data.push_back("\t<pubDate>"+m_iso_date+"</pubDate>");
	}
	
	for(deque<string>::iterator it=m_tags.begin();it!=m_tags.end();++it){
		data.push_back("\t<category>"+*it+"</category>");
	}
	
	data.push_back("</item>");
	
	return data;
}

///Non-member-functions:
/*

deque<blogentry> read_entries(string filename, bool with_content){
	LINES data=read_config_file(filename);
	deque<blogentry> returndata;
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		returndata.push_back(blogentry(*it,with_content));
	}
	return returndata;
}

*/

void read_entries(settings &S, bool with_content){
	if(!S.blogentries.empty()){
		if(with_content){
			for(list<blogentry*>::iterator it=S.blogentries.begin();it!=S.blogentries.end();++it){
				(*it)->read_content();
				(*it)->read_comments();
			}
		}
		return;
	}
	LINES data=read_config_file(S.list_of_entries);
	blogentry *ptr;
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		ptr=new blogentry(*it,S,with_content);
		S.blogentries.push_back(ptr);
	}
}


blogentry* select(list<blogentry*> &blogentries,ID id){
	for(list<blogentry*>::iterator it=blogentries.begin();it!=blogentries.end();++it){
		if((*it)->id()==id){
			return *it;
		}
	}
	return NULL;
}

