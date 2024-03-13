// Assignment: ASU CSE310 HW#3 Spring 2024
// Joel Hudgens
// 12244491216
// jdhudge1@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.


//only include the necessary header file
//----
#include <iostream>
#include <string>
#include "MaxHeap.h"
using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;

	//declare any other variables in case you need them
	//----

    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = new MaxHeap(0);
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':{	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				heap1 = new MaxHeap(capacity);

				break;
			}

			case 'D':{	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				//INiti
				delete heap1;

				//re-initialize it with capacity 5
				heap1 = new MaxHeap(5);
				break;
			}

			case 'E':{	//Extract the maximum node
                if (heap1->getSize() == 0){
                    cout << "\nEmpty heap, can NOT extract max" << endl;
				}
                else {
                    cout << "\nBefore extract heap max operation:" << endl;			//Print befpre
					heap1->printHeap();		
					cout << "\nAfter extract heap max operation:" << endl;			
					heap1->extractHeapMax();											//Extract, then print
					heap1->printHeap();
                }
				break;
			}

			case 'F':{	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer
				if(heap1->isFound(vin) != -1){											//Check if the car is found
					cout << "\nCar with VIN: " << vin << " is found" << endl;			
				}
				else{
					cout << "\nCar with VIN: " << vin << " is NOT found" << endl;
				}
				break;
			}

			case 'I':{	//Insert a Car
				cout << "\nEnter the car model: ";					//INPUTS
				cin >> model;
				cin.ignore(20, '\n');
				cout << "\nEnter the car make: ";
				cin >> make;
				cin.ignore(20, '\n');
				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cin.ignore(20, '\n');
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');								//INPUTS

				//Add your own code
				bool ret = heap1->heapInsert(vin,model,make,price);							//If ret is false then it infact did not work
				if(ret == true){
					cout << "\nCar \"" << model << " " << make << "\" is added" << endl;				//Print if it was added or not
				}
				else{
					cout << "\nCar \"" << model << " " << make << "\" is NOT added" << endl;

				}

				break;
			}

			case 'K': {	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

				//Add your own code
				Car newCar;
				int indexOfOldVin = heap1->isFound(vin);

				if (newVIN <= vin){																			//Heres a bunch of if statements for edge cases
					cout << "\nIncrease VIN error: new vin is smaller than current vin\n";					//Exit the case if one of these cases happens
					break;}
				if (indexOfOldVin == -1){
					cout << "\nThe old VIN you try to increase does not exist\n";
					break;}
				if (heap1->isFound(newVIN) != -1){
					cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n";
					break;}
			

				cout << "\nBefore increase VIN operation:\n";														//Print Before
				heap1->printHeap();

				newCar = heap1->getCarArr()[indexOfOldVin];															//new vin but same everything else
				newCar.vin = newVIN;

				heap1->heapIncreaseVIN(indexOfOldVin,newCar);							
				cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN << endl;

				cout << "\nAfter increase VIN operation: \n";														//Print After
				heap1->printHeap();
				break;
			}
			
			case 'M':{	//get maximum node

			    if (heap1->getSize() > 0) {
					Car maxCar = heap1->getHeapMax(); //Assign max car

					// Print max car using format specified
					cout << "\nThe maximum heap node is:" << endl;
					cout << left;
					cout << setw(8) << maxCar.vin
						<< setw(12) << maxCar.model
						<< setw(12) << maxCar.make
						<< setw(8) << fixed << setprecision(2) << maxCar.price << endl;
				} 
				else {
					cout << "Empty heap, can NOT get max node" << endl;
				}
				break;
			}

			case 'P':{	//Print heap contents

			    if (heap1->getSize() > 0){
					heap1->printHeap();}
				else{
					cout << "\nEmpty heap, no elements" << endl;
				}
				break;
			}

			case 'S':{	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				heapSort(heap1);
				break;
			}

			case 'Q':{	//Quit
				delete heap1;
				break;
			}

			case '?':{	//Display Menu
				printMenu();
				break;
			}

			default:{
				cout << "Unknown action\n";
				break;
			}
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap) {
    int ourSize = oneMaxHeap->getSize();  
	Car sortedCars[ourSize + 1];    							//create an array to store sorted heap

    for (int i = ourSize - 1; i >= 0; i--) {				//For every Car
		sortedCars[i] = oneMaxHeap->getHeapMax();			//store max in sorted array
		oneMaxHeap->extractHeapMax();						//Extract max
    }
	// Print all the cars in the sortedCars array
    for (int i = 0; i < ourSize; i++) {
        cout << setw(8) << sortedCars[i].vin
             << setw(12) << sortedCars[i].model
             << setw(12) << sortedCars[i].make
             << setw(8) << fixed << setprecision(2) << sortedCars[i].price << endl;
    }
}


//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
