#include "WriterFactory.h"


WriterFactory::WriterFactory(void)
{
}


WriterFactory::~WriterFactory(void)
{
}

IWriter* WriterFactory::getWriter(NodeType nodetype)
{
	switch (nodetype)
	{
	case File:
		return FileWriter::getInstance();
		break;
	case Network:
		break;
	default:
		break;
	}
}