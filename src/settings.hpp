#ifndef __settings_blog__
#define __settings_blog__

#include <string>
#include <deque>
#include <list>
#include <map>

#include "id.hpp"

using std::string;
using std::deque;
using std::list;

///SETTINGS:
#ifdef __unix__
const string GLOBAL_EASYBLOGGER_CONFIG_FILE="/etc/easyblogger.conf";
#elif defined _WIN32
const string GLOBAL_EASYBLOGGER_CONFIG_FILE="C:\\windows\\system32\\easyblogger.conf";
#else
const string GLOBAL_EASYBLOGGER_CONFIG_FILE="/etc/easyblogger.conf";
#endif


const string DEFAULT_INDICATOR="_DEFAULT_";

const string BEGIN_BLOG_CONFIG="BEGINBLOG";
const string END_BLOG_CONFIG="ENDBLOG";

class blogentry;

struct settings{
	string template_file;
	string name;
	string settingsdir;
	string datadir;
	string blog;
	string list_of_entries;
	string single_entries_dir;
	string single_entries_dir_rel;
	string url;
	string title;
	string rss_feed;
	string rss_channel_description_file;
	string editor;
	string public_path_to_comment_function;
	string name_of_link_to_comment;
	string comment_section_heading;
	string comment_url;
	string comment_name;
	string locale;
	string time_format;
	string toc_title;
	string toc_pre;
	string toc_post;
	string mainpage_toc_title;
	string mainpage_toc_pre;
	string mainpage_toc_post;
	int number_of_mainpageposts;
	int max_date_size;
	bool enable_comments;
	bool toc_in_singleentries;
	bool sorting_by_date;
	ID last_id;
	
	list<blogentry*> blogentries;
	map<string,list<blogentry*> > tags;
	
	
	~settings();
};

settings read_settings(string filename);

settings get_blog_by_name(string name=DEFAULT_INDICATOR);

string get_blog_conf_file(string name=DEFAULT_INDICATOR);

#endif
