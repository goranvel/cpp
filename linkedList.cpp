#include <iostream>
#include <iomanip>

using namespace std;

namespace {
	struct Node {
		int m_data;
		Node* next;
	};

	class LinkedList
	{
			Node *head;
		public:
			LinkedList () : head(nullptr) {
			}

			~LinkedList () {
				if (head == nullptr)
					return;

				Node* current = head;
				Node* previous = nullptr;
				while (current != nullptr) {
					previous = current;
					current = current->next;
					delete previous;
				} 
			}

			void insert(int num){
				if (head == nullptr) {
					head = new Node();
					head->m_data=num;
					
					return;
				}

				Node *n = new Node();
				n->m_data = num;
				n->next = head;
				head = n;
			}

			void print() const {
				// print out everything in the list
				Node *cNode = head;

				for (; cNode != nullptr; cNode = cNode->next)
					cout << setw(2) << cNode->m_data << " ";

				cout << "\n";
			}

			void insert(int position, int num){
				if (position < 0) {
					cerr << "Positon cannot be negative";
					return;
				}

				if (position == 0) {
					insert(num);
					return;
				}

				Node* cNode = head;
				for (int p = 0; cNode->next != nullptr && p < position; cNode = cNode->next, ++p);

				Node *newNode = new Node();
				newNode->m_data = num;
					
				if (cNode->next != nullptr)
					newNode->next = cNode->next;

				cNode->next = newNode;
		    }

			void remove(int num){
				if (head->m_data == num) {
					Node *p = head;
					head = head->next;
					delete p;
					return;
				}
			
				Node* cNode = head;
				Node* pNode = nullptr;

				for (; cNode != nullptr && cNode->m_data != num; pNode = cNode, cNode = cNode->next);
				
				// end of the list was reached
				if (cNode == nullptr)
					return;
					
				// point previous node to the next node
				if (cNode->next != nullptr && pNode !=nullptr)
					pNode->next = cNode->next;
				// MISSING LINES vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
				else
					pNode->next = nullptr;
				// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

				delete cNode;
			}
		
			void reverse() {
				Node *cNode = head;
				Node *pNode = nullptr, *nNode = nullptr;

				while (cNode != nullptr) {
					nNode = cNode->next; 
					cNode->next = pNode;
					pNode = cNode;
					cNode = nNode;
				}

				head = pNode;
			}
			
	};
}

// To execute C++, please define "int main()"
int main() {
	LinkedList list;

	for(int num = 0; num < 100; ++num) {
		list.insert(num);
	}

// list.print();
// list.reverse();
//  list.print();
//  list.insert(1000, 999);
  list.print();
 //  list.remove(999);
  list.reverse();
  list.print(); 

  return 0;

}
