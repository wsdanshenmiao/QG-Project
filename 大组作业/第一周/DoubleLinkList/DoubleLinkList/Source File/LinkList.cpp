#include <assert.h>
#include <iostream>

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
	typedef Node<T> this_type;

public:
	T m_Data;	//存储数据
	this_type* m_Next;	//指向下一个节点
	this_type* m_Pre;	//指向上一个节点

public:
	inline Node();
	inline Node(const T& value);
	inline Node(const T& value, this_type* pre, this_type* next);
	inline void insert(this_type* next);
};


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : inline Node<T>::Node()
 *	@description : 节点的默认构造函数
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node()
	:m_Next(nullptr), m_Pre(nullptr) {}

/**
 *  @name        : inline Node<T>::Node(const T& value)
 *	@description : 有参构造
 *	@param		 : const T& value
 *	@return		 : status
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value)
	:m_Data(value), m_Pre(nullptr), m_Next(nullptr) {}

/**
 *  @name        : inline Node<T>::Node(const T& value, this_type* pre, this_type* next)
 *	@description : 有参构造
 *	@param		 : const T& value, this_type* pre, this_type* next
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline Node<T>::Node(const T& value, this_type* pre, this_type* next)
	:m_Data(value), m_Pre(pre), m_Next(next) {}

/**
 *  @name        : inline void Node<T>::insert(this_type* next)
 *	@description : 将节点插入next之前
 *	@param		 : this_type* next
 *	@return		 : None
 *  @notice      : None
 */
template <typename T>
inline void Node<T>::insert(this_type* next)
{
	m_Next = next;
	m_Pre = next->m_Pre;
	next->m_Pre->m_Next = this;
	next->m_Pre = this;
}



/**************************************************************
*	Struct Define Section
**************************************************************/

//链表类
template <typename T>
class LinkList
{
public:
	typedef Node<T> node_type;
	//链表迭代器
	class iterator
	{
	public:
		typedef Node<T> node_type;

	public:
		iterator()
			:m_Pointer(nullptr) {}
		iterator(node_type* pointer)
			:m_Pointer(pointer) {}
		iterator(const iterator& it)
			:m_Pointer(it.m_Pointer) {}
		~iterator() {}

		//解引用操作符
		inline T& operator*()const
		{
			return m_Pointer->m_Data;
		}

		inline T* operator->()const
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
	inline void PopBack();
	inline void PopFront();
	inline iterator empalce(iterator pos, T&& value);
	inline iterator insert(iterator pos, const T& value);
	inline iterator insert(iterator pos, size_t num, const T& value);
	inline iterator insert(iterator pos, T&& value);
	inline iterator erase(iterator pos);
	inline iterator erase(iterator first, iterator last);
	inline void clear();
	inline void resize(size_t size);
	inline void resize(size_t size, const T& value);


private:
	inline void _Resize(size_t size, const T& value);

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
template <typename Type>
inline static Type* allocate_memory(const size_t& size)
{
	return static_cast<Type*>(::operator new(size));
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
	m_Head = allocate_memory<node_type>(sizeof(node_type));	//创建头节点
	m_Head->m_Next = nullptr;
	m_Head->m_Pre = nullptr;
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
	clear();
	delete m_Head;
	m_Head = nullptr;
	m_Tail = nullptr;
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
*  @name        : inline LinkList<T>::iterator LinkList<T>::Begin()const
*  @description : 返回首节点的迭代器
*  @param		: None
*  @return		: iterator(m_Head->m_Next)
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::Begin()const
{
	if (IsEmpty()) {
		return End();
	}
	return iterator(m_Head->m_Next);
}
	
/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::End()const
*  @description : 返回最后一个元素下一个位置的迭代器
*  @param		: None
*  @return		: ++iterator(m_Tail)
*  @notice      : 不知道该怎么实现原本功能的End()就自定义了指向最后一个元素。
	随后发现把最后一个元素的迭代器加加一下就能达到预期的效果，虽然不知道原因，但只能将就着用。
	知道原因了，加加后成了空指针，Begin()加加最后也会成空指针，所以迭代就停了，但这样无法让迭代器前移。
	最后决定定义成指向尾节点
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::End()const
{
	iterator it(m_Tail);
	return it;
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
	
/**
*  @name        : inline void LinkList<T>::PopBack()
*  @description : 尾部删除元素
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PopBack()
{
	assert(!IsEmpty());
	node_type* node = m_Tail;
	m_Tail = m_Tail->m_Pre;
	m_Tail->m_Next = node->m_Next;
	delete node;
	node = nullptr;
	m_Size--;
}

/**
*  @name        : inline void LinkList<T>::PopFront()
*  @description : 头部删除元素
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::PopFront()
{
	assert(!IsEmpty());
	node_type* node = m_Head->m_Next;
	m_Head->m_Next = node->m_Next;
	if (node->m_Next) {
		node->m_Next->m_Pre = m_Head;	//更新前驱元
	}
	delete node;
	node = nullptr;
	m_Size--;
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::empalce(iterator pos, T&& value)
*  @description : pos前就地构造对象
*  @param		: ListIterator<T> pos, T&& value
*  @return		: iterator(pos.m_Pointer->m_Pre)
*  @notice      : 由此了解到可变模板参数，但不是很了解，所以没有应用
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::empalce(iterator pos, T&& value)
{
	node_type* node = allocate_memory<node_type>(sizeof(node_type));	//使用全局new分配内存
	new ((void*) &(node->m_Data)) T(value);	//手动构造函数
	if (!IsEmpty()) {
		node->insert(pos.m_Pointer);
	}
	else {
		node->m_Next = m_Head->m_Next;
		node->m_Pre = m_Head;
		m_Head->m_Next = node;
	}
	if (!node->m_Next) {	//更新尾节点
		m_Tail = node;
	}
	m_Size++;
	return iterator(pos.m_Pointer->m_Pre);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, const T& value)
*  @description : 在pos前插入value
*  @param		: ListIterator<T> pos, const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, const T& value)
{
	node_type* node = new node_type(value);
	if (IsEmpty()) {
		node->m_Next = m_Head->m_Next;
		node->m_Pre = m_Head;
		m_Head->m_Next = node;
	}
	else {
		node->insert(pos.m_Pointer);
	}
	if (!node->m_Next) {	//更新节点
		m_Tail = node;
	}
	m_Size++;
	return iterator(node);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, size_t num, const T& value)
*  @description : 在pos前插入num个value
*  @param		: ListIterator<T> pos, size_t num, const T& value
*  @return		: ++it
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, size_t num, const T& value)
{
	iterator it(pos);
	if (!IsEmpty()) {
		--it;	//偏移到插入点的前一个迭代器
	}
	for (; num > 0; num--, pos) {
		insert(pos, value);
		if (pos.m_Pointer == m_Head) {
			pos++;
		}
	}
	return ++it;
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, T&& value)
*  @description : 在pos前插入value,右值版本
*  @param		: ListIterator<T> pos, const T&& value
*  @return		: ++it
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::insert(iterator pos, T&& value)
{
	return empalce(pos, std::move(value));
}

/**
*  @name        : LinkList<T>::iterator LinkList<T>::erase(iterator pos)
*  @description : 删除pos处的元素
*  @param		: iterator pos
*  @return		: 移除后的下一个迭代器
*  @notice      : 这才发现加个尾节点很麻烦
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::erase(iterator pos)
{
	assert(!IsEmpty());
	node_type* node = pos.m_Pointer;
	++pos;
	node->m_Pre->m_Next = node->m_Next;
	if (node->m_Next) {	//不是尾节点
		node->m_Next->m_Pre = node->m_Pre;
	}
	else {	//更新尾节点
		m_Tail = node->m_Pre;
	}
	delete node;
	m_Size--;
	return iterator(pos);
}

/**
*  @name        : inline LinkList<T>::iterator LinkList<T>::erase(iterator pos)
*  @description : 删除first到last的元素
*  @param		: iterator first, iterator last
*  @return		: 移除后的下一个迭代器
*  @notice      : None
*/
template <typename T>
typename inline LinkList<T>::iterator LinkList<T>::erase(iterator first, iterator last)
{
	for (; first != last;) {
		erase(first++);
	}
	erase(last);
	return ++last;
}

/**
*  @name        : inline void LinkList<T>::clear()
*  @description : 删除所有元素
*  @param		: None
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::clear()
{	
	node_type* node = m_Head->m_Next;
	m_Head->m_Next = nullptr;
	m_Tail = m_Head;
	while (node) {
		node_type* tmp = node->m_Next;
		delete node;
		node = tmp;
	}
	m_Size = 0;
}

/**
*  @name        : inline void resize(size_t size)
*  @description : 重新指定大小
*  @param		: size_t size, const T& value
*  @return		: None
*  @notice      : None
*/
template <typename T>
inline void LinkList<T>::_Resize(size_t size, const T& value)
{
	if (size < m_Size) {	//删除多余节点
		for (; size < m_Size;) {
			PopBack();
		}
	}
	else {	//构造新节点
		for (; size > m_Size;) {
			PushBack(value);
		}
	}
}
template <typename T>
inline void LinkList<T>::resize(size_t size)
{
	_Resize(size, T());
}
template <typename T>
inline void LinkList<T>::resize(size_t size, const T& value)
{
	_Resize(size, value);
}

}

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // !__LINKLIST__H__
