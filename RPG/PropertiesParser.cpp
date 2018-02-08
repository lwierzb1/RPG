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

	Properties PropertiesParser::Read(const string& file) {
		Properties properties;

		ifstream is;
		is.open(file.c_str());
		if (!is.is_open()) {
			string msg = "Unable to read " + file;
			throw PropertiesException(msg.c_str());
		}

		try {
			string line;
			while (getline(is, line)) {
				if (PropertiesUtils::IsEmptyLine(line) || PropertiesUtils::isComment(line)) {
					// ignore it
				}
				else if (PropertiesUtils::IsProperty(line)) {
					pair<string, string> prop = PropertiesUtils::ParseProperty(line);
					properties.AddProperty(prop.first, prop.second);
				}
				else {
					string msg = "Invalid line: " + line;
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
	vector<string> PropertiesParser::Split(const string & s, char delim[])
	{
		stringstream ss(s);
		string item, finalItem;
		vector<string> elems;
		int x = strlen(delim);
		if (strlen(delim) == 2)
			while (getline(ss, item, delim[0])) {
				stringstream s1(item);
				while(getline(s1, finalItem, delim[1]))
				elems.push_back(finalItem);
				// elems.push_back(move(item)); // if C++11 (based on comment from @mchiasson)
			}
		else
			while (getline(ss, item, delim[0])) {
					elems.push_back(item);
				// elems.push_back(move(item)); // if C++11 (based on comment from @mchiasson)
		}
		return elems;
	}
	void PropertiesParser::Write(const string& file, const Properties& props) {
		Properties pro;

		fstream os;
		os.open(file.c_str());
		if (!os.is_open()) {
			string msg = "Unable to write " + file;
			throw PropertiesException(msg.c_str());
		}

		try {
			pro = Read(file);
			vector<string> names = pro.getPropertyNames(); //read existing keys 
			
			const vector<string>& keys = props.getPropertyNames();
			
			for (vector<string>::const_iterator i = keys.begin(); i != keys.end(); ++i) 
				pro.AddProperty((*i), props.getProperty(*i)); // add/update new keys
			
			names = pro.getPropertyNames(); // update vector of keys with new elements needed for loop iteration
			
			for (vector<string>::const_iterator i = names.begin(); i != names.end(); ++i) 
				os << *i << " = " << pro.getProperty(*i) << endl; //print to file
			
			os.close();
		}
		catch (...) {
			// don't forget to close the ofstream
			os.close();
			throw;
		}
	}

} /* namespace cppproperties */