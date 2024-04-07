#ifndef __BINARY_SORT_TREE__HPP__
#define __BINARY_SORT_TREE__HPP__

#include "allocator.hpp"
#include "iostream"

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

private:
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
	inline sizeType& Size() const;
	inline iterator Begin() const;
	inline iterator End() const;


private:
	inline void _InitTree();
	inline std::pair<iterator, bool> _Insert(const keyType& key);

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
inline size_t& Tree<Key, C, A>::Size() const
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
	iterator it(m_Head->m_Left);
	return it;
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
	iterator it(m_Head);
	return it;
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
void Tree<Key, C, A>::_InitTree()
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
