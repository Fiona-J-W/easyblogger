//      page.cpp
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

#include <iostream>
using namespace std;

#include "page.hpp"
#include "lines.hpp"
#include "files.hpp"

int write_page(deque<blogentry> entries, settings &S, string filename,bool comments){
	LINES data, header, footer,tmp;
	header=read_file(S.header);
	footer=read_file(S.footer);
	string lastdate="";
	bool first_post=true;
	data+=header;
	for(deque<blogentry>::iterator it=entries.begin();it!=entries.end();++it){
		if(lastdate!=it->get_date()){
			if(first_post){
				first_post=false;
			}
			else{
				data.push_back(string("</ul>\n</div>"));
				
			}
			data.push_back(string("<div class=\"content\">\n<h2>")+it->get_date()+string("</h2>\n<ul class=\"blogentry\" >"));
			lastdate=it->get_date();
		}
		data.push_back("<li id=\""+it->get_id()+"\" class=\"blogentry\">");
		data.push_back("<h3><a class=\"headline_link\" href=\""+S.single_entries_dir_rel+it->get_id()+".html\" >"+it->get_heading()+"</a></h3>");
		tmp=it->content();
		for(LINES::iterator it_content=tmp.begin();it_content!=tmp.end();++it_content){
			data.push_back(*it_content);
		}
		tmp=it->comments();
		if(comments&&tmp.empty()){
			it->read_comments();
			tmp=it->comments();
		}
		if(comments&&(!tmp.empty())){
			data.push_back("<hr/><h3>"+S.comment_section_heading+"</h3>\n<ul class=\"comments\">");
			for(LINES::iterator it_comment=tmp.begin();it_comment!=tmp.end();++it_comment){
				data.push_back(*it_comment);
			}
			data.push_back("</ul>");
			data.push_back("<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
		}
		else if(comments){
			data.push_back(string("<hr/>\n")+"<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
			
		}
		data.push_back("</li>");
	}
	data.push_back(string("</ul>\n</div>"));
	data+=footer;
	return write_file(filename,data);
}

int write_page(blogentry entry, settings &S,string filename,bool comments){
	deque<blogentry> entries;
	entries.push_back(entry);
	return write_page(entries, S, filename,comments);
}
