#include "allocator.hpp"

/***************************************************************************************
 *    File Name                :   queue.hpp
 *    CopyRight                :
 *
 *    SYSTEM                   :   Windows
 *    Create Data              :   2024.3.23
 *    Author/Corportation      :   LiWenHao
 *
 *
 *--------------------------------Revision History--------------------------------------
 *    No    version        Data            Revised By            Item            Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
  *    Multi-Include-Prevent Section
  **************************************************************/

#ifndef __QUEUE__HPP__
#define __QUEUE__HPP__

namespace QGHW {

/**************************************************************
 *    Struct Define Section
 **************************************************************/

//队列节点
template <typename T>
class QueueNode
{
public:
	using valueType = T;
	using thisType = QueueNode<T>;
	using pointer = thisType*;

	valueType m_Data;
	pointer m_Next;

	QueueNode();
	QueueNode(const valueType& value, const pointer next);
};

/**************************************************************
 *    Prototype Declare Section
**************************************************************/

/**
 *  @Name        : QueueNode<T>::QueueNode()
 *  @Description : 默认构造
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueNode<T>::QueueNode(){}


/**
 *  @Name        : QueueNode<T>::QueueNode(const valueType& value, const pointer next)
 *  @Description : 有参构造
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueNode<T>::QueueNode(const valueType& value, const pointer next)
	:m_Data(value), m_Next(next) {}



/**************************************************************
 *    Struct Define Section
 **************************************************************/

template <typename T>
class QueueIterator
{
public:
	using thisType = QueueIterator<T>;
	using valueType = T;
	using pointer = T*;
	using reference = T&;
	using nodeType = QueueNode<T>*;

	QueueIterator();
	QueueIterator(nodeType node);
	QueueIterator(const thisType& other);

	inline reference operator*()const;
	inline pointer operator->()const;
	inline thisType& operator++();
	inline thisType operator++(int);
	inline bool operator==(const thisType& other)const;
	inline bool operator!=(const thisType& other)const;

private:
	nodeType m_Node;
};

 /**************************************************************
  *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : QueueIterator<T>::QueueIterator()
  *  @Description : 默认构造
  *  @Parameters  : None
  *  @Return value: None
  *  @Notice      : None
  */
template <typename T>
QueueIterator<T>::QueueIterator()
	:m_Node(nullptr) {}


/**
 *  @Name        : QueueIterator<T>::QueueIterator(nodeType node)
 *  @Description : 有参构造
 *  @Parameters  : nodeType node，要维护的节点
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueIterator<T>::QueueIterator(nodeType node)
	:m_Node(node) {}


/**
 *  @Name        : QueueIterator<T>::QueueIterator(const thisType& other)
 *  @Description : 拷贝构造
 *  @Parameters  : const thisType& other，要被拷贝的对象
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
QueueIterator<T>::QueueIterator(const thisType& other)
	:m_Node(other.m_Node) {}


/**
 *  @Name        : inline T& QueueIterator<T>::operator*()const
 *  @Description : 重载解引用，返回节点数据
 *  @Parameters  : None
 *  @Return value: m_Node->m_Data，节点数据
 *  @Notice      : None
 */
template <typename T>
inline T& QueueIterator<T>::operator*()const
{
	return m_Node->m_Data;
}


/**
 *  @Name        : inline T& QueueIterator<T>::operator*()const
 *  @Description : 重载成员访问运算符，返回节点数据地址
 *  @Parameters  : None
 *  @Return value: &(m_Node->m_Data)，节点数据地址
 *  @Notice      : None
 */
template <typename T>
inline T* QueueIterator<T>::operator->()const
{
	return &(m_Node->m_Data);
}


/**
 *  @Name        : inline QueueIterator<T>& QueueIterator<T>::operator++()
 *  @Description : 重载前置加加
 *  @Parameters  : None
 *  @Return value: *this
 *  @Notice      : None
 */
template <typename T>
inline QueueIterator<T>& QueueIterator<T>::operator++()
{
	this->m_Node = this->m_Node->m_Next;
	return *this;
}


/**
 *  @Name        : inline QueueIterator<T> QueueIterator<T>::operator++(int)
 *  @Description : 重载后置加加
 *  @Parameters  : None
 *  @Return value: *tmp
 *  @Notice      : None
 */
template <typename T>
inline QueueIterator<T> QueueIterator<T>::operator++(int)
{
	thisType tmp = *this;
	++(*this);
	return tmp;
}


/**
 *  @Name        : inline bool QueueIterator<T>::operator==(const thisType& other)const
 *  @Description : 迭代器比较
 *  @Parameters  : const thisType& other
 *  @Return value: this->m_Node == other.m_Node
 *  @Notice      : None
 */
template <typename T>
inline bool QueueIterator<T>::operator==(const thisType& other)const
{
	return this->m_Node == other.m_Node;
}


/**
 *  @Name        : inline bool QueueIterator<T>::operator==(const thisType& other)const
 *  @Description : 迭代器比较
 *  @Parameters  : const thisType& other
 *  @Return value: this->m_Node == other.m_Node
 *  @Notice      : None
 */
template <typename T>
inline bool QueueIterator<T>::operator!=(const thisType& other)const
{
	return !(*this == other);
}


/**************************************************************
 *    Struct Define Section
 **************************************************************/

template <typename T, typename Allocator = QGHW::allocator<T>>
class queue
{
public:
	using valueType = T;
	using nodeType = QueueNode<T>;
	using valueAllocator = Allocator;
	using nodeAllocator = QGHW::allocator<nodeType>;
	using sizeType = size_t;
	using reference = valueType&;
	using constReference = const valueType&;
	using pointer = typename valueAllocator::pointer;
	using constPointer = typename valueAllocator::constPointer;
	using iterator = QueueIterator<T>;

public:
	inline queue();
	inline queue(sizeType count, const valueType& value);
	inline queue(const queue& other);
	inline queue(queue&& other);

	inline ~queue();

	inline sizeType Size()const;
	inline bool IsEmpty()const;
	inline reference Front()const;
	inline reference Back()const;
	inline iterator Begin()const;
	inline iterator End()const;
	inline void Push(constReference value);
	inline void Push(valueType&& value);
	inline void Pop();
	inline void Assign(sizeType count, constReference value);
	//突然想起来队列好像不能做这些功能
	//inline iterator Insert(iterator pos, constReference value);
	//inline iterator Insert(iterator pos, valueType&& value);
	//inline iterator Insert(iterator pos, sizeType count, constReference value);
	//inline iterator Erase(iterator pos);
	inline void Clear();
	inline void Resize(sizeType count);
	inline void Resize(sizeType count, constReference value);
	inline void Swap(queue<T, Allocator>& other);

	inline queue<T, Allocator>& operator=(const queue<T, Allocator>& other);
	inline queue<T, Allocator>& operator=(queue<T, Allocator>&& other);

private:
	inline nodeType* FindPre(nodeType* node);

	inline void _Resize(sizeType count, constReference value);


private:
	nodeType* m_Head;
	nodeType* m_Tail;
	sizeType m_Size;
	valueAllocator m_vAllocator;
	nodeAllocator m_nAllocator;
};


/**************************************************************
 *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : inline queue<T, Allocator>::queue()
  *  @Description : 默认构造,创建头节点
  *  @Parameters  : None
  *  @Return value: None
  *  @Notice      : None
  */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue()
	:m_Size(0)
{
	m_Head = m_nAllocator.allocate(1);	//分配头节点内存
	m_Head->m_Next = m_Head;	//循环链表
	m_Tail = m_Head;
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(sizeType count, const valueType& value)
 *  @Description : 有参构造,创建头节点
 *  @Parameters  : sizeType count, const valueType& value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(sizeType count, const valueType& value)
{
	m_Head = m_nAllocator.allocate(1);	//分配头节点内存
	m_Head->m_Next = m_Head;	//循环链表
	m_Tail = m_Head;
	for (int i = 0; i < count; i++) {
		Push(std::move(value));
	}
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(const queue& other)
 *  @Description : 拷贝构造
 *  @Parameters  : const queue& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(const queue<T, Allocator>& other)
{
	m_Head = m_nAllocator.allocate(1);	//分配头节点内存
	m_Head->m_Next = m_Head;	//循环链表
	m_Tail = m_Head;
	for (queue<T, Allocator>::iterator it = other.Begin(); it != other.End(); it++) {
		this->Push(std::move(*it));
	}
}


/**
 *  @Name        : inline queue<T, Allocator>::queue(queue&& other)
 *  @Description : 移动构造
 *  @Parameters  : queue&& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::queue(queue<T, Allocator>&& other)
{
	this->m_Head = other.m_Head;
	this->m_Tail = other.m_Tail;
	this->m_Size = other.m_Size;
	other.m_Head = nullptr;
	other.m_Tail = nullptr;
	other.m_Size = 0;
}


/**
 *  @Name        : inline queue<T, Allocator>::~queue()
 *  @Description : 析构函数
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>::~queue()
{
	if (m_Head) {
		Clear();
		m_nAllocator.deallocate(m_Head, 1);	//释放头节点
	}
}


/**
 *  @Name        : inline size_t queue<T, Allocator>::Size()const
 *  @Description : 返回队列大小
 *  @Parameters  : None
 *  @Return value: m_Size
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline size_t queue<T, Allocator>::Size()const
{
	return m_Size;
}


/**
 *  @Name        : inline bool queue<T, Allocator>::IsEmpty()const
 *  @Description : 判断是否为空
 *  @Parameters  : None
 *  @Return value: m_Size == 0
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool queue<T, Allocator>::IsEmpty()const
{
	return m_Size == 0;
}


/**
 *  @Name        : inline T& queue<T, Allocator>::Front()const
 *  @Description : 返回首节点的数据
 *  @Parameters  : None
 *  @Return value: m_Head->m_Next->m_Data
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline T& queue<T, Allocator>::Front()const
{
	assert(!IsEmpty());
	return m_Head->m_Next->m_Data;
}


/**
 *  @Name        : inline T& queue<T, Allocator>::Back()const
 *  @Description : 返回尾节点的数据
 *  @Parameters  : None
 *  @Return value: m_Tail->m_Data
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline T& queue<T, Allocator>::Back()const
{
	assert(!IsEmpty());
	return m_Tail->m_Data;
}


/**
 *  @Name        : inline QueueIterator<T> queue<T, Allocator>::Begin()const
 *  @Description : 返回维护首节点的迭代器
 *  @Parameters  : None
 *  @Return value: iterator(m_Head->m_Next)
 *  @Notice      : 为空时返回Ended()
 */
template <typename T, typename Allocator>
inline QueueIterator<T> queue<T, Allocator>::Begin()const
{
	if (IsEmpty()) {
		return End();
	}
	else {
		return iterator(m_Head->m_Next);
	}
}


/**
 *  @Name        : inline QueueIterator<T> queue<T, Allocator>::End()const
 *  @Description : 返回维护头节点的迭代器
 *  @Parameters  : None
 *  @Return value: iterator(m_Head)
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline QueueIterator<T> queue<T, Allocator>::End()const
{
	return iterator(m_Head);
}


/**
 *  @Name        : inline void queue<T, Allocator>::Push(const valueType& value)
 *  @Description : 头部插入元素
 *  @Parameters  : const valueType& value，要插入的数据
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Push(constReference value)
{
	nodeType* node = m_nAllocator.allocate(1);	//分配节点内存
	m_vAllocator.construct((pointer)node, value);	//构造元素
	node->m_Next = m_Head->m_Next;
	m_Head->m_Next = node;
	if (IsEmpty()) {
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Push(valueType&& value)
 *  @Description : 头部插入元素,接收右值
 *  @Parameters  : valueType&& value，要插入的数据
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Push(valueType&& value)
{
	nodeType* node = m_nAllocator.allocate(1);	//分配节点内存
	m_vAllocator.construct((pointer)node, std::move(value));	//传入右值构造元素
	node->m_Next = m_Head->m_Next;
	m_Head->m_Next = node;
	if (IsEmpty()) {
		m_Tail = node;
	}
	node = nullptr;
	m_Size++;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Pop()
 *  @Description : 尾部删除元素
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Pop()
{
	assert(!IsEmpty());
	nodeType* node = m_Tail;
	nodeType* pre = FindPre(node);	//寻找前驱元
	pre->m_Next = node->m_Next;
	m_vAllocator.destroy((pointer)node);	//调用节点内元素的析构函数
	m_nAllocator.deallocate(node, 1);	//释放节点内存
	node = nullptr;
	m_Tail = pre;
	m_Size--;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Assign(sizeType count, constReference value)
 *  @Description : 清空后重新分配
 *  @Parameters  : sizeType count, constReference value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Assign(sizeType count, constReference value)
{
	Clear();
	for (int i = 0; i < count; i++) {
		Push(std::move(value));
	}
}


/**
 *  @Name        : inline void queue<T, Allocator>::Clear()
 *  @Description : 清除所有元素
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Clear()
{
	m_Tail->m_Next = nullptr;	//断开循环
	nodeType* node = m_Head->m_Next;	//接管元素
	m_Head->m_Next = m_Head;	//重新循环
	m_Tail = m_Head;
	while (node) {
		nodeType* tmp = node->m_Next;
		m_vAllocator.destroy((pointer)node);	//调用析构
		m_nAllocator.deallocate(node, 1);	//释放内存
		node = tmp;
	}
	m_Size = 0;
}


/**
 *  @Name        : inline void queue<T, Allocator>::Resize(sizeType count)
 *  @Description : 重置大小
 *  @Parameters  : sizeType count
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Resize(sizeType count)
{
	_Resize(count, T());
}


/**
 *  @Name        : inline void queue<T, Allocator>::Resize(sizeType count)
 *  @Description : 重置大小
 *  @Parameters  : sizeType count, constReference value
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Resize(sizeType count, constReference value)
{
	_Resize(count, T(value));
}


/**
 *  @Name        : inline void queue<T, Allocator>::Swap(queue<T, Allocator>& other)
 *  @Description : 交换两个队列
 *  @Parameters  : queue<T, Allocator>& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::Swap(queue<T, Allocator>& other)
{
	nodeType* headTmp = m_Head;
	nodeType* tailTmp = m_Tail;
	sizeType sizeTmp = m_Size;
	m_Head = other.m_Head;
	m_Tail = other.m_Tail;
	m_Size = other.Size;
	other.m_Head = headTmp;
	other.m_Tail = tailTmp;
	other.Size = sizeTmp;
}


/**
 *  @Name        : inline queue<T, Allocator>& queue<T, Allocator>::operator=(const queue<T, Allocator>& other)
 *  @Description : 赋值函数
 *  @Parameters  : const queue<T, Allocator>& other
 *  @Return value: *this
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>& queue<T, Allocator>::operator=(const queue<T, Allocator>& other)
{
	if (m_Head) {	//非空先释放原内存
		Clear();
	}
	else {	//为空
		m_Head = m_nAllocator.allocate(1);	//分配头节点内存
		m_Head->m_Next = m_Head;	//循环链表
		m_Tail = m_Head;
	}
	for (queue<T, Allocator>::iterator it = other.Begin(); it != other.End(); it++) {
		this->Push(std::move(*it));
	}
	return *this;
}


/**
 *  @Name        : inline queue<T, Allocator>& queue<T, Allocator>::operator=(queue<T, Allocator>&& other)
 *  @Description : 移动赋值
 *  @Parameters  : queue<T, Allocator>&& other
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline queue<T, Allocator>& queue<T, Allocator>::operator=(queue<T, Allocator>&& other)
{
	if (m_Head) {	//非空先释放原内存
		Clear();
		m_nAllocator.deallocate(m_Head, 1);	//释放头节点
	}
	this->m_Head = other.m_Head;
	this->m_Tail = other.m_Tail;
	this->m_Size = other.m_Size;
	other.m_Head = nullptr;
	other.m_Tail = nullptr;
	other.m_Size = 0;
	return *this;
}


/**
 *  @Name        : inline bool operator==(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列是否相等
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator==(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	if (left.Size() != right.Size()) {
		return false;
	}
	for (QueueIterator<T> itl = left.Begin(), itr = right.Begin()
		; itl != left.End(); itl++, itr++) {
		if (*itl != *itr) {
			return false;
		}
	}
	return true;
}


/**
 *  @Name        : inline bool operator!=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列是否相等
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator!=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left == right);
}


/**
 *  @Name        : inline bool operator<(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列的大小
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator<(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	size_t size = left.Size() < right.Size() ? left.Size() : right.Size();
	int i = 0;
	for (QueueIterator<T> itl = left.Begin(), itr = right.Begin()
		; i < size; itl++, itr++, i++) {
		if (*itl > *itr) {
			return false;
		}
	}
	if (left.Size() < right.Size()) {	//前面元素都相等，就看大小
		return true;
	}
	return false;
}


/**
 *  @Name        : inline bool operator<=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列的大小
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator<=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return (left < right || left == right);
}


/**
 *  @Name        : inline bool operator>(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列的大小
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator>(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left <= right);
}


/**
 *  @Name        : inline bool operator>=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
 *  @Description : 判断两个队列的大小
 *  @Parameters  : 两个队列
 *  @Return value: true or false
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline bool operator>=(const queue<T, Allocator>& left, const queue<T, Allocator>& right)
{
	return !(left < right);
}





/**
 *  @Name        : inline QueueNode<T>* queue<T, Allocator>::FindPre(nodeType* node)
 *  @Description : 寻找前驱元
 *  @Parameters  : nodeType* node，要寻找前驱元的节点
 *  @Return value: pre
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline QueueNode<T>* queue<T, Allocator>::FindPre(nodeType* node)
{
	assert(node);
	nodeType* pre;
	for (pre = m_Head; pre->m_Next != node; pre = pre->m_Next);
	return pre;
}


/**
 *  @Name        : inline void queue<T, Allocator>::_Resize(sizeType count, constReference value)
 *  @Description : 重置大小
 *  @Parameters  : sizeType count
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T, typename Allocator>
inline void queue<T, Allocator>::_Resize(sizeType count, constReference value)
{
	if (0 <= count && count <= m_Size) {
		for (size_t i = count; i < m_Size;) {
			Pop();
		}
	}
	if (count > m_Size) {
		for (size_t i = m_Size; i < count; i++) {
			Push(std::move(value));
		}
	}
}




}

#endif 
