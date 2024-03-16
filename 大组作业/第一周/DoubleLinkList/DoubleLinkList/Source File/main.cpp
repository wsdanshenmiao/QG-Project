#include <iostream>
#include <list>
#include"LinkList.cpp"

class Entity
{
public:
	int m_X, m_Y;

	Entity(int x, int y)
		:m_X(x), m_Y(y) {}

	Entity& operator++()
	{
		m_X++;
		m_Y++;
		return *this;
	}
	Entity& operator++(int)
	{
		Entity e = *this;
		m_X++;
		m_Y++;
		return e;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Entity& e);
	bool operator!=(const Entity& e) {
		return m_X != e.m_X || m_Y != e.m_Y;
	}
};

std::ostream& operator<<(std::ostream& stream, const Entity& e)
{
	stream << e.m_X << " " << e.m_Y << std::endl;
	return stream;
}

#if 1
int main()
{
	QGHW::LinkList<Entity> l;
	std::cout << l.IsEmpty() << std::endl;
	for (int i = 0; i < 5; i++) {
		l.PushFront(Entity(i, i + 1));
	}
	for (int i = 0; i < 5; i++) {
		l.PushBack(Entity(i, i + 1));
	}
	std::cout << *l.Begin() << std::endl;
	std::cout << l.Front() << std::endl;
	std::cout << l.Back() << std::endl;
	for (QGHW::ListIterator<Entity> it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << l.Size() << std::endl;
}


#else
int main()
{
	std::list<int> l;
	for (int i = 0; i < 5; i++) {
		l.push_back(i);
	}
	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) {
		std::cout << *it << std::endl;
	}
}

#endif // 0


