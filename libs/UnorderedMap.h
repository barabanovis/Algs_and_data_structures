#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <random>
#include <iostream>
#include <vector>


template <typename Key_type = int, typename Value_type>
class UnorderedMap {
private:
	Node<Key_type, Value_type>** _table;
	size_t _size;
	size_t _capacity;

	size_t hash(const int value) const;

	void rehash();


	struct Node {
		Key_type key;
		Value_type value;
		Node<Key_type, Value_type>* next;

		Node(Key_type key, Value_type value, Node* next) :key(key), value(value), next(next) {};
	};
public:
	UnorderedMap(const int capacity);

	
	UnorderedMap(const size_t capacity, const size_t fill_count, const Value_type& fill_value);

	UnorderedMap(const UnorderedMap<Key_type,Value_type>& copy);
	~UnorderedMap();

	UnorderedMap<Key_type, Value_type>& operator=(const UnorderedMap<Key_type,Value_type>& copy);
	

	void print() const;
	std::vector<Value_type> vectorization() const;

	bool insert(Key_type key, const Value_type& value);
	void insert_or_assign(Key_type key, const Value_type& value);

	bool contains(const Value_type& value) const;
	Value_type* search(Key_type key) const;
	bool erase(Key_type key);


	int count(Key_type key) const;
	int count_collisions() const;
	float load_factor() const;

	size_t get_size() const;
	size_t get_capacity() const;
};

template <typename Key_type, typename Value_type>
float UnorderedMap<Key_type, Value_type>::load_factor() const {
	int count = 0;
	for (size_t i = 0; i < _capacity; ++i) {
		if (_table[i]) {
			count++;
		}
	}
	return (float)count / _capacity;
}


//template <typename Key_type, typename Value_type>
//UnorderedMap<Key_type, Value_type>::UnorderedMap(const size_t capacity, const size_t fill_count, const Value_type& fill_value): _size(capacity), _capacity(capacity){
//	std::random_device rd;                    // �������� ��������
//	std::mt19937 gen(rd());                 // ��������� Mersenne Twister, ������������������ ����� random_device
//	std::uniform_int_distribution<int> distrib(1, 1000);  
//
//	_table = new Node<Key_type, Value_type>*[capacity]();
//
//	for (size_t i = 0; i < fill_count; i++) {
//		insert_or_assign(distrib(gen), fill_value);
//	}
//}

//template <>
//unorderedmap<float>::unorderedmap(const size_t capacity, const size_t fill_count, const float& fill_max_abs): _size(capacity), _capacity(capacity) {
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	
//	
//	std::uniform_int_distribution<int> int_distrib(1, 1000);  
//	std::uniform_real_distribution<float> float_distrib(-fill_max_abs, fill_max_abs);
//
//	_table = new node<float>*[capacity]();
//UnorderedMap<Key_type, Value_type>
//	for (size_t i = 0; i < fill_count; i++) {
//		insert_or_assign(int_distrib(gen), float_distrib(gen));
//	}
//}

template <typename Key_type, typename Value_type>
size_t UnorderedMap<Key_type, Value_type>::get_size() const {
	return _size;
}

template <typename Key_type, typename Value_type>
size_t UnorderedMap<Key_type, Value_type>::get_capacity() const {
	return _capacity;
}

//template <typename Key_type, typename Value_type>
//size_t UnorderedMap<Key_type, Value_type>::hash(const int value) const{
//	return value % _capacity;
//}

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::UnorderedMap(const int capacity) :_size(0), _capacity(capacity) {
	_table = new Node<Key_type, Value_type>*[_capacity]();
}

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::~UnorderedMap() {
	for (size_t i = 0; i < _capacity; ++i) {
		Node<Key_type, Value_type>* ptr = _table[i];
		while (ptr) {
			Node<Key_type, Value_type>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	_size = 0;
	_capacity = 0;
}

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::UnorderedMap(const UnorderedMap<Key_type, Value_type>& copy) {
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node<Key_type, Value_type>*[_capacity];


	for (size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			_table[i] = nullptr;
			continue;
		}

		_table[i] = new Node<Key_type, Value_type>(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node<Key_type, Value_type>* ptr_table = _table[i];
		Node<Key_type, Value_type>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<Key_type, Value_type>(ptr_copy->key, ptr_copy->value,nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}


template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>& UnorderedMap<Key_type, Value_type>::operator=(const UnorderedMap<Key_type, Value_type>& copy) {
	//�������� ������� ������
	for (size_t i = 0; i < _capacity; ++i) {
		Node<Key_type, Value_type>* ptr = _table[i];
		while (ptr) {
			Node<Key_type, Value_type>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	
	// ������ �����
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node<Key_type, Value_type>*[_size];


	for (size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			continue;
		}

		_table[i] = new Node<Key_type, Value_type>(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node<Key_type, Value_type>* ptr_table = _table[i];
		Node<Key_type, Value_type>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<Key_type, Value_type>(ptr_copy->key, ptr_copy->value, nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}

template <typename Key_type, typename Value_type>
void UnorderedMap<Key_type, Value_type>::print() const {
	for (size_t i = 0; i < _capacity; i++) {
		std::cout << "$ ";
		Node<Key_type, Value_type>* cur = _table[i];
		while (cur) {
			std::cout << "[ " << cur->key << ", " << cur->value << " ] * ";
			cur = cur->next;
		}
		std::cout << '\n';
	}
}

template <typename Key_type, typename Value_type>
bool UnorderedMap<Key_type, Value_type>::contains(const Value_type& value) const {
	// ������ �� ���� ������� � ����� �������� ����� ��� ��
	for (size_t i = 0; i < _capacity; ++i) {
		Node<Key_type, Value_type>* ptr = _table[i];
		while (ptr) {
			if (ptr->value == value) {
				return true;
			}
			ptr = ptr->next;
		}
	}
	return false;
}

template <typename Key_type, typename Value_type>
int UnorderedMap<Key_type, Value_type>::count(Key_type key) const {
	size_t pos = hash(key);
	Node<Key_type, Value_type>* ptr = _table[pos];
	int result = 0;
	while (ptr) {
		result++;
		ptr = ptr->next;
	}
	return result;
}

template <typename Key_type, typename Value_type>
Value_type* UnorderedMap<Key_type, Value_type>::search(Key_type key) const {
	size_t pos = hash(key);
	Node<Key_type, Value_type>* ptr = _table[pos];
	while (ptr) {
		if (ptr->key == key) {
			return &ptr->value;
		}
		ptr = ptr->next;
	}
	return nullptr;
}

template <typename Key_type, typename Value_type>
bool UnorderedMap<Key_type, Value_type>::erase(Key_type key) {
	size_t pos = hash(key);
	Node<Key_type, Value_type>* ptr = _table[pos];

	// �������� ���������� ������, ����� ��������� ������� ��������� � ������ ������
	if (ptr->key == key) {
		_table[pos] = ptr->next;
		delete ptr;
		ptr = nullptr;
		_size -= 1;
		return true;
	}

	// ���� �� � ������, ����� ����� ������� ������� ��� ������
	// ���������������� ��������� ptr_prev �� ���������� �������
	Node<Key_type, Value_type>* ptr_prev = ptr;
	ptr = ptr->next;
	while (ptr) {
		if (ptr->key == key) {
			ptr_prev->next = ptr->next;
			delete ptr;
			ptr = nullptr;
			_size -= 1;
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

template <typename Key_type, typename Value_type>
bool UnorderedMap<Key_type, Value_type>::insert(Key_type key, const Value_type& value) {
	rehash();

	size_t pos = hash(key);
	Node<Key_type, Value_type>* ptr = _table[pos];
	// ��������, ���� �� ��� ����� �������
	while (ptr) {
		if (ptr->key == key) {
			// ���� ������� ������ � ���� ������...
			return false;
		}
		ptr = ptr->next;
	}
	// ���� �� �������...
	_table[pos] = new Node(key, value, _table[pos]);
	_size += 1;
	return true;
}

template <typename Key_type, typename Value_type>
void UnorderedMap<Key_type, Value_type>::insert_or_assign(Key_type key, const Value_type& value) {
	rehash();

	size_t pos = hash(key);
	Node<Key_type, Value_type>* ptr = _table[pos];
	while (ptr) {
		if (ptr->key == key) {
			ptr->value = value;
			return;
		}
		ptr = ptr->next;
	}
	_table[pos] = new Node(key, value, _table[pos]);
	_size += 1;
	return;
}

template <typename Key_type, typename Value_type>
void UnorderedMap<Key_type, Value_type>::rehash() {
	if (load_factor() < 0.5) {
		return;
	}


	UnorderedMap<Key_type, Value_type> new_map(_capacity * 2);
	// ������ �� ���� ��������� ������� ������
	for (size_t i = 0; i < _capacity; ++i) {
		Node<Key_type, Value_type>* ptr = _table[i];
		while (ptr) {
			new_map.insert(ptr->key, ptr->value);
			ptr = ptr->next;
		}
	}

	// Clearing current table
	delete[] _table;
	_table = nullptr;

	_capacity *= 2;
	_table = new_map._table;
	new_map._table = nullptr;
	new_map._capacity = 0;
}

template <typename Key_type, typename Value_type>
int UnorderedMap<Key_type, Value_type>::count_collisions() const {
	int res = 0;
	for (size_t i = 0; i < _capacity; ++i) {
		Node<Key_type, Value_type>* ptr = _table[i];
		bool first_flag = false;
		while (ptr) {
			if (!first_flag) {
				first_flag = true;
			}
			else {
				res += 1;
			}
			ptr = ptr->next;
		}
	}
	return res;
}
#endif