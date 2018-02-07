#pragma once
#include <string>
#include <exception>
#include "Properties.h"
#include "stdafx.h"
namespace cppproperties {

	class PropertiesParser {
	public:
		PropertiesParser();
		virtual ~PropertiesParser();

		/**
		* Reads a properties file and returns a Properties object.
		*/
		static Properties Read(const std::string& file);

		/**
		* Writes Properties object to a file.
		*/
		static void Write(const std::string& file, const Properties& props);
		static std::vector<std::string> Split(const std::string &s, char delim[]);
	};

} /* namespace cppproperties */

