//      sites.cpp
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


#include "actions.hpp"
#include "blogentry.hpp"
#include "date.hpp"
#include "files.hpp"
#include "lines.hpp"
#include "os_commands.hpp"


#include <iostream>
#include <cstdlib>

using namespace std;

int create_all(settings &S){
	deque<blogentry> data=read_entries(S.list_of_entries,true);
	string filename;
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		filename=S.single_entries_dir+it->get_id()+".html";
		write_page(*it,S,filename);
		
	}
	if(S.number_of_mainpageposts<=-1||int(data.size())<=S.number_of_mainpageposts){
		write_page(data,S,S.blog);
	}
	else{
		deque<blogentry> mainpageposts;
		for(int i=0;i<S.number_of_mainpageposts&&i<int(data.size());++i){
			mainpageposts.push_back(data.at(i));
		}
		write_page(mainpageposts,S,S.blog);
	}
	create_rss(S,data);
	return 0;
}

int create_latest(settings &S){
	if(S.number_of_mainpageposts<0){
		return create_all(S);
	}
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	deque<blogentry> mainpageposts;
	string filename;
	for(int i=0;i<S.number_of_mainpageposts&&i<int(data.size());++i){
		data.at(i).read_content();
		filename=S.single_entries_dir+data.at(i).get_id()+".html";
		write_page(data.at(i),S,filename);
		mainpageposts.push_back(data.at(i));
	}
	write_page(mainpageposts,S,S.blog);
	create_rss(S,data);
	return 0;
}

int create(settings &S,ID id){
	string filename;
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	int n=-1;
	for(size_t i=0;i<data.size();++i){
		if(data.at(i).id()==id){
			n=i;
			break;
		}
	}
	if(n==-1){
		return 1;
	}
	if(n<=S.number_of_mainpageposts){
		return create_latest(S);
	}
	data.at(n).read_content();
	data.at(n).read_comments();
	filename=S.single_entries_dir+data.at(n).get_id()+".html";
	write_page(data.at(n),S,filename);
	return 0;
}

int create_rss(settings &S,deque<blogentry> &blogentries){
	deque<string> tags;
	if(S.rss_feed.empty()){
		return 1;
	}
	LINES feed,content;
	feed.push_back(string("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
	feed.push_back(string("<rss version=\"2.0\">\n\t<channel>"));
	feed+=read_file(S.rss_channel_description_file);
	for(int i=0;i<S.number_of_mainpageposts&&i<int(blogentries.size());++i){
		content=push_string_to_front_of_every_line(blogentries[i].content(),"\t\t\t\t");
		replace(content,"href=\"/","href=\""+S.url+"/");
		replace(content,"src=\"/","src=\""+S.url+"/");
		
		feed.push_back(string("\t\t<item>"));
		feed.push_back(string("\t\t\t<title>")+blogentries[i].get_heading()+"</title>");
		feed.push_back(string("\t\t\t<link>")+blogentries[i].get_url(S)+".html</link>");
		feed.push_back(string("\t\t\t<description><![CDATA["));
		feed+=content;
		feed.push_back(string("\t\t\t]]></description>"));
		
		///optional data:
		if(!blogentries[i].get_iso_date().empty()){
			feed.push_back(string("\t\t\t<pubDate>")+blogentries[i].get_iso_date()+"</pubDate>");
		}
		feed.push_back(string("\t\t\t<guid>")+blogentries[i].get_url(S)+".html</guid>");
		
		tags=blogentries[i].get_tags();
		for(deque<string>::iterator it=tags.begin();it!=tags.end();++it){
			if(!it->empty()){
				feed.push_back(string("\t\t\t<category>")+*it+"</category>");
			}
		}
		
		feed.push_back(string("\t\t</item>"));
	}
	feed.push_back(string("\t</channel>\n</rss>"));
	write_file(S.rss_feed,feed);
	return 0;
}

int import(settings &S,string filename){
	string heading, date, content_file, comment_file, conf_file, tags;
	LINES data=read_file(filename), conf_file_content;
	list<string> conf_lines;
	int number_of_conf_lines=0;
	
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		if(it[0]=="#"){
			conf_lines.push_back(*it);
			++number_of_conf_lines;
		}
		else{
			break;
		}
	}
	for(list<string>::iterator it=conf_lines.begin();it!=conf_lines.end();++it){
		if(it->find("#HEADING=")==0){
			heading=cut(*it,"=").second;
		}
		else if(it->find("#TAGS")==0){
			if(tags.empty()){
				tags=cut(*it,"=").second;
			}
			else{
				tags+=","+cut(*it,"=").second;
			}
		}
	}
	
	if(number_of_conf_lines){
		data.erase(data.begin(),data.begin()+number_of_conf_lines);
	}
	
	while(heading==""){
		cout<<">>> ";
		getline(cin,heading);
	}
	++S.last_id;
	content_file=S.datadir+S.last_id.get()+".html";
	comment_file=S.datadir+S.last_id.get()+"-comments.html";
	conf_file=S.datadir+S.last_id.get()+".conf";
	
	conf_file_content.push_back(ID_SETTER+'='+S.last_id.get());
	conf_file_content.push_back(HEADING_SETTER+'='+heading);
	conf_file_content.push_back(CONTENT_FILE_SETTER+'='+content_file);
	conf_file_content.push_back(COMMENTS_FILE_SETTER+'='+comment_file);
	conf_file_content.push_back(DISPLAY_DATE_SETTER+'='+get_localdate(S));
	conf_file_content.push_back(ISO_DATE_SETTER+'='+get_isodate());
	conf_file_content.push_back(TAGS_SETTER+'='+tags);
	
	write_file(conf_file,conf_file_content);
	
	insert_to_begin_of_file(S.list_of_entries,conf_file);
	
	write_file(content_file,data);
	cout<<S.last_id.get()<<": "<<heading<<endl;
	if(S.toc_in_singleentries){
		create_all(S);
	}
	else{
		create_latest(S);
	}
	change_rights(content_file,"a+w");
	write_file(comment_file,"");
	change_rights(comment_file,"a+w");
	change_rights(S.single_entries_dir+S.last_id.get()+".html","a+w");
	return 0;
}

int edit(settings &S, ID id){
	string filename="", command;
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		if(it->id()==id){
			filename=it->get_filename();
			break;
		}
	}
	if(filename==""){
		cerr<<"Error: Entry not found."<<endl;
		return 1;
	}
	if(S.editor==""){
		cerr<<"Error: No editor specified."<<endl;
		return 2;
	}
	command=S.editor+" "+filename;
	
	system(command.c_str());
	
	return create(S,id);
}


int comment(settings &S,ID id,string filename){
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		if(it->id()==id){
			it->new_comment(filename,S);
			return create(S,id);
		}
	}
	cerr<<"Not found"<<endl;
	return 1;
}

int edit_comment(settings &S, ID id){
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		if(it->id()==id){
			system((S.editor+" "+it->get_comments_filename()).c_str());
			return create(S,id);
		}
	}
	cerr<<"Not found"<<endl;
	return 1;
}


int list_entries(settings &S){
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	for(deque<blogentry>::reverse_iterator it=data.rbegin();it!=data.rend();++it){
		cout<<it->get_id()<<":\t"<<it->get_heading()<<"\n";
	}
	cout<<flush;
	return 0;
}
