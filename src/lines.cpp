#include "lines.hpp"

#include <stdexcept>
#include <iostream>
using namespace std;

string clean_whitespace(string str){
	unsigned int i=0;
	while(str[i]==' '||str[i]=='\t'){
		++i;
	}
	str.erase(0,i);
	return str;
}

string clean_whitespace_both_sides(string str){
	str=clean_whitespace(str);
	size_t n=str.size();
	for(string::reverse_iterator it=str.rbegin();*it==' '||*it=='\t';++it){
		--n;
	}
	if(n<str.size()){
		str.erase(n-1);
	}
	return str;
}

pair<string,string> cut(string line,string divider){
	pair<string,string> PAIR;
	size_t pos=line.find(divider);
	PAIR.first=clean_whitespace(line.substr(0,pos));
	PAIR.second=clean_whitespace(line.substr(pos+divider.size()));
	return PAIR;
}

deque<string> cut_words(string line){
	return cut_fields(line," ");
}


deque<string> cut_fields(string line,string divider){
	size_t pos;
	deque<string> data;
	while((pos=line.find(divider))!=string::npos){
		data.push_back(line.substr(0,pos));
		line=line.substr(pos+1);
		line=clean_whitespace(line);
	}
	if(!line.empty()){
		data.push_back(line);
	}
	return data;
}



string replace(string str,string old_phrase,string new_phrase){
	size_t pos, l_old(old_phrase.size());
	pos=str.find(old_phrase);
	string returnstr="";
	while(pos!=string::npos){
		returnstr+=str.substr(0,pos)+new_phrase;
		str=str.substr(pos+l_old);
		pos=str.find(old_phrase);
	}
	returnstr+=str;
	return returnstr;
}

string remove_double_spaces(string str){
	return replace(str,"  "," ");
}

LINES operator+(LINES L1, LINES L2){
	return (L1+=L2);
}
LINES operator+=(LINES &L1, LINES L2){
	for(LINES::iterator it=L2.begin();it!=L2.end();++it){
		L1.push_back(*it);
	}
	return L1;
}


LINES push_string_to_front_of_every_line(LINES L, string str){
	for(LINES::iterator it=L.begin();it!=L.end();++it){
		it->insert(0,str);
	}
	return L;
}

deque<string> operator+=(deque<string> &L1,deque<string> L2){
	for(deque<string>::iterator it=L2.begin();it!=L2.end();++it){
		L1.push_back(*it);
	}
	return L1;
}


deque<string> operator+=(deque<string> &L1,string str){
	L1.push_back(str);
	
	return L1;
}


list<string>operator+=(list<string> &L1,deque<string> L2){
	for(deque<string>::iterator it=L2.begin();it!=L2.end();++it){
		L1.push_back(*it);
	}
	return L1;
}


/*
list<string>operator+=(list<string> &L1,list<string> L2){
	for(list<string>::iterator it=L2.begin();it!=L2.end();++it){
		L1.push_back(*it);
	}
	return L1;
}
*/

/*
LINES operator+=(LINES &L1,list<string> L2){
	for(list<string>::iterator it=L2.begin();it!=L2.end();++it){
		L1.push_back(*it);
	}
	return L1;
}
*/


void replace(LINES &L, string old_phrase, string new_phrase){
	for(LINES::iterator it=L.begin();it!=L.end();++it){
		*it=replace(*it,old_phrase,new_phrase);
	}
}




string escape_html(string str,bool escape_quotation_mark){
	str=replace(str,"&","&amp;");
	str=replace(str,"<","&lt;");
	str=replace(str,">","&gt;");
	if(escape_quotation_mark){
		str=replace(str,"'","&#39;");
		str=replace(str,"\"","&quot;");
	}
	return str;
}

string unescape_html(string str){
	str=replace(str,"&amp;","&");
	str=replace(str,"&lt;","<");
	str=replace(str,"&gt;",">");
	str=replace(str,"&#39;","'");
	str=replace(str,"&quot;","\"");
	return str;
}



map<string,string> parse_xml_tag_args(string str){
	size_t pos;
	string key, value;
	map<string,string> returnmap;
	if(str[0]=='<'){
		str.erase(0,1);
	}
	if (((pos=str.find(' '))!=string::npos)&&(str.find('=')>pos)){
		str.erase(0,pos+1);
	}
	while((pos=str.find('='))!=string::npos){
		str=clean_whitespace(str);
		pos=str.find('=');
		key=str.substr(0,pos);
		str.erase(0,pos+1);
		if(str[0]=='\''){
			str.erase(0,1);
			pos=str.find('\'');
			value=str.substr(0,pos);
			str.erase(0,pos+1);
		}
		else if(str[0]=='"'){
			str.erase(0,1);
			pos=str.find('"');
			value=str.substr(0,pos);
			str.erase(0,pos+1);
		}
		else{
			throw logic_error("invalid xml-arguments");
		}
		returnmap[key]=value;
	}
	return returnmap;
}

