#include "comment.hpp"

LINES comment::get_html(settings &S){
	LINES returnval;
	returnval.push_back("<li class=\"comment\">");
	returnval.push_back("<p><strong>"+m_author+"</strong> ("+format_time(m_date,S.time_format,S.locale)+"):</p>");
	for(LINES::const_iterator it=m_data.begin();it!=m_data.end();++it){
		returnval.push_back(*it);
	}
	returnval.push_back("</li>");
	return returnval;
}

void comment::set_data(LINES data){
	m_data=data;
}



LINES comment::get_save_format(){
	LINES returnval;
	returnval.push_back("<comment author='"+m_author+"' date=''>");
	for(LINES::const_iterator it=m_data.begin();it!=m_data.end();++it){
		returnval.push_back(escape_html(*it));
	}
	returnval.push_back("</comment>");
	return returnval;
}