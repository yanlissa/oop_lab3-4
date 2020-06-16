#include <iostream>
#include "UnorderedMap.h"

using namespace std;

int main()
{
	UnorderedMap<string, int> map;

	map.insert({"a", 1});
	map.insert({"b", 2});
	map.insert({"ab", 3});
	map.insert({"hash", 4});
	map.insert({"table", 5});

	map.print();

	return 0;
}
