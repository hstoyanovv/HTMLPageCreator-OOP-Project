#ifndef Heading_H
#define Heading_H
#include "Tag.h"

class Heading:public Tag
{
private:
	char* hSize;
	void clear();
public:
	Heading();
	Heading(const char* hSize, const char* description, const char* content);
	Heading(const Heading & rhs);
	Heading & operator=(const Heading & rhs);
	virtual Tag* clone() const;
	virtual void SaveInHTML(std::ofstream & file);
	virtual ~Heading();
	void SethSize(const char* hSize);
};

#endif
