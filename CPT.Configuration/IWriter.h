#pragma once
class IWriter
{
public:
	IWriter(void);
	~IWriter(void);

	virtual void write();
	virtual char* read();
};

