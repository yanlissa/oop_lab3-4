#include <iostream>
#include "UnorderedMap.h"

using namespace std;

int main()
{
	UnorderedMap<string, int> map;

	map.print();
	cout << "map.size(): " << map.size() << endl;
	cout << "map is empty: " << map.empty() << endl;

	map.insert({"a", 1});
	map.print();
	cout << "map.size(): " << map.size() << endl;
	cout << "map is empty: " << map.empty() << endl;

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
	map["a"] = 6;
	map["c"] = 7;
	auto found = map.find("a");
	cout << found->first << ": " << found->second << "\n";

	try {
		cout << "c:" << map.at("c") << endl;
		cout << "d:" << map.at("d") << endl;
	} catch (const std::out_of_range& oor) {
		cout << "(std::out_of_range exception at ";
		cout << oor.what() << ")\n";
	}
	map.print();
	cout << "map.size(): " << map.size() << endl;

	map.clear();
	map.print();
	cout << "map.size(): " << map.size() << endl;
	cout << "map is empty: " << map.empty() << endl;

	return 0;
}
