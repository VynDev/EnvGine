/*
 * Author: Vyn
 * Created: 2020-07-21 12:40
 * Modified: 2020-07-25 06:52
 */

#pragma once
#include <exception>
#include <string>

namespace EnvGine {

	inline std::string methodName(const std::string &prettyFunction)
	{
		size_t colons = prettyFunction.find("::");
		size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
		size_t end = prettyFunction.rfind("(") - begin;

		return prettyFunction.substr(begin,end) + "()";
	}

	#define __ENVGINE_METHOD_NAME__ EnvGine::methodName(__PRETTY_FUNCTION__)
	
	class Exception : public std::exception {

		private:

		std::string reason;

		public:
		
		Exception(std::string methodName, std::string message) {
			this->reason = methodName + " " + message;
		}

		virtual const char* what() const noexcept {
			return reason.c_str();
		}
	};
}

#define Exception(message) Exception(__ENVGINE_METHOD_NAME__, message)