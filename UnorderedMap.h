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

	static int hash(const T& value);
public:
	UnorderedMap(const size_t size);

	// Çàïîëíåíèå ÑÂ ñîãëàñíî âàğèàíòó
	// UnorderedMap(const size_t size, const T lower)

	UnorderedMap(const UnorderedMap<T>& copy);
	//ÊÎÍÑÒĞÓÊÒÎĞ ÇÀÏÎËÍßŞÙÈÉ ÑËÓ×ÀÉÍÛÌÈ ÇÍÀ×ÅÍÈßÌÈ!!! ÄÎÏÈÑÀÒÜ!!!
	~UnorderedMap();

	UnorderedMap<T>& operator=(const UnorderedMap<T>& copy);
	

	void print();

	bool insert(int key, const T& value);
	void insert_or_assign(int key, const T& value);

	bool contains(const T& value);
	T* search(int key);
	bool erase(int key);
	int count(int key);
};

template<typename T>
int UnorderedMap<T>::hash(const T& value) {
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

		_table[i] = new Node<T>(copy._table[i]->value, nullptr);
		Node<T>* ptr_table = _table[i];
		Node<T>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<T>(ptr_copy->value,nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}


template <typename T>
UnorderedMap<T>& UnorderedMap<T>::operator=(const UnorderedMap<T>& copy) {
	for (size_t i = 0; i < _capacity; ++i) {
		Node<T>* ptr = _table[i];
		if (!ptr) {
			continue;
		}
		while (ptr) {
			Node<T>* ptr_next = ptr->next;
			delete ptr;
			ptr = nullptr;
			ptr = ptr_next;
		}
	}
	
	_size = copy._size;
	_capacity = copy._capacity;
	_table = new Node<T>*[_size];


	for (size_t i = 0; i < _capacity; i++) {
		if (!copy._table[i]) {
			continue;
		}

		_table[i] = new Node<T>(copy._table[i]->value, nullptr);
		Node<T>* ptr_table = _table[i];
		Node<T>* ptr_copy = copy._table[i]->next;

		while (ptr_copy) {
			ptr_table->next = new Node<T>(ptr_copy->value, nullptr);
			ptr_copy = ptr_copy->next;
		}
	}
}

template <typename T>
void UnorderedMap<T>::print() {
	for (size_t i = 0; i < _capacity; i++) {
		Node<T> cur;
		if (cur = _table[i]) {
			cout << "[ key = " << cur->key << " ], < values = ";
			while (cur) {
				cout << cur->value << " ";
				cur = cur->next;
			}
			cout << " >\n";
		}
	}
}

template <typename T>
bool UnorderedMap<T>::contains(const T& value) {
	
}
#endif