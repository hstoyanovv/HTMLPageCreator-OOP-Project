#include "Video.h"

Video::Video(const char * description, const char * content) : Tag(description,content)
{
}

Tag * Video::clone() const
{
	return new Video(*this);
}

void Video::SaveInHTML(std::ofstream & file)
{
	file << "<iframe src=" << '"' << content << '"' << " descr=" <<'"'<< description <<'"' << '>' << "</iframe>\n";
	file << "<br>\n";
}
