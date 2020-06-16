#pragma once

#include <functional>

template<class _KeyType,
	class _DataType,
	class _Hash = std::hash<_KeyType>>
class UnorderedMap
{
private:
public:
	UnorderedMap();
};

template<class _KeyType,
	class _DataType,
	class _Hash>
UnorderedMap<_KeyType, _DataType, _Hash>::UnorderedMap() {}
