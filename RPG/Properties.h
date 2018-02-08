#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
namespace cppproperties {

	class PropertiesException : public std::exception {
	public:
		PropertiesException(const char* msg) throw() : message(msg) {}
		virtual ~PropertiesException() throw() {}

		virtual const char* what() const throw() { return message; }
	private:
		const char* message;
	};

	class PropertyNotFoundException : public std::exception {
	public:
		PropertyNotFoundException(const char* msg) throw() : message(msg) {}
		virtual ~PropertyNotFoundException() throw() {}

		virtual const char* what() const throw() { return message; }
	private:
		const char* message;
	};

	class Properties {
	public:
		Properties();
		virtual ~Properties();

		/**
		* gets the property value from a given key.
		*
		* This method throws a PropertyNotFoundException when a given key does not
		* exist.
		*/
		std::string getProperty(const std::string& key) const;

		/**
		* gets the property value from a given key. Use a default value if not found.
		*/
		std::string getProperty(const std::string& key, const std::string& defaultValue) const;

		/**
		* gets the list of property names.
		*/
		std::vector<std::string> getPropertyNames() const;

		/**
		* Adds a new property. If the property already exists, it'll overwrite
		* the old one.
		*/
		void AddProperty(const std::string& key, const std::string& value);

		/**
		* Removes the property from a given key.
		*
		* If the property doesn't exist a PropertyNotFoundException will be thrown.
		*/
		void RemoveProperty(const std::string& key);
		bool stringToBool(std::string var);
	private:
		// to preserve the order
		std::vector<std::string> keys;
		std::map<std::string, std::string> properties;
	};

} /* namespace cppproperties */

