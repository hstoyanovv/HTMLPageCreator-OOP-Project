#ifndef Video_H
#define Video_H
#include "Tag.h"

class Video:public Tag
{
public:
	Video(const char* description, const char* content);
	virtual Tag* clone() const;
	virtual void SaveInHTML(std::ofstream & file);
};

#endif
