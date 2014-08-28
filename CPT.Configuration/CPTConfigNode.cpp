#include "CPTConfigNode.h"

CPTConfigNode::CPTConfigNode()
{
}

CPTConfigNode::~CPTConfigNode(void)
{
}

char* CPTConfigNode::getKeys()
{
	//return _keyAndValues._Key;
	return nullptr;
}

char* CPTConfigNode::getValue(char* key)
{
	auto iter = _keyAndValues.find(key);
	if (iter != _keyAndValues.end())
	{
		return iter->second;
	}else
	{
		return nullptr;
	}
}

void CPTConfigNode::setValue(char* key, char* newValue)
{
	auto iter = _keyAndValues.find(key);
	if (iter != _keyAndValues.end())
	{
		iter->second = newValue;
	}else
	{
		_keyAndValues.insert(map<char*, char*>::value_type(key, newValue));
		//_keyAndValues.insert(key, newValue);
	}
}

CPTConfigNode* CPTConfigNode::createNode(char* name)
{
	CPTConfigNode* node = new CPTConfigNode;
	node->setNodeName(name);
	this->_subNodes.push_back(node);
	return node;
}

void CPTConfigNode::setNodeName(char* nodeName)
{
	this->nodeName = nodeName;
}

char* CPTConfigNode::getNodeName()
{
	return this->nodeName;
}

char* CPTConfigNode::getNodePath()
{
	return this->nodePath;
}

CPTConfigNode* CPTConfigNode::getNode(char* name)
{
	auto iter = _subNodes.begin();
	while (iter != _subNodes.end())
	{
		if ((*iter)->getNodeName() == name)
		{
			return *iter;
		}

		iter++;
	}

	return nullptr;
}

void CPTConfigNode::setWriter(IWriter* writer)
{
	this->writer = writer;
}

void CPTConfigNode::save()
{
	if (this->writer == nullptr)
	{
		return;
	}

	// 调用writer的写方法
}

NodeType CPTConfigNode::getNodeType(char* nodePath)
{
	int length = strlen(nodePath);
	char lastChar = nodePath[length - 1];
	switch (lastChar)
	{
	case '*':
		return NodeType::Network;
		break;
	default:
		return NodeType::File;
		break;
	}
}