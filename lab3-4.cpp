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

	UnorderedMap<std::string, Student> cont_1 = {
		{"Student1", {"Student1", "group1", 5.0}},
		{"Student2", {"Student2", "group1", 4.9}},
		{"Student3", {"Student3", "group1", 4.9}},
		{"Student4", {"Student4", "group1", 4.8}},
		{"Student5", {"Student5", "group2", 4.8}}
	};
        forEach(cont_1.begin(), cont_1.end(), [](const std::pair<std::string, Student>& p){
			std::cout << p.second.m_name;
			std::cout << " (" << p.second.m_group << "): ";
			std::cout << p.second.m_average_rating;
			std::cout << std::endl;
	});

	Student st6{"Student6", "group3", 5.0};
	Student st7{"Student7", "group3", 4.0};
	Student st8{"Student8", "group4", 3.0};

	UnorderedMap<std::string, Student> cont_2;
	std::cout << "cont_2 is " << (cont_2.empty() ? "" : "not ") << "empty" << std::endl;
        forEach(cont_2.begin(), cont_2.end(), [](const std::pair<std::string, Student>& p){
			std::cout << p.second.m_name;
			std::cout << " (" << p.second.m_group << "): ";
			std::cout << p.second.m_average_rating;
			std::cout << std::endl;
	});

	cont_2.insert(std::pair<std::string, Student>(st6.m_name, st6));
	cont_2.insert(std::pair<std::string, Student>(st7.m_name, st7));
	cont_2.insert(std::pair<std::string, Student>(st8.m_name, st8));

	std::cout << "cont_2 is " << (cont_2.empty() ? "" : "not ") << "empty" << std::endl;
        forEach(cont_2.begin(), cont_2.end(), [](const std::pair<std::string, Student>& p){
			std::cout << p.second.m_name;
			std::cout << " (" << p.second.m_group << "): ";
			std::cout << p.second.m_average_rating;
			std::cout << std::endl;
	});

	std::cout << std::endl;
	cont_1.insert(cont_2.begin(), cont_2.end());
        forEach(cont_1.begin(), cont_1.end(), [](const std::pair<std::string, Student>& p){
			std::cout << p.second.m_name;
			std::cout << " (" << p.second.m_group << "): ";
			std::cout << p.second.m_average_rating;
			std::cout << std::endl;
	});

	std::cout << std::endl;
	std::vector<Student> cont_3;
        forEach(cont_1.begin(), cont_1.end(), [&cont_3](const std::pair<std::string, Student>& p){
			cont_3.insert(cont_3.end(), p.second);
	});
        forEach(cont_3.begin(), cont_3.end(), [](const Student& st){
			std::cout << st.m_name;
			std::cout << " (" << st.m_group << "): ";
			std::cout << st.m_average_rating;
			std::cout << std::endl;
	});

	std::cout << std::endl;
	Sort(cont_3.begin(), cont_3.end(), [](const Student& p1, const Student& p2){
		return p1.m_name < p2.m_name;
	});
        forEach(cont_3.begin(), cont_3.end(), [](const Student& st){
			std::cout << st.m_name;
			std::cout << " (" << st.m_group << "): ";
			std::cout << st.m_average_rating;
			std::cout << std::endl;
	});

	return 0;
}
