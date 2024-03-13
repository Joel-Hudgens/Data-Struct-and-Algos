// ASU CSE310 Spring 2024 Assignment #1
// Name: Joel Hudgens
// ASU ID: 1224491216
// Description: This file represents a linked list data structure (comprised of cars)
//and contains serveral functions that operate on the linked list

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Car represents a Car information
struct Car
{
    string model, make;
    int vin;            //vehicle identification number
    double price;
    struct Car* next;
};

//class LinkedList will contains a linked list of Cars
class LinkedList
{
    private:
        struct Car* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findCar(int aVin);
        bool addCar(string model, string make, int vin, double price);
        bool removeByVin(int aVin);
        bool removeByModelAndMake(string model, string make);
        bool changeCarInfo(int aVin, string newModelAndMake);
        bool updateCarPrice(int aVin, double newPrice);
        void printCarListByMake(string make);
        void printCarList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	if (head == nullptr) //list is already deleted
    {
        cout<< "The number of deleted Car is: 0\n";
        return;
    }

    int counter = 0;
    Car* current = head;

    while (current != nullptr)
    {
        Car* nextNode = current->next;  // Capture the next node
        delete current;                 // Delete the current node
        current = nextNode;             // Move to the next node
        counter++;
    }
    cout<< "The number of deleted Car is: " << counter <<"\n";
}

//A function to identify if the parameterized Car is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    Car* curr = head; //dummy node

    if (curr == nullptr){ //If there is no head
        return false;
    }
	while (curr!= nullptr) //Until we get to end of list
    {
        if (curr->vin == aVin) { //check if curr matches aVin
            return true;
        }
        curr = curr->next;
    }
    return false;  //If we exit the loop, there is no match, so return false
}

//Creates a new Car and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Cars by their make and model, i.e.
//first by make, if two cars have same makes, then we will list them by model. Note: each Car
//has a unique vin, the vehicle identification number, but may have the same make and model.
//In case two Cars have same make and model, they should be inserted according to the
//increasing order of their vins.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    //if the Car already exist, return false
    //add your own code
    if (findCar(vin)) {
        cout << "Duplicated Car. Not added.";
        return false;
    }

    //Create new car object to insert
    Car* newCar = new Car;
    newCar->price = price;
    newCar->model = model;
    newCar->vin = vin;
    newCar->make = make;
    newCar->next = nullptr;

    //newCar beccomes head if list is empty
    if (head == nullptr) {
        head = newCar;
        return true;
    }

    //First, checking if it needs to be insterted before head
    if (make < head->make  //make is smaller
    || (model < head->model && make == head->make) //same make, smaller model
    || (vin < head->vin && make == head->make && model == head->model)) { //vin, make, and model the same
        newCar->next = head;
        head = newCar;
        return true;
    }

    //If it does not get inserted before head, find the correct position within list
    Car* prev = nullptr;
    Car* curr = head;
    
    while (curr != nullptr && //While curr is not null and one of the conditions is met
    (make > curr->make // and while make is greater
    || (make == curr->make && model > curr->model) // same make, greater model
    || ( vin > curr->vin && make == curr->make && model == curr->model))) { //vin, make, and model the same
        prev = curr;
        curr = curr->next;     //traverse to next car
    }

    //In case it is inserted last
    prev->next = newCar; 
    newCar->next = curr;

    return true;
}

//Removes the specified Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
 {
	if (head == nullptr){ //If list empty
        return false;
    }

    if (head->vin == aVin){ //If we need to remove head
        Car* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Car* curr = head->next; //dummy nodes
    Car* prev = head;

     while (curr != nullptr) { 
        if (curr->vin == aVin) { //Traverse to matching vin in list
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
            return true;
        }
        prev = curr; //Handle last node
        curr = curr->next;
    }

    return false;
 }



//Removes the given Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Cars with
//the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
    if (head == nullptr){ //If list empty
        cout << "No such Car found.\n";
        return false;
    }
    bool carRemoved = false;
    //If head needs to be removed
    while (head != nullptr && head->make == make && head->model == model) {
        Car* temp = head;
        head = head->next;
        delete temp;
        carRemoved = true;
    }

    Car* curr = head; //dummy nodes
    Car* prev = nullptr;

    while (curr != nullptr) { //Traverse
        if (curr->make == make && curr->model == model) { //If model and make match
            // Remove the current node
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            delete curr;
            curr = (prev)? prev->next : head; //curr is prev.next if there is a prev, otherwise, it is head
            carRemoved = true;
        } else {
            // Move to the next node
            prev = curr;
            curr = curr->next;
        }
    }
    if (carRemoved == false) { //
        cout << "No such Car found.\n";}

    return carRemoved;
}



//Modifies the data of the given Car. Return true if it modifies successfully and
//false otherwise. Note: after changing a Car model and make, the linked list must still
//maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
   // Split newModelAndMake string to get model and make accordingly
    size_t spacePos = newModelAndMake.find(" ");

    string newModel = newModelAndMake.substr(0, spacePos); //substring method to split
    string newMake = newModelAndMake.substr(spacePos + 1,newModelAndMake.length());

    //dummy nodes
    Car* foundCar = nullptr;
    Car* curr = head;
    Car* prev = nullptr;

    while (curr != nullptr) //Go to where vin matches or end of list
    {
        // If Car with VIN is found, store its VIN and price, and remove it it from the list
        if (aVin == curr->vin)
        {
            int storedVIN = curr->vin;
            double storedPrice = curr->price;

            // Remove the Car from its current position
            if (prev != nullptr)
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }

            delete curr;

            // Add a new Car with updated model and make, and stored VIN and price
            addCar(newModel, newMake, storedVIN, storedPrice);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
        return false;
}

bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
	//add your own code
    if (head == nullptr){ //If list empty
        return false;
    }
    Car* curr = head; //dummy node

    while (curr != nullptr && curr->vin != aVin) //Go to where vin matches or end of list
    {
        curr = curr->next;
    }
    if (curr == nullptr){
        return false;
    }else{
        curr->price = newPrice;
        return true;
    }
    
}

//Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    Car* temp = head;  //dummy node
    bool found = false;

    // Iterate through the list
    while (temp != nullptr) {
        // If it has the same make
        if (temp->make == make) {
            // Print that car
            cout << left    << setw(12) << temp->model
                 << left    << setw(12) << temp->make
                 << right   << setw(8) << temp->vin
                 << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            found = true;
        }
        // Move to the next Car in the list
        temp = temp->next;
    }

    // If no cars with the make are found
    if (!found) {
        cout << "No Cars with the specified make found.\n";
    }
 }

//Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    if (head == nullptr){ //If list empty
        cout << "The list is empty\n";
        return;
    }
    //add your own code
    Car* temp = head;

    while (temp != nullptr)
    {
        cout << left    << setw(12) << temp->model
            << left    << setw(12) << temp->make
            << right   << setw(8) << temp->vin
            << setw(10) << fixed << setprecision(2) << temp->price << "\n";

        temp = temp->next;
    }
}
