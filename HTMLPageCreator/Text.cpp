#include "Text.h"

Text::Text(const char * description, const char * content) : Tag(description,content)
{
}

Tag * Text::clone() const
{
	return new Text(*this);
}

void Text::SaveInHTML(std::ofstream & file)
{
	file << "<p descr=" << '"' << description << '"' << '>' << content << "</p>\n";
	file << "<br>\n";
}
