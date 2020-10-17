#include "Heading.h"

void Heading::clear()
{
	delete[] hSize;
	hSize = nullptr;
}

Heading::Heading() : hSize(nullptr)
{
}

Heading::Heading(const char * hSize, const char* description, const char* content) : hSize(nullptr), Tag(description,content)
{
	SethSize(hSize);
}

Heading::Heading(const Heading & rhs) :hSize(nullptr)
{
	Tag::copyFrom(rhs);
	SethSize(rhs.hSize);
}

Heading & Heading::operator=(const Heading & rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);
		clear();
		SethSize(rhs.hSize);
	}

	return *this;
}

Tag * Heading::clone() const
{
	return new Heading(*this);
}

void Heading::SaveInHTML(std::ofstream & file)
{
	file << '<' << hSize << " descr=" << '"' << description << '"' << '>' << content << "</" << hSize << ">\n";
	file << "<br>\n";
}

Heading::~Heading()
{
	clear();
}

void Heading::SethSize(const char * hSize)
{
	int len = strlen(hSize) + 1;
	this->hSize = new char[len];
	strcpy_s(this->hSize, len, hSize);
}
