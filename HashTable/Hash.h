// ASU CSE310 Assignment #5 Spring 2024
// Joel Hudgens
// 1224491216
// Description: This class represents a Hash Table which solves collisions by chaining.
// Structurally, this is an Array of Linked Lists of type 'Car'
// Given a car, we use that cars data to make a key. Using that key, we map that car to a specific
// index in the array using the hash function. This allows us a direct lookup into the hashtable using a key
// which is much faster than traversing. 

//only include necessary header file here
#include "LinkedList.h"
#include <iostream>


using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string model, string make, int vin);
      bool hashInsert(string model, string make, int vin, double price);
      bool hashDelete(string model, string make, int vin);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
      int getSize(int index);
  };

//constructor
Hash::Hash(int size){
   m = size;
   hashTable = new LinkedList[m]; // Allocate memory for array of LinkedList
}

//Destructor
Hash::~Hash()
{
   for(int i = 0;i < m; i++){         //for every position in array
      hashTable[i].~LinkedList();     //delete the linked list in that position
   }
   delete[] hashTable;
}

// Return the size of the linked list at a given slot
int Hash::getSize(int index) {
      return hashTable[index].getSize();   //(In linked list file)
   }

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{
   string hashKey = model + make + to_string(vin);                // Concatenate strings

   int index = hashFunction(hashKey);    
   bool found = hashTable[index].searchCar(vin);                   //Search linked list at the given index

   if (found == true){                                            //Print results and return
      cout << "\n" << left
          << setw(18) << model
          << setw(18) << make
          << setw(8)  << vin
          << " is found inside the hash table." << endl;
   }
   else {
      cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT found inside the hash table." << endl;
   }
   return found;
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
   bool inserted;
   string hashKey = model + make + to_string(vin);                // Concatenate strings
   int index = hashFunction(hashKey);                             //compute the index

   inserted = hashTable[index].insertCar(model,make,vin,price);   //Into the linked list at index, insert car at the head

   return inserted;                                               //return if the insertion was successful or not
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
   string hashKey = model + make + to_string(vin);                // Concatenate strings
   int index = hashFunction(hashKey);                             //compute the index

   bool found = hashSearch(model,make,vin);                       //Determine if car is found

   if (found == false){                                           //If not in linked list, return false
      cout << "\n";
      cout << setw(18) << model
         << setw(18) << make
         << setw(8)  << vin
         << " is NOT deleted from hash table." << endl;

         return false;
   }

   bool deleted = false;                                          //If it is, call delete and return whether it was deleted
   deleted = hashTable[index].deleteCar(vin);

   cout << "\n";
   cout << setw(18) << model
         << setw(18) << make
         << setw(8)  << vin
         << " is deleted from hash table." << endl;

   return deleted;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
   int result = 0;               //We will over-write this everytime we find a larger length

   for(int i = 0;i < m; i++){                         //For every position in hash array
      int currLength = hashTable[i].getSize();        //get size of linked list at that position

      if(currLength > result){                        //Update result if the currentLength is bigger
         result = currLength;
      }
   }
   return result;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   for(int i = 0;i < m; i++){                                                                   //For every position in hash array
      int currentLength = hashTable[i].getSize();
      if (currentLength == 0) {                                                                 //If linked list is empty                
            cout << "\nHashTable[" << i << "] is empty, size = " << currentLength << endl;
        }
      else {
         cout << "\nHashTable[" << i << "], size = " << currentLength << endl;              
         hashTable[i].displayList();
      }
   }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
   int sum = 0;
   for (int i = 0; i < (int)key.length(); ++i) { // For each char in string
        sum += key[i]; // Add the ASCII value of the character to sum
    }
   return sum % m;             // Compute the index
}
