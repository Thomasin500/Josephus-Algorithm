#ifndef CIRCULARLINKEDLIST_h
#define CIRCULARLINKEDLIST_h

////////////////////////////////////////////////////////////////////////////
// Thomas Freeman
// Josephus Problem using Circular Linked List
////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

// This is the class definition for the linked list
// It is circular in design and also allows for the user to run the Josephus Algorithm
// The class is also templated allowing the linked list to contain any type of data
template <class T>
class List {

private:
	class Node {
	public:
		T data;
		Node * next;
		Node(T data, Node * ptr = 0)

			: data(data), next(ptr)
		{}
	};

public:

	//default constructor
	List()
		: head(0)
	{}
	/*-----------------------------------------------------------------------
	Construct a singly linked circular linked list object.
	Precondition:  None.
	Postcondition: An empty Stack object has been constructed
	(head is a null pointer).
	------------------------------------------------------------------------*/

	//copy constructor
	List(const List& oldList) {

		head = NULL;

		if (oldList.head != NULL) {

			Node * currentNode = oldList.head;
			Node * refNode = oldList.head;	//keeps track of nodes in the original list 

											//copy first node in the list
			head = new Node(currentNode->data);
			refNode = head;

			currentNode = new Node(oldList.head->next->data); //create next node
			head->next = currentNode; //link them together

			currentNode->next = head; //creates link that makes the list circular

			refNode = oldList.head->next->next;

			do {  //go through to the end of the list coping each element

				currentNode->next = new Node(refNode->data);
				currentNode = currentNode->next;
				refNode = refNode->next;

				currentNode->next = head; //creates link that makes the list circular
			} while (refNode != oldList.head);

			//when the last element is copied, point the last node to the head node to make it circular
			currentNode->next = head;
		}
	}
	/*-----------------------------------------------------------------------
	Copy constructor for a singly linked circular linked list
	Precondition:  A copy of the original list is needed and is a const value.
	Postcondition: A copy of the list is created.
	------------------------------------------------------------------------*/

	//default destructor
	~List() {

		Node * currentNode = head;
		Node * prevNode = head;
		int i = 1;

		while (i < 0) { //while this is technically an infinite loop, a condition will be met to exit once the list is deleted

			prevNode = currentNode;

			if (currentNode->next) { // condition to check this node is the last node in the list

				currentNode = currentNode->next;
			}
			else {

				delete currentNode;
				return;
			}

			delete prevNode;
		};

		head = NULL;
	}
	/*-----------------------------------------------------------------------
	Class Descructor, deletes all nodes within the list
	Precondition:  None.
	Postcondition: The list nodes memory has been freed.
	------------------------------------------------------------------------*/

	//Returns the size of the linked list as an integer
	int getSize() const {

		int size = 0;
		Node * node = head;

		if (node) {
			do {

				size++;
				node = node->next;
			} while (node != head);
		}
		return size;
	}
	/*-----------------------------------------------------------------------
	Counts the number of nodes in the list
	Precondition:  None.
	Postcondition: Returns an int with value the length of the list.
	------------------------------------------------------------------------*/

	//returns a boolean determining wether the linked list is empty or not
	bool isEmpty() const {

		return (head == NULL);
	}
	/*-----------------------------------------------------------------------
	Checks is the list is empty
	Precondition:  None.
	Postcondition: Returns a boolean indicating if list length is 0.
	------------------------------------------------------------------------*/

	//an algorithm to insert a new node right before the indexed location		
	bool insert(const T& data, const int& index) {

		Node * newNode = new List::Node(data);
		newNode->data = data;

		//check to see if the list is empty first
		//index doesnt matter in this situation
		if (head == NULL) {

			head = newNode;
			newNode->next = newNode;
			return true;
		}

		//node used to track the list
		Node * currentNode = head;
		Node * prevNode = head;

		int i = 0;

		if (currentNode) {
			do {
				if (i == index) {
					if (index == 0) { //find last node so that the pointers can be set correctly							
						do {

							currentNode = currentNode->next;

							if (currentNode->next == head) {	//currentNode is now last node							

								currentNode->next = newNode;
								newNode->next = head;
								head = newNode;
								return true;
							}

						} while (currentNode != head);
					}
					else {

						//insert new node 
						prevNode->next = newNode;
						newNode->next = currentNode;
						return true;
					}
				}
				else { //keep going

					i++;
					prevNode = currentNode;
					currentNode = currentNode->next;
				}
			} while (currentNode != head);

			//if the function has reached this point then the index is invalid				
			cout << "Index is invalid" << endl;
		}
		else {

			cout << "Error on creation of new node";
			return false;
		}
	}
	/*-----------------------------------------------------------------------
	Inserts a new node at the index specified with the passed in data.
	Precondition:  The data that the new node will contain,
	the index at which the node will be place at.
	Postcondition: A  new node has been created with the passed in data
	------------------------------------------------------------------------*/

	//remove the node at the index specified
	bool remove(const int& index) {

		Node * currentNode = head;
		Node * prevNode = head;
		int i = 0;

		if (currentNode) {
			while (i != index + 1) {
				if (index == 0) { //find last node so that the pointers can be set correctly			
					do {

						currentNode = currentNode->next;

						if (currentNode->next == head) {	//currentNode is now last node							

							currentNode->next = currentNode->next->next;
							prevNode = head;
							head = currentNode->next;
							delete prevNode;
							return true;
						}
					} while (currentNode != head);
				}
				if (i == index) {

					prevNode->next = currentNode->next;
					delete currentNode;
					return true;
				}

				prevNode = currentNode;
				currentNode = currentNode->next;
				i++;

			}
		}
		else {

			cout << "Error deleting node" << endl;
			return false;
		}
	}
	/*-----------------------------------------------------------------------
	Removes the node at the specified index
	Precondition:  The index of the to be delete node.
	Postcondition: The specified node was deleted
	------------------------------------------------------------------------*/

	//Defining the '=' operator for 2 lists allows for the assignment of a new list from the old one
	const List& operator=(const List& RHSList) {

		if (this != &RHSList) {

			this->~List();

			if (RHSList.isEmpty()) { //check is list to be copied from is empty

				head = NULL;
			}
			else {	//RHS list has some nodes in it

					//copy first node of RHS list
				head = new Node(RHSList.head->data);

				Node * refNode = RHSList.head;
				Node * currentNode = head;
				head->next = currentNode; //connect two nodes

				while (refNode->next != RHSList.head) {

					refNode = refNode->next;
					currentNode->next = new Node(refNode->data);
					currentNode = currentNode->next;
					currentNode->next = head; //make the list circular
				}
			}
		}
		return *this;
	}
	/*-----------------------------------------------------------------------
	Assigns the values of the RHS list to the LHS object.
	Precondition:  An instantiated list .
	Postcondition: The LHS list now has the values of the RHS list.
	------------------------------------------------------------------------*/

	//allows for a simpler way of displaying the list within the cout syntax
	const List& operator<<(const List& list) {
	}

	//displays each data item of each node followd by a new line
	void display(ostream& out) const {

		out << "Here are the contents of the current list:" << endl << endl;

		if (head == NULL) {

			out << "List is empty" << endl;
			return;
		}
		else {

			Node * currentNode = head;

			do {

				out << currentNode->data << endl;
				currentNode = currentNode->next;
			} while (currentNode != head);
		}
		cout << endl;
	}
	/*------------------------------------------------------------------------
	Displays each node's data in the list
	Precondition:  The stream you wish to be outputted with the data.
	Postcondition: Outputs each Node's data.
	------------------------------------------------------------------------*/

	//This algorithm correctly replicates the Josephus Problem
	//*********
	//FOR THE TA: The Project description makes it seem that the starting index and the count are inputted from the user before the algorithm is ran.
	//However, the breakdown of points per function (page 3 of the assigment paper) makes it seem that the starting index and count should be randomly generated
	//at each iteration, but that does not make sense for how the algorithm is called and would make prediction of the final result impossible.
	//I would be happy to create the other option if needed, please let me know. Thank you.
	T runJosephusAlgorithm() {

		int numPeople = 0;
		int count = 0;

		cout << "Enter the number of people in the circle" << endl;
		cin >> numPeople;

		cout << "\nEnter the number used for counting off \n(Must be between 0 and 2 * number of people in the circle" << endl;
		cin >> count;

		//verify that the count is between 0 and 2 * numPeople			
		while (count < 0 || count >(2 * numPeople)) {

			cout << "\nInvalid count, please enter a number between 0 and 2 * number of people \nin the circle" << endl;
			cin >> count;
		}

		cout << "\n";

		int min = 1;
		int max = numPeople;
		int range = max - min + 1;
		int startPos = rand() % range + min; //start position should be between 1 and numPeople					

											 //create the original list from the inputted values
		List originalList;
		int i = numPeople + 1;
		do {

			i--;
			originalList.insert(i, 0);
		} while (i != 1);

		//create a copy of the original list to run the algorithm on
		List runList = originalList;

		Node * prevNode = runList.head;
		Node * currentNode = runList.head;

		//find starting position	
		i = 1;
		if (currentNode) {
			while (i != startPos) {

				currentNode = currentNode->next;
				i++;
			}
		}	//currentNode should now be at the correct position to remove node


			//run this loop until there is only 1 node left, the survivor			
		while (runList.getSize() != 1) {

			currentNode = runList.head; //count starting from the next node from the current node
			int counter = 0;
			while (counter != count) {

				counter++;
				currentNode = currentNode->next;
			}

			cout << "Node Removed: " << currentNode->data << endl;

			//move currentNode to the next node after the one to be deleted
			currentNode = currentNode->next;

			//the counter should now be at the index of the node to be removed
			runList.remove(counter); //+1 because the list is indexed from 0 while the count assumes indexing is from 1

			runList.head = currentNode; // set the head to the left of the node that is to be removed
		}

		//make sure to output who is removed each iteration

		//final output should return the remaining survivor

		cout << "\nThe survivor of the Josephus Algorithm is: " << runList.head->data << "\n\n\n";

		int option = 0;
		cout << "Would you like to run the Josephus Algorithm again? (0 for no, 1 for yes)" << endl;
		cin >> option;
		cout << endl;

		if (option == 1) {

			runJosephusAlgorithm();
		}
		else if (option == 0) {

			return runList.head->data;
		}
		else {

			cout << "Invalid selection, running algorithm again" << endl;
			runJosephusAlgorithm();
		}
	}
	/*------------------------------------------------------------------------
	Computes the survivor of the Josephus Problem
	Precondition:  None.
	Postcondition: returns the data entry fo the surviving node
	------------------------------------------------------------------------*/

private:
	Node * head; //pointer to first element of the Linked List
};

#endif