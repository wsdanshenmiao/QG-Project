#include <assert.h>

/***************************************************************************************
 *	File Name				:	LinkList.hpp
 *	CopyRight				:	2024 QG Studio
 *	SYSTEM					:   win11
 *	Create Data				:	2024.3.16
 *
 *
 *--------------------------------Revision History--------------------------------------
 *
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/

#ifndef __LINKLIST__H__
#define __LINKLIST__H__

namespace QGHW {

/**************************************************************
*	Macro Define Section	宏定义
**************************************************************/


/**************************************************************
*	Struct Define Section
**************************************************************/

//节点类
template <typename T>
class Node
{
public:
	T m_Data;	//存储数据
	Node* m_Next;	//指向下一个节点
	Node* m_Pre;	//指向上一个节点

public:
	Node();
	Node(const T& value, Node* pre, Node* next);
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>::Node()
 *	@description : 节点的默认构造函数
 *	@param		 : None
 *	@return		 : Node
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node()
	:m_Next(nullptr), m_Pre(nullptr) {}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value, Node* pre, Node* next)
	:m_Data(value), m_Pre(pre), m_Next(next) {}


/**************************************************************
*	Struct Define Section
**************************************************************/

//链表迭代器
template <typename T>
class ListIterator
{
public:
	typedef ListIterator<T> iterator;
	typedef Node<T> node_type;

public:
	ListIterator()
		:m_Pointer(nullptr) {}
	ListIterator(node_type* pointer)
		:m_Pointer(pointer) {}
	ListIterator(const iterator& it)
		:m_Pointer(it.m_Pointer) {}
	~ListIterator() {}

	//解引用操作符
	inline T& operator*()const
	{
		return m_Pointer->m_Data;
	}

	inline T& operator->()const
	{
		return &(m_Pointer->m_Data);
	}

	//迭代器前置加加,链表的迭代器为双向迭代器，只能前移后移，不可跳跃式增减
	inline iterator& operator++()
	{
		this->m_Pointer = this->m_Pointer->m_Next;
		return *this;
	}
	//后置加加,不能返回局部数据的引用
	inline iterator operator++(int)
	{
		iterator tmp = *this;
		++(*this);
		return tmp;
	}

	//前置减减
	inline iterator& operator--()
	{
		this->m_Pointer = this->m_Pointer->m_Pre;
		return *this;
	}
	//后置减减
	inline iterator operator--(int)
	{
		iterator tmp = *this;
		--(*this);
		return tmp;
	}

	//迭代器比较
	inline bool operator==(const iterator& right)const
	{
		return m_Pointer == right.m_Pointer;
	}
	inline bool operator!=(const iterator& right)const
	{
		return !(*this == right);
	}

public:
	node_type* m_Pointer;
};


/**************************************************************
*	Struct Define Section
**************************************************************/

//链表类
template <typename T>
class LinkList
{
public:
	typedef Node<T> node_type;
	typedef ListIterator<T> iterator;

public:
	LinkList();	//默认构造
	LinkList(const T& value);	//有参构造
	~LinkList();	//析构

	inline bool IsEmpty()const;
	inline size_t Size()const;
	inline iterator Begin()const;
	inline iterator End()const;
	inline T& Front()const;
	inline T& Back()const;
	inline void PushBack(const T& value);
	inline void PushFront(const T& value);

private:
	inline Node<T>* allocate_memory();

private:
	node_type* m_Head;	//链表的头节点	
	node_type* m_Tail;	//链表尾节点
	size_t m_Size;	//链表的大小
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>* LinkList<T>::allocate_memory()
 *	@description : 手动分配函数,处理没有默认构造函数的情况
 *	@param		 : None
 *	@return		 : static_cast<node_type*>(::operator new(sizeof(node_type)));
 *  @notice      : None
 */
template <typename T>
inline Node<T>* LinkList<T>::allocate_memory()
{
	return static_cast<node_type*>(::operator new(sizeof(node_type)));
}
	
/**
 *  @name        : inline LinkList<T>::LinkList()
 *	@description : 默认构造
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline LinkList<T>::LinkList()
	:m_Size(0)
{
	m_Head = allocate_memory();	//创建头节点

	m_Tail = m_Head;
}
/**
 *  @name        : inline LinkList<T>::LinkList(const T& value)
 *	@description : 默认构造
 *	@param		 : const T& value
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline LinkList<T>::LinkList(const T& value)
{
	m_Size = 0;
	m_Head = new node_type();	//创建头节点
	PushBack(value);	//尾部插入元素
}	

/**
*  @name        : inline LinkList<T>::~LinkList()
*  @description : 析构函数
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline LinkList<T>::~LinkList()
{
}
	
/**
*  @name        : inline bool LinkList<T>::IsEmpty()const
*  @description : 判断是否为空
*  @param		: None
*  @return		: m_Size == 0
*  @notice      : None
*/
template <typename T>
inline bool LinkList<T>::IsEmpty()const
{
	return m_Size == 0;
}
	
/**
*  @name        : inline size_t LinkList<T>::Size()const
*  @description : 返回链表大小
*  @param		: None
*  @return		: m_Size
*  @notice      : None
*/
template <typename T>
inline size_t LinkList<T>::Size()const
{
	return m_Size;
}
	
/**
*  @name        : typename inline ListIterator<T> LinkList<T>::Begin()const
*  @description : 返回首节点的迭代器
*  @param		: None
*  @return		: iterator(m_Head->m_Next)
*  @notice      : None
*/
template <typename T>
typename inline ListIterator<T> LinkList<T>::Begin()const
{
	assert(!IsEmpty());
	return iterator(m_Head->m_Next);
}
	
/**
*  @name        : typename inline ListIterator<T> LinkList<T>::End()const
*  @description : 返回最后一个元素下一个位置的迭代器
*  @param		: None
*  @return		: ++iterator(m_Tail)
*  @notice      : 不知道该怎么实现原本功能的End()就自定义了指向最后一个元素。
	随后发现把最后一个元素的迭代器加加一下就能达到预期的效果，虽然不知道原因，但只能将就着用。
	知道原因了，加加后成了空指针，Begin()加加最后也会成空指针，所以迭代就停了，但这样无法让迭代器前移。
*/
template <typename T>
typename inline ListIterator<T> LinkList<T>::End()const
{
	assert(!IsEmpty());
	return ++iterator(m_Tail);
}
	
/**
*  @name        : typename inline T& LinkList<T>::Front()const
*  @description : 返回首节点
*  @param		: None
*  @return		: m_Head->m_Next->m_Data
*  @notice      : None
*/
template <typename T>
typename inline T& LinkList<T>::Front()const
{
	assert(!IsEmpty());
	return m_Head->m_Next->m_Data;
}
	
/**
*  @name        : typename inline T& LinkList<T>::Back()const
*  @description : 返回尾节点
*  @param		: None
*  @return		: m_Tail->m_Data
*  @notice      : None
*/
template <typename T>
typename inline T& LinkList<T>::Back()const
{
	assert(!IsEmpty());
	return m_Tail->m_Data;
}
	
/**
*  @name        : inline void LinkList<T>::PushBack(const T& value)
*  @description : 尾部插入元素
*  @param		: const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PushBack(const T& value)
{
	node_type* node = new node_type(value, m_Tail, m_Tail->m_Next);
	m_Tail->m_Next = node;
	m_Tail = node;
	node = nullptr;
	m_Size++;
}
	
/**
*  @name        : inline void LinkList<T>::PushBack(const T& value)
*  @description : 头部插入元素
*  @param		: const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PushFront(const T& value)
{
	node_type* node = new node_type(value, m_Head, m_Head->m_Next);
	if (!IsEmpty()) {	//若为非空要处理前驱指针
		m_Head->m_Next->m_Pre = node;
		m_Head->m_Next = node;
	}
	else {	//若为空要处理尾指针
		m_Head->m_Next = node;
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}
	


}

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // !__LINKLIST__H__
