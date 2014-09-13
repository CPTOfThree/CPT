#include "TestList.h"


TestList::TestList(void)
{
	this->classes = new list<ClassA*>;
}


TestList::~TestList(void)
{
}

void TestList::AddClassA(ClassA* classA)
{
	this->classes->push_back(classA);
}