#include "DummyFile.h"
#include <iostream>

File::File()
{
	std::cout << "Open file" << std::endl;
}

File::~File()
{
	std::cout << "Close file" << std::endl;
}

ConfigFile::ConfigFile()
{
	std::cout << "Open config file" << std::endl;
}

ConfigFile::~ConfigFile()
{
	std::cout << "Close config file" << std::endl;
}