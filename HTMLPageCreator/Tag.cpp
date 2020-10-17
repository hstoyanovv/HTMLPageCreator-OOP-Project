#include "Tag.h"

void Tag::copyFrom(const Tag & rhs)
{
	SetDescription(rhs.description);
	SetContent(rhs.content);
}

void Tag::clear()
{
	delete[] description;
	description = nullptr;
	delete[] content;
	content = nullptr;
}

Tag::Tag()
{
	description = nullptr;
	content = nullptr;
}

Tag::Tag(const char * description, const char * content) : description(nullptr), content(nullptr)
{
	SetDescription(description);
	SetContent(content);
}

Tag::Tag(const Tag & rhs) : description(nullptr), content(nullptr)
{
	copyFrom(rhs);
}

Tag & Tag::operator=(const Tag & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}

	return *this;
}

Tag::~Tag()
{
	clear();
}

void Tag::SetDescription(const char * desc)
{
	int len = strlen(desc) + 1;
	this->description = new char[len];
	strcpy_s(this->description, len, desc);
}

void Tag::SetContent(const char * cont)
{
	int len = strlen(cont) + 1;
	this->content = new char[len];
	strcpy_s(this->content, len, cont);
}

const char * Tag::GetDescription() const
{
	return description == nullptr ? "" : description;
}

const char * Tag::GetContent() const
{
	return content == nullptr ? "" : content;
}
