#include <set>
#include <iostream>
#include "BinarySortTree.cpp"

class Entity
{
public:
	size_t* m_Location;

	Entity()
		:m_Location(nullptr) {}
	Entity(const size_t& value)
	{
		m_Location = new size_t(value);
	}
	Entity(const Entity& other)
	{
		m_Location = new size_t(*other.m_Location);
	}
	Entity(Entity&& other) noexcept
	{
		m_Location = other.m_Location;
		m_Location = nullptr;
	}
	~Entity()
	{
		if (m_Location) {
			delete m_Location;
		}
	}

	Entity& operator=(const Entity& other)
	{
		m_Location = new size_t(*other.m_Location);
	}
	Entity& operator=(Entity&& other) noexcept
	{
		if (m_Location) {
			delete m_Location;
		}
		m_Location = other.m_Location;
		m_Location = nullptr;
	}
	Entity& operator++()
	{
		++(*m_Location);
		return *this;
	}
	Entity operator++(int)
	{
		Entity e = *this;
		++*this;
		return e;
	}

	bool operator!=(const Entity& e) const{
		if (e.m_Location) {
			return *m_Location != *e.m_Location;
		}
		else {
			return m_Location == m_Location;
		}
	}
	bool operator==(const Entity& e) const{
		return !(*this != e);
	}
	bool operator<(const Entity& e) const {
		return *m_Location < *e.m_Location;
	}
	bool operator<=(const Entity& e) const {
		return *m_Location < *e.m_Location || *this == e;
	}
	bool operator>(const Entity& e) const {
		return !(*this <= e);
	}
	bool operator>=(const Entity& e) const {
		return !(*this < e);
	}
	friend std::ostream& operator<<(std::ostream& stream, const Entity& e);
};

std::ostream& operator<<(std::ostream& stream, const Entity& e)
{
	stream << *e.m_Location << std::endl;
	return stream;
}


void test1()
{
	std::set<Entity> tree;
	tree.insert({ Entity(1), Entity(9), Entity(6), Entity(7), Entity(5), Entity(7), Entity(4) });
	std::cout << sizeof(tree) << std::endl;
	std::cout << *tree.erase(tree.begin()) << std::endl;
	//for (std::set<Entity>::iterator it = tree.begin(); it != tree.end(); it++)
	//{
	//	std::cout << *it << std::endl;
	//}
}

void test2()
{
	QGHW::Tree<Entity> tree;
	std::cout << "sizeof(tree):" << sizeof(tree) << std::endl;
	tree.Insert(Entity(6));
	tree.Insert(Entity(8));
	tree.Insert(Entity(2));
	tree.Insert(Entity(4));
	tree.Insert(Entity(68));
	tree.Insert(Entity(71));
	tree.Insert(Entity(32));
	tree.Insert(Entity(7));
	std::cout << "不是红黑树所以某些情况判断不了头节点与根节点，所以--可能会出问题\n";
	for (QGHW::Tree<Entity>::iterator it = tree.Begin(); it != tree.End(); it++)
	{
		std::cout << *it << std::endl;
	}

}

int main()
{
	//test1();
	test2();
}