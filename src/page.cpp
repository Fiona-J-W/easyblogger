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

const string TEMPLATE_FILE_PUT_POSTINGS=string("<<POSTINGS>>");
const string TEMPLATE_FILE_PUT_TITLE=string("<<TITLE>>");
const string TEMPLATE_FILE_PUT_TOC=string("<<TOC>>");
const string TEMPLATE_FILE_PUT_MAINPAGE_TOC=string("<<MAINPAGE_TOC>>");///will only be shown on mainpage



int write_page(blogentry &entry, settings &S,string filename,bool comments){
	deque<blogentry> entries;
	entries.push_back(entry);
	list<string> data, temp_lines=read_file_to_list(S.template_file);
	for(list<string>::iterator it=temp_lines.begin();it!=temp_lines.end();++it){
		*it=replace(*it,TEMPLATE_FILE_PUT_TITLE,S.name+" - "+entry.get_heading());
		if(*it==TEMPLATE_FILE_PUT_POSTINGS){
			data+=get_postings(entries,S,comments);
		}
		else if(*it==TEMPLATE_FILE_PUT_TOC){
			if(S.toc_in_singleentries){
				data+=get_TOC(S);
			}
		}
		else if(*it==TEMPLATE_FILE_PUT_MAINPAGE_TOC){
			continue;
		}
		else{
			data.push_back(*it);
		}
	}
	return write_file(filename,data);
}


int write_page(deque<blogentry> &entries, settings &S, string filename,bool comments){
	list<string> data, temp_lines=read_file_to_list(S.template_file);
	for(list<string>::iterator it=temp_lines.begin();it!=temp_lines.end();++it){
		*it=replace(*it,TEMPLATE_FILE_PUT_TITLE,S.name);
		if(*it==TEMPLATE_FILE_PUT_POSTINGS){
			data+=get_postings(entries,S,comments);
		}
		else if(*it==TEMPLATE_FILE_PUT_TOC){
			data+=get_TOC(S);
		}
		else if(*it==TEMPLATE_FILE_PUT_MAINPAGE_TOC){
			data+=get_mainpage_TOC(entries,S);
		}
		else{
			data.push_back(*it);
		}
	}
	return write_file(filename,data);
}


list<string> get_postings(deque<blogentry> &entries, settings &S,bool comments){
	if(!S.enable_comments){
		comments=false;
	}
	list<string> tmp,data;
	string lastdate="";
	bool first_post=true;
	if(S.sorting_by_date){
		for(deque<blogentry>::iterator it=entries.begin();it!=entries.end();++it){
			if(lastdate!=it->get_display_date()){
				if(first_post){
					first_post=false;
				}
				else{
					data.push_back(string("</ul>\n</div>"));
					
				}
				data.push_back(string("<div class=\"content\">\n<h2>")+it->get_display_date()+string("</h2>\n<ul class=\"blogentry\" >"));
				lastdate=it->get_display_date();
			}
			data.push_back("<li id=\""+it->get_id()+"\" class=\"blogentry\">");
			data.push_back("<h3><a class=\"headline_link\" href=\""+S.single_entries_dir_rel+it->get_id()+".html\" >"+it->get_heading()+"</a></h3>");
			data+=it->content();
			if(comments){
				tmp.clear();
				tmp+=it->comments();
				if(tmp.empty()){
					data.push_back(string("<hr/>\n")+"<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
				}
				else{
					data.push_back("<hr/><h3>"+S.comment_section_heading+"</h3>\n<ul class=\"comments\">");
					data+=tmp;
					data.push_back("</ul>");
					data.push_back("<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
				}
			}
			data.push_back("</li>");
		}
	data.push_back(string("</ul>\n</div>"));
	}
	else{
		for(deque<blogentry>::iterator it=entries.begin();it!=entries.end();++it){
			data.push_back("<div class=\"content\">");
			data.push_back("<article>");
			data.push_back("<h2><a class=\"headline_link\" id=\""+it->get_id()+"\" href=\""+S.single_entries_dir_rel+it->get_id()+".html\" >"+it->get_heading()+"</a></h2>\n");
			data.push_back("<span class=\"post_time\" >"+it->get_display_date()+"</span>\n");
			data+=it->content();
			data.push_back("</article>");
			if(comments){
				tmp.clear();
				tmp+=it->comments();
				if(tmp.empty()){
					data.push_back(string("<hr/>\n")+"<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
				}
				else{
					data.push_back("<hr/><h3>"+S.comment_section_heading+"</h3>\n<ul class=\"comments\">");
					data+=tmp;
					data.push_back("</ul>");
					data.push_back("<a href=\""+S.comment_url+it->get_id()+"\">"+S.comment_name+"</a>");
				}
			}
			data.push_back("</div>");
		}
	}
	
	
	return data;
}


list<string> get_TOC(settings &S){
	list<string> data;
	deque<blogentry> blogentries=read_entries(S.list_of_entries,true);
	if(!S.toc_pre.empty()){
		data.push_back(S.toc_pre);
	}
	if(!S.toc_title.empty()){
		data.push_back("<h2>"+S.toc_title+"</h2>");
	}
	data.push_back("<ul class=\"toc\">");
	for(deque<blogentry>::iterator it=blogentries.begin();it!=blogentries.end();++it){
		data.push_back("<li class=\"tocitem\"><a href=\""+S.single_entries_dir_rel+it->get_id()+".html\" class=\"toclink \">"+it->get_heading()+"</a></li>");
	}
	data.push_back("</ul>");
	if(!S.toc_post.empty()){
		data.push_back(S.toc_post);
	}
	return data;
}

list<string> get_mainpage_TOC(deque<blogentry> &entries, settings &S){
	list<string> data;
	if(!S.mainpage_toc_pre.empty()){
		data.push_back(S.mainpage_toc_pre);
	}
	if(!S.mainpage_toc_title.empty()){
		data.push_back("<h2>"+S.mainpage_toc_title+"</h2>");
	}
	data.push_back("<ul class=\"mainpagetoc\">");
	for(deque<blogentry>::iterator it=entries.begin();it!=entries.end();++it){
		data.push_back("<li class=\"mainpagetocitem\"><a class=\"mainpagetoclink\" href=\"#"+it->get_id()+"\" >"+it->get_heading()+"</a></li>");
	}
	data.push_back("</ul>");
	if(!S.mainpage_toc_post.empty()){
		data.push_back(S.mainpage_toc_post);
	}
	return data;
}