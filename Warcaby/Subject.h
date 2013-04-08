#pragma once
#include "Listener.h"
#include <list>

class Subject
{
private:
	std::list<Listener*> m_listeners;
public:
	void addListener(Listener* ptr) { m_listeners.push_back(ptr); }
	void broadcast() { for(auto it = m_listeners.begin(); it != m_listeners.end(); ++it) (*it)->update(); }
	~Subject() { m_listeners.clear(); }
};