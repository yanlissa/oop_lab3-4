#pragma once

struct MapNodeBase
{
	MapNodeBase *m_next;

	MapNodeBase()
		:m_next(nullptr)
	{}

};

template<class Value>
struct MapNode : MapNodeBase
{
	Value m_value;
	std::size_t m_hash;

	MapNode(Value v, std::size_t h)
		:m_value(v), m_hash(h)
	{}

	MapNode* next() const
	{
		return static_cast<MapNode*> (this->m_next);
	}
};

template<class Value>
struct MapNodeIterator
{
	using node_type = MapNode<Value>;
	using data_type = typename std::tuple_element<1, Value>::type;

	node_type* m_ptr;

	MapNodeIterator(node_type* ptr = nullptr)
		:m_ptr(ptr)
	{}

	MapNodeIterator(const MapNodeIterator& i)
		:m_ptr(i.m_ptr)
	{}

	void next()
	{
		m_ptr = m_ptr->next();
	}

	MapNodeIterator& operator=(const MapNodeIterator& i)
	{
		return m_ptr = i->m_ptr;
	}

	Value& operator*() const
	{
		return m_ptr->m_value;
	}

	Value* operator->() const
	{
		return &(m_ptr->m_value);
	}

	MapNodeIterator& operator++()
	{
		next();
		return *this;
	}

	MapNodeIterator operator++(int)
	{
		MapNodeIterator tmp(*this);
		next();
		return tmp;
	}
};

template<class Value>
bool operator==(const MapNodeIterator<Value>& x, const MapNodeIterator<Value>& y)
{
	return x.m_ptr == y.m_ptr;
}

template<class Value>
bool operator!=(const MapNodeIterator<Value>& x, const MapNodeIterator<Value>& y)
{
	return x.m_ptr != y.m_ptr;
}
