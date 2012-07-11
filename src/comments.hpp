#ifndef comments_hpp
#define comments_hpp

#include <string>
#include <list>
using namespace std;

#include "files.hpp"
#include "lines.hpp"
#include "comment.hpp"
#include "settings.hpp"

class blogentry;

class comments{
public:
	comments();
	comments(string filename);
	
	void read_from_file();
	int import_from_file(string filename);
	void save();
	void set_filename(string filename);
	LINES get_html(settings &S);
	
private:
	bool m_loaded;
	string m_filename;
	list<comment> m_comments;
};


#endif