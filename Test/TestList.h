#pragma once
#include <list>
#include "ClassA.h"
using namespace std;
class TestList
{
public:
	TestList(void);
	~TestList(void);
	void AddClassA(ClassA* classA);

private:
	list<ClassA*>* classes;
};

