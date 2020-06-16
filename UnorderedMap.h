#pragma once

#include <iostream>

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
	std::size_t m_count = 0;
	node_base **m_table;
	node_base m_before_begin;
public:
	UnorderedMap()
		:m_hash(Hash()), m_size(256)
	{
		m_table = new node_base *[m_size];
	}

	~UnorderedMap()
	{
		delete m_table;
	}

	node_type *insert(value_type &&v)
	{
		std::cout << "<" << v.first << ": " << v.second << "> " << m_hash(v.first) << "\n";
		return nullptr;
	}

	void print()
	{
		node_base *n = m_before_begin.m_next;
		if (!n) {
			return;
		}

		node_type *p = static_cast<node_type*>(n);
		while (p) {
			value_type *v = p->m_value;
			std::cout << "<" << v->first << ": " << v->second << "> " << p->m_hash << "\n";
		}
	}
};
