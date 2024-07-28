//********************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Joel Hudgens
// 1224491216
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges
//********************************************************************
#include "Edge.h"
using namespace std;

class Graph
{
   private:
      int V, E;         //number of vertice and edges in the graph
      City* cityArr;    //an array of City objects
      Edge* edgeArr;    //an array of Edge objects

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      ~Graph();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void sortEdges();
      void merge(Edge* arr, int left, int mid, int right);
      void mergeSort(Edge* arr, int left, int right);
      void MST_Kruskal();

};

//Constructor
//Initilaize graph's data with the given arguments
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray){
   V = numOfCities;
   E = numOfEdges;
   edgeArr = edgeArray;
   cityArr = cityArray;
}

Graph::~Graph(){
   //delete the allocated arrays
   delete[] cityArr;
   delete[] edgeArr;
}

//Given a City object, this function creates a new disjoint set with one member
void Graph::make_set(City* aCity){
   //first nodes parent is itself
   aCity->parent = aCity;
   aCity->rank = 0;
}

//Given a city in the set, return a pointer to the representative in the set
City* Graph::find_set(City* aCity){
   if(aCity != aCity->parent){ //If its parent is not 
      aCity->parent = find_set(aCity->parent);
   }
      return aCity->parent;
}

//Given two city objects, correct their position within the set
void Graph::link(City* aCity, City* bCity){
   if (aCity->rank > bCity->rank){        //if a rank is larger
      bCity->parent = aCity;              //a becomes b's parent
   }
   else{
      aCity->parent = bCity;
      if(aCity->rank == bCity->rank){
         bCity->rank = bCity->rank + 1;
      }
   }
}

//Given two cities that are members of disjoint sets, combine the two sets
void Graph::Union(City* aCity, City* bCity){
   link(find_set(aCity),find_set(bCity));       //link the corresponding represntatives
}

//Sorts the edges array using merge sort
void Graph::sortEdges() {
   mergeSort(edgeArr, 0, E - 1);
}

//Helper for mergeSort()
//This function merges a split array into one array
void Graph::merge(Edge* arr, int left, int mid, int right) { //Arrays are automatically passed by reference. 
   int Lsize = mid - left + 1;
   int Rsize = right - mid;

    // Create temporary arrays
   Edge* leftArr = new Edge[Lsize];
   Edge* rightArr = new Edge[Rsize];

   // Copy data to temp left and right arrays
   for (int i = 0; i < Lsize; i++){
      leftArr[i] = arr[left + i];
   }
   for (int j = 0; j < Rsize; j++) {
      rightArr[j] = arr[mid + 1 + j];
   }

   // Merge the temporary arrays back into arr[left..right]
   int i,j = 0;
   int k = left; 

   //loop until we reach the end of one of the temp arrays
   while (i < Lsize && j < Rsize) {
      if (leftArr[i].getDistance() <= rightArr[j].getDistance()) {   //pick the smaller element to insert into OG array
         arr[k] = leftArr[i];
         i++;                          //whicher ever array has the smaller element we increment that index
      } else {
         arr[k] = rightArr[j];
         j++;
      }
      k++;  
   }

    //Use two while loops to check for left over elements in either array
   while (i < Lsize) {
      arr[k] = leftArr[i];
      k++;
      i++;
   }
   while (j < Rsize) {
      arr[k] = rightArr[j];
      k++;
      j++;
   }
   
   //array was passed as reference, no need to return
}

// Merge sort is the correct choice.
void Graph::mergeSort(Edge* arr, int left, int right) {
   if (left < right) {
      //A little trick only the OGs know about
      int mid = left + (right - left) / 2;

      // Recursively sort left and right sub-arrays
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);

      // Merge the sorted halves
      merge(arr, left, mid, right);
   }
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal() {
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;

   // cout<< "BEFORE SORT\n";
   // for (int i = 0; i < E; i++) {
   //    cout<< edgeArr[i].getCity1()->cityName << " ----->";
   //    cout<< edgeArr[i].getCity2()->cityName << "\n";
   // }
   // Initialize each city as a set
   for (int i = 0; i < V; i++) {
      make_set(&cityArr[i]); //pass the address to make_set because it takes a pointer
   }

   // Sort the edges in non-decreasing order of their weights
   sortEdges();

   // cout<< "AFTER SORT\n";
   // for (int i = 0; i < E; i++) {
   //    cout<< edgeArr[i].getCity1()->cityName << " ----->";
   //    cout<< edgeArr[i].getCity2()->cityName << "\n\n\n\n";
   // }
   
   // Iterate through the edges
   for (int i = 0; i < E; i++) {
      Edge curr = edgeArr[i];
      City* u = curr.getCity1();
      City* v = curr.getCity2();

      //If u and v are not in the same set
      if (find_set(u) != find_set(v)) {
         // Add the edge to the MST
         totalDistance += curr.getDistance();

         // Merge the disjoint sets of u and v
         Union(u,v);

         edgeArr[i].printEdge();
      }
    }

    cout << "=================================================" << endl;
    cout << "Total Distance: " << totalDistance << endl;
}
