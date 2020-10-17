#include "HyperLink.h"

void HyperLink::clear()
{
	delete[] text;
	text = nullptr;
}

HyperLink::HyperLink() : text(nullptr)
{
}

HyperLink::HyperLink(const HyperLink & rhs) : text(nullptr)
{
	copyFrom(rhs);
	SetText(rhs.text);
}

HyperLink & HyperLink::operator=(const HyperLink & rhs)
{
	if(this != &rhs)
	{
		Tag::operator=(rhs);
		clear();
		SetText(rhs.text);
	}

	return *this;
}

HyperLink::~HyperLink()
{
	clear();
}

HyperLink::HyperLink(const char * description, const char * content, const char* text) : text(nullptr),Tag(description,content)
{
	SetText(text);
}

Tag * HyperLink::clone() const
{
	return new HyperLink(*this);
}

void HyperLink::SaveInHTML(std::ofstream & file)
{
	file << "<a href=" << '"' << content << '"' << " descr=" << '"' << description << '"' << '>' << text << "</a>\n";
	file << "<br>\n";
}

void HyperLink::SetText(const char * txt)
{
	int len = strlen(txt) + 1;
	text = new char[len];
	strcpy_s(text, len, txt);
}

const char * HyperLink::GetText() const
{
	return text == nullptr? "" : text;
}
