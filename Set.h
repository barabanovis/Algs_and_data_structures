#ifndef SET_H
#define SET_H

struct SetNode {
	int _value;
	SetNode* _left;
	SetNode* _right;
};


class Set {
private:
	SetNode* root;
public:
	SetNode();
	SetNode(const SetNode& copy);


	void print() const;
	bool insert(int key);
	bool contains(int key) const;
	bool erase(int key);
	bool strictly_balanced() const;
};

#endif