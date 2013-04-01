#include <fstream>

#include "BotMemory.h"
#include "Dependencies\rapidxml.hpp"
#include "Dependencies\rapidxml_utils.hpp"

void CBotMemory::addMoveToLastSet(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	m_memory.back()->addMove(srcx, srcy, dstx, dsty, winning, color);
}

void CBotMemory::addSet(const std::vector<CPiece*>& board)
{
	m_memory.push_back(new CSet(board));
}

void CBotMemory::saveToFile(std::string path)
{
}

void CBotMemory::loadFromFile(std::string path)
{
	rapidxml::file<> xmlFile(path.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<>* root = doc.first_node("memory");

	rapidxml::xml_node<>* set = root->first_node("set");

	rapidxml::xml_node<>* move;

	int p1, p2, p3;

	char src, dst, info;

	while(set != 0)
	{
		p1 = std::strtol(set->first_node("part1")->first_attribute("value")->value(), 0, 10);
		p2 = std::strtol(set->first_node("part2")->first_attribute("value")->value(), 0, 10);
		p3 = std::strtol(set->first_node("part3")->first_attribute("value")->value(), 0, 10);

		move = set->first_node("moves")->first_node("move");

		m_memory.push_back(new CSet(p1, p2, p3));
		
		while(move != 0)
		{
			src = set->first_attribute("src")->value()[0];
			dst = set->first_attribute("dst")->value()[0];
			info = set->first_attribute("info")->value()[0];

			m_memory.back()->addMove(src, dst, info);

			move = move->next_sibling();
		}

		set = set->next_sibling();
	}
}

CBotMemory::CBotMemory(void)
{
}


CBotMemory::~CBotMemory(void)
{
	for(auto it = m_memory.begin(); it != m_memory.end(); ++it)
	{
		delete(*it);
	}
	m_memory.clear();
}
