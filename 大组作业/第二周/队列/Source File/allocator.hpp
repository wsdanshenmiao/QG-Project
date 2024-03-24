#include <new>
#include <assert.h>

/***************************************************************************************
 *    File Name                :   allocator.hpp
 *    CopyRight                :
 *
 *    SYSTEM                   :   Windows
 *    Create Data              :   2024.3.23
 *    Author/Corportation      :   LiWenHao
 *
 *
 *--------------------------------Revision History--------------------------------------
 *
 *
 *
 ***************************************************************************************/

/**************************************************************
 *    Multi-Include-Prevent Section
 **************************************************************/

#ifndef __ALLOCATOR__HPP__
#define __ALLOCATOR__HPP__

namespace QGHW{

/**************************************************************
 *    Struct Define Section
 **************************************************************/


template <typename T>
class allocator
{
public:
	//指定别名
	using valueType = T;
	using pointer = T*;
	using constPointer = const T*;
	using reference = T&;
	using constReference = const T&;
	using sizeType = size_t;

	//构造函数
	allocator();
	allocator(const allocator&) = default;

	inline ~allocator() = default;

	inline T* allocate(const size_t& count);
	inline void deallocate(pointer const ptr, const size_t& count);
	inline void construct(pointer ptr, constReference value);
	inline void construct(pointer ptr, valueType&& value);
	inline void destroy(pointer ptr);
};


/**************************************************************
 *    Prototype Declare Section
 **************************************************************/

 /**
  *  @Name        : inline bool operator==(const allocator<T1>&, const allocator<T2>&)
  *  @Description : 比较两个默认分配器
  *  @Parameters  : 默认分配器
  *  @Return value: true
  *  @Notice      : 两个默认分配器总是相等的
  */
template <class T1, class T2>
inline bool operator==(const allocator<T1>&, const allocator<T2>&)
{
	return true;
}


/**
 *  @Name        : inline bool operator!=(const allocator<T1>&, const allocator<T2>&)
 *  @Description : 比较两个默认分配器
 *  @Parameters  : 默认分配器
 *  @Return value: false
 *  @Notice      : 两个默认分配器总是相等的
 */
template <class T1, class T2>
inline bool operator!=(const allocator<T1>&, const allocator<T2>&)
{
	return false;
}


/**
 *  @Name        : allocator<T>::allocator()
 *  @Description : 默认构造
 *  @Parameters  : None
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
allocator<T>::allocator() {}


/**
 *  @Name        : inline T* allocator<T>::allocate(const size_t& count)
 *  @Description : 使用全局new分配内存
 *  @Parameters  : const size_t count
 *  @Return value: 返回指向分配成功的内存的指针
 *  @Notice      : None
 */
template <typename T>
inline T* allocator<T>::allocate(const size_t& count)
{
	if (count > static_cast<size_t>(-1) / sizeof(T)) {
		throw std::bad_array_new_length();
	}
	T* ptr = static_cast<T*>(::operator new(count * sizeof(T)));
	if (!ptr) {
		throw std::bad_alloc();
	}
	return ptr;
}


/**
 *  @Name        : inline void allocator<T>::deallocate(T* const ptr, const size_t& count)
 *  @Description : 使用全局delete释放内存
 *  @Parameters  : ptr指向内存的指针，count释放的个数
 *  @Return value: None
 *  @Notice      : None
 */
template <typename T>
inline void allocator<T>::deallocate(pointer const ptr, const size_t& count)
{
	assert(ptr);
	::operator delete(ptr, count * sizeof(T));
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : 在指定地址处进行构造
 *  @Parameters  : ptr指向内存的指针，value构造使用的值
 *  @Return value: None
 *  @Notice      : placement new在已知地址完成构造
 */
template <typename T>
inline void allocator<T>::construct(pointer ptr, constReference value)
{
	new (static_cast<void*>(ptr)) T(value);
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : 在指定地址处进行构造
 *  @Parameters  : ptr指向内存的指针，value构造使用的值
 *  @Return value: None
 *  @Notice      : placement new在已知地址完成构造
 */
template <typename T>
inline void allocator<T>::construct(pointer ptr, valueType&& value)
{
	new (static_cast<void*>(ptr)) T(std::move(value));	//使用右值构造元素
}


/**
 *  @Name        : inline void allocator<T>::construct(pointer ptr, const_reference value)
 *  @Description : 在指定地址处进行构造
 *  @Parameters  : ptr指向内存的指针，value构造使用的值
 *  @Return value: None
 *  @Notice      : placement new在已知地址完成构造
 */
template <typename T>
inline void allocator<T>::destroy(pointer ptr)
{
	ptr->~T();
}


}

#endif 
