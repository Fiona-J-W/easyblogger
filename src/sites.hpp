//      sites.hpp
//      
//      Copyright 2011 Florian Weber <florian@mars>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      


#ifndef SITES_HPP
#define SITES_HPP

#include "page.hpp"
#include "settings.hpp"
#include "id.hpp"


int create_all(settings S);
int create_latest(settings S);
int create(settings S,ID id);

int import(settings S,string filename);
int comment(settings S,ID id,string filename);
int edit(settings S, ID id);

#endif /* SITES_HPP */ 
