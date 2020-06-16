#pragma once

#include <functional>
#include "MapNode.h"

template<class Key,
	 class T,
	 class Hash = std::hash<Key>>
class UnorderedMap
{
public:
	using value_type = std::pair<Key, T>;
	using node_base = MapNodeBase;
	using node_type = MapNode<value_type>;
private:
	Hash m_hash;
	std::size_t m_size;
	node_type **m_table;
public:
	UnorderedMap()
		:m_hash(Hash()), m_size(256)
	{
		m_table = new node_type *[m_size];
	}

	~UnorderedMap()
	{
		delete m_table;
	}

	node_type *insert()
	{
		return nullptr;
	}
};
