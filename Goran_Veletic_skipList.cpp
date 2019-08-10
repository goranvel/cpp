#include <iostream>
#include <ctime>
#include <cstdlib>

//	Node class to hold int value and pointer to 
//		the previous (left), next (right), down node
class Node {
		int value;

		Node *previous;
		Node *next;
		Node *down;
	public :
		// Node constractor accepting only nodes value
		Node (const int v) :
			value (v),
				previous (nullptr),
					next (nullptr),
						down (nullptr) {
		}

		// copy constructor accepting reference to another node
		Node (const Node &n) :
			value (n.value), 
				previous (n.previous), 
					next (n.next), 
						down (n.down) {
		}

		// copy constructor accpeting pointer to another node
		Node (const Node *n) :
			value (n->value), 
				previous (n->previous),
					next (n->next), 
						down (n->down) {
		}

		// Node destructor
		~Node () {
			value = -1;
		}

		// gets next conde
		Node* getNext () const {
			return next;
		}

		// gets previous node
		Node* getPrevious () const {
			return previous;
		}

		// gets node below
		Node* getDown () const {
			return down;
		}

		// gets value
		int getValue() const {
			return value;
		}

		// sets pointer to the next node to n
		void setNext (Node* n) {
			next = n;
		}

		// sets pointer to the previous node to n
		void setPrevious (Node* n) {
			previous = n;
		}

		// sets pointer to the node below
		void setDown (Node* n) {
			down = n;
		}
};

// prints out node with its down siblings
std::ostream& operator<< (std::ostream& os, Node* n) {
	Node* c = n;
	// prints 
	os << "[" << c->getValue();

	bool parenthesesAreOpen = false;
	// prints ( if node has downward siblings
	if (c->getDown() != nullptr) {
		parenthesesAreOpen = true;
		os << " (";
	}

	// prints all the nodes that are going down from original node
	for (c = c->getDown(); c != nullptr; c = c->getDown()) {
		os << c->getValue();
		if (c->getDown() != nullptr)
			os << " ";
	}

	// prints ) if there was downward siblings
	if (parenthesesAreOpen && c == nullptr)
		os << ")";

	// prints ] denoting end of current linked list
	os << "]";
	return os;
}

// Linked list taking in an int
class LinkedList {
		Node* head;
	public :
		// default consturctor
		LinkedList ( ) : head (nullptr) {
		}

		// constructor accepting node
		LinkedList (Node* h) : head (h) {
		}

		// delete list
		~LinkedList () {
			if (head == nullptr)
				return;

			Node* current = head;
			Node* previous = nullptr;
			while (current != nullptr) {
				previous = current;
				current = current->getNext();
				delete previous;
			} 

		}

		// insert new node by with given value
		void insert (int val) {
			return insert (new Node(val));
		}

		// insert given node 
		void insert (Node* n) {
			return insert (n, head);
		}

		// insert node after previous and returns previous node
		void insert (Node* n, Node* prev) {
			if (head == nullptr || prev == nullptr) {
				head = n;
				return;
			}
	
			// gets nodes aligned
			Node* current = prev;
			Node* previous = nullptr;
			if (prev->getPrevious() != nullptr)
				previous = prev->getPrevious();

			// finds the node where new node would be inserted
			for ( ;	current != nullptr && current->getValue() < n->getValue();
						previous = current, current = current->getNext()); 

			// insert first node in linked list
			if (current == head) {
				head->setPrevious(n);
				n->setNext(head);
				head = n;
				return;
			}

			// insert node at the end of linked list
			if (current == nullptr) {
				previous->setNext (n);
				n->setPrevious(previous);
				return;
			}

			// insert none in normal circumstances
			n->setNext(current);
			current->setPrevious(n);
			n->setPrevious(previous);

			// sets previous node to point to new node
			if (previous != nullptr)
				previous->setNext(n);

			// reuturns current node
			return;
		}

		// retunrs head
		Node* getHead() const {
			return head;
		}

		// remove head
		void removeHead() {
			Node* oldHead = head;
			head = head->getNext();
			head->setPrevious(oldHead->getPrevious());
			delete oldHead;
		}

		// prints linked list in reverse
		void reverse () {
			Node* end = head;
			// finds the end
			for (; end->getNext() != nullptr; end = end->getNext());

			// prints all nodes except head
			for (; end != head; end = end->getPrevious())
				std::cout << end->getValue() << " ";

			// prints head node
			std::cout << end->getValue() << "\n";
		}
};

// printing each linked list, and the nodes down siblings for testing purposes for now
std::ostream& operator<< (std::ostream& os, const LinkedList& l) {
	Node* current = l.getHead();
	// prints linked list;
	for (; current != nullptr; current = current->getNext())
		os << current << " ";

	return os;
}

//	Level class that hold the pointer to the linked list of current level and
//		level below as well
class Level {
		int level;

		LinkedList* list;
		Level* below;
	public :
		// creates new level given the numerical value for level
		Level (int l) : level (l), list (nullptr), below (nullptr) {
		}

		// creates new level
		Level () : level (-1), list (nullptr), below (nullptr) {
		}

		// deletes level
		~Level () {
			delete list;
		}

		// returns list 
		LinkedList* getList () {
			if (list == nullptr)
				return nullptr;
			return list;
		}

		// puts list into level
		void setList (LinkedList *l) {
			list = l;
		}

		// inserts new node into level
		void insert (Node *n) {
			if (list == nullptr)
				list = new LinkedList;
			list->insert (n);
		}

		// returns level below this level
		Level* getBelow () const {
			return below;
		}

		// sets level below
		void setBelow (Level* l) { 
			below = l;
		}

		// returns numerical value for current level
		int getLevel () const {
			return level;
		}
};

//	SkipList class of nodes containing integer values
class SkipList {
		int height;
		Level* head;

		// randomize number of levels for nodes to be inserted
		int randomizeLevel () {
			int level = 1;

			// generates number of levels
			for (; std::rand() % 2 == 0; ++level);

			return level;
		}

		// private method for creating new levels of skip lists
		void createLevel () {
			Level* newLevel = new Level(height);
			if (head->getBelow() != nullptr)
				newLevel->setBelow(head->getBelow());
			head->setBelow(newLevel);
			++height;
		}
	public :
		// creates standard skip list
		SkipList() : height (0), head (new Level) {
			std::srand(std::time(nullptr));
		}

		// deletes each level in skiplist
		~SkipList() {
			Level* currentLevel = head;
			while (currentLevel != nullptr) {
				head = head->getBelow();
				delete currentLevel;
				currentLevel = head;
			}
		}

		// inserts new node into skip list
		void insert (int val) {
			// find how many levels does insertion go to
			int level = randomizeLevel ();

			// creates new levels
			for (;height < level;)
				createLevel();

			// declares level
			Level* currentLevel = head->getBelow();

			// declares nodes
			Node *newNode = nullptr; // = new Node (val);
			Node *previousNode = nullptr;
			Node *insertionPoint = nullptr;

			// goes down to insertion point
			for ( ; currentLevel->getLevel() >= level; currentLevel = currentLevel->getBelow());

			// inserts new nodes into skip list
			for (int i = 0; currentLevel != nullptr && i < level;
						currentLevel = currentLevel->getBelow()) {
				// sets up current and node from previous level
				if (newNode != nullptr) {
					previousNode = newNode;
					newNode = new Node(previousNode);
					previousNode->setDown(newNode);
				} else
					newNode = new Node (val);

				// creates new list for the level if it is empty
				if (currentLevel->getList() == nullptr) 
					currentLevel->setList(new LinkedList());

				// inserts new nodes
				if (insertionPoint == nullptr) 
					// inserts new nodes into empty list
					currentLevel->getList()->insert(newNode);
				 else 
					// inserts new node into list below given insertion point
					currentLevel->getList()->insert(newNode, insertionPoint);

				// sets next insertion point
				if (newNode->getPrevious() != nullptr)
					insertionPoint = newNode->getPrevious()->getDown();
			} 
		}

		// find node in skip list returns pointer to the node or null pointer if node is not found
		Node* find (int val) {
			// gets level and the list;
			Level* currentLevel = head->getBelow();
			LinkedList* currentList = currentLevel->getList();

			// goes through lists where head node is higher than value being inserted
			for (;	currentList->getHead()->getValue() > val; 
						currentList = currentLevel->getList(),
							currentLevel = currentLevel->getBelow());

			// goes thorugh levels using node pointer to find given value
			Node* currentNode = currentList->getHead();

			// goes goes down from given node to the downwards 
			for (; currentNode != nullptr;	currentNode = currentNode->getDown()) {
				//	goes through current level (current linked list) to check 
				//		if value is in current level
				for (; currentNode->getNext() != nullptr && currentNode->getValue() < val;
						currentNode = currentNode->getNext());

				// if node is found returns it
				if (val == currentNode->getValue()) 
					return currentNode;

				// goes down one level
				if (currentNode->getPrevious() != nullptr)
					currentNode = currentNode->getPrevious();
			}

			// returns null pointer if node is not found
			return nullptr;
		}

		// deletes node from skip list
		void remove (int val) {
			// gets level and the list declared
			Level* currentLevel = head->getBelow();
			LinkedList* currentList = currentLevel->getList();

			//	goes through lists where head node value 
			//		is higher or equal to the value being removed
			while (currentLevel != nullptr && currentList->getHead()->getValue() >= val) {
				//	if current lists head node has value same as given value
				if (currentList->getHead()->getValue() == val) {
					//	if list contains only one node (head node) remove entire level 
					//		else remove head only
					if (currentList->getHead()->getNext() == nullptr) {
						head->setBelow (currentLevel->getBelow());
						delete currentLevel;
					} else  // remove head only
						currentList->removeHead();
				}
		
				// update level to the next level
				currentLevel = currentLevel->getBelow(); 

				// update list to the list from current level
				if (currentLevel != nullptr)
					currentList = currentLevel->getList();
			}

			// if no more levels exit the fucntion 
			if (currentLevel == nullptr)
				return;

			// Deals with removing nodes (those are not head nodes)
			Node* currentNode = find(val);
			Node* prev = nullptr;

			// removes non head nodes
			while (currentNode != nullptr) {
				prev = currentNode;
				currentNode = currentNode->getDown();
				prev->getPrevious()->setNext(prev->getNext());
				if (prev->getNext() != nullptr)
					prev->getNext()->setPrevious(prev->getPrevious());
				delete prev;
			}
		}

		// retuns the head list
		Level* getHead() const {
			return head;
		}

		// returns height of skip list	
		int getHeight () const {
			return height;
		}
};

// prints skip list 
std::ostream& operator<< (std::ostream& os, const SkipList& l)  {
	Level* currentLevel = l.getHead()->getBelow();
	int h = l.getHeight();

	// prints each level of skip list including nodes downward siblings
	for (int i = 0; i <= h && currentLevel != nullptr; 
			++i, currentLevel = currentLevel->getBelow()) {
		// prints level number
		os << '{' << currentLevel->getLevel() << "} ";

		// prints
		if (currentLevel->getList() != nullptr) 
			os << *currentLevel->getList() << "\n";
	}
	return os;
}

int main (void) {
	SkipList list;
	list.insert (5);
	list.insert (7);
	list.insert (3);
	list.insert (9);
	list.insert (1);
	list.insert (8);
	list.insert (4);
	list.insert (6);
	list.insert (2);
	list.insert (0); 
	std::cout << list << "\n";
	Node* n1 = list.find(9);
	if (n1 != nullptr)
		std::cout << "found " << n1->getValue();
	else
		std::cout << "Cannot find given value";
	list.remove(3);
	list.remove(8);
	list.remove(1);
	list.remove(5);
	list.remove(0);
	list.remove(9);
	list.remove(6);
	list.remove(2);
	list.insert(5);
	list.remove(7);
	std::cout << "\n\n";
	std::cout << list << "\n";

	return 0;
}
