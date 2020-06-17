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
private:
	std::size_t table_index(std::size_t hash)
	{
		return hash % m_size;
	}

	node_type* find_node(std::size_t t, const Key &k)
	{
		node_base *p = m_table[t];
		if (!p) {
			return nullptr;
		}
		node_type *n = static_cast<node_type*>(p->m_next);
		do {
			if (k == n->m_value.first) {
				return n;
			}
			p = n;
			n = n->next();
		}
		while (n && table_index(n->m_hash) == t);
		return nullptr;
	}

	node_type* insert_at_beginning(std::size_t t, node_type *n)
	{
		if (m_table[t]) {
			n->m_next = m_table[t]->m_next;
			m_table[t]->m_next = n;
		} else {
			n->m_next = m_before_begin.m_next;
			m_before_begin.m_next = n;
			if (n->m_next) {
				m_table[table_index(n->next()->m_hash)] = n;
			}
			m_table[t] = &m_before_begin;
		}
		m_count++;
		return n;
	}
public:
	UnorderedMap()
		:m_hash(Hash()), m_size(4)
	{
		m_table = new node_base *[m_size];
	}

	~UnorderedMap()
	{
		delete m_table;
	}

	node_type *insert(value_type &&v)
	{
		Key k = v.first;
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);
		std::cout << "<" << k << ": " << v.second << "> " << h << ", " << t << "\n";

		node_type *n = find_node(t, k);
		if (n) {
			return n;
		}

		n = new node_type(v, h);
		return insert_at_beginning(t, n);
	}

	void print()
	{
		node_base *n = m_before_begin.m_next;
		if (!n) {
			return;
		}

		node_type *p = static_cast<node_type*>(n);
		while (p) {
			value_type *v = &(p->m_value);
			std::cout << "<" << v->first << ": " << v->second << "> " << p->m_hash << "\n";
			p = p->next();
		}
	}
};
