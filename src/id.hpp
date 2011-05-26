//      id.hpp
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


#ifndef ID_HPP
#define ID_HPP

#include <string>

using namespace std;

class ID
{
	public:
		ID();
		ID(string id);
		string get();
		void read_file(string filename);
		void set(string id);
		void save();
		void save(string filename);
		ID str_to_id(string str);
		ID operator++();
		ID operator--();
		bool operator ==(ID id);
	private:
		string m_name;
		int m_num;
		int m_num_length;
		string m_filename;
};

#endif /* ID_HPP */ 
