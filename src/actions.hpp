//      sites.hpp
//      
//      Copyright 2011 Florian Weber <florian.weber@sfz-bw.de>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU Affero General Public License as published by
//      the Free Software Foundation; either version 3 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU Affero General Public License for more details.
//      
//      You should have received a copy of the GNU Affero General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      


#ifndef __ACTIONS_HPP__
#define __ACTIONS_HPP__

#include "page.hpp"
#include "settings.hpp"
#include "id.hpp"

///recreates all posts and the mainpage:
int create_all(settings &S);

///recreates all posts, that are shown on the mainpage and the mainpage:
int create_latest(settings &S);

///recreates the post with the ID id; if the post is shown on the mainpage
///create_latest() will be called:
int create(settings &S,ID id);

///create RSS-feed:
int create_rss(settings &S);

///create RSS-feeds for every tag, if this is configured
int create_tag_rss(settings &S);

///create RSS-feeds for all given tags:
int create_tag_rss(settings &S, deque<string> tags);

///create a new posting; the content has to stand within the given file
int import(settings &S,string filename);

///add a comment for a post; the comment has to be in the given file
///WARNING: This won't search for security problems. Do this part in PHP
///or your language of choice:
int comment(settings &S,ID id,string filename);

///edit a post with the ID id:
int edit(settings &S, ID id);

///edit the comments of the post with the ID id:
int edit_comment(settings &S, ID id);

///list all existing entries:
int list_entries(settings &S);

///search in all blogentries for phrase
list<blogentry*> search(settings &S,string phrase);

int print_search(settings &S,string phrase);

int print_html_search(settings &S,string phrase);

#endif /* __ACTIONS_HPP__ */ 
