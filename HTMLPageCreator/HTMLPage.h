#ifndef HTMLPage_H
#define HTMLPage_H
#include "Heading.h"
#include "Text.h"
#include "Video.h"
#include "Image.h"
#include "HyperLink.h"
class HTMLPage
{
private:
	Tag** data;
	size_t capacity;
	size_t size;
	void copyFrom(const HTMLPage & rhs);
	void clear();
	void resize();
public:
	HTMLPage();
	HTMLPage(const HTMLPage & rhs);
	HTMLPage & operator=(const HTMLPage & rhs);
	~HTMLPage();
	void AddTag(const Tag & obj);
	void removeTag(const char* desc);
	void print() const;
	void moveTo(const int & pos, const char* desc);
	void LoadFile(std::ifstream & file);
	void SaveFile(std::ofstream & file);
	void ExtractInfo(std::ifstream & file,char* tagtype, char* descr, char* content);
	void ExtractInfo1(std::ifstream & file,char* tagtype, char* descr, char* content);
	bool CheckDescription(const char* descr) const;

};
#endif
