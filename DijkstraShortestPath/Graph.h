//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Joel Hudgens
// 1224491216
// Description: This file defines a weighted directed graph
//              The graph is created using an adjacenecy list of Departures and Arrivals
//              We implememt this by using a heap of Departures in which each departure has a list of Arrivals
//              There are also graph opeartions in this file such as DiJkstra's shortest path algorithm
//********************************************************************
#include "MinPriorityQueue.h"
using namespace std;

class Graph {
   private:
   int numOfNode;
   MinPriorityQueue* departureHeap;     //adjacency list of the graph, it is a min-heap of Departure objects based on d value

   public:
   Graph(int numOfNode, MinPriorityQueue* departureHeap);
   ~Graph();
   MinPriorityQueue* getDepartureHeap();
   void printGraph();
   void initialize_single_source(string sourceDepAddress);
   void relax(Departure u, Departure v);
   int findOneDeparture(string aDepAddress);
   void dijkstra(string sourceDepAddress);
   void printDijkstraPath(string sourceDepAddress); 
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* departureHeap){
   this->departureHeap = departureHeap;      //just pass in the arguments
   this->numOfNode = numOfNode;
}

//*******************************************************************
//Destructor Graph::~Graph()
Graph::~Graph(){
   delete[] departureHeap;
}

//Public access method
MinPriorityQueue* Graph::getDepartureHeap(){
   return departureHeap;
}

//*******************************************************************
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph(){
   departureHeap->printHeap();
}

//Given a source departure address, initialize the graph
void Graph::initialize_single_source(string sourceDepAddress){
   int res = departureHeap->isFound(sourceDepAddress);      
   Departure key;
   key.d = 0;                       //The starting distance is 0
   departureHeap->decreaseKey(res,key);
}

//Given two departures, perfomrm the relax operation. 
void Graph::relax(Departure u, Departure v){
   Arrival* curr = u.arrList->findArrival(v.depAddress);
   int speed = 0;

   if(curr->roadCategory == "I"){         //Assign the edge weight according to the type of highway
      speed = 65;                         //
   }else if(curr->roadCategory == "A"){   //
      speed = 55;                         //
   }                                      //
   else if(curr->roadCategory == "C"){    //
      speed = 45;                         //
   }                                      //
   else if(curr->roadCategory == "L"){    //
      speed = 25;                         //
   }                                      //
   else{                                  //
      speed = 0;                          //
   }                                      //

   //The weight is the time traveled (distance/speed) betweeen the departure and arrival 
   double weight = (u.arrList->findArrival(v.depAddress)->distance) / speed;        

   cout << weight; //remove

   if (v.d > u.d + weight ){           //If the Arrival's distance is greater than the edge we are checking
      v.d = u.d + weight;              //Update with new shorter distance
      v.pi = &u;                       //Update v's parent with the Departure that is shorter
   }
}

//returns the index that it occurs in the array
//Returns -1 if it doesnt exist
int Graph::findOneDeparture(string aDepAddress){
   return departureHeap->isFound(aDepAddress);
}

//Given a a departure address, this function performs dijiktras shortset path based on the departure
void Graph::dijkstra(string sourceDepAddress){
   initialize_single_source(sourceDepAddress);
   Departure *arr = departureHeap->getDepartureArr();

   while(departureHeap->getSize() > 0){               //while we havent reached the end of the departures (heap)
      Departure u = departureHeap->getHeapMin();

      departureHeap->extractHeapMin();          //MAYBE ADD THIS TO A TEMP HEAP BEFORE DESTORYING??
      Arrival* curr = u.arrList->getHead();

      while(curr != nullptr){                            //while we havent reached the end of the arrivals (linked list)
         departureHeap->isFound(curr->arrAddress);
         int index = findOneDeparture(curr->arrAddress);
         if (index != -1){                               //If the departure wasn't found
            Departure v = arr[index];
            relax(u,v);
         }
         curr = curr->next;
      }
   }
}

void Graph::printDijkstraPath(string sourceDepAddress){
   cout << "Print the Dijkstra algorithm running result" << endl;
   cout << "Departure address: " << sourceDepAddress << endl;

   Departure* arr = departureHeap->getDepartureArr();       //make and array that represents the heap

   cout << left;
   cout << setw(15) << "Arrival"
      << setw(20) << "Shortest Time (h)"
      << "Shortest Path" << endl;

   for (int i = 0; i < numOfNode; i++) {     //loop through the array
      Departure curr = arr[i];
      string path = "";
      
      while (curr.pi != nullptr){                     //while the parent is not NULL
         path = curr.pi->depAddress + " -> " + path;  //append curr's parent to the path
         curr = *(curr.pi);                           //Go to the curr's parent.  CHECK THIS LATER IDK WHATS HAPPENENING HERE
      }

      cout << left << fixed;
      cout << setw(15) << arr[i].depAddress
            << setw(20) << setprecision(2) << arr[i].d 
            << path << endl;
   }
}
