#include "comments.hpp"

#include <ctime>
#include <map>
using namespace std;

const string DEFAULT_COMMENT_AUTHOR=string("Anonymous");
const string COMMENT_AUTHOR_SETTER=string("#AUTHOR=");

comments::comments(){
	m_loaded=false;
}

comments::comments(string filename){
	m_loaded=false;
	m_filename=filename;
}

void comments::read_from_file(){
	LINES lines=read_file(m_filename);
	bool commentsection=false;
	string author, date;
	LINES tmp;
	for(LINES::iterator it=lines.begin();it!=lines.end();++it){
		if(commentsection){
			if(it->find('<')!=string::npos){
				if(it->find("</comment>")!=string::npos){
					commentsection=false;
					m_comments.push_back(comment(author,str_to_time(date),tmp));
					tmp.clear();
				}
			}
			else{
				tmp.push_back(unescape_html(*it));
			}
		}
		else{
			if(it->find("<comment")!=string::npos){
				map<string,string> args=parse_xml_tag_args(*it);
				author=args["author"];
				date=args["date"];
				if(author.size()){
					author=DEFAULT_COMMENT_AUTHOR;
				}
				commentsection=true;
			}
		}
	}
}



int comments::import_from_file(string filename){
	LINES raw_data=read_file(filename),data;
	string author=DEFAULT_COMMENT_AUTHOR,tmp;
	tm time=get_time();
	bool p_open=false;
	if(raw_data.begin()->find(COMMENT_AUTHOR_SETTER)==0){
		author=escape_html(cut(raw_data.front(),"=").second,true);
		raw_data.erase(raw_data.begin());
	}
	for(LINES::iterator it=raw_data.begin();it!=raw_data.end();++it){
		tmp=clean_whitespace(*it);
		if(p_open){
			if(tmp.empty()){
				p_open=false;
				data.push_back("</p>");
			}
			else{
				data.push_back(escape_html(tmp));
			}
		}
		else{
			if(tmp.empty()){
				continue;
			}
			else{
				p_open=true;
				data.push_back("<p>"+escape_html(tmp));
			}
		}
	}
	if(p_open){
		data.push_back("</p>");
	}
	m_comments.push_back(comment(author,time,data));
	save();
	return 0;
}


void comments::save(){
	LINES output;
	for(list<comment>::iterator it=m_comments.begin();it!=m_comments.end();++it){
		LINES tmp=it->get_save_format();
		for(LINES::const_iterator it=tmp.begin();it!=tmp.end();++it){
			output.push_back(*it);
		}
	}
	write_file(m_filename,output);
}


LINES comments::get_html(settings &S){
	LINES returnval;
	//returnval.push_back("<ul class=\"comments\">");
	for(list<comment>::iterator it=m_comments.begin();it!=m_comments.end();++it){
		LINES tmp=it->get_html(S);
		for(LINES::const_iterator it=tmp.begin();it!=tmp.end();++it){
			returnval.push_back(*it);
		}
	}
	//returnval.push_back("</ul>");
	return returnval;
}


void comments::set_filename(string filename){
	m_filename=filename;
}