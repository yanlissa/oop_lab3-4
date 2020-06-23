#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>

#include "Algorithm.h"
#include "UnorderedMap.h"

using namespace std;

struct Student
{
	std::string m_name;
	std::string m_group;
	double m_average_rating;
};

UnorderedMap<string, int> generate_map()
{
	return UnorderedMap<string, int>({{"a", 1}, {"b", 2}, {"c", 3}});
}

void print(int i)
{
        std::cout << std::setw(3) << i;
}

void print1(pair<string, int> MapE)
{
        std::cout << "<" << MapE.first << ": " << MapE.second << "> " << "\n";
}

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
		cout << oor.what() << ")" << endl; 
	}
	map.print();
	cout << "map.size(): " << map.size() << endl;

	try {
		map.erase(found);
		map.erase(map.end());
	} catch (const std::out_of_range& oor) {
		cout << "(std::out_of_range exception at ";
		cout << oor.what() << ")\n";
	}
	map.erase("c");
	map.erase("x");
	map.print();
	cout << "map.size(): " << map.size() << endl;

	map.clear();
	map.print();
	cout << "map.size(): " << map.size() << endl;
	cout << "map is empty: " << map.empty() << endl;

	UnorderedMap<string, int> map1(2);

	for (int i = 1; i<=9; i++) {
		char key[2];
		key[0] = 'a' + i - 1;
		key[1] = 0;
		pair<string,int> p(key, i);
		map1.insert(p);
	}
	map1.print();

	MapNodeIterator<pair<string, int>> iter = map1.begin();
	forEach(map1.begin(), map1.end(), print1);

	try {
		map = map;
	} catch (const std::logic_error& e) {
		cout << "(std::logic_error exception at ";
		cout << e.what() << ")" << endl; 
	}

	cout << "constructing from iterators: " << endl;
	UnorderedMap<string, int> map2(map1.begin(), map1.end());
	cout << "map2.size(): " << map2.size() << endl;
	map2.print();

	UnorderedMap<string, int> map3 = generate_map();
	cout << "map3.size(): " << map3.size() << endl;
	map3.print();

	UnorderedMap<string, int> map4(map2);
	cout << "map4.size(): " << map4.size() << endl;
	map4.print();

	std::vector<int> v{ 12, 11, 13, 5, 6, 7, 10, 11, 5, 12, 1, 14, 17 };

	iter = iter;
        forEach(v.begin(), v.end(), [](int i){
			std::cout << std::setw(3) << i;
	});
        std::cout << std::endl;

        Sort(v.begin(), v.end());

        forEach(v.begin(), v.end(), print);
        std::cout << std::endl;

	UnorderedMap<std::string, Student> cont_1 = {{"Янович Елизавета", {"Янович Елизавета", "", 5.0}}};

	return 0;
}
