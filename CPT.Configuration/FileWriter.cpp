#include "FileWriter.h"


FileWriter* FileWriter::getInstance()
{
	if (_fileWriter != nullptr)
	{
		_fileWriter = new FileWriter;
	}

	return _fileWriter;
}

FileWriter::FileWriter(void)
{
}


FileWriter::~FileWriter(void)
{
	delete this->_fileWriter;
}

void FileWriter::write() 
{

}

char* FileWriter::read() 
{
	return nullptr;
}