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

void test1()
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
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << l.Size() << std::endl;

	for (int i = 0; i < 2; i++) {
		l.PopFront();
	}
	for (int i = 0; i < 2; i++) {
		l.PopBack();
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << l.Size() << std::endl;

	while(!l.IsEmpty()){
		l.erase(l.Begin());
	}
	l.insert(l.Begin(), Entity(0, 0));
	l.insert(++l.Begin(), 3, Entity(10, 10));
	l.insert(l.Begin(), std::move(Entity(9, 9)));
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}

}


void test2()
{
	std::list<int> l;
	for (int i = 0; i < 5; i++) {
		l.push_back(i);
	}
	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) {
		std::cout << *it << std::endl;
	}
}

int main()
{
	test1();
}

