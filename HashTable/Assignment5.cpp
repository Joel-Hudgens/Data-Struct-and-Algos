// ASU CSE310 Assignment #5 Spring 2024
// Joel Hudgens
// 1224491216
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
********************************************************************************/
// 1)    My hash function is a very straight forward computation using a modulus.
//       Given the String "key", I compute the ASCII value of each character in the string.
//       Then, I add all those values together and modulus it with the length of the hashTable
//       This effectively distibutes the Cars into indexes in the hashTable
//
// 2)     My hash function proved to be effective. The longer the hashTable and the more inputs given,
//        the better it performs. This is because with more values, there is less of a chance that 
//        the computed indexes will be skewed. With more values, the distribution will tend closer toward
//        a normal bell curve. This is seen as the longest test case(4) had the best performance ratio. 
//       Test case 1) Longest: 6    performance ratio: 1.88
//       Test case 2) Longest: 9    performance ratio: 1.66
//       Test case 3) Longest: 8    performance ratio: 1.69
//       Test case 4) Longest: 25   performance ratio: 1.44
//
// 3)    One way to reduce collions is to not allow them. We learned about this in class and it is called 
//       direct hashing. We do this by making a more complicated hash function that handles collisions by
//       computing a new unique index rather than chaining. As far as a way to further optimize my hash with
//       chaining, I would play around with how I manipulate the key. This is because there might be some sort 
//       of bias with the given data set that I could optimize by switching up the key a little bit. 


#include "Hash.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

//Define function members
string getKey(string oneLine, string& model, string& make, int& vin);
void getCarAttributes(string oneLine, string& model, string& make, int& vin,double& price);


int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   string model, make;
   int vin;
   double price;

   //declare any other necessary variables here
   string carString;

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   //Instantiate the hash table with the relevant number of slots
   Hash *table = new Hash(size);
 
   do {
      //use this do..while loop to repeatly get one line Car info. and extract tokens
      //create one Car object and insert it inside the hashTable until seeing the message
      //"InsertionEnd" to terminate

      //Get the carString from user
      getline(cin, carString);

      // Check if it's the exit command
      if (carString == "InsertionEnd"){
         break;
      }

      //Parse input into 4 car parameters
      getCarAttributes(carString,model,make,vin,price);
      // Insert the Car into the hash table
      table->hashInsert(model, make, vin, price);

   } while(true);

   //cout << "\nEnter number of commands: ";   //***need to comment out in submitting
   cin >> numOfCommand;
   cin.ignore(20, '\n');

   for(int i= 0; i < numOfCommand; i++)
   {  
      string oneLine;
      getline(cin,oneLine);

      if(oneLine.compare("hashDisplay") == 0){                          //If hashDisplay or hashLoadFactor...no more splicing needed.
         table->hashDisplay();                                          //Seperate these commands from hashSearch and hashDelete
      }
      else if(oneLine.compare("hashLoadFactor")==0){
            int totalCars = 0;
            for(int i = 0;i < size; i++){                            //for every position in table
               totalCars += table->getSize(i);
            }
            float idealLoadFactor = (float)totalCars / (float)size;      //Was getting division error without explicit casting
            float actualLoadFactor = table->hashLoadFactor();
            float performanceRatio = actualLoadFactor / idealLoadFactor;


            std::cout << "The ideal load factor is: " << std::fixed << std::setprecision(2) << idealLoadFactor << std::endl;
            std::cout << "My hash table real load factor is: " << std::fixed << std::setprecision(2) << actualLoadFactor << std::endl;
            std::cout << "My hash table performance ratio is: " << std::fixed << std::setprecision(2) << performanceRatio << std::endl;
         }

      else{                                                                       //If hashSearch or hashDelete, We need to splice the input "oneLine" 
         oneLine = getKey(oneLine,model,make,vin);                                 //In order to get the additional car data from it.

         if(oneLine.compare("hashSearch")==0){                                   
            table->hashSearch(model,make,vin);
         }
         else if(oneLine.compare("hashDelete")==0){
            table->hashDelete(model,make,vin);
         }
         else {
            cout<<"Invalid command"<<endl;
         }
      }
   }
    //end for loop
   return 0;
}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens
string getKey(string oneLine, string& model, string& make, int& vin)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   string command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
   return command;
}

//Given a string of user input,splice it and get the model, make, vin, and price.
void getCarAttributes(string oneLine, string& model, string& make, int& vin, double& price)
{
   string delimiter = ",";   //look for commas to splice
   int pos;           //start at the beggining of the string
   string token;

   //extract model
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   model = token;
   oneLine.erase(0, pos + delimiter.length());

   //extract make
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   make = token;
   oneLine.erase(0, pos + delimiter.length());

   //extract VIN
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   vin = stoi(token);
   oneLine.erase(0, pos + delimiter.length());

   //extract price
   price = stod(oneLine);
}



