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
	using iterator = MapNodeIterator<value_type>;
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

	node_type* find_node(const Key &k, std::size_t t)
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

	node_type* first_node()
	{
		return static_cast<node_type*>(m_before_begin.m_next);
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

	iterator find(const Key& k)
	{
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		return find_node(k, t);
	}

	iterator insert(value_type &&v)
	{
		Key k = v.first;
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		node_type *n = find_node(k, t);
		if (n) {
			return n;
		}

		n = new node_type(v, h);
		return insert_at_beginning(t, n);
	}

	T& operator[](const Key& k)
	{
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		node_type *n = find_node(k, t);
		if (n) {
			return n->m_value.second;
		}

		value_type v(std::piecewise_construct,
				std::tuple<const Key&>(k),
				std::tuple<>());
		n = new node_type(v, h);
		return insert_at_beginning(t, n)->m_value.second;
	}

	T& at(const Key& k)
	{
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		node_type *n = find_node(k, t);
		if (!n) {
			throw std::out_of_range("UnorderedMap::at");
		}

		return n->m_value.second;
	}

	iterator begin()
	{
		return first_node();
	}

	iterator end()
	{
		return nullptr;
	}

	bool empty()
	{
		return m_count == 0;
	}
	void print()
	{
		node_base *p = m_before_begin.m_next;
		if (!p) {
			std::cout << "UnorderedMap is empty\n";
			return;
		}

		node_type *n = static_cast<node_type*>(p);
		while (n) {
			value_type *v = &(n->m_value);
			std::cout << "<" << v->first << ": " << v->second << "> " << n->m_hash << "\n";
			n = n->next();
		}
	}
};
