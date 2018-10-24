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

}
