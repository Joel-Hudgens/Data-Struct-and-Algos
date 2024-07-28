//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Joel Hudgens
// 1224491216
// Description: This file represents a linked list of Objects called Arrivals. 
//              Each arrival holds the roadCategory to itself, as well as distance, address, and next Arrival
//              This file also defines necessary linked list opeartions
//********************************************************************
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Arrival represents an arrival address with distance and road
//category info. from a specific departure address
struct Arrival
{
    string arrAddress;
    double distance;        //miles from the departure address to this arrival address
    string roadCategory;    //Interstates, Arterials, Collectors or Local streets
    struct Arrival* next;
};

//class ArrivalList contains a linked list of Arrival objects
class ArrivalList
{
    private:
        struct Arrival* head;

    public:
        ArrivalList();
        ~ArrivalList();
        Arrival* getHead();
        Arrival* findArrival(string oneAddress);
        bool addArrival(string oneAddress, double distance, string roadCategory);
        void printArrivalList();
};


//Constructor
//creates an empty linked list.
ArrivalList::ArrivalList() {
    head = nullptr;
}


//*****************************************************************************************************
//Destructor. Before termination, the destructor is called to free the associated memory occupied by the
//existing linked list. It deletes all the Arrivals including the head and finally prints the number of
//Arrival deleted by it.
//Return value: Prints the number of nodes deleted by it.
ArrivalList::~ArrivalList() {
	if (head == nullptr) //list has a length of 0
    {
        cout<< "The number of deleted arrival addresses are: 0";
        return;
    }

    Arrival* current = head;
 
    while (current != nullptr)
    {
        Arrival* nextNode = current->next;  // Capture the next node
        delete current;                 // Delete the current node
        current = nextNode;             // Move to the next node
    }
}


//accessor to the head class attribute
Arrival* ArrivalList::getHead(){
    return head;
}


//Find whether the parameterized address is inside the LinkedList or not
//It returns a pointer that points to the Arrival object if it exist, otherwise it return NULL
Arrival* ArrivalList::findArrival(string oneAddress){
    Arrival* curr = head; //dummy node

    if (curr == nullptr){ //If there is no head
        return nullptr;
    }
	while (curr!= nullptr) //Until we get to end of list
    {
        if (curr->arrAddress == oneAddress) { //check if curr matches 
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;  //If we exit the loop, there is no match, so return null
}

//Given arrival attributes, insert a new arrival object into ArrivalList based on alphabetical order of the address
bool ArrivalList::addArrival(string oneAddress, double distance, string roadCategory){
    Arrival* newArrival = new Arrival;
    newArrival->arrAddress = oneAddress;
    newArrival->distance = distance;
    newArrival->roadCategory = roadCategory;
    newArrival->next = nullptr;

    Arrival* curr = head; //dummy node

    if (curr == nullptr) {
        // If the list is empty, set the new arrival as the head
        head = newArrival;
        return true;
    }

    // If the new arrival comes before the head, update head and link to the old head
    if (oneAddress.compare(head->arrAddress) < 0) {
        newArrival->next = head;
        head = newArrival;
        return true;
    }

    // Find the correct position in the list
    while (curr->next && oneAddress.compare(curr->next->arrAddress) > 0) {
        curr = curr->next;
    }

    // Insert the new arrival at that position
    newArrival->next = curr->next;
    curr->next = newArrival;
    return true;
}

//Prints all the arrival address in the linked list starting from the head.
void ArrivalList::printArrivalList()
{
    Arrival* temp = head;
    if (temp == nullptr){
        cout << "Arrival list is empty";
    }
    else
    {
        while (temp != nullptr){        //Iterate through list and print follwowing the format
            cout << temp->arrAddress
            << fixed << setprecision(2) << "(" << temp->distance << "/" << temp->roadCategory << "),";
		    temp = temp->next;
        }
	}
	cout <<"\n";
}
