#ifndef __MYALGORITHM__HPP__
#define __MYALGORITHM__HPP__

#include <vector>
#include <iostream>

namespace QGHW {


//辅助打印函数
template <typename T>
inline void print(T* ptr, const size_t count)
{
	for (size_t i = 0; i < count; i++) {
		std::cout << *(ptr + i) << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
}




//默认比较函数
template <typename T>
inline bool DefaultCmp(const T* v1, const T* v2)
{
	return *v1 > *v2;
}




//插入排序
template <typename T>
inline void InsertSort(T* const ptr, const size_t count, bool cmp(const T* v1, const T* v2) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	for (size_t i = 1; i < count; i++) {	//从第二个元素开始
		T value = *(ptr + i);	//记录第i个元素
		long long j = i - 1;	//要插入元素的前一个元素
		for (; j >= 0 && cmp(ptr + j, &value);) {	//cmp返回true时执行
			//*(ptr + j + 1) = *(ptr + j);	//若第j个元素比value大，第j个元素后移
			j--;	//索引前移
		}
		//使用memmove在元素内存很大时可显著提速
		std::memmove(ptr + j + 2, ptr + j + 1, sizeof(T) * (i - j - 1));
		*(ptr + j + 1) = value;	//插入元素
	}
}





//归并排序递归函数
template <typename T>
inline void SeparateAndMerge(T* const ptr, std::vector<T>& tmpData, size_t left, size_t right, bool cmp(const T*, const T*))
{
	//分离到只剩一个后递归停止
	if (left < right) {
		//中间索引
		size_t mid = (left + right) / 2;
		//左侧分离
		SeparateAndMerge(ptr, tmpData, left, mid, cmp);
		//右侧分离
		SeparateAndMerge(ptr, tmpData, mid + 1, right, cmp);
		//分离后合并
		size_t lpos = left, rpos = mid + 1;
		//合并前后的下标
		size_t pos = left;
		for (; lpos <= mid && rpos <= right;) {
			//若返回true取右侧，也就是左侧大于右侧
			if (cmp(ptr + lpos, ptr + rpos)) {
				tmpData[pos++] = *(ptr + rpos++);
			}
			else {
				tmpData[pos++] = *(ptr + lpos++);
			}
		}
		//左侧剩余
		for (; lpos <= mid;) {
			tmpData[pos++] = *(ptr + lpos++);
		}
		//右侧剩余
		for (; rpos <= right;) {
			tmpData[pos++] = *(ptr + rpos++);
		}
		std::memmove(ptr + left, tmpData.data() + left, (right - left + 1) * sizeof(T));
		//使用std::mommove好像更快一点
		//std::copy(tmpData.data() + left, tmpData.data() + right + 1, ptr + left);
	}
}

//归并排序
template <typename T>
inline void MergeSort(T* const ptr, const size_t count, bool cmp(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//储存分离后合并的数据
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, T(*ptr));
	//递归分离
	SeparateAndMerge(ptr, tmpData, 0, count - 1, cmp);
}




//快速排序
template <typename T>
inline void QuickSort(T* const ptr, const size_t count, bool cmp(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//选定第一个元素为中心轴
	T pivot = *ptr;
	//左右指针
	T* left = ptr, * right = ptr + count - 1;
	if (left < right) {
		for (; left < right;) {
			//以递增为例，若右指针指向的元素比中心轴大或相等，右指针减减
			while (left < right && cmp(right, &pivot) || *right == pivot) {
				--right;
			}
			//否则右指针的元素移到左指针处
			*left = *right;
			//若左指针指向的元素比中心轴小或相等，左指针加加
			while (left < right && cmp(&pivot, left) || *left == pivot) {
				++left;
			}
			//否则左指针的元素移到右指针处
			*right = *left;
		}
		//确定中心轴的位置
		*left = pivot;
		//左侧递归
		QuickSort(ptr, left - ptr, cmp);
		//右侧递归
		QuickSort(left + 1, count - (left + 1 - ptr), cmp);
	}
}




//计数排序,暂时只能排整数,第三个参数为占位参数方便统一测试
template <typename T>
inline void CountingSort(T* const ptr, const size_t count,bool (const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//寻找最大值
	size_t max = *ptr;
	for (size_t i = 0; i < count; i++) {
		if (*(ptr + i) > max) {
			max = *(ptr + i);
		}
	}
	//计数数组
	std::vector<size_t> countArray;
	countArray.reserve(max + 1);
	countArray.resize(max + 1, 0);
	for (size_t i = 0; i < count; countArray[*(ptr + i)]++, i++);
	//累计数组，提高稳定性，最后要倒叙遍历
	for (size_t i = 1; i < max + 1; countArray[i] += countArray[i - 1], i++);
	//进行排序
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, 0);
	for (size_t i = count; i > 0; i--) {
		//把第i个原始数放在累计数组中第原始数个累计数减一的下标处
		tmpData[countArray[*(ptr + i - 1)]-- - 1] = *(ptr + i - 1);
	}
	std::memcpy(ptr, tmpData.data(), count * sizeof(T));
}




//基数排序,暂时只能排整数,采用LSD基数排序
template <typename T>
inline void RadixCountSort(T* const ptr, const size_t count, bool(const T*, const T*) = DefaultCmp)
{
	if (!count || !ptr) {
		return;
	}
	//寻找最大值
	size_t max = *ptr;
	for (size_t i = 0; i < count; i++) {
		if (*(ptr + i) > max) {
			max = *(ptr + i);
		}
	}
	std::vector<T> tmpData;
	tmpData.reserve(count);
	tmpData.resize(count, 0);
	//分别按每个位分配
	for (size_t digit = 1; max / digit > 0; digit *= 10) {
		//每一位的计数排序
		std::vector<size_t> countArr;
		countArr.resize(10, 0);
		//*(ptr + i) / digit为需要排序的位数，如123/100=1；再%10为要计数的数
		for (size_t i = 0; i < count; countArr[*(ptr + i) / digit % 10]++, i++);
		//累计数组，方便排序
		for (size_t i = 1; i < 10; countArr[i] += countArr[i - 1], i++);
		//收集按位排序后的数据
		for (size_t i = count; i > 0; i--) {
			//把第i个原始数放在累计数组中第原始数个累计数减一的下标处
			tmpData[countArr[*(ptr + i - 1) / digit % 10]-- - 1] = *(ptr + i - 1);
		}
		std::memcpy(ptr, tmpData.data(), count * sizeof(T));
	}
}





}



#endif // !__MYALGORITHM__HPP__
