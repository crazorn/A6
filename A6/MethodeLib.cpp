#include "MethodeLib.h"

void MethodeLib::erase_first_substr(std::string& org, std::string sub)
{
	size_t pos = org.find(sub);
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		org.erase(pos, sub.length());
	}
}

void MethodeLib::remove_xmltags(std::string& org, std::string tag)
{
	std::string open = "<" + tag + ">";
	std::string close = "</" + tag + ">";
	erase_first_substr(org, open);
	erase_first_substr(org, close);
}
