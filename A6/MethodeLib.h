#pragma once
#include <string>
class MethodeLib
{
public:
	static void erase_first_substr(std::string& org, std::string sub);
	static void remove_xmltags(std::string& org, std::string tag);
private:
	//static class
	MethodeLib() {}
};

