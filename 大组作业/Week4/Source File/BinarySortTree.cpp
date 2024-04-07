#ifndef __BINARY_SORT_TREE__HPP__
#define __BINARY_SORT_TREE__HPP__

#include "allocator.hpp"
#include <iostream>
#include <queue>
#include <stack>

namespace QGHW {



/*****************************
Class Declaration
*****************************/

//树的节点
template <typename Type>
class TreeNode
{
public:
	using valueType = Type;
	using thisType = TreeNode<valueType>;

	valueType m_Key;
	thisType* m_Parent;
	thisType* m_Left;
	thisType* m_Right;

	//使用默认构造函数
	TreeNode() = default;
	TreeNode(const thisType& other) = delete;
	thisType& operator==(const thisType& other) = delete;
};

template <typename T>
TreeNode<T>* FindPosterior(TreeNode<T>* node);	//父类指针接收子类节点
template <typename T>
TreeNode<T>* FindFront(TreeNode<T>* node);



/*****************************
Class Declaration
*****************************/

//树的迭代器
template <typename Key>
class TreeIterator
{
public:
	//使用typename告诉编译器这是一个类型，不是变量
	using nodePointer = TreeNode<Key>*;
	using keyType = Key;
	using pointer = keyType*;
	using reference = keyType&;
	using thisType = TreeIterator<Key>;

	TreeIterator();
	TreeIterator(nodePointer node);
	TreeIterator(const TreeIterator<Key>& other);
	inline TreeIterator<Key>& operator=(const TreeIterator<Key>& other);

	inline reference operator*() const;
	inline pointer operator->() const;
	inline thisType& operator++();
	inline thisType operator++(int);
	inline thisType& operator--();
	inline thisType operator--(int);

	inline bool operator==(const thisType& other) const;
	inline bool operator!=(const thisType& other) const;

public:
	nodePointer m_Pointer;
};

/*****************************
Class Definition
*****************************/

/**
 *  @Name        : TreeIterator()
 *  @Description : 默认构造
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator()
	:m_Pointer(nullptr) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : 有参构造
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator(nodePointer node)
	:m_Pointer(node) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : 有参构造
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
TreeIterator<Key>::TreeIterator(const TreeIterator<Key>& other)
	:m_Pointer(other.m_Pointer) {}

/**
 *  @Name        : TreeIterator()
 *  @Description : 有参构造
 *  @Parameters  : const pointer& node
 *  @Return value: None
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator=(const TreeIterator<Key>& other)
{
    m_Pointer = other.m_Pointer;
    return *this;
}
/**
 *  @Name        : operator*()
 *  @Description : 重载解引用
 *  @Parameters  : None
 *  @Return value: 树节点中的键值
 */
template <typename Key>
inline Key& TreeIterator<Key>::operator*() const
{
	return m_Pointer->m_Key;
}

/**
 *  @Name        : operator->()
 *  @Description : 重载箭头操作符
 *  @Parameters  : None
 *  @Return value: 树节点中键值的地址
 */
template <typename Key>
inline Key* TreeIterator<Key>::operator->() const
{
	return &(m_Pointer->m_Key);
}

/**
 *  @Name        : operator++()
 *  @Description : 重载前置++，要寻找比其大且最接近的节点
 *  @Parameters  : None
 *  @Return value: ++后的迭代器
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator++()
{
	m_Pointer = static_cast<nodePointer>(FindPosterior(m_Pointer));
	return *this;
}

/**
 *  @Name        : operator++(int)
 *  @Description : 重载后置++，要寻找比其大且最接近的节点
 *  @Parameters  : None
 *  @Return value: ++前的迭代器
 */
template <typename Key>
inline TreeIterator<Key> TreeIterator<Key>::operator++(int)
{
	thisType tmp(*this);
	m_Pointer = static_cast<nodePointer>(FindPosterior(m_Pointer));
	return tmp;
}

/**
 *  @Name        : operator--()
 *  @Description : 重载前置--
 *  @Parameters  : None
 *  @Return value: --后的迭代器
 */
template <typename Key>
inline TreeIterator<Key>& TreeIterator<Key>::operator--()
{
	m_Pointer = static_cast<nodePointer>(FindFront(m_Pointer));
	return *this;
}

/**
 *  @Name        : operator--(int)
 *  @Description : 重载后置--
 *  @Parameters  : None
 *  @Return value: --前的迭代器
 */
template <typename Key>
inline TreeIterator<Key> TreeIterator<Key>::operator--(int)
{
	thisType tmp(*this);
	m_Pointer = static_cast<nodePointer>(FindFront(m_Pointer));
	return tmp;
}

/**
 *  @Name        : operator==
 *  @Description : 判断是否相等
 *  @Parameters  : const thisType& other
 *  @Return value: true or false
 */
template <typename Key>
inline bool TreeIterator<Key>::operator==(const thisType& other) const
{
	return m_Pointer == other.m_Pointer;
}

/**
 *  @Name        : operator!=
 *  @Description : 判断是否相等
 *  @Parameters  : const thisType& other
 *  @Return value: true or false
 */
template <typename Key>
inline bool TreeIterator<Key>::operator!=(const thisType& other) const
{
	return !(*this == other);
}


/*****************************
Class Declaration
*****************************/

template <
	typename Key,
	typename Compare =std::less<Key>,
	typename Allocator = QGHW::allocator<Key>
>class Tree
{
public:
	using keyType = Key;
	using sizeType = size_t;
	using keyCompare = Compare;
	using keyAllocator = Allocator;
	using reference = keyType&;
	using constReference = const keyType&;
	using pointer = typename Allocator::pointer;
	using constPointer = typename Allocator::constPointer;
	using thisType = Tree<Key, Compare, Allocator>;
	using iterator = QGHW::TreeIterator<Key>;
	using nodeType = TreeNode<Key>;
	using nodePointer = nodeType*;
	using nodeAllocator = QGHW::allocator<nodeType>;

	Tree();
	Tree(const thisType& other);
	Tree(thisType&& other);
	Tree(std::initializer_list<keyType> initList);

	inline iterator Find(const keyType& key) const;
	inline std::pair<iterator, bool> Insert(const keyType& key);
	inline bool IsEmpty() const;
	inline sizeType Size() const;
	inline iterator Begin() const;
	inline iterator End() const;
	inline sizeType Erase(const Key& key);
	inline iterator Erase(iterator pos);

	inline Key* Traversal(void function(const TreeNode<Key>*, Key*));
	inline Key* PreTraversal();
	inline Key* InorderTraversal();
	inline Key* PostorderTraversal();

	inline Key* HierarchicalTraversal();

	inline Key* PreTNoRecursion();
	inline Key* ITNoRecursion();
	inline Key* PosTNoRecursion();

private:
	inline void _InitTree();
	inline std::pair<iterator, bool> _Insert(const keyType& key);
	inline std::pair<iterator, bool> _Erase(const Key& key);

private:
	sizeType m_Size;	//树的大小
	nodePointer m_Head;	//树的头节点，用来维护根节点，Begin()和End()
	keyCompare m_keyCompate;	//键值比较
};

/*****************************
Class Definition	(public)
*****************************/

/**
 *  @Name        : Tree()
 *  @Description : 默认构造只构造头节点
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key,typename C,typename A>
Tree<Key, C, A>::Tree()
{
	_InitTree();
}

template <typename Key, typename C, typename A>
Tree<Key, C, A>::Tree(const thisType& other)
{
	_InitTree();
	for (typename Tree<Key, C, A>::iterator it = other.Begin(); it != other.End(); it++){
		Insert(*it);
	}
}

template <typename Key, typename C, typename A>
Tree<Key, C, A>::Tree(thisType&& other)
{
	m_Head = other.m_Head;
	m_Size = other.m_Size;
	m_keyCompate = other.m_keyCompate;
	other.m_Head = nullptr;
	other.m_Size = 0;
}


/**
 *  @Name        : Find(const keyType& key)
 *  @Description : 寻找某个节点
 *  @Parameters  : const keyType& key
 *  @Return value: 要寻找节点的迭代器
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Find(const keyType& key) const
{
	nodePointer node = m_Head->m_Parent;
	for (; node && key != node->m_Key;) {
		if (m_keyCompate(key, node->m_Key)) {	//若key比该节点小，移动到左子树
			node = node->m_Left;
		}
		else {	//否则移动到右子树
			node = node->m_Right;
		}
		return iterator(node);	//返回找到节点的迭代器，没找到就返回空指针迭代器
	}
	return iterator(node);
}

/**
 *  @Name        : Insert(const keyType& key)
 *  @Description : 插入某个元素
 *  @Parameters  : const keyType& key
 *  @Return value: std::pair
 */
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::Insert(const keyType& key)
{
	return _Insert(key);
}

/**
 *  @Name        : IsEmpty()
 *  @Description : 判断是否为空
 *  @Parameters  : None
 *  @Return value: true or false
 */
template <typename Key, typename C, typename A>
inline bool Tree<Key, C, A>::IsEmpty() const
{
	return m_Size == 0;
}

/**
 *  @Name        : Size()
 *  @Description : 返回树的大小
 *  @Parameters  : None
 *  @Return value: 返回树的大小
 */
template <typename Key, typename C, typename A>
inline size_t Tree<Key, C, A>::Size() const
{
	return m_Size;
}

/**
 *  @Name        : Begin()
 *  @Description : 最小元素的迭代器，空时返回End()
 *  @Parameters  : None
 *  @Return value: 最小元素的迭代器
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Begin() const
{
	if (IsEmpty()) {
		return End();
	}
	return iterator(m_Head->m_Left);
}

/**
 *  @Name        : End()
 *  @Description : 头节点的迭代器
 *  @Parameters  : None
 *  @Return value: 头节点的迭代器
 */
template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::End() const
{
	
	return iterator(m_Head);;
}

template <typename Key, typename C, typename A>
inline size_t Tree<Key, C, A>::Erase(const Key& key)
{
	std::pair<iterator, bool> pair = _Erase(key);
	return pair.second;
}

template <typename Key, typename C, typename A>
inline TreeIterator<Key> Tree<Key, C, A>::Erase(iterator pos)
{
	std::pair<iterator, bool> pair = _Erase(*pos);
	return pair.first;
}

template <typename Key>
inline void pre_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		*(arr + i++) = node->m_Key;
		pre_Traversal(node->m_Left, arr);
		pre_Traversal(node->m_Right, arr);
	}
}
template <typename Key>
inline void inorder_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		inorder_Traversal(node->m_Left, arr);
		*(arr + i++) = node->m_Key;
		inorder_Traversal(node->m_Right, arr);
	}
}
template <typename Key>
inline void pos_Traversal(const TreeNode<Key>* node, Key* arr)
{
	if (node) {
		static size_t i = 0;
		pos_Traversal(node->m_Left, arr);
		pos_Traversal(node->m_Right, arr);
		*(arr + i++) = node->m_Key;
	}
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::Traversal(void function(const TreeNode<Key>*, Key*))
{
	if (m_Size == 0) {
		return nullptr;
	}
	QGHW::allocator<Key> k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	function(m_Head->m_Parent, arr);
	return arr;
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PreTraversal()
{
	return Traversal(pre_Traversal);
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::InorderTraversal()
{
	return Traversal(inorder_Traversal);
}
template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PostorderTraversal()
{
	return Traversal(pos_Traversal);
}


template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::HierarchicalTraversal()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::queue<nodePointer> queue;
	queue.push(m_Head->m_Parent);	//根节点入队
	for (; !queue.empty();) {	//若不为空则没遍历完
		nodePointer tmp = queue.front();
		queue.pop();	//出队
		*(arr + i++) = tmp->m_Key;
		if (tmp->m_Left) {	//左节点入队
			queue.push(tmp->m_Left);
		}
		if (tmp->m_Right) {	//右节点入队
			queue.push(tmp->m_Right);
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PreTNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::stack<nodePointer> stack;	//使用栈模拟递归
	stack.push(m_Head->m_Parent);	//根节点入栈
	while (!stack.empty()) {	//中左右
		nodePointer tmp = stack.top();	//记录栈顶
		stack.pop();	//出栈
		*(arr + i++) = tmp->m_Key;
		if (tmp->m_Right) {	//右节点入栈
			stack.push(tmp->m_Right);
		}
		if (tmp->m_Left) {	//左节点入栈
			stack.push(tmp->m_Left);
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::ITNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::stack<nodePointer> stack;	//使用栈模拟递归
	nodePointer node = m_Head->m_Parent;
	while (!stack.empty() || node) {
		if (node) {
			stack.push(node);
			node = node->m_Left;
		}
		else {
			node = stack.top();
			stack.pop();
			*(arr + i++) = node->m_Key;
			node = node->m_Right;
		}
	}
	return arr;
}

template <typename Key, typename C, typename A>
inline Key* Tree<Key, C, A>::PosTNoRecursion()
{
	if (m_Size == 0) {
		return nullptr;
	}
	size_t i = 0, j = 0;
	keyAllocator k_Allocator;
	Key* arr = k_Allocator.allocate(m_Size);
	std::vector<Key> vector;	//临时数组，最后反转
	vector.reserve(m_Size);
	std::stack<nodePointer> stack;	//使用栈模拟递归
	stack.push(m_Head->m_Parent);	//根节点入栈
	while (!stack.empty()) {	//中右左
		nodePointer tmp = stack.top();	//记录栈顶
		stack.pop();	//出栈
		vector.push_back(tmp->m_Key);
		if (tmp->m_Left) {	//左节点入栈
			stack.push(tmp->m_Left);
		}
		if (tmp->m_Right) {	//右节点入栈
			stack.push(tmp->m_Right);
		}
	}
	//最后反转数组即为左右中
	for (typename std::vector<Key>::reverse_iterator it = vector.rbegin(); it != vector.rend(); *(arr + j++) = *it, it++);
	return arr;
}




/*****************************
Class Definition	(private)
*****************************/

/**
 *  @Name        : InitTree()
 *  @Description : 初始化树,构造头节点
 *  @Parameters  : None
 *  @Return value: None
 */
template <typename Key, typename C, typename A>
inline void Tree<Key, C, A>::_InitTree()
{
	nodeAllocator n_Allocator;
	keyAllocator k_Allovator;
	m_Head = n_Allocator.allocate(1);
	k_Allovator.construct((Key*)m_Head, Key());
	m_Head->m_Parent = nullptr;
	m_Head->m_Left = nullptr;
	m_Head->m_Right = nullptr;
	m_Size = 0;
}

//插入主函数
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::_Insert(const keyType& key)
{
	nodePointer node = m_Head->m_Parent;
	nodePointer pre = m_Head;
	for (; node && node->m_Key != key;) {	//寻找插入点，有相同的退出循环
		pre = node;
		if (m_keyCompate(key, node->m_Key)) {
			node = node->m_Left;
		}
		else {
			node = node->m_Right;
		}
	}
	if (node) {
		iterator it(node);
		return { it, false };	//返回阻止插入的节点的迭代器
	}
	else {
		nodeAllocator n_Allocator;
		nodePointer ret = n_Allocator.allocate(1);
		keyAllocator k_Allocator;
		k_Allocator.construct((Key*)ret, key);
		ret->m_Left = nullptr;
		ret->m_Right = nullptr;
		ret->m_Parent = pre;
		if (IsEmpty()) {
			pre->m_Parent = ret;
			pre->m_Left = ret;
			pre->m_Right = ret;
		}
		else {
			if (m_keyCompate(key, pre->m_Key)) {	//插入左子树
				ret->m_Left = pre->m_Left;
				pre->m_Left = ret;
			}
			else {	//插入右子树
				ret->m_Right = pre->m_Right;
				pre->m_Right = ret;
			}
			if (m_keyCompate(key, m_Head->m_Left->m_Key)) {
				m_Head->m_Left = ret;
			}
			else if (m_keyCompate(m_Head->m_Right->m_Key, key)) {
				m_Head->m_Right = ret;
			}
		}
		++m_Size;
		iterator it(ret);
		return { it, true };	//返回插入的节点
	}
}

//删除主函数
template <typename Key, typename C, typename A>
inline std::pair<TreeIterator<Key>, bool> Tree<Key, C, A>::_Erase(const Key& key)
{
	nodePointer node = Find(key).m_Pointer;
	if (!node) {
		iterator it(node);
		return { it,false };
	}
	nodePointer const transform = FindPosterior(node);
	if (node == m_Head->m_Left) {
		m_Head->m_Left = transform;
	}
	nodeAllocator n_Allocator;
	keyAllocator k_Allocator;
	if (node->m_Parent->m_Parent == node) {	//为根节点
		if (!node->m_Left && !node->m_Right) {	//若都为空
			m_Head->m_Left = nullptr;
			m_Head->m_Parent = nullptr;
			m_Head->m_Right = nullptr;
		}
		else {	//有一方为空
			if (node->m_Left) {
				m_Head->m_Parent = node->m_Left;
				node->m_Left->m_Parent = m_Head;
			}
			else {
				m_Head->m_Parent = node->m_Right;
				node->m_Right->m_Parent = m_Head;
			}
		}
	}
	else {
		if (!node->m_Left && !node->m_Right) {	//若都为空
			if (node->m_Parent->m_Left == node) {
				node->m_Parent->m_Left = nullptr;
			}
			else {
				node->m_Parent->m_Right = nullptr;
			}
		}
		else if (node->m_Left && node->m_Right) {	//都不为空
			nodePointer trans = transform;	//寻找其后位
			nodePointer tmp = trans;
			node->m_Key = trans->m_Key;	//让后位顶替
			trans = node;
			node = tmp;	//交换
		}
		else {	//有一方为空
			if (node->m_Parent->m_Left == node) {	//node为左子树
				if (node->m_Left) {
					node->m_Parent->m_Left = node->m_Left;
					node->m_Left->m_Parent = node->m_Parent;
				}
				else {
					node->m_Parent->m_Left = node->m_Right;
					node->m_Right->m_Parent = node->m_Parent;
				}
			}
			else {	//node为右子树
				if (node->m_Left) {
					node->m_Parent->m_Right = node->m_Left;
					node->m_Left->m_Parent = node->m_Parent;
				}
				else {
					node->m_Parent->m_Right = node->m_Right;
					node->m_Right->m_Parent = node->m_Parent;
				}
			}
		}
	}
	k_Allocator.destroy((Key*)node);	//先调用析构
	n_Allocator.deallocate(node, 1);	//在释放内存
	node = nullptr;
	m_Size--;
	iterator it(transform);
	return { it,true };
}

/*****************************
Auxiliary Function
*****************************/

/**
 *  @Name        : FindPosterior(TreeNode* node)
 *  @Description : 寻找某个节点的后位节点,若对头节点使用会造成未定义行为
 *  @Parameters  : TreeNode* node要寻找的节点
 *  @Return value: 后位节点
 */
template <typename T>
TreeNode<T>* FindPosterior(TreeNode<T>* node)
{
	if (node->m_Right){	//若右子树存在
		for (node = node->m_Right; node->m_Left; node = node->m_Left);	//寻找右子树最小的值
	}
	else {	//若右子树不存在
		TreeNode<T>* tmp = node->m_Parent;
		//若当前节点是临时节点的右子树，则继续攀升，直到node为以原始值为左树最大值为止
		for (; node == tmp->m_Right; node = tmp, tmp = tmp->m_Parent);
		//还要区分只有根节点的情况，若只有根节点，node会攀升到头节点处，tmp为根节点；否则反之
		if (node->m_Right != tmp) {	//若node不是头节点
			node = tmp;	//成为头节点
		}
	}

	return node;
}

/**
 *  @Name        : FindFront(TreeNode* node)
 *  @Description : 寻找某个节点的前位节点，若对最小的节点使用会造成未定义行为
 *  @Parameters  : TreeNode* node要寻找的节点
 *  @Return value: 前位节点
 */
template <typename T>
TreeNode<T>* FindFront(TreeNode<T>* node)
{
	if (node->m_Left) {	//若左子树存在
		for (node = node->m_Left; node->m_Right; node = node->m_Right);	//寻找左子树最大的值
	}
	else {	//若左子树不存在
		TreeNode<T>* tmp = node->m_Parent;
		//若当前节点是临时节点的左子树，则继续攀升，直到node为以原始值为右树最小值为止
		for (; node == tmp->m_Left; node = tmp, tmp = tmp->m_Parent);
		node = tmp;
	}
	return node;
}






}


#endif // !__BINARY_SORT_TREE__HPP__
