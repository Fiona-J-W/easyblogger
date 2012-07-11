#ifndef comment_hpp
#define comment_hpp

#include <string>
#include <ctime>
using namespace std;

#include "date.hpp"
#include "lines.hpp"
#include "settings.hpp"



//const string DEFAULT_COMMENT_AUTHOR="Anonymous";

class comment{
public:
	comment()=default;
	comment(string author,tm date=tm(), LINES data=LINES()): m_author(author), m_date(date), m_data(data){}
	
	LINES get_html(settings &S);
	LINES get_save_format();
	void set_data(LINES data);
	void set_author(string author);
	void set_time(tm time);
	
private:
	string m_author;
	tm m_date;
	LINES m_data;
	
};


#endif