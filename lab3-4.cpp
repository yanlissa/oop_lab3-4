#include <iostream>
#include "UnorderedMap.h"

using namespace std;

int main()
{
	UnorderedMap<int, int> map;
	hash<string> hasher;
	cout << "a: " << hasher("a") % 32 << "\n";
	cout << "b: " << hasher("b") % 32 << "\n";
	cout << "ab: " << hasher("ab") % 32 << "\n";
	cout << "hash: " << hasher("hash") % 32 << "\n";
	cout << "table: " << hasher("table") % 32 << "\n";
	return 0;
}
