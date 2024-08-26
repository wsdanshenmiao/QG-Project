#include <iostream>
#include <random>
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
		return *this;
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


void test2()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	//指定随机数的类型和范围
	std::uniform_int_distribution<size_t> dis(0, 100);
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
	std::cout << "size():" << tree.Size() << std::endl;
	std::cout << "不是红黑树所以某些情况判断不了头节点与根节点，所以--可能会出问题\n";
	std::cout << "迭代器本身是中序\n";
	for (QGHW::Tree<Entity>::iterator it = tree.Begin(); it != tree.End(); it++){
		std::cout << *it << std::endl;
	}
	
	std::cout << "size():" << tree.Size() << std::endl;
	std::cout << "先序遍历：\n";
	Entity* arr1 = tree.PreTraversal();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}
	std::cout << "中序遍历：\n";
	arr1 = tree.InorderTraversal();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}
	std::cout << "后序遍历：\n";
	arr1 = tree.PostorderTraversal();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}
	std::cout << "先序遍历非递归：\n";
	arr1 = tree.PreTNoRecursion();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}
	std::cout << "中序遍历非递归：\n";
	arr1 = tree.ITNoRecursion();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}
	std::cout << "后序遍历非递归：\n";
	arr1 = tree.PosTNoRecursion();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}

	std::cout << "层次遍历：\n";
	arr1 = tree.HierarchicalTraversal();
	for (int i = 0; i < tree.Size(); i++) {
		std::cout << *(arr1 + i) << std::endl;
	}

	std::cout << "----------------------------------------\n";
	for (int i = 0; i < 10; i++) {
		tree.Insert(dis(gen));
	}
	for (QGHW::Tree<Entity>::iterator it = tree.Begin(); it != tree.End(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "----------------------------------------\n";
}

int main()
{
	//test1();
	test2();
}