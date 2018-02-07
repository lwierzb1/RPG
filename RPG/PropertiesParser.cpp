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
				if (PropertiesUtils::IsEmptyLine(line) || PropertiesUtils::isComment(line)) {
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
	std::vector<std::string> PropertiesParser::Split(const std::string & s, char delim[])
	{
		std::stringstream ss(s);
		std::string item, finalItem;
		std::vector<std::string> elems;
		int x = strlen(delim);
		if (strlen(delim) == 2)
			while (std::getline(ss, item, delim[0])) {
				std::stringstream s1(item);
				while(std::getline(s1, finalItem, delim[1]))
				elems.push_back(finalItem);
				// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
			}
		else
			while (std::getline(ss, item, delim[0])) {
					elems.push_back(item);
				// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
		}
		return elems;
	}
	void PropertiesParser::Write(const std::string& file, const Properties& props) {
		Properties pro;

		std::fstream os;
		os.open(file.c_str());
		if (!os.is_open()) {
			std::string msg = "Unable to write " + file;
			throw PropertiesException(msg.c_str());
		}

		try {
			pro = Read(file);
			std::vector<std::string> names = pro.getPropertyNames(); //read existing keys 
			
			const std::vector<std::string>& keys = props.getPropertyNames();
			
			for (std::vector<std::string>::const_iterator i = keys.begin(); i != keys.end(); ++i) 
				pro.AddProperty((*i), props.getProperty(*i)); // add/update new keys
			
			names = pro.getPropertyNames(); // update vector of keys with new elements needed for loop iteration
			
			for (std::vector<std::string>::const_iterator i = names.begin(); i != names.end(); ++i) 
				os << *i << " = " << pro.getProperty(*i) << std::endl; //print to file
			
			os.close();
		}
		catch (...) {
			// don't forget to close the ofstream
			os.close();
			throw;
		}
	}

} /* namespace cppproperties */