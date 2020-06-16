#pragma once

struct MapNodeBase
{
	MapNodeBase *m_next;
};

template<class Value>
struct MapNode : MapNodeBase
{
	Value *m_value;

	MapNode* next() const
	{
		return static_cast<MapNode*> (this->m_next);
	}
};
