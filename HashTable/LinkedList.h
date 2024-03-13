// ASU CSE310 Assignment #5 Spring 2024
// Joel Hudgens
// 1224491216
// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
   string model, make;
   int vin;
   double price;
   struct Car* next;
};

class LinkedList
{
   private:
     struct Car* head;
     int size;      //a variable represents number of Cars inside the list
   public:
     LinkedList();
     ~LinkedList();
     Car* getHead();
     int getSize();
     bool searchCar(int carVIN);
     bool insertCar(string model, string make, int vin, double price);
     bool deleteCar(int carVIN);
     void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    head = nullptr;
}

//Destructor
LinkedList::~LinkedList()
{
    if (head == nullptr) //list is already deleted
    {
        return;
    }

    Car* current = head;
    while (current != nullptr)
    {
        Car* nextNode = current->next;  // Capture the next node
        delete current;                 // Delete the current node
        current = nextNode;             // Move to the next node
    }
}

Car* LinkedList::getHead()
{
    return head;
}

//Return number of Cars inside the Linked list
int LinkedList::getSize() {
    if(head == nullptr){            //If it is empty
            return 0;
        }

    int count = 0;
    Car* temp = head;       //dummy node

    while (temp != nullptr){        //Iterate while incrementing count
        count++;
        temp = temp->next;
    }
    return count;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{
    Car* curr = head; // Start from head

    // Traverse 
    while (curr != nullptr) {
        // Check if the curr matches targer
        if (curr->vin == carVIN) {
            return true;
        }
        // Move to the next Car in the linked list
        curr = curr->next;
    }
    // VIN not found
    return false;
}




//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
    Car* newCar = new Car;          //Initialize new car
    newCar->price = price;          //
    newCar->model = model;          //
    newCar->vin = vin;              //
    newCar->make = make;            //
    newCar->next = nullptr;         //

    //newCar beccomes head if list is empty
    if (head == nullptr) {
        head = newCar;
        size++;
        return true;
    }else{
        newCar->next = head;        //Otherwise, insert at head and update head
        head = newCar;
        size++;
        return true;
    }
}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN)
{
    if (head == nullptr){ //If list empty
        return false;
    }

    if (head->vin == carVIN){ //If we need to remove head
        Car* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    Car* curr = head->next; //dummy nodes
    Car* prev = head;

     while (curr != nullptr) { 
        if (curr->vin == carVIN) { //Traverse to matching vin in list
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
            size--;
            return true;
        }
        prev = curr; //Handle last node
        curr = curr->next;
    }

    return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
   struct Car *temp = head;
   if(head == NULL)
   {
   	//empty linked list, print nothing here
   }
   else
   {
      while(temp != NULL)
      {
         cout << left    << setw(18) << temp->model
              << left    << setw(18) << temp->make
              << right   << setw(8)  << temp->vin
              << setw(10) << fixed << setprecision(2) << temp->price << "\n";
         temp = temp->next;
      }
   }
}
