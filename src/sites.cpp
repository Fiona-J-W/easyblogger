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


#include "sites.hpp"
#include "blogentry.hpp"
#include "date.hpp"
#include "files.hpp"
#include "lines.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

int create_all(settings S){
	deque<blogentry> data=read_entries(S.list_of_entries,true);
	string filename;
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		filename=S.single_entries_dir+it->get_id()+".html";
		//cout<<filename<<endl;
		write_page(*it,S,filename);
		
	}
	if(S.number_of_mainpageposts<=-1||int(data.size())<=S.number_of_mainpageposts){
		write_page(data,S,S.blog);
	}
	else{
		deque<blogentry> mainpageposts;
		for(int i=0;i<S.number_of_mainpageposts;++i){
			mainpageposts.push_back(data[i]);
		}
		write_page(mainpageposts,S,S.blog);
	}
	return 0;
}

int create_latest(settings S){
	if(S.number_of_mainpageposts<0){
		return create_all(S);
	}
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	deque<blogentry> mainpageposts;
	string filename;
	for(int i=0;i<S.number_of_mainpageposts&&i<=int(data.size());++i){
		data.at(i).read_content();
		filename=S.single_entries_dir+data.at(i).get_id()+".html";
		write_page(data.at(i),S,filename);
		mainpageposts.push_back(data.at(i));
	}
	write_page(mainpageposts,S,S.blog);
	return 0;
}

int create(settings S,ID id){
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

int import(settings S,string filename){
	string heading, date, new_file, new_comment_file, dataline;
	LINES data=read_file(filename);
	date=get_localdate();
	if(data.size()>0&&data[0].find("#HEADING=")==0){
		heading=cut(data[0],"=").second;
		data.erase(data.begin());
	}
	while(heading==""){
		cout<<">>> ";
		getline(cin,heading);
	}
	++S.last_id;
	new_file=S.datadir+S.last_id.get()+".html";
	new_comment_file=S.datadir+S.last_id.get()+"-comments.html";
	dataline= new_file+"\t"+date+"\t"+heading+"\t"+S.last_id.get()+"\t"+new_comment_file;
	insert_to_begin_of_file(S.list_of_entries,dataline);
	//cout<<dataline<<endl;
	write_file(new_file,data);
	cout<<S.last_id.get()<<": "<<heading<<endl;
	return create_latest(S);
}


int edit(settings S, ID id){
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


int comment(settings S,ID id,string filename){
	deque<blogentry> data=read_entries(S.list_of_entries,false);
	for(deque<blogentry>::iterator it=data.begin();it!=data.end();++it){
		if(it->id()==id){
			it->new_comment(filename);
			return create(S,id);
		}
	}
	cout<<"Not found"<<endl;
	return 1;
}
