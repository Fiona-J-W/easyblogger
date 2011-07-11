#include "lines.hpp"

string clean_whitespace(string str){
	while(str[0]==' '||str[0]=='\t'){
		str=str.substr(1);
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
	data.push_back(line);
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
