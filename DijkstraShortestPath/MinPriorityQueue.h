//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Joel Hudgens
// 1224491216
// Description: This file represents a heap object.
//              Each node in the heap is a departure object
//              Each departure object conatins its own address, distance, parent, and ArrivalList object
//              This file also defines necessary heap opeartions
//********************************************************************
#include "ArrivalList.h"
using namespace std;

//represent each node of the graph which is a departure location
//with all the relevant info.
struct Departure
{
    string depAddress;
    double d;
    struct Departure* pi;
    ArrivalList* arrList;
};

//class MinPriorityQueue represents a Min-heap that contains Departure objects.
class MinPriorityQueue
{
    private:
        struct Departure* departureArr;	//a Departure array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        Departure* getDepartureArr();
        int getSize();
        int getCapacity();
        int isFound(string oneDepAddress);
        bool decreaseKey(int index, Departure oneDepartureWithNewDValue);
        bool insert(Departure oneDeparture);
        void heapify(int index);
        Departure getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();
        void build_min_heap();

        //add other function definitions here if 100% necessary
        void swap(Departure arr[], int index1, int index2);
};

//Constructor for MinPriorityQueue
//An array of departure objects of capacity
MinPriorityQueue::MinPriorityQueue(int capacity)
{
 	this->capacity = capacity;           //initialize arary the size of capacity
	departureArr = new Departure[capacity];
	size = 0;
}
//Destructor
MinPriorityQueue::~MinPriorityQueue()
{
	delete[] departureArr;
}

int MinPriorityQueue::getCapacity() {		        //PUBLIC ACCESS METHODS
    return capacity;				                //
}									                //
Departure* MinPriorityQueue::getDepartureArr() {	//
    return departureArr;					        //
}									                //
int MinPriorityQueue::getSize() {			        //
    return size;					                //
}									                //PUBLIC ACCESS METHODS

//return the heap minimum (the root)
Departure MinPriorityQueue::getHeapMin() {			  
    return departureArr[0];				              
}	


int MinPriorityQueue::parent(int childIndex) {			//Given a node, returns its parent's index
    return (childIndex - 1) / 2;
}
int MinPriorityQueue::rightChild(int parentIndex) {		//Given a node, returns its right child's index
    return (2 * (parentIndex + 1));
}
int MinPriorityQueue::leftChild(int parentIndex) { 		//Given a node, returns its left child's index
    return (2 * (parentIndex) + 1);
}

//Given a departure address, returns the index that it occurs in the array
//Returns -1 if it doesnt exist
int MinPriorityQueue::isFound(string oneDepAddress){
    for (int i = 0; i < size; i++) {					//Traverse through heap
        if (departureArr[i].depAddress == oneDepAddress) {
            return i; 									// Return the index if the Car if it is found
        }
    }
    return -1;                                          //otherwise return -1
}

//Given an array of departures and two indexes, swap the position of the departures in the array.
void MinPriorityQueue::swap(Departure arr[], int index1, int index2) {
    Departure temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

//decrease a departures index in the array after changing its departure
//decrease it according to departure value to satisfy the heap properties
bool MinPriorityQueue::decreaseKey(int index, Departure oneDepartureWithNewDValue){
    //first check our car is already smaller... we cant decrease(return false)
    if(departureArr[index].d < oneDepartureWithNewDValue.d){
        return false;
    }

    departureArr[index] = oneDepartureWithNewDValue;

    //while we dont go past root, and the parent and the parent index is still greater  
    while ((index >= 0) && (departureArr[parent(index)].d > departureArr[index].d)){
        swap(departureArr,index,parent(index));										//Swap elements and reset index
		index = parent(index);
    }
    return true;
}


//*********************************************************
void MinPriorityQueue::printHeap()
{

		cout << "\nHeap size = " << getSize() << "\n" << endl;

		cout << left;
		cout << setw(15) << "Departure"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival List" << endl;
        

        for (int i = 0; i < size; i++) {            //print the attributes of each Departure
                cout << left;
                cout << setw(15) << departureArr[i].depAddress
                    << setw(12) << departureArr[i].d;

                if(departureArr[i].pi == nullptr){
                    cout << setw(15) << "No Parent";
                }
                else{
                    cout << setw(15) << departureArr[i].pi;
                }
                departureArr[i].arrList->printArrivalList();
        }

}

//************************************************************
//when you create the dummy node, initialize its d value to be
//50000 which represents infinite large
bool MinPriorityQueue::insert(Departure oneDeparture) 
{
    if(isFound(oneDeparture.depAddress) != -1){						//If departure already exists in heap, don't insert
			return false;
		}

    //If size has reached capacity, double capacity
    if (capacity == size) {
        capacity *= 2;
    }

		Departure* temp = new Departure[capacity];		//Initialize temp array with a length of "capacity"

        for (int j = 0; j < size; j++) {	//Copy elements to temp
            temp[j] = departureArr[j];
        }

        delete[] departureArr;					// Delete, then re-assign
        departureArr = temp;                    //We have now doubled the capacity of our departureArr

        departureArr[size] = oneDeparture;      //Assign new departure to last indicie
        size++;
        return decreaseKey(size -1,oneDeparture); //return whether we increased it
}

//Given an index of the heap, "float down" the departure at the index in order to maintain the heap property
void MinPriorityQueue::heapify(int index){
    int right = rightChild(index);				//Calculate left,right
	int left = leftChild(index);
	int smallest = index;

    // If the left child is smaller than the current node 
    if (left < size && departureArr[left].d < departureArr[smallest].d) {
        smallest = left;
    }

    // If the right child is smaller than the current node
    if (right < size && departureArr[right].d < departureArr[smallest].d){
        smallest = right;
    }
    // If the smallest node is not the current node, swap them and heapify 
    if (smallest != index) {
        swap(departureArr, index, smallest);
        heapify(smallest);
    }

}

//Remove root while preseving heap
void MinPriorityQueue::extractHeapMin(){
    departureArr[0] = departureArr[size-1];         //last element is the new root
    size--;
    heapify(0);                             //Heapify the root(last node is removed by size--)
}

//****************************************************************************
//Given the original departureArr, the function build a min-heap by using d value
void MinPriorityQueue::build_min_heap() {
    for (int i = size / 2 - 1; i >= 0; i--) {           //heapify non-leaf nodes
        heapify(i);
    }
}
