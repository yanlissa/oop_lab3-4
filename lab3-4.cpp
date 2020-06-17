#include <iostream>
#include "UnorderedMap.h"

using namespace std;

int main()
{
	UnorderedMap<string, int> map;

	map.print();

	map.insert({"a", 1});
	map.insert({"b", 2});
	map.insert({"ab", 3});
	map.insert({"hash", 4});
	map.insert({"table", 5});
	int a = (*map.insert({"a", 2})).second;
	cout << "a: " << a << endl;
	cout << "begin: <";
	cout << (*map.begin()).first << ": " << (*map.begin()).second << ">\n";
	cout << "end is null: ";
	cout << (map.end() == MapNodeIterator<std::pair<string, int>>(nullptr)) << endl;

	map.print();

	return 0;
}
