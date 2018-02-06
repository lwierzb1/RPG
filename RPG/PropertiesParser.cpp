#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "PropertiesParser.h"
#include "PropertiesUtils.h"

namespace cppproperties {

	PropertiesParser::PropertiesParser() {
	}

	PropertiesParser::~PropertiesParser() {
	}

	Properties PropertiesParser::Read(const std::string& file) {
		Properties properties;

		std::ifstream is;
		is.open(file.c_str());
		if (!is.is_open()) {
			std::string msg = "Unable to read " + file;
			throw PropertiesException(msg.c_str());
		}

		try {
			std::string line;
			while (getline(is, line)) {
				if (PropertiesUtils::IsEmptyLine(line) || PropertiesUtils::IsComment(line)) {
					// ignore it
				}
				else if (PropertiesUtils::IsProperty(line)) {
					std::pair<std::string, std::string> prop = PropertiesUtils::ParseProperty(line);
					properties.AddProperty(prop.first, prop.second);
				}
				else {
					std::string msg = "Invalid line: " + line;
					throw PropertiesException(msg.c_str());
				}
			}
			is.close();
		}
		catch (...) {
			// don't forget to close the ifstream
			is.close();
			throw;
		}

		return properties;
	}
	std::vector<std::string> PropertiesParser::Split(const std::string & s, char delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
			// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
		}
		return elems;
	}
	void PropertiesParser::Write(const std::string& file, const Properties& props) {
		Properties pro;

		std::fstream os;
		os.open(file.c_str(),std::fstream::out);
		if (!os.is_open()) {
			std::string msg = "Unable to write " + file;
			throw PropertiesException(msg.c_str());
		}

		try {
			pro = Read(file);
			std::vector<std::string> names = pro.GetPropertyNames(); //read existing keys 
			
			const std::vector<std::string>& keys = props.GetPropertyNames();
			
			for (std::vector<std::string>::const_iterator i = keys.begin(); i != keys.end(); ++i) 
				pro.AddProperty((*i), props.GetProperty(*i)); // add/update new keys
			
			names = pro.GetPropertyNames(); // update vector of keys with new elements needed for loop iteration
			
			for (std::vector<std::string>::const_iterator i = names.begin(); i != names.end(); ++i) 
				os << *i << " = " << pro.GetProperty(*i) << std::endl; //print to file
			
			os.close();
		}
		catch (...) {
			// don't forget to close the ofstream
			os.close();
			throw;
		}
	}

} /* namespace cppproperties */