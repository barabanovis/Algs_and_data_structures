#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iostream>
#include <random>
#include <vector>
#include <cstddef>

template <typename Key_type = int, typename Value_type = int>
class UnorderedMap {
private:
	struct Node {
		Key_type key;
		Value_type value;
		Node* next;

		Node(Key_type key, Value_type value, Node* next) :key(key), value(value), next(next) {};
	};

	Node** _table;
	std::size_t _size;
	std::size_t _capacity;

	std::size_t hash(const Key_type& value) const;

	void rehash();
public:
	UnorderedMap();
	UnorderedMap(const int capacity);

	UnorderedMap(const UnorderedMap<Key_type,Value_type>& copy);
	~UnorderedMap();

	UnorderedMap<Key_type, Value_type>& operator=(const UnorderedMap<Key_type,Value_type>& copy);
	

	void print() const;

	bool insert(const Key_type key, const Value_type& value);
	void insert_or_assign(const Key_type key, const Value_type& value);

	bool contains(const Value_type& value) const;
	Value_type* search(const Key_type key) const;
	Value_type* search_if(const Key_type key, bool (*predicate)(Value_type)) const;// ищет первый объект, соответствующий ключу key и для которого выполняется предикат
	
	std::vector<Value_type> all_with_key(const Key_type key) const;

	bool erase(Key_type key);
	bool erase_if(Key_type key, bool (*predicate)(Value_type));

	int count(const Key_type key) const;
	int count_collisions() const;
	float load_factor() const;

	std::size_t get_size() const;
	std::size_t get_capacity() const;
};

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::UnorderedMap() :_size(0), _capacity(10) {
	_table = new Node * [_capacity]();
}

template <typename Key_type, typename Value_type>
float UnorderedMap<Key_type, Value_type>::load_factor() const {
	int count = 0;
	for (std::size_t i = 0; i < _capacity; ++i) {
		if (_table[i]) {
			count++;
		}
	}
	return (float)count / _capacity;
}

template <typename Key_type, typename Value_type>
std::size_t UnorderedMap<Key_type, Value_type>::get_size() const {
	return _size;
}

template <typename Key_type, typename Value_type>
std::vector<Value_type> UnorderedMap<Key_type, Value_type>::all_with_key(const Key_type key) const{
	std::vector<Value_type> result(0);
	size_t pos = hash(key);

	Node* ptr = _table[pos];
	while (ptr) {
		result.push_back(ptr->value);
		ptr = ptr->next;
	}
	return result;
}

template <typename Key_type, typename Value_type>
std::size_t UnorderedMap<Key_type, Value_type>::get_capacity() const {
	return _capacity;
}

template <typename Key_type, typename Value_type>
std::size_t UnorderedMap<Key_type, Value_type>::hash(const Key_type& value) const {
	// Работает для: string, int, double, и ссылок на них
	using PlainType = std::remove_cv_t<std::remove_reference_t<Key_type>>;
	return std::hash<PlainType>{}(value) % _capacity;
}

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::UnorderedMap(const int capacity) :_size(0), _capacity(capacity) {
	_table = new Node*[_capacity]();
}

template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>::~UnorderedMap() {
	for (std::size_t i = 0; i < _capacity; ++i) {
		Node* ptr = _table[i];
		while (ptr) {
			Node* ptr_next = ptr->next;
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
	_table = new Node*[_capacity];


	for (std::size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			_table[i] = nullptr;
			continue;
		}

		_table[i] = new Node(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node* ptr_table = _table[i];
		Node* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node(ptr_copy->key, ptr_copy->value,nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}


template <typename Key_type, typename Value_type>
UnorderedMap<Key_type, Value_type>& UnorderedMap<Key_type, Value_type>::operator=(const UnorderedMap<Key_type, Value_type>& copy) {
	//�������� ������� ������
	for (std::size_t i = 0; i < _capacity; ++i) {
		Node* ptr = _table[i];
		while (ptr) {
			Node* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	
	// ������ �����
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node*[_size];


	for (std::size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			continue;
		}

		_table[i] = new Node(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node* ptr_table = _table[i];
		Node* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node(ptr_copy->key, ptr_copy->value, nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}

template <typename Key_type, typename Value_type>
void UnorderedMap<Key_type, Value_type>::print() const {
	for (std::size_t i = 0; i < _capacity; i++) {
		std::cout << "$ ";
		Node* cur = _table[i];
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
	for (std::size_t i = 0; i < _capacity; ++i) {
		Node* ptr = _table[i];
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
int UnorderedMap<Key_type, Value_type>::count(const Key_type key) const {
	std::size_t pos = hash(key);
	Node* ptr = _table[pos];
	int result = 0;
	while (ptr) {
		result++;
		ptr = ptr->next;
	}
	return result;
}

template <typename Key_type, typename Value_type>
Value_type* UnorderedMap<Key_type, Value_type>::search(const Key_type key) const {
	std::size_t pos = hash(key);
	Node* ptr = _table[pos];
	while (ptr) {
		if (ptr->key == key) {
			return &ptr->value;
		}
		ptr = ptr->next;
	}
	return nullptr;
}

template <typename Key_type, typename Value_type>
Value_type* UnorderedMap<Key_type, Value_type>::search_if(const Key_type key, bool (*predicate)(Value_type)) const {
	std::size_t pos = hash(key);
	Node* ptr = _table[pos];
	while (ptr) {
		if (predicate(ptr->value)) {
			return &ptr->value;
		}
		ptr = ptr->next;
	}
	return nullptr;
}

template <typename Key_type, typename Value_type>
bool UnorderedMap<Key_type, Value_type>::erase(const Key_type key) {
	std::size_t pos = hash(key);
	Node* ptr = _table[pos];

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
	Node* ptr_prev = ptr;
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
bool UnorderedMap<Key_type, Value_type>::erase_if(const Key_type key, bool (*predicate)(Value_type)) {
	std::size_t pos = hash(key);
	Node* ptr = _table[pos];

	// �������� ���������� ������, ����� ��������� ������� ��������� � ������ ������
	if (predicate(ptr->value)) {
		_table[pos] = ptr->next;
		delete ptr;
		ptr = nullptr;
		_size -= 1;
		return true;
	}

	// ���� �� � ������, ����� ����� ������� ������� ��� ������
	// ���������������� ��������� ptr_prev �� ���������� �������
	Node* ptr_prev = ptr;
	ptr = ptr->next;
	while (ptr) {
		if (predicate(ptr->value)) {
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
bool UnorderedMap<Key_type, Value_type>::insert(const Key_type key, const Value_type& value) {
	rehash();

	std::size_t pos = hash(key);
	Node* ptr = _table[pos];
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
void UnorderedMap<Key_type, Value_type>::insert_or_assign(const Key_type key, const Value_type& value) {
	rehash();

	std::size_t pos = hash(key);
	Node* ptr = _table[pos];
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
	for (std::size_t i = 0; i < _capacity; ++i) {
		Node* ptr = _table[i];
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
	for (std::size_t i = 0; i < _capacity; ++i) {
		Node* ptr = _table[i];
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