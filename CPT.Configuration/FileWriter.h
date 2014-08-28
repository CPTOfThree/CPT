#pragma once
#include "IWriter.h"
class FileWriter : public IWriter
{
public:
	static FileWriter* getInstance();
	~FileWriter(void);

	void write() override;
	char* read() override;

private:
	FileWriter(void);
	static FileWriter* _fileWriter;
};

