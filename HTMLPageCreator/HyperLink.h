#ifndef HyperLink_H
#define HyperLink_H
#include "Tag.h"

class HyperLink : public Tag
{
private:
	char* text;
	void clear();
public:
	HyperLink();
	HyperLink(const HyperLink & rhs);
	HyperLink & operator=(const HyperLink & rhs);
	virtual ~HyperLink();
	HyperLink(const char* description, const char* content, const char* text);
	virtual Tag* clone() const;
	virtual void SaveInHTML(std::ofstream & file);
	void SetText(const char* txt);
	const char* GetText() const;

};

#endif