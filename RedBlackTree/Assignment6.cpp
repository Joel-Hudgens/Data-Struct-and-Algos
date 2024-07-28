//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Joel Hudgens
// 1224491216
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int& vin, string& model, string& make); 
//This function used to get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price);

int main()
{

   int vin;
   string model, make;
   double price;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object here, use it throughout the program
   RedBlackTree* tree = new RedBlackTree();

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());


      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         delete tree;         //should call deconstructor and print number of nodes deleted
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;

          tree->treePreorder();
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;

         tree->treeInorder();
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;
         tree->treePostorder();
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;

         tree->treeMinimum();
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;

        tree->treeMaximum();
      }
      else if(command.compare("tree_predecessor")==0)
      {
         cout << "\nCommand: tree_predecessor" << endl;
         getCarKey(oneLine,vin,model,make);
         tree->treePredecessor(vin,model,make);
      }
      else if(command.compare("tree_successor")==0)
      {
         cout << "\nCommand: tree_successor" << endl;
         getCarKey(oneLine,vin,model,make);
         tree->treeSuccessor(vin,model,make);
      }
      else if(command.compare("tree_search")==0)
      {
         getCarKey(oneLine,vin,model,make);
         Node* searched = tree->treeSearch(vin,model,make);


         cout << "\nCommand: tree_search" << endl;

         if (searched != nullptr){
            cout << left;
                  cout << setw(8) << searched->vin
                  << setw(12) << searched->model
                  << setw(12) << searched->make
                  << setw(12) << "is FOUND.\n";
         }
         else {
               cout << setw(8) << vin
                  << setw(12) << model
                  << setw(12) << make
                  << setw(12) << "is NOT FOUND.\n";
            
         }
      }
      else if(command.compare("tree_insert")==0)
      {
         //call the getCarInfo function to get the Car key first
         getCarInfo(oneLine,vin,model,make,price);

         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << price << endl;

         tree->treeInsert(vin,model,make,price);
        }
   } while(true);  //continue until 'quit'
   return 0;
}

//*********************************************************************************
//This function from one line, extracts the vin, model, make of a Car.
//It is important to note that we are referencing the original copies of vin, model, and make within this function
// So we are pointing to those original values and directly manipulating them
//****************************************************************************************
void getCarKey(string oneLine, int& vin, string& model, string& make)
{
   string delimiter = ",";
   int pos;
   string token;     

   //extract VIN
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   //extract model
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   //extract make
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price)
{
   string delimiter = ",";   //look for commas to splice
   int pos;           //start at the beggining of the string
   string token;

   //extract VIN
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0, pos);
   vin = stoi(token);
   oneLine.erase(0, pos + delimiter.length());

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

   //extract price
   price = stod(oneLine);
}