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
