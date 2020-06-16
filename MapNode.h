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
	Value *m_value;
	std::size_t m_hash;

	MapNode* next() const
	{
		return static_cast<MapNode*> (this->m_next);
	}
};
