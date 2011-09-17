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
#include <list>
using namespace std;

#include "page.hpp"
#include "lines.hpp"
#include "files.hpp"

const string TEMPLATE_FILE_PUT_POSTINGS=string("<<POSTINGS>>");
const string TEMPLATE_FILE_PUT_TITLE=string("<<TITLE>>");
const string TEMPLATE_FILE_PUT_TOC=string("<<TOC>>");
const string TEMPLATE_FILE_PUT_MAINPAGE_TOC=string("<<MAINPAGE_TOC>>");///will only be shown on mainpage
const string TEMPLATE_FILE_PUT_TAGS="<<TAGS>>";



int write_page(blogentry *entry, settings &S,string filename,bool comments){
	list<blogentry*> entries;
	entries.push_back(entry);
	list<string> data, temp_lines=read_file_to_list(S.template_file);
	for(list<string>::iterator it=temp_lines.begin();it!=temp_lines.end();++it){
		*it=replace(*it,TEMPLATE_FILE_PUT_TITLE,S.name+" - "+entry->get_heading());
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


int write_page(list<blogentry*> &entries, settings &S, string filename,bool comments){
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


list<string> get_postings(list<blogentry*> &entries, settings &S,bool comments){
	if(!S.enable_comments){
		comments=false;
	}
	list<string> tmp,data;
	string lastdate="";
	bool first_post=true;
	if(S.sorting_by_date){
		for(list<blogentry*>::iterator it=entries.begin();it!=entries.end();++it){
			if(lastdate!=(*it)->get_display_date()){
				if(first_post){
					first_post=false;
				}
				else{
					data.push_back(string("</ul>\n</div>"));
					
				}
				data.push_back(string("<div class=\"content\">\n<h2>")+(*it)->get_display_date()+string("</h2>\n<ul class=\"blogentry\" >"));
				lastdate=(*it)->get_display_date();
			}
			data.push_back("<li id=\""+(*it)->get_id()+"\" class=\"blogentry\">");
			data.push_back("<h3><a class=\"headline_link\" href=\""+(*it)->get_rel_url(S)+"\" >"+(*it)->get_heading()+"</a></h3>");
			data+=(*it)->content();
			if(comments){
				tmp.clear();
				tmp+=(*it)->comments();
				if(tmp.empty()){
					data.push_back(string("<hr/>\n")+"<a href=\""+S.comment_url+(*it)->get_id()+"\">"+S.comment_name+"</a>");
				}
				else{
					data.push_back("<hr/><h3>"+S.comment_section_heading+"</h3>\n<ul class=\"comments\">");
					data+=tmp;
					data.push_back("</ul>");
					data.push_back("<a href=\""+S.comment_url+(*it)->get_id()+"\">"+S.comment_name+"</a>");
				}
			}
			data.push_back("</li>");
		}
	data.push_back(string("</ul>\n</div>"));
	}
	else{
		for(list<blogentry*>::iterator it=entries.begin();it!=entries.end();++it){
			data.push_back("<div class=\"content\">");
			data.push_back("<article>");
			data.push_back("<h2><a class=\"headline_link\" id=\""+(*it)->get_id()+"\" href=\""+(*it)->get_rel_url(S)+"\" >"+(*it)->get_heading()+"</a></h2>\n");
			data.push_back("<span class=\"post_time\" >"+(*it)->get_display_date()+"</span>\n");
			data+=(*it)->content();
			data.push_back("</article>");
			if(S.enable_tag_file){
				deque<string> tags=(*it)->get_tags();
				if(!tags.empty()){
					data.push_back("<span class=\"tags_header\">"+S.tags_title+"</span>");
					data.push_back("<ul class=\"tag_list\" >");
					for(deque<string>::iterator it=tags.begin();it!=tags.end();++it){
						data.push_back("<li><a href=\""+S.tag_file_rel+"#"+replace(*it," ","_")+"\" >"+*it+"</a></li>");
					}
					data.push_back("</ul>");
				}
			}
			if(comments){
				tmp.clear();
				tmp+=(*it)->comments();
				if(tmp.empty()){
					data.push_back(string("<hr/>\n")+"<a href=\""+S.comment_url+(*it)->get_id()+"\">"+S.comment_name+"</a>");
				}
				else{
					data.push_back("<hr/><h3>"+S.comment_section_heading+"</h3>\n<ul class=\"comments\">");
					data+=tmp;
					data.push_back("</ul>");
					data.push_back("<a href=\""+S.comment_url+(*it)->get_id()+"\">"+S.comment_name+"</a>");
				}
			}
			data.push_back("</div>");
		}
	}
	
	
	return data;
}


list<string> get_TOC(settings &S){
	list<string> data;
	if(S.blogentries.empty()){
		read_entries(S,true);
	}
	if(!S.toc_pre.empty()){
		data.push_back(S.toc_pre);
	}
	if(!S.toc_title.empty()){
		data.push_back("<h2>"+S.toc_title+"</h2>");
	}
	data.push_back("<ul class=\"toc\">");
	for(list<blogentry*>::iterator it=S.blogentries.begin();it!=S.blogentries.end();++it){
		data.push_back("<li class=\"tocitem\"><a href=\""+(*it)->get_rel_url(S)+"\" class=\"toclink\">"+(*it)->get_heading()+"</a></li>");
	}
	data.push_back("</ul>");
	if(!S.toc_post.empty()){
		data.push_back(S.toc_post);
	}
	return data;
}

list<string> get_mainpage_TOC(list<blogentry*> &entries, settings &S){
	list<string> data;
	if(!S.mainpage_toc_pre.empty()){
		data.push_back(S.mainpage_toc_pre);
	}
	if(!S.mainpage_toc_title.empty()){
		data.push_back("<h2>"+S.mainpage_toc_title+"</h2>");
	}
	data.push_back("<ul class=\"mainpagetoc\">");
	for(list<blogentry*>::iterator it=entries.begin();it!=entries.end();++it){
		data.push_back("<li class=\"mainpagetocitem\"><a class=\"mainpagetoclink\" href=\"#"+(*it)->get_id()+"\" >"+(*it)->get_heading()+"</a></li>");
	}
	data.push_back("</ul>");
	if(!S.mainpage_toc_post.empty()){
		data.push_back(S.mainpage_toc_post);
	}
	return data;
}

int create_tags_page(settings &S){
	if(!S.enable_tag_file){
		return 1;
	}
	list<string> data, temp_lines=read_file_to_list(S.tag_file_template);
	
	for(list<string>::iterator it=temp_lines.begin();it!=temp_lines.end();++it){
		if(it->find("<<")==string::npos){
			data.push_back(*it);
		}
		else{
			if(*it==TEMPLATE_FILE_PUT_TAGS){
				data+=get_tag_list(S);
			}
			else{
				cerr<<"WARNING: Unknown template used"<<endl;
			}
		}
	}
	
	return write_file(S.tag_file,data);
}

list<string> get_tag_list(settings &S){
	list<string> lines;
	string heading;
	lines.push_back("<dl class=\"tag_list\" >");
	for(map<string,list<blogentry*> >::iterator it=S.tags.begin();it!=S.tags.end();++it){
		heading="<dt id=\""+replace(it->first," ","_")+"\">"+it->first;
		if(S.tag_feeds){
			heading+=" (<a href=\""+S.tag_feeds_dir_rel+replace(it->first," ","_")+S.rss_file_extension+"\" >RSS</a>)";
		}
		heading+="</dt>";
		lines.push_back(heading);
		for(list<blogentry*>::iterator inner_it=it->second.begin();inner_it!=it->second.end();++inner_it){
			lines.push_back("<dd><a href=\""+(*inner_it)->get_rel_url(S)+"\" >"+(*inner_it)->get_heading()+"</a></dd>");
		}
	}
	lines.push_back("</dl>");
	return lines;
}