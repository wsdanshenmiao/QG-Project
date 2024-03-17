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
	std::cout << "IsEmpty: " << l.IsEmpty() << std::endl;

	std::cout << "PushFront后:" << std::endl;
	for (int i = 0; i < 5; i++) {
		l.PushFront(Entity(i, i + 1));
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "PushBack后:" << std::endl;
	for (int i = 0; i < 5; i++) {
		l.PushBack(Entity(i, i + 1));
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "Begin: " << *l.Begin() << std::endl;
	std::cout << "Front: " << l.Front() << std::endl;
	std::cout << "Back: " << l.Back() << std::endl;
	std::cout << "Size: " << l.Size() << std::endl;

	std::cout << "PopFront后:" << std::endl;
	for (int i = 0; i < 2; i++) {
		l.PopFront();
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "PopBack后:" << std::endl;
	for (int i = 0; i < 2; i++) {
		l.PopBack();
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "Size: " << l.Size() << std::endl;

	std::cout << "erase后:" << std::endl;
	while(!l.IsEmpty()){
		l.erase(l.Begin());
	}
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "insert后:" << std::endl;
	Entity e = Entity(0, 0);
	l.insert(l.Begin(), e);
	l.insert(l.Begin(), 3, Entity(10, 10));
	l.insert(++l.Begin(), std::move(Entity(9, 9)));
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}

	//l.erase(l.Begin(), l.End());

	std::cout << "clear后:" << std::endl;
	l.clear();
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != l.End(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "resize后:" << std::endl;
	l.resize(10, Entity(1, 1));
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "Size: " << l.Size() << std::endl;

	std::cout << "resize后:" << std::endl;
	l.resize(5, Entity(2, 2));
	for (QGHW::LinkList<Entity>::iterator it = l.Begin(); it != ++l.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "Size: " << l.Size() << std::endl;


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

