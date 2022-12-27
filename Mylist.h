#ifndef Mylist_h
#define Mylist_h

#include <iostream>

using namespace std;

template <typename T>
class Node
{
private:
	T elem; //data element 
	Node* next; //Link (pointer) to the next Node
	Node* prev; //Link (pointer) to the previous Node
	template <typename T2> friend class Mylist;

public:
	Node() {
		next = NULL;
		prev = NULL;
	}
	Node(T elem) : elem(elem), next(NULL), prev(NULL)
	{}
};
//==============================================================


template <typename T>
class Mylist
{
private:
	Node<T>* head; 	// pointer to the head of List
	Node<T>* tail; 	// pointer to the tail of List
	int Size = 0;
public:
	Mylist(); // empty list constructor
	~Mylist(); // destructor to clean up all nodes
	bool empty() const; // is list empty?
	const T& front() const; // get the value (element) from front Node<T> of list
	const T& back() const;  // get the value (element) from last Node<T> of the List 
	void addBefore(Node<T>* ptr, const T& elem);	 //add a new node before ptr
	void addFront(const T& elem); // add a new node to the front of list
	void addBack(const T& elem); //add a new node to the back of the list
	void remove(Node<T>* v);
	void removeFront(); // remove front node from list
	void removeBack();  // remove last node from list
	void reverseList();	// reverse the list
	int size();
	bool isPalindrome(); //check if the List is Palindrome or not
	void display() const;	// display all element of the list
	//Iterator
	class iterator;   //Forwarding declarion of iterator class
	iterator begin()
	{
		//todo
		return iterator(head->next);
	}
	iterator end()
	{
		//todo
		return iterator(tail);
	}

	class iterator
	{
		//complete the itereator class (which include iterator traits)
	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using reference = Node<T>&;
		using pointer = Node<T>*;
	public:
		T& operator*();
		bool operator== (const iterator& p)const;
		bool operator!= (const iterator& p)const;
		Node<T>* key();
		iterator& operator++();
		iterator& operator--();
		friend class Mylist;
	private:
		Node<T>* v;
		iterator(Node<T>* u);
	};
};

template <typename T>
Mylist<T>::Mylist()
{
	this->head = new Node<T>();
	this->tail = new Node<T>();
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
template <typename T>
Mylist<T>::~Mylist() // destructor to clean up all nodes
{
	while (!empty())
		removeFront();
}
//============================================================
template <typename T>
bool Mylist<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================
template <typename T>
const T& Mylist<T>::front() const // get front element
{
	if (!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
const T& Mylist<T>::back() const // get front element
{
	if (!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void Mylist<T>::addBefore(Node<T>* ptr, const T& elem)
{
	Node<T>* tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev = tmp;

}
//============================================================
template <typename T>
void Mylist<T>::addFront(const T& elem) // add to front of list
{
	addBefore(this->head->next, elem);
	++Size;
}
//============================================================
template <typename T>
void Mylist<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
	++Size;
}
//============================================================
template <typename T>
void Mylist<T>::remove(Node<T>* v) { // remove front item from list
	//Node<T>* v = new Node<T>(elem);
	Node<T>* u = v->prev;
	Node<T>* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
	--Size;
}
template <typename T>
void Mylist<T>::removeFront() // remove front item from list
{
	if (!empty())
	{
		Node<T>* tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
	--Size;
}
//============================================================
template <typename T>
void Mylist<T>::removeBack() // remove last item from list
{
	if (!empty())
	{
		Node<T>* tmp = this->tail->prev;
		this->tail->prev = tmp->prev;
		tmp->prev->next = tail;
		delete tmp;
	}
	--Size;
}
//============================================================
template <typename T>
int Mylist<T>::size() // size of list
{
	return Size;
}

//============================================================
template <typename T>
void Mylist<T>::display() const
{
	Node<T>* curr = head;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl << "|";
	curr = head;
	while (curr != NULL)
	{
		if (curr == head)		cout << " Head |";
		else if (curr == tail)	cout << " Tail |";
		else 					cout << setw(5) << curr->elem << " |";

		curr = curr->next;
	}
	curr = head;
	cout << endl;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl;
}

template <typename T> T& Mylist<T>::iterator::operator*() {
	return v->elem;
}
// checks for operator
template <typename T>bool Mylist<T>::iterator::operator==(const iterator& p)const {
	return v == p.v;
}
// checks for operator
template <typename T>bool Mylist<T>::iterator::operator!= (const iterator& p)const {
	return v != p.v;
}
// Moves operator forward
template <typename T>
typename Mylist<T>::iterator& Mylist<T>::iterator::operator++() {
	v = v->next;
	return *this;
}
// moves operator backwards 
template <typename T>
typename Mylist<T>::iterator& Mylist<T>::iterator::operator--() {
	v = v->prev;
	return *this;
}
// Sets iterator to a position
template <typename T>Mylist<T>::iterator::iterator(Node<T>* u) {
	v = u;
}

template <typename T> Node<T>* Mylist<T>::iterator::key() {
	return v;
}




//T& Mylist<T>::iterator::operator*()


#endif