// Assignment: ASU CSE310 HW#3 Spring 2024
// Joel Hudgens
// 1224491216
// jdhudge1@asu.edu
//Description:
//This File represents a Heap data strcuture.
//The heap is implemented with an array of structs which we have defined (Cars).
//This file contains all the necessary methods to access and maintain the heap.
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
    private:
    struct Car* carArr;	//an array of Cars
    int capacity, size;

	public:
    MaxHeap(int capacity);
    ~MaxHeap();

	Car* getCarArr();
	int getSize();
	void setSize(int newSize);
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
//Capacity can be thought of as carArr.length
MaxHeap::MaxHeap(int capacity)
{
 	this->capacity = capacity;   //initialize arary the size of capacity
	carArr = new Car[capacity];
	size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	int carCount = this->size;
	delete[] carArr;
	cout << "\nThe number of deleted cars is: " << carCount << endl;
}


int MaxHeap::getCapacity() {		//PUBLIC ACCESS METHODS
    return capacity;				//
}									//
Car* MaxHeap::getCarArr() {			//
    return carArr;					//
}									//
int MaxHeap::getSize() {			//
    return size;					//
}									//PUBLIC ACCESS METHODS

void MaxHeap::setSize(int newSize) {			//Added this in order for heapsort algo to publically access
        size = newSize;
    }

int MaxHeap::parent(int childIndex) {			//Given a node, returns its parent's index
    return (childIndex - 1) / 2;
}
int MaxHeap::rightChild(int parentIndex) {		//Given a node, returns its right child's index
    return (2 * (parentIndex + 1));
}
int MaxHeap::leftChild(int parentIndex) { 		//Given a node, returns its left child's index
    return (2 * (parentIndex) + 1);
}

//Given an array of cars and two indexes, swap the position of the cars in the array.
void swap(Car arr[], int index1, int index2) {
    Car temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

//Given a vin number, returns the index that the vin number occurs.
//Returns -1 if the vin does not exist in the heap.
int MaxHeap::isFound(int aVin) {
    for (int i = 0; i < size; i++) {					//Traverse through heap
        if (carArr[i].vin == aVin) {
            return i; 									// Return the index if the Car if it is found
        }
    }
    return -1; 											// Return -1 if Car is not found
}

//****************************************************
//increase the Car's VIN located at the specific index
//Given a Car , and the car's index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN) {
	if (carArr[index].vin > oneCarWithNewVIN.vin){						//If its already greater, we cant increase
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }

	carArr[index] = oneCarWithNewVIN;
	
	while((index > 0) && (carArr[parent(index)].vin < carArr[index].vin)) { 	//While greater than root and parent is still smaller
		swap(carArr,index,parent(index));										//Swap elements and reset index
		index = parent(index);
	}
	return true;
}


//Given the parameters for a car object, this function creates a new car 
//and inserts it into the correct position in the heap. 
//Returns TRUE if task is completed, returns FALSE if there is an error. 
bool MaxHeap::heapInsert(int vin, string model, string make, double price) {
	if(isFound(vin) != -1){						//If vin already exists in heap, don't insert
			cout << "\nDuplicated Car. Not added\n";
			return false;
		}
    //If size has reached capacity, double capacity
    if (capacity == size) {
        capacity *= 2;

		Car* temp = new Car[capacity];		//Initialize temp array with a length of "capacity"

        for (int j = 0; j < size; j++) {	//Copy elements to temp
            temp[j] = carArr[j];
        }

        delete[] carArr;					// Delete, then re-assign
        carArr = temp;

        cout << "\nReach the capacity limit, double the capacity now.\n";
        cout << "\nThe new capacity now is " << capacity << endl;
    }
	
	Car newCar = {model,make,vin,price}; //Initialize new Car

	carArr[size] = newCar;					//Set last node to new car to insert
	size++;									//Increment size
	return heapIncreaseVIN(size - 1,newCar);	//Return if we can increase, or float up, newCar
}

//Given an index of the heap, "float down" the car at the index in order to maintain the heap property
void MaxHeap::heapify(int index){
	int right = rightChild(index);				//Calculate left,right
	int left = leftChild(index);
	int largest;

	if (carArr[left].vin > carArr[index].vin && left <= size){		 			//Calculate the largest vin between parent(index) and child
		largest = left;															//If left is bigger, left is largest
	}																			//If right is bigger, right is largest
	else{
		largest = index;
	}
	if (carArr[right].vin > carArr[largest].vin && right <= size) {				//This way, we take larger of left and right if they both larger
        largest = right;
    }
	if(largest!=index){															//If left or right child is larger,swap it and call function again
		swap(carArr,index,largest);
		heapify(largest);
	}
}

//Returns the root/largest element in the max heap
Car MaxHeap::getHeapMax(){
	return carArr[0];
}

//Removes the root of the heap while preserving the heap
void MaxHeap::extractHeapMax(){
	if(size < 0){
		//Maybe add something here later
	}
	else{
		carArr[0]=carArr[size - 1];			//last element is the new root
		size--;							
		heapify(0);						//Heapify the root(last node is removed by size--)
	}
}

//Prints the Heap in specified formtted output
void MaxHeap::printHeap() {
	
    if (size == 0) {										//If the heap is empty, print error message and return
        cout << "Empty heap, no elements" << endl;
        return;
    }

    //First print heap capacity and size
    cout << "\nHeap capacity = " << capacity << endl;			//no newline before(maybe)
    cout << "\nHeap size = " << size << endl << "\n";

    //Next, print the data of each car in the heap
    for (int i = 0; i < size; i++) {
        Car car = carArr[i];
        cout << left;																	//Format given by rubric
        cout << setw(8) << car.vin														//
             << setw(12) << car.model													//
             << setw(12) << car.make													//
             << setw(8) << fixed << setprecision(2) << car.price << endl;				//
    }
}




