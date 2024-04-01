#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include "MyAlgorithm.hpp"
#include "Timer.h"


class Entity
{
public:
	size_t m_X, m_Y;

	Entity() {};

	Entity(size_t v)
		:m_X(v), m_Y(v) {}

	Entity(size_t x, size_t y)
		:m_X(x), m_Y(y) {}

	Entity(const Entity& other)
		:m_X(other.m_X), m_Y(other.m_Y) {}


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
	bool operator==(const Entity& e) {
		return !(*this != e);
	}
	bool operator<(const Entity& e) const {
		return m_X < e.m_X && m_Y < e.m_Y;
	}
	bool operator>(const Entity& e) const {
		return m_X > e.m_X && m_Y > e.m_Y;
	}
};

std::ostream& operator<<(std::ostream& stream, const Entity& e)
{
	stream << e.m_X << " " << e.m_Y << std::endl;
	return stream;
}

template <typename T>
void WriteFile(const size_t& num)
{
	//创建随机数引擎
	std::random_device rd;
	std::mt19937 gen(rd());
	//指定随机数的类型和范围
	std::uniform_int_distribution<size_t> dis(0, num);

	//创建文件对象
	std::ofstream ofs;
	//打开文件
	ofs.open("Data File.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	for (size_t i = 0; i < num; i++) {
		T value = T(dis(gen));
		ofs.write((char*)&value, sizeof(T));
	}
	ofs.close();
}

template <typename T>
std::vector<T>& ReadFile(std::vector<T>& data, const size_t& num)
{
	std::ifstream ifs;
	WriteFile<T>(num);
	ifs.open("Data File.dat", std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		WriteFile<T>(num);
		ifs.open("Data File.dat");
	}
	T value;
	while (ifs.read((char*) & value, sizeof(T))) {
		data.emplace_back(value);
	}
	ifs.close();
	return data;
}

template <typename T>
std::vector<T> InitData(const size_t& num)
{
	//创建随机数引擎
	std::random_device rd;
	std::mt19937 gen(rd());

	//指定随机数的类型和范围
	std::uniform_int_distribution<size_t> dis(0, num);

	std::vector<T> data;
	data.reserve(num);
	for (size_t i = 0; i < num; i++) {
		T value = T(dis(gen));
		data.emplace_back(value);
	}
	
	return data;
}


#if 0
bool Insertcmp(const size_t* e1 , const size_t* e2)
{
	return *e1 > *e2;
}
void TestInsert()
{
	std::cout << "InsertSort:\n";
	//创建随机数引擎
	std::random_device rd;
	std::mt19937 gen(rd());

	std::cout << "Data Size:10000:\n";
	{
		size_t num = 10000;
		//指定随机数的类型和范围
		std::uniform_int_distribution<size_t> dis(0, num);

		std::vector<size_t> data;
		data.reserve(num);
		for (size_t i = 0; i < num; i++) {
			data.emplace_back(dis(gen));
		}

		Timer timeCost;
		QGHW::InsertSort<size_t>(data.data(), num);
		//QGHW::InsertSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
	std::cout << "Data Size:50000:\n";
	{
		size_t num = 50000;
		std::uniform_int_distribution<size_t> dis(0, num);

		std::vector<size_t> data;
		data.reserve(num);
		for (size_t i = 0; i < num; i++) {
			data.emplace_back(dis(gen));
		}

		Timer timeCost;
		QGHW::InsertSort<size_t>(data.data(), num);
		//QGHW::InsertSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
	std::cout << "Data Size:200000:\n";
	{
		size_t num = 200000;
		std::uniform_int_distribution<size_t> dis(0, num);

		std::vector<size_t> data;
		data.reserve(num);
		for (size_t i = 0; i < num; i++) {
			data.emplace_back(dis(gen));
		}

		Timer timeCost;
		QGHW::InsertSort<size_t>(data.data(), num);
		//QGHW::InsertSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
}

bool Mergecmp(const size_t* v1, const size_t* v2)
{
	return *v1 > *v2;
}
void TestMerge()
{
	std::cout << "MergeSort:\n";

	std::cout << "Data Size:10000:\n";
	{
		size_t num = 10000;

		std::vector<size_t> data = InitData<size_t>(num);

		Timer timeCost;
		QGHW::MergeSort<size_t>(data.data(), num);
		//QGHW::MergeSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
	std::cout << "Data Size:50000:\n";
	{
		size_t num = 50000;

		std::vector<size_t> data = InitData<size_t>(num);

		Timer timeCost;
		QGHW::MergeSort<size_t>(data.data(), num);
		//QGHW::MergeSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
	std::cout << "Data Size:200000:\n";
	{
		size_t num = 200000;

		std::vector<size_t> data = InitData<size_t>(num);

		Timer timeCost;
		QGHW::MergeSort<size_t>(data.data(), num);
		//QGHW::MergeSort<size_t>(data.data(), num, [](auto v1, auto v2) {return *v1 < *v2; });
	}
}

bool Quickcmp(const size_t* v1, const size_t* v2)
{
	return *v1 > *v2;
}
#endif


template <typename T, typename Func = void(T* const,const size_t,bool(const T*, const T*))>
inline void TestInLargeData(const size_t& num, Func function)
{
	std::cout << "Data Size:" << num << ":	";
	
	//std::vector<T> data = InitData<T>(num);
	std::vector<T> data;
	data.reserve(num);
	data = ReadFile<T>(data, num);

	Timer timeCost;
	//QGHW::print<T>(data.data(), num);
	function(data.data(), num, QGHW::DefaultCmp<T>);
}

template <typename T, typename Func = void(T* const, const size_t, bool(const T*, const T*))>
inline void TestThreeTimes(const char* name, Func function)
{
	std::cout << name << ":\n";
	TestInLargeData<T>(10000, function);
	TestInLargeData<T>(50000, function);
	TestInLargeData<T>(200000, function);
}


template <typename T, typename Func = void(T* const, const size_t, bool(const T*, const T*))>
inline void TestInRepeatedly(const char* name, Func function)
{
	std::cout << name << std::endl;

	std::cout << "Data Size:100 Times Of Repetition:50000	";
	Timer timeCost;
	for (size_t i = 0; i < 50000; i++) {
		size_t num = 100;
		std::vector<T> data = InitData<T>(num);
		function(data.data(), num, QGHW::DefaultCmp<T>);
	}
}


int main()
{
	//TestInsert();
	//TestMerge();
	std::cout << "Test In Large Data Sort:\n";

	std::cout << "type: size_t\n";
	std::cout << "稍等，插入排序有点慢\n";
	TestThreeTimes<size_t>("InsertSort", QGHW::InsertSort);
	TestThreeTimes<size_t>("MergeSort", QGHW::MergeSort);
	TestThreeTimes<size_t>("QuickSort", QGHW::QuickSort);
	TestThreeTimes<size_t>("CountingSort", QGHW::CountingSort);
	TestThreeTimes<size_t>("RadixCountSort", QGHW::RadixCountSort);

	std::cout << "type: Entity\n";
	std::cout << "稍等，插入排序有点慢,这个是真的慢\n";
	TestThreeTimes<Entity>("InsertSort", QGHW::InsertSort);
	TestThreeTimes<Entity>("MergeSort", QGHW::MergeSort);
	TestThreeTimes<Entity>("QuickSort", QGHW::QuickSort);


	std::cout << "\nTest In Repeatedly Sort:\n";
	std::cout << "type: size_t\n";

	TestInRepeatedly<size_t>("InsertSort", QGHW::InsertSort);
	TestInRepeatedly<size_t>("MergeSort", QGHW::MergeSort);
	TestInRepeatedly<size_t>("QuickSort", QGHW::QuickSort);
	TestInRepeatedly<size_t>("CountingSort", QGHW::CountingSort);
	TestInRepeatedly<size_t>("RadixCountSort", QGHW::RadixCountSort);

	std::cout << "type: Entity\n";
	TestInRepeatedly<Entity>("InsertSort", QGHW::InsertSort);
	TestInRepeatedly<Entity>("MergeSort", QGHW::MergeSort);
	TestInRepeatedly<Entity>("QuickSort", QGHW::QuickSort);

}