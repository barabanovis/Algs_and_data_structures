#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

template <typename T>
struct Node {
	int key;
	T value;
	Node<T>* next;

	Node(int key, T value, Node* next) :key(key), value(value), next(next) {};
};



template <typename T>
class UnorderedMap {
private:
	Node<T>** _table;
	size_t _size;
	size_t _capacity;

	static size_t hash(const T& value);

	void rehash();
public:
	UnorderedMap(const size_t size);

	// Заполнение СВ согласно варианту
	// UnorderedMap(const size_t size, const T lower)

	UnorderedMap(const UnorderedMap<T>& copy);
	//КОНСТРУКТОР ЗАПОЛНЯЮЩИЙ СЛУЧАЙНЫМИ ЗНАЧЕНИЯМИ!!! ДОПИСАТЬ!!!
	~UnorderedMap();

	UnorderedMap<T>& operator=(const UnorderedMap<T>& copy);
	

	void print() const;

	bool insert(int key, const T& value);
	void insert_or_assign(int key, const T& value);

	bool contains(const T& value) const;
	T* search(int key) const;
	bool erase(int key);
	int count(int key) const;
};

template<typename T>
size_t UnorderedMap<T>::hash(const T& value) {
	return value % _capacity;
}

template <typename T>
UnorderedMap<T>::UnorderedMap(const size_t size) :_size(size), _capacity(size) {
	_table = new Node<T>*[size]();
}

template <typename T>
UnorderedMap<T>::~UnorderedMap() {
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		while (ptr) {
			Node<T>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	_size = 0;
	_capacity = 0;
}

template <typename T>
UnorderedMap<T>::UnorderedMap(const UnorderedMap<T>& copy) {
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node<T>*[_size];


	for (size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			continue;
		}

		_table[i] = new Node<T>(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node<T>* ptr_table = _table[i];
		Node<T>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<T>(ptr_copy->key, ptr_copy->value,nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}


template <typename T>
UnorderedMap<T>& UnorderedMap<T>::operator=(const UnorderedMap<T>& copy) {
	//Удаление текущих данных
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		while (ptr) {
			Node<T>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	
	// Запись новых
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node<T>*[_size];


	for (size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			continue;
		}

		_table[i] = new Node<T>(copy._table[i]->key, copy._table[i]->value, nullptr);
		Node<T>* ptr_table = _table[i];
		Node<T>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<T>(ptr_copy->value, nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}

template <typename T>
void UnorderedMap<T>::print() const {
	for (size_t i = 0; i < _capacity; i++) {
		Node<T> cur = _table[i];
		while (cur) {
			cout << "[ key = " << cur->key << " ], < value = " << cur->value << " >\n";
			cur = cur->next;
		}
	}
}

template <typename T>
bool UnorderedMap<T>::contains(const T& value) const {
	// Проход по всей таблице и поиск значения черех всю неё
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		while (ptr) {
			if (ptr->value == value) {
				return true;
			}
			ptr = ptr->next;
		}
	}
	return false;
}

template <typename T>
int UnorderedMap<T>::count(int key) const {
	size_t pos = hash(key);
	Node<T>* ptr = _table[pos];
	int result = 0;
	while (ptr) {
		result++;
		ptr = ptr->next;
	}
	return result;
}

template <typename T>
T* UnorderedMap<T>::search(int key) const {
	size_t pos = hash(key);
	Node<T>* ptr = _table[pos];
	while (ptr) {
		if (ptr->key == key && ptr->value == value) {
			return ptr->value
		}
		ptr = ptr->next;
	}
	return nullptr;
}

template <typename T>
bool UnorderedMap<T>::erase(int key) {
	size_t pos = hash(key);
	Node<T>* ptr = _table[pos];

	// Отдельно рассмотрим случай, когда удаляемый элемент находится в голове списка
	if (ptr->key == key) {
		_table[pos] = ptr->next;
		delete ptr;
		ptr = nullptr;
		_size -= 1;
		return true;
	}

	// Если не в голове, тогда будем удалять элемент при помощи
	// вспомогательного указателя ptr_prev на предыдущий элемент
	Node<T>* ptr_prev = ptr;
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

template <typename T>
bool UnorderedMap<T>::insert(int key, const T& value) {
	if (_size == _capacity) {
		rehash();
	}

	size_t pos = hash(key);
	Node<T>* ptr = _table[pos];
	// Проверим, есть ли уже такой элемент
	while (ptr) {
		if (ptr->key == key) {
			// Если нашлась запись с этим ключом...
			return false;
		}
	}
	// Если не нашлось...
	_table[pos] = new Node(key, value, _table[pos]);
	_size += 1;
	return true;
}

template <typename T>
void UnorderedMap<T>::insert_or_assign(int key, const T& value) {
	if (_size == _capacity) {
		rehash();
	}

	size_t pos = hash(key);
	Node<T>* ptr = _table[pos];
	while (ptr) {
		if (ptr->key == key) {
			ptr->value = value;
			return;
		}
		ptr = ptr->next;
	}
	_table[pos] = new Node(key, value, _table[pos]);
	_size += 1;
}

template <typename T>
void UnorderedMap<T>::rehash() {
	UnorderedMap<T> new_map(_capacity * 2);
	// Проход по всем элементам таблицы подряд
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		while (ptr) {
			new_map.insert(ptr->key, ptr->value);
			ptr = ptr->next;
		}
	}

	// Clearing current table
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		while (ptr) {
			Node<T>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	_capacity *= 2;
	_table = new_map._table;
	new_map._table = nullptr;
}
#endif