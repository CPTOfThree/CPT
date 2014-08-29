#include "CPTConfigNode.h"

CPTConfigNode::CPTConfigNode()
{
}

CPTConfigNode::~CPTConfigNode(void)
{
}

CPTSTRING CPTConfigNode::GetKeys()
{
	//return _keyAndValues._Key;
	return nullptr;
}

CPTSTRING CPTConfigNode::GetValue(CPTSTRING key)
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

void CPTConfigNode::setValue(CPTSTRING key, CPTSTRING newValue)
{
	auto iter = _keyAndValues.find(key);
	if (iter != _keyAndValues.end())
	{
		iter->second = newValue;
	}else
	{
		_keyAndValues.insert(map<CPTSTRING, CPTSTRING>::value_type(key, newValue));
		//_keyAndValues.insert(key, newValue);
	}
}

CPTConfigNode* CPTConfigNode::createNode(CPTSTRING name)
{
	CPTConfigNode* node = new CPTConfigNode;
	node->setNodeName(name);
	this->_subNodes.push_back(node);
	return node;
}

void CPTConfigNode::setNodeName(CPTSTRING nodeName)
{
	this->nodeName = nodeName;
}

CPTSTRING CPTConfigNode::getNodeName()
{
	return this->nodeName;
}

CPTSTRING CPTConfigNode::GetNodePath()
{
	return this->nodePath;
}

CPTConfigNode* CPTConfigNode::getNode(CPTSTRING name)
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

void CPTConfigNode::Save()
{
	if (this->writer == nullptr)
	{
		return;
	}

	// 调用writer的写方法
}

NodeType CPTConfigNode::getNodeType(const CPTSTRING nodePath)
{
	int length = nodePath.length();
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