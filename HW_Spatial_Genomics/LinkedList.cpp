#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include <cmath>

using std::cout;
using std::endl;

using std::string;
using std::ostream;

// c++ is dumb and adds a bunch of zeroes when converting from 
LinkedList::LinkedList():head(nullptr), tail(nullptr){
	  // Implement this function
}

Node *LinkedList::copy() const{
    Node *prevNode, *nextNode, *firstNode, *currNode;
    currNode = this->head;
    //Make sure there is one
    if (currNode == nullptr){
        return nullptr;
    }

    // Do the first one
    prevNode = new Node;
    prevNode->data = currNode->data;
    prevNode->next = nullptr;
    firstNode = prevNode;
    
    currNode = currNode->next;

    while (currNode != nullptr){
        Node *newOne = new Node;
        newOne->data = currNode->data;
        newOne->next = nullptr;
        prevNode->next = newOne;
        prevNode = newOne;
        currNode = currNode->next;
    }
    return firstNode;
}


void LinkedList::clear(){
    Node *currNode, *nextNode;
    currNode = this->head;

    // While currNode is not nullptr, we go through and delete its node:
    while (currNode != nullptr){
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::~LinkedList() {
    // Implement this function
    this->clear();
}

LinkedList::LinkedList(const LinkedList& other) {
    // Implement this function
    //this->clear();
    this->head = other.copy();

    // We still have to get tail:
    if (this->head == nullptr){
        this->tail = nullptr;
    }else{
        Node *currNode;
        currNode = this->head;
        while (currNode->next!=nullptr){
            currNode = currNode->next;
        }
        this->tail = currNode;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other) 
{
    // Implement this function
    this->clear();
    this->head = other.copy();

    // We still have to get tail:
    if (this->head == nullptr){
        this->tail = nullptr;
    }else{
        Node *currNode;
        currNode = this->head;
        while (currNode->next!=nullptr){
            currNode = currNode->next;
        }
        this->tail = currNode;
    }

    return *this;
}

// DO NOT TOUCH IT WORKS SOMEHOW
void LinkedList::insert(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y)
{
    // Implement this function
    // Records in the linked list are first ordered by fov, then ID
    Node *currNode, *prevNode, *newNode;

    newNode = new Node(id, fov, volume, center_x, center_y, min_x, max_x, min_y, max_y);
    currNode = this->head;

    // We gotta check the first element
    // If the head is nullptr:
    if (currNode == nullptr){
        // This means the list is empty, so there will now be one element
        this->head = newNode;
        this->tail = newNode;
        return;
    }
    // If the new node is less than the currNode:
    if (newNode->data < currNode->data){
        // We make the head into newNode
        this->head = newNode;
        newNode->next = currNode;
        return;
    }

    while(currNode->next != nullptr){
        prevNode = currNode;
        currNode = currNode->next;
        if ((prevNode->data < newNode->data) && (newNode->data < currNode->data)){
            prevNode->next = newNode;
            newNode->next = currNode;
            return;
        }
    }

    // If the node hasn't been inserted, we will reach this point
    // currNode->next is nullptr, meaning we insert at end of list.
    currNode->next = newNode;
    this->tail = newNode;
    newNode->next = nullptr;
}

void LinkedList::remove(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y)
{
    // Implement this function
    Node *nodeToRemove, *prevNode, *deleteMe;
    nodeToRemove = new Node(id, fov, volume, center_x, center_y, min_x, max_x, min_y, max_y);
    
    if (this->head->data == nodeToRemove->data){
        deleteMe = this->head;
        this->head = this->head->next;
        delete deleteMe;
        delete nodeToRemove; // Added this
        return;
    }
    prevNode = this->head;
    while((prevNode->next !=nullptr)){
        if ((prevNode->next->data == nodeToRemove->data)){
            break;
        }
        prevNode = prevNode->next;
    }

    if (prevNode->next == nullptr){
        delete nodeToRemove; // Added this
        return; // There was nothing that matched
    }
    deleteMe = prevNode->next;
    prevNode->next = prevNode->next->next;
    delete deleteMe;
    delete nodeToRemove;
}

/* I declared this one earlier so commenting this to avoid conflict
void LinkedList::clear() 
{	
    // Implement this function
}
*/

Node* LinkedList::getHead() const 
{
    // Implement this function it will be used to help grade other functions
    return this->head;
}

string LinkedList::print() const 
{
   	// Implement this function
    Node *currNode;
    string printString = "";
    char comma = ',';
    char newL = '\n';
    std::stringstream streamThing;

    printString += "fov,volume,center_x,center_y,min_x,max_x,min_y,max_y\n";
    
    currNode = this->head;
    while (currNode!=nullptr){
        streamThing << currNode->data.id;
        streamThing << comma;
        streamThing << currNode->data.fov;
        streamThing << comma;
        streamThing << currNode->data.volume;
        streamThing << comma;
        streamThing << currNode->data.center_x;
        streamThing << comma;
        streamThing << currNode->data.center_y;
        streamThing << comma;
        streamThing << currNode->data.min_x;
        streamThing << comma;
        streamThing << currNode->data.max_x;
        streamThing << comma;
        streamThing << currNode->data.min_y;
        streamThing << comma;
        streamThing << currNode->data.max_y;
        streamThing << newL;

        currNode = currNode->next;
    }
    printString += streamThing.str();
    return printString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

// given a fov number, count the cells observed in that fov
int LinkedList::countN(int fov)
{
	/* Do not modify this function */
    int count = 0;
    Node* cur = head;
    while (cur)
    {
        if (cur->data.fov == fov)
            count++;
        cur = cur->next;
    }
    return count;
}

/* given a fov number, compute the average volume of all the cells observed in
 * that fov
 */
double LinkedList::average(int fov)
{
    // Implement this function
    Node *currNode = this->head;
    double sum = 0;
    double count = 0;
    double avg = 0;
    while (currNode != nullptr){
        if (currNode->data.fov == fov){
            sum += currNode->data.volume;
            count += 1;
        }
        currNode = currNode->next;
    }
    if (count){avg = sum/count;}
    return avg;
}

/* given a fov number, compute the variance volume of all the cells observed in
 * that fov
 */
double LinkedList::variance(int fov)
{
	/* Do not modify this function */
    double sum = 0;
    double avg = average(fov);
    int count = countN(fov);

    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov)
            sum += (cur->data.volume - avg) * (cur->data.volume - avg);
        cur = cur->next;
    }

    return sum/count;
}

/* given a fov number, remove outliers
 */
string LinkedList::outliers(int fov, int j, int N)
{
    // Implement this function
    int cellsRemoved = 0;
    double avg = this->average(fov);

    if (countN(fov) < N){
        std::stringstream stream;
        stream << "Less than " << N << " cells in fov " << fov;
        return stream.str();
        
    }else{
        double deltaK = sqrt(this->variance(fov));
        Node *currNode = this->head;

        while (currNode != nullptr){
            if (currNode->data.fov != fov){ // If the fov does not match, we do not care
                currNode = currNode->next;
                continue;
            }
            // Now we actually care if it is in range:
            Node *nextNode = currNode->next; // In case we delete currNode
            if ((currNode->data.volume < (avg - j*deltaK)) || (currNode->data.volume > (avg + j*deltaK))){
                this->remove(currNode->data.id, currNode->data.fov,currNode->data.volume,currNode->data.center_x,currNode->data.center_y,currNode->data.min_x,currNode->data.max_x,currNode->data.min_y,currNode->data.max_y);
                cellsRemoved++;
            }
            currNode = nextNode;
        }
    }
    string returnStr = std::to_string(cellsRemoved);
    returnStr = returnStr + " cells are removed.";
    return returnStr;
}

