#include "MainFunctions.h"

int getCommand(const char* command)
{
	if (strcmp(command, "add") == 0)
	{
		return 1;
	}
	else if (strcmp(command, "remove") == 0)
	{
		return 2;
	}
	else if (strcmp(command, "print") == 0)
	{
		return 3;
	}
	else if (strcmp(command, "moveTo") == 0)
	{
		return 4;
	}
	else if (strcmp(command, "load") == 0)
	{
		return 5;
	}
	else if (strcmp(command, "save") == 0)
	{
		return 6;
	}
	else if (strcmp(command, "exit") == 0)
	{
		return 7;
	}
	else
	{
		return 8;
	}
}
void CreateAndAdd(HTMLPage & page)
{
	char tagtype[20];
	std::cin >> tagtype;
	std::cin.get();
	char descr[256];
	std::cin.getline(descr, 256, '>');
	if (!RemoveCottages(descr))
	{
		std::cout << "Invalid description!\n";
		return;
	}
	if (page.CheckDescription(descr))
	{
		std::cout << "This description tag already exist!\n";
		return;
	}
	char content[1024];

	if (strcmp(tagtype, "text") == 0)
	{
		std::cin.getline(content, 1024);
		page.AddTag(Text(descr, content));
	}
	else if (strcmp(tagtype, "image") == 0)
	{
		std::cin.getline(content, 1024);
		page.AddTag(Image(descr, content));
	}
	else if (strcmp(tagtype, "video") == 0)
	{
		std::cin.getline(content, 1024);
		page.AddTag(Video(descr, content));
	}
	else if (strcmp(tagtype, "link") == 0)
	{
		std::cin.get();
		std::cin >> content;
		char text[1024];
		std::cin.getline(text, 1024);
		page.AddTag(HyperLink(descr, content, text));
	}
	else if (tagtype[0] == 'h')
	{
		std::cin.getline(content, 1024);
		page.AddTag(Heading(tagtype, descr, content));
	}
}

bool RemoveCottages(char * descr)
{
	if (descr[0] != '<')
	{
		return false;
	}
	else
	{
		char descr1[256];
		int j = 0;
		for (int i = 1; i < strlen(descr); i++)
		{
			descr1[j++] = descr[i];
		}
		descr1[strlen(descr) - 1] = '\0';
		strcpy_s(descr, strlen(descr1) + 1, descr1);
	}

	return true;
}

void Run()
{
	HTMLPage page;

	char FilePath[256] = { 0 };
	char command[50];
	int n = 0, cnt = 0;

	while (n != 7)
	{
		memset(command, 0, 50);
		std::cin >> command;
		std::cin.get();
		n = getCommand(command);

		switch (n)
		{
		case 1:
		{
			CreateAndAdd(page);
			cnt++;
			break;
		}
		case 2:
		{
			char descr[256];
			std::cin.getline(descr, 256);
			page.removeTag(descr);
			cnt++;
			break;
		}
		case 3:
		{
			page.print();
			break;
		}
		case 4:
		{
			int pos = 0;
			char descr[256];
			std::cin >> pos;
			std::cin.get();
			std::cin.getline(descr, 256);
			page.moveTo(pos, descr);
			cnt++;
			break;
		}
		case 5:
		{
			std::cin.getline(FilePath, 256);
			std::ifstream file(FilePath);
			if (!file)
			{
				std::ofstream file1(FilePath);
				if (!file1)
				{
					std::cout << "Bad File!\n";
				}

				file1.close();
			}
			else
			{
				page.LoadFile(file);
			}
			file.close();
			cnt++;
			break;
		}
		case 6:
		{
			std::cin.getline(FilePath, 256);
			std::ofstream file(FilePath);
			if (!file)
			{
				std::cout << "Bad File!\n";
				
			}
			else
			{
				page.SaveFile(file);
			}

			file.close();
			cnt = 0;
			break;

		}
		case 7:
		{
			if (cnt != 0)
			{
				if (strlen(FilePath) > 0)
				{
					std::ofstream file(FilePath);
					if (!file)
					{
						std::cout << "Bad File!\n";
					}
					else
					{
						page.SaveFile(file);
					}

					file.close();
				}
				else
				{
					std::ofstream file1("MyHomePage.html");
					if (!file1)
					{
						std::cout << "Bad File!\n";
					}
					else
					{
						page.SaveFile(file1);
					}
					file1.close();
				}
			}
			break;
		}
		case 8:
		{
			std::cout << "Please enter the correct command!\n";
			break;
		}
		}
	}
}
