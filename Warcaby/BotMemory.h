#pragma once

#include <list>
#include "Set.h"

class CBotMemory
{
private:
	std::list<CSet*> m_memory;
public:
	CBotMemory(void);
	~CBotMemory(void);
};

