#ifndef BRANCH_H
#define BRANCH_H
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Branch
{
	public:
	unsigned long long addr;
	unsigned long long target;
	string behavior;
	string predict;
	Branch(unsigned long long address, string behave, unsigned long long nTarget)
	{
		this->addr = address;
		this->behavior = behave;
		this->target = nTarget;
	}
	unsigned long long getAddr() {return addr;}
	unsigned long long getTarget() {return target;}
	string getBehavior() {return behavior;}
};

#endif
