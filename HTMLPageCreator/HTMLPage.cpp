#include "HTMLPage.h"

void HTMLPage::copyFrom(const HTMLPage & rhs)
{
	data = new Tag*[rhs.size];
	for (int i = 0; i < rhs.size; i++)
	{
		data[i] = rhs.data[i]->clone();
	}
	capacity = size = rhs.size;
}

void HTMLPage::clear()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}

	delete[] data;
	data = nullptr;
}

void HTMLPage::resize()
{
	if (capacity == 0)
	{
		capacity = 2;
	}
	else
	{
		capacity *= 2;
	}

	Tag** data1 = new Tag*[capacity];
	for (int i = 0; i < size; i++)
	{
		data1[i] = data[i];
	}

	delete[] data;
	data = data1;
}

HTMLPage::HTMLPage() : data(nullptr), capacity(0), size(0)
{
}

HTMLPage::HTMLPage(const HTMLPage & rhs)
{
	copyFrom(rhs);
}

HTMLPage & HTMLPage::operator=(const HTMLPage & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

HTMLPage::~HTMLPage()
{
	clear();
}

void HTMLPage::AddTag(const Tag & obj)
{
	if (size >= capacity)
		resize();
	data[size++] = obj.clone();
}

void HTMLPage::removeTag(const char * desc)
{

	if (!CheckDescription(desc))
	{
		std::cout << "Don't exist this description tag!\n";
	}
	else
	{
		int index = 0;
		for (int i = 0; i < size; i++)
		{
			if (strcmp(data[i]->GetDescription(), desc) == 0)
			{
				index = i;
				break;
			}
		}

		for (int j = index; j < size - 1; j++)
		{
			std::swap(data[j], data[j + 1]);
		}
		size--;
	}
}

void HTMLPage::print() const
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1 << ". " << data[i]->GetDescription() <<  std::endl;
	}
}

void HTMLPage::moveTo(const int & pos, const char * desc)
{

	if (!CheckDescription(desc))
	{
		std::cout << "Don't exist this description tag!\n";
	}
	else
	{
		int index = 0;
		for (int i = 0; i < size; i++)
		{
			if (strcmp(data[i]->GetDescription(), desc) == 0)
			{
				index = i;
			}
		}

		for (int j = index; j >= pos; j--)
		{
			std::swap(data[j], data[j - 1]);
		}
	}
}

void HTMLPage::LoadFile(std::ifstream & file)
{
	char tagtype[50];
	char descr[256];
	char content[1024];
	while (!file.eof())
	{
		if (!file)
		{
			std::cout << "The File broke!\n";
			return;
		}

		file.getline(tagtype, 50, '<');
		file >> tagtype;
		if (tagtype[0] == 'h' && strlen(tagtype) <= 2)
		{
			char type[10];
			strcpy_s(type, 10, tagtype);
			ExtractInfo(file, tagtype, descr, content);
			AddTag(Heading(type, descr, content));
		}
		else if (strcmp(tagtype,"p") == 0)
		{
			ExtractInfo(file, tagtype, descr, content);
			AddTag(Text(descr, content));
		}
		else if (strcmp(tagtype, "img") == 0)
		{
			ExtractInfo1(file, tagtype, descr, content);
			AddTag(Image(descr, content));
		}
		else if (strcmp(tagtype, "iframe") == 0)
		{
			ExtractInfo1(file, tagtype, descr, content);
			AddTag(Video(descr, content));
		}
		else if(strcmp(tagtype,"a") == 0)
		{
			ExtractInfo1(file, tagtype,descr,content);
			file.getline(tagtype, 20, '>');
			char text[1024];
			file.getline(text, 1024, '<');
			AddTag(HyperLink(descr, content,text));
		}
		memset(tagtype, 0, 50);
		memset(descr, 0, 256);
		memset(content, 0, 1024);
	}
}

void HTMLPage::SaveFile(std::ofstream & file)
{
	file << "<!DOCTYPE html>\n" << "<html>\n" << "<head> </head>\n" << "<body>\n";
	for (int i = 0; i < size; i++)
	{
		data[i]->SaveInHTML(file);
	}
	file << "</body>\n" << "</html>\n";
}

void HTMLPage::ExtractInfo(std::ifstream & file, char* tagtype,char* descr, char* content)
{
	file.getline(tagtype,50, '"');
	file.getline(descr, 256, '"');
	file.getline(tagtype, 50, '>');
	file.getline(content, 1024, '<');
}

void HTMLPage::ExtractInfo1(std::ifstream & file, char * tagtype,char* descr, char*content)
{
	file.getline(tagtype, 50, '"');
	if (strstr(tagtype, "descr"))
	{
		file.getline(descr, 256, '"');
		file.getline(tagtype, 20, '"');
		file.getline(content, 1024, '"');
	}
	else
	{
		file.getline(content, 1024, '"');
		file.getline(tagtype, 20, '"');
		file.getline(descr, 256, '"');
	}
	
}

bool HTMLPage::CheckDescription(const char * descr) const
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(data[i]->GetDescription(), descr) == 0)
		{
			return true;
		}
	}
	return false;
}
