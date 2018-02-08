#include "stdafx.h"
#include "PropertiesUtils.h"

namespace cppproperties {
	namespace PropertiesUtils {

		namespace {
			const string TRIM_DELIMITERS = " \f\n\r\t\v";
			string ltrim(const string& str) {
				string::size_type s = str.find_first_not_of(TRIM_DELIMITERS);
				if (s == string::npos) {
					return "";
				}
				return str.substr(s);
			}
		}

		string RightTrim(const string& str) {
			string::size_type s = str.find_last_not_of(TRIM_DELIMITERS);
			if (s == string::npos) {
				return "";
			}
			return str.substr(0, s + 1);
		}

		string LeftTrim(const string& str) {
			string rstr = ltrim(str);

			while (rstr != ltrim(rstr)) {
				rstr = ltrim(rstr);
			}

			return rstr;
		}

		string Trim(const string& str) {
			return RightTrim(LeftTrim(str));
		}

		bool IsProperty(const string& str) {
			string trimmedStr = LeftTrim(str);
			string::size_type s = trimmedStr.find_first_of("=");
			if (s == string::npos) {
				return false;
			}
			string key = Trim(trimmedStr.substr(0, s));
			// key can't be empty
			if (key == "") {
				return false;
			}
			return true;
		}

		pair<string, string> ParseProperty(const string& str) {
			string trimmedStr = LeftTrim(str);
			string::size_type s = trimmedStr.find_first_of("=");
			string key = Trim(trimmedStr.substr(0, s));
			string value = LeftTrim(trimmedStr.substr(s + 1));

			return pair<string, string>(key, value);
		}

		bool isComment(const string& str) {
			string trimmedStr = LeftTrim(str);
			return trimmedStr[0] == '#';
		}

		bool IsEmptyLine(const string& str) {
			string trimmedStr = LeftTrim(str);
			return trimmedStr == "";
		}

	} // namespace PropertiesUtils
} // namespace cppproperties

