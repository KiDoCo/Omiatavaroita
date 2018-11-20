#ifndef ifnDefHead
#define MOMS_SPAGHETTI

#include <string>
#include <iostream>

class TestClass
{
public:
	TestClass();
	~TestClass();
	void addItem(int i);
	void print();

protected:

	int numberArray[10];
	int addedNumbers;

private:

};



TestClass::TestClass()
{
}

TestClass::~TestClass()
{
}

#endif
