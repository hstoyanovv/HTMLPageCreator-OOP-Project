#ifndef Text_H
#define Text_H
#include "Tag.h"

class Text :public Tag
{
public:
	Text(const char* description, const char* content);
	virtual Tag* clone() const;
	virtual void SaveInHTML(std::ofstream & file);
};

#endif
