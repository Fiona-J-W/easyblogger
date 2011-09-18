//      id.cpp
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

#include <cstdlib>
#include <cstdio>

#include "files.hpp"

#include "id.hpp"

#include <iostream>

using namespace std;

ID::ID(){
	
}

ID::ID(string id){
	set(id);
}

void ID::set(string id){
	*this=str_to_id(id);
	
}

string ID::get(){
	string returnstr=m_name;
	char *temp_str=new char[m_num_length+1];
	sprintf(temp_str,"%0*d",m_num_length,m_num);
	returnstr+=string(temp_str);
	delete temp_str;
	return returnstr;
}


void ID::read_file(string filename){
	LINES data=read_config_file(filename);
	if(data.empty()){
		throw string("ID-File empty");
	}
	*this=str_to_id(data[0]);
	m_filename=filename;
}

ID ID::str_to_id(string str){
	unsigned int i=str.size();
	for(string::reverse_iterator it=str.rbegin();it!=str.rend();++it){
		if(*it>='0'&&*it<='9'){
			--i;
		}
		else{
			break;
		}
	}
	m_name=str.substr(0,i);
	m_num=atoi(str.substr(i).c_str());
	m_num_length=int(str.substr(i).size());
	return *this;
}

ID ID::operator++(){
	++m_num;
	save();
	return *this;
}

ID ID::operator--(){
	--m_num;
	save();
	return *this;
}

void ID::save(){
	LINES tmp;
	tmp.push_back(get());
	write_file(m_filename,tmp);
	//cout << get()<<" >> "<<m_filename<<endl;
}

void ID::save(string filename){
	m_filename=filename;
	save();
}

bool ID::operator ==(ID id){
	if(m_num!=id.m_num)return false;
	if(m_name!=id.m_name)return false;
	return true;
}


bool ID::operator<(ID id){
	if(m_name==id.m_name){
		return (m_num<id.m_num);
	}
	else return (m_name<id.m_name);
}

bool ID::operator>(ID id){
	if(m_name==id.m_name){
		return (m_num>id.m_num);
	}
	else return (m_name>id.m_name);
}