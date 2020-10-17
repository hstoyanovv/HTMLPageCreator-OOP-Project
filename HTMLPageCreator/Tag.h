#ifndef TAG_H
#define TAG_H
#include<iostream>
#include<fstream>
class Tag
{
private:
	void clear();
protected:
	char* description;
	char* content;
	void copyFrom(const Tag & rhs);
public:
	Tag();
	Tag(const char* description, const char* content);
	Tag(const Tag & rhs);
	Tag & operator=(const Tag & rhs);
	virtual ~Tag();
	virtual Tag* clone() const = 0;
	virtual void SaveInHTML(std::ofstream & file) = 0;
	void SetDescription(const char* desc);
	void SetContent(const char* cont);
	const char* GetDescription() const;
	const char* GetContent() const;
};


#endif
