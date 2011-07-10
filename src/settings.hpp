#ifndef __settings_blog__
#define __settings_blog__

#include <string>
#include <deque>

#include "id.hpp"

using std::string;
using std::deque;

///SETTINGS:
const string GLOBAL_EASYBLOGGER_CONFIG_FILE="/etc/easyblogger.conf";
const string DEFAULT_INDICATOR="_DEFAULT_";

const string BEGIN_BLOG_CONFIG="BEGINBLOG";
const string END_BLOG_CONFIG="ENDBLOG";

struct settings{
	string settingsdir;
	string datadir;
	string header;
	string footer;
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
	int number_of_mainpageposts;
	int max_date_size;
	ID last_id;
};

settings read_settings(string filename);

settings get_blog_by_name(string name=DEFAULT_INDICATOR);

string get_blog_conf_file(string name=DEFAULT_INDICATOR);

#endif
