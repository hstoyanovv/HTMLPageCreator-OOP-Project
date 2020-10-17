#ifndef Image_H
#define Image_H
#include "Tag.h"

class Image :public Tag
{
public:
	Image(const char* description, const char* content);
	virtual Tag* clone() const;
	virtual void SaveInHTML(std::ofstream & file);
};

#endif