
#include "files.hpp"
#include "lines.hpp"
#include <fstream>

#include <iostream>

using namespace std;



LINES read_file(string filename){
	list<string> data=read_file_to_list(filename);
	LINES returndata;
	returndata.resize(data.size());
	int pos=0;
	for(list<string>::iterator it=data.begin();it!=data.end();++it){
		returndata[pos]=*it;
		++pos;
	}
	return returndata;

}


list<string> read_file_to_list(string filename){
	ifstream file;
	list<string> content;
	string line;
	file.open(filename.c_str());
	while(getline(file,line)){
		content.push_back(line);
	}
	return content;
}

LINES read_config_file(string filename){
	LINES content=read_file(filename),lines;
	string line;
	for(LINES::iterator it=content.begin();it!=content.end();++it){
		line=*it;
		line=clean_whitespace(line);
		if(line.empty()||line[0]=='#'){
			continue;
		}
		else{
			lines.push_back(line);
		}
	}
	return lines;
}

int write_file(string filename, LINES data){
	ofstream file;
	file.open(filename.c_str());
	if(!file.is_open()){
		return 1;
	}
	for(LINES::iterator it=data.begin();it!=data.end();++it){
		file<<*it<<"\n";
	}
	file.close();
	return 0;
}


int write_file(string filename, list<string> data){
	ofstream file;
	file.open(filename.c_str());
	if(!file.is_open()){
		return 1;
	}
	for(list<string>::iterator it=data.begin();it!=data.end();++it){
		file<<*it<<"\n";
	}
	file.close();
	return 0;
}

int write_file(string filename, string data){
	ofstream file;
	file.open(filename.c_str());
	if(!file.is_open()){
		return 1;
	}
	file<<data;
	file.close();
	return 0;
}

int insert_into_file(string filename, string line,int pos){
	LINES data=read_file(filename);
	LINES::iterator it=data.begin();
	it+=pos;
	data.insert(it,line);
	return write_file(filename,data);
}


int insert_to_begin_of_file(string filename, string line){
	LINES data=read_file(filename);
	data.push_front(line);
	return write_file(filename,data);
}
