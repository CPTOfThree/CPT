#pragma once

#include <map>
#include <list>
#include "ConfigBase.h"
#include "IWriter.h"
using namespace std; 
class CPTConfigNode
{
public:
	CPTConfigNode();
	~CPTConfigNode(void);
	char* getKeys();
	char* getValue(char* key);
	void setValue(char* key, char* newValue);
	void setNodeName(char* nodeName);
	void setNodePath(char* nodePath);
	CPTConfigNode* createNode(char* name);
	CPTConfigNode* getNode(char* name);
	char* getNodeName();
	char* getNodePath();
	void setWriter(IWriter* writer);
	void save();
	static NodeType getNodeType(char* nodePath);

private:
	list<CPTConfigNode*> _subNodes;  // �ӽ�㼯��
	map<char*, char*> _keyAndValues; // ���ֵ����
	char* nodeName;  // �������
	char* nodePath;  // ���·��
	IWriter* writer;
	//hash_map<char*, char*> _keyAndValues;
};

