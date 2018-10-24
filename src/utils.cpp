#include "utils.h"

namespace utils {
	
	std::string gdStringToString(godot::String s) {
		/*
		std::wstring ws(s.c_str());
		std::string _ret(ws.begin(), ws.end());
		*/
		std::string _ret( s.alloc_c_string() );
		return _ret;
	}
	
	bool getBool( godot::Variant& v, bool& b ) {
		switch ( v.get_type() ) {
			case godot::Variant::BOOL:
				b = v;
				return true;
			case godot::Variant::INT:
			case godot::Variant::REAL:
				{
					int i = v;
					if ( i > 0 ) {
						b = true;
					} else {
						b = false;
					}
				}
				return true;
			case godot::Variant::STRING:
				{
					godot::String s = v;
					s = s.to_lower();
					if ( s.match('1') || s.match('y') || s.match('yes') || s.match('true') ) {
						b = true;
					} else {
						b = false;
					}
				}
				return true;
		}
		return false;
	}
	
	bool getInt( godot::Variant& v, int& i ) {
		switch ( v.get_type() ) {
			case godot::Variant::INT:
			case godot::Variant::REAL:
				i = v;
				return true;
		}
		return false;
	}
	
	bool getString( godot::Variant& v, godot::String& s ) {
		switch ( v.get_type() ) {
			case godot::Variant::STRING:
				s = v;
				return true;
		}
		return false;
	}

}
