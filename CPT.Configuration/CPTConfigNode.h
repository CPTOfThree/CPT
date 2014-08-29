#pragma once

#include <map>
#include <list>
#include "../CPT.Core/CPTBase.h"
#include "ConfigBase.h"
#include "IWriter.h"

using namespace std;
 
class CPTConfigNode
{
public:
	CPTConfigNode();
	~CPTConfigNode(void);
	CPTSTRING GetKeys();

	CPTSTRING GetValue(CPTSTRING key);

	void setValue(CPTSTRING key, CPTSTRING newValue);
	void setNodeName(CPTSTRING nodeName);
	void setNodePath(CPTSTRING nodePath);
	CPTConfigNode* createNode(CPTSTRING name);
	CPTConfigNode* getNode(CPTSTRING name);
	CPTSTRING getNodeName();
	CPTSTRING GetNodePath();
	void setWriter(IWriter* writer);
	void Save();
	static NodeType getNodeType(const CPTSTRING nodePath);

private:
	list<CPTConfigNode*> _subNodes;  // �ӽ�㼯��
	map<CPTSTRING, CPTSTRING> _keyAndValues; // ���ֵ����
	CPTSTRING nodeName;  // �������
	CPTSTRING nodePath;  // ���·��
	IWriter* writer;
	//hash_map<CPTSTRING, CPTSTRING> _keyAndValues;
};

