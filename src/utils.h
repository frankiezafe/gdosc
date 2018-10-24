#ifndef OSCUTILS_H
#define OSCUTILS_H

#include <cstdlib>
#include <iostream>

#include <Variant.hpp>
#include <String.hpp>

namespace utils {
	std::string gdStringToString(godot::String s);
	bool getBool( godot::Variant&, bool& );
	bool getInt( godot::Variant&, int& );
	bool getString( godot::Variant&, godot::String& );
}  // end namespace utils

#endif