#include "Image.h"

Image::Image(const char * description, const char * content) : Tag(description,content)
{
}

Tag * Image::clone() const
{
	return new Image(*this);
}

void Image::SaveInHTML(std::ofstream & file)
{
	file << "<img src=" << '"' << content << '"' << " descr=" <<'"'<< description <<'"'<< ">\n";
	file << "<br>\n";
}
