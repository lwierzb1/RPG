#include "stdafx.h"
#include "Properties.h"
#include <algorithm>

namespace cppproperties {

	Properties::Properties() {
	}

	Properties::~Properties() {
	}

	string Properties::getProperty(const string& key) const {
		if (properties.find(key) == properties.end()) {
			string msg = key + " does not exist";
			throw PropertyNotFoundException(msg.c_str());
		}
		return properties.at(key);
	}

	string Properties::getProperty(const string& key, const string& defaultValue) const {
		if (properties.find(key) == properties.end()) {
			return defaultValue;
		}
		return properties.at(key);
	}

	vector<string> Properties::getPropertyNames() const {
		return keys;
	}

	void Properties::AddProperty(const string& key, const string& value) {
		if (properties.find(key) == properties.end()) {
			keys.push_back(key);
		}
		properties[key] = value;
	}

	void Properties::RemoveProperty(const string& key) {
		if (properties.find(key) == properties.end()) {
			string msg = key + " does not exist";
			throw PropertyNotFoundException(msg.c_str());
		}
		keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
		properties.erase(key);
	}
	bool Properties::stringToBool(string var)
	{
		if (var == "true")
			return true;
		else 
			return false;
	}

} /* namespace cppproperties */
