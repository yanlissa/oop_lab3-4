#pragma once

#include <iostream>

#include <functional>
#include "MapNode.h"


// ЗАДАНИЕ НА ЗАЩИТУ
// РЕАЛИЗОВАТЬ МЕТОД insert С ПЕРЕНОСОМ
// РЕАЛИЗОВАТЬ МЕТОД emplace (https://en.cppreference.com/w/cpp/container/unordered_map/emplace)
// В MAIN ПРИВЕСТИ ТЕСТИРОВАНИЕ МЕТОДА


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
	std::size_t m_table_size;
	std::size_t m_size = 0;
	float m_max_load_factor = 2.0; // ЭТО МНОГОВАТО - ДЖОССАТТИС ГОВОВОРИТ ЛУЧШЕ O.75-0.85 ПРИМЕРНО
	node_base **m_table;
	node_base m_before_begin;
	
private:
	std::size_t table_index(std::size_t hash)
	{
		return hash % m_table_size;
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
		m_size++;
		if (overload()) {
			reserve(m_table_size * 2 * m_max_load_factor);
		}
		return n;
	}

	node_type* first_node() const
	{
		return static_cast<node_type*>(m_before_begin.m_next);
	}

	node_base* find_parent(node_type* n, std::size_t t)
	{
		node_base* p = m_table[t];
		while (p->m_next != n) {
			p = p->m_next;
		}
		return p;
	}

	bool overload()
	{
		return (float) m_size / m_table_size > m_max_load_factor;    // static_cast
	}

	void copy(const UnorderedMap& m)
	{
		m_table_size = m.m_table_size;
		m_table = new node_base *[m_table_size]();

		for(iterator i = m.begin(); i != m.end(); ++i) {
			insert(*i);
		}
	}

	void move(UnorderedMap&& m)
	{
		m_table_size = m.m_table_size;
		m_max_load_factor = m.m_max_load_factor;
		m_size = m.m_size;
		m_table = m.m_table;
		m_before_begin = m.m_before_begin;
		m.m_table = nullptr;
		m.m_before_begin.m_next = nullptr;
	}
public:
	UnorderedMap()
		:m_hash(Hash()), m_table_size(4)
	{
		m_table = new node_base *[m_table_size]();
	}

	UnorderedMap(std::size_t table_size)
		:m_hash(Hash()), m_table_size(table_size)
	{
		m_table = new node_base *[m_table_size]();
	}

	template<class InputIt>
	UnorderedMap(InputIt first, InputIt last, std::size_t table_size = 4)
		:m_hash(Hash()), m_table_size(table_size)
	{
		m_table = new node_base *[m_table_size]();

		for(InputIt i = first; i != last; i++) {
			insert(*i);
		}
	}

	UnorderedMap(std::initializer_list<value_type> init, std::size_t table_size = 4) // init ПО КОНСТАНТНОЙ ССЫЛКЕ
		:m_hash(Hash()), m_table_size(table_size)
	{
		m_table = new node_base *[m_table_size]();

		for(auto it = std::begin(init); it != std::end(init); ++it) {
			insert(*it);
		}
	}

	UnorderedMap(const UnorderedMap& m)
	{
		copy(m);
	}

	UnorderedMap(UnorderedMap&& m)
	{
		move(std::move(m));
	}

	~UnorderedMap()
	{
		clear();
		delete m_table; // ЭТО ЖЕ ДИНАМИЧЕСКИЙ МАССИВ
	}

	UnorderedMap& operator=(const UnorderedMap& m)
	{
	    // ПРОВЕРКА НА СОМОПРИСВАИВАНИЕ
	    
		clear();
		delete m_table; // ЭТО ЖЕ ДИНАМИЧЕСКИЙ МАССИВ
		copy(m);
	}

	UnorderedMap& operator=(UnorderedMap&& m)
	{
	    // ПРОВЕРКА НА СОМОПРИСВАИВАНИЕ
	    
		clear();
		delete m_table; // ЭТО ЖЕ ДИНАМИЧЕСКИЙ МАССИВ
		move(std::move(m));
	}

	iterator find(const Key& k)
	{
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		return find_node(k, t);
	}

	iterator insert(value_type v) // ПО КОНСТАНТНОЙ ССЫЛКЕ. ТУТ ЖЕ МОЖЕТ БЫТЬ КОПИРОВАНИЕ БОЛЬШОГО ОБЪЕКТА В ПРОТИВНОМ СЛУЧАЕ
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

    // ХЕШ-ТАБЛИЦА МОЖЕТ БЫТЬ КОНСТАНТНЫМ ОБЪЕКТОМ. ПОЭТОМУ ДОЛЖНО БЫТЬ 2 ВЕРСИИ МЕТОДА:
    // НЕКОНСТАНТНЫЙ (ДЛЯ ЗАПИСИ) И КОНСТАНТНЫЙ (ДЛЯ ЧТЕНИЯ)
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

    // ХЕШ-ТАБЛИЦА МОЖЕТ БЫТЬ КОНСТАНТНЫМ ОБЪЕКТОМ. ПОЭТОМУ ДОЛЖНО БЫТЬ 2 ВЕРСИИ МЕТОДА:
    // НЕКОНСТАНТНЫЙ (ДЛЯ ЗАПИСИ) И КОНСТАНТНЫЙ (ДЛЯ ЧТЕНИЯ)
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

	iterator begin() const
	{
		return first_node();
	}

	iterator end() const
	{
		return nullptr;
	}

	bool empty() const
	{
		return m_size == 0;
	}

	std::size_t size() const
	{
		return m_size;
	}

	iterator erase(iterator i)
	{
		node_type* n = i.m_ptr;
		if (!n) {
			throw std::out_of_range("UnorderedMap::erase(it)");
		}
		std::size_t t = table_index(n->m_hash);
		node_base* p = find_parent(n, t);
		bool is_first = p == m_table[t];
		node_type* next = n->next();
		if (next) {
			std::size_t next_t = table_index(next->m_hash);
			if (t != next_t) {
				m_table[next_t] = p;
			}
		} else {
			if (is_first) {
				m_table[t] = nullptr;
			}
		}
		p->m_next = next;
		delete n;
		m_size--;
		return next;
	}

	std::size_t erase(const Key& k)
	{
		std::size_t h = m_hash(k);
		std::size_t t = table_index(h);

		node_type *n = find_node(k, t);
		if (!n) {
			return 0;
		}

		erase(n);
		return 1;
	}

	void clear()
	{
		while (m_before_begin.m_next) {
			node_type *n = static_cast<node_type*>(m_before_begin.m_next);
			m_before_begin.m_next = m_before_begin.m_next->m_next;
			m_size--;
			delete n;
		}
		m_before_begin.m_next = nullptr;
		for (std::size_t i = 0; i < m_table_size; i++) {
			m_table[i] = nullptr;
		}
	}

	void max_load_factor(float mlf)
	{
		m_max_load_factor = mlf;
	}

	float max_load_factor()
	{
		return m_max_load_factor;
	}

	void reserve(std::size_t size)
	{
		std::size_t new_table_size = (float) size / m_max_load_factor;
		if (new_table_size == m_table_size) {
			return;
		}
		m_table_size = new_table_size;
		m_size = 0;
		node_base* p = m_before_begin.m_next;
		delete m_table;                          // ЭТО МАССИВ
		m_before_begin.m_next = nullptr;
		m_table = new node_base *[m_table_size];
		while (p) {
			node_type *n = static_cast<node_type*>(p);
			p = p->m_next;
			std::size_t t = table_index(n->m_hash);
			n->m_next = nullptr;
			insert_at_beginning(t, n);
		}
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
			std::cout << "<" << v->first << ": " << v->second << "> " << n->m_hash << "\n"; // ВМЕСТО \n ЛУЧШЕ STD::ENDL
			n = n->next();
		}
	}
};
