#pragma once
#include "IWriter.h"
#include "FileWriter.h"
#include "CPTConfigNode.h"
class WriterFactory
{
public:
	WriterFactory(void);
	~WriterFactory(void);

	static IWriter* getWriter(NodeType nodeType);
};

