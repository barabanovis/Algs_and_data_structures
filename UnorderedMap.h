#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

template <typename T>
struct Node {
	T value;
	Node* next;
};

template <typename T>
class UnorderedMap {
private:
	Node** _table;
public:
	UnorderedMap(const size_t size);

	// Заполнение СВ согласно варианту
	// UnorderedMap(const size_t size, const T lower)

	UnorderedMap(const UnorderedMap& copy);
	~UnorderedMap();

	void operator=(const UnorderedMap& copy);
	
	void print();

	bool insert(int key, const T& value);
	void insert_or_assign(int key, const T& value);
	bool contains(const T& value);
	T* search(int key);
	bool erase(int key);
	int count(int key);
};
#endif