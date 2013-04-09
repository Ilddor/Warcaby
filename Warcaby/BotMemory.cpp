#include <fstream>
#include <sstream>

#include "BotMemory.h"
#include "Dependencies\rapidxml.hpp"

char* TextFileRead(const char* fn) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) 
	{
		fp = fopen(fn,"rt");

		if (fp != NULL) 
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

void CBotMemory::addMoveToLastSet(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	m_memory.back().addMove(srcx, srcy, dstx, dsty, winning, color);
}

void CBotMemory::addSet(const std::vector<CPiece*>& board)
{
	m_memory.push_back(CSet(board));
}

void CBotMemory::setWinner(EPieceColor color)
{
	for(auto it = m_memory.begin(); it != m_memory.end(); ++it)
	{
		if(color == EPieceColor::WHITE)
			(*it).setColorWinning(true);	//true == white
		else
			(*it).setColorWinning(false);
	}
}

CMove* CBotMemory::findSet(const std::vector<CPiece*>& board)
{
	CSet set(board);
	for(auto it = m_memory.begin(); it != m_memory.end(); ++it)
	{
		if((*it).getPart1() == set.getPart1() &&
			(*it).getPart2() == set.getPart2() &&
			(*it).getPart3() == set.getPart3())
		{
			for(auto it2 = (*it).getMoves().begin(); it2 != (*it).getMoves().end(); ++it2)
			{
				if((*it2)->getWinning())
					return *it2;
			}
			return *(*it).getMoves().begin();
		}
	}
	return nullptr;
}

void CBotMemory::saveToFile(std::string path)
{
	std::fstream file(path, std::ios::out);

	file << "<memory>" << std::endl;

	for(auto it = m_memory.begin(); it != m_memory.end(); ++it)
	{
		file << "	<set ";
		file << "part1=\"" << (*it).getPart1() << "\" ";
		file << "part2=\"" << (*it).getPart2() << "\" ";
		file << "part3=\"" << (*it).getPart3() << "\"";
		if(!(*it).getMoves().empty())
			file << ">" << std::endl;
		else
			file << "/>" << std::endl;

		for(auto it2 = (*it).getMoves().begin(); it2 != (*it).getMoves().end(); ++it2)
		{
			file << "		<move ";
			file << "src=\"" << (int)(*it2)->getSource() << "\" ";
			file << "dst=\"" << (int)(*it2)->getDestination() << "\" ";
			file << "info=\"" << (int)(*it2)->getInfo() << "\"";
			file << "/>" << std::endl;
		}

		if(!(*it).getMoves().empty())
			file << "	</set>" << std::endl;
	}

	file << "</memory>";

	file.close();
}

void CBotMemory::loadFromFile(std::string path)
{
	char* data = TextFileRead(path.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(data);

	rapidxml::xml_node<>* root = doc.first_node("memory");

	int p1, p2, p3;

	char src, dst, info;

	for(auto set = root->first_node("set"); set != 0; set = set->next_sibling())
	{
		p1 = std::strtol(set->first_attribute("part1")->value(), 0, 10);
		p2 = std::strtol(set->first_attribute("part2")->value(), 0, 10);
		p3 = std::strtol(set->first_attribute("part3")->value(), 0, 10);

		m_memory.push_back(CSet(p1, p2, p3));
		
		for(auto move = set->first_node("move"); move != 0; move = move->next_sibling())
		{
			src = (char)atoi(move->first_attribute("src")->value());
			dst = (char)atoi(move->first_attribute("dst")->value());
			info = (char)atoi(move->first_attribute("info")->value());

			m_memory.back().addMove(src, dst, info);
		}
	}
}

void CBotMemory::merge(CBotMemory& other)
{
	bool tmp;
	for(auto it = other.m_memory.begin(); it != other.m_memory.end(); ++it)
	{
		tmp = false;
		for(auto it2 = m_memory.begin(); it2 != m_memory.end(); ++it2)
		{
			if(((*it).getPart1() == (*it2).getPart1()) &&
				((*it).getPart2() == (*it2).getPart2()) &&
				((*it).getPart3() == (*it2).getPart3()))
			{
				(*it2).MergeMoves(*it);
				tmp = true;
			}
		}
		if(!tmp)
		{
			m_memory.push_back(*it);
		}
		//if(it == other.m_memory.end())
		//	break;
	}
}

CBotMemory::CBotMemory(void)
{
}


CBotMemory::~CBotMemory(void)
{
	/*for(auto it = m_memory.begin(); it != m_memory.end(); ++it)
	{
		delete(*it);
	}*/
	m_memory.clear();
}
