//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Joel Hudgens
// 1224491216
// Description: This class is the main driver of the Assignment 7 project.
//              It uses a loop to continually ask the user how they wish to run Djkstra's algorithm
//********************************************************************
#include "Graph.h"
using namespace std;

void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList);
void getArrivalInfo(string oneArrivalInfo, string& arrAddress, double& distance, string& roadCategory); //**optional

int main() {
   int count;       //a variable for number of nodes
   string oneLine, sourceDepAddress;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times or not

   //cout << "Enter number of departure address: ";
   cin >> count;
   cin.ignore(20, '\n');

   //Create an array called 'departureArr' that holds 'count' number of Departure objects
   Departure* departureArr = new Departure[count];
   MinPriorityQueue* departureHeap = new MinPriorityQueue(count); //make a new heap


   //Initialize departureArr. Note: you will need to initialize each of the instance variable
   //including arrival list
   for(int i = 0; i < count; i++) {
      departureArr[i].d = 10000.0 + i;  //***this is to make sure each node has different d value
      departureArr[i].pi = nullptr;
      departureArr[i].depAddress = "";
      departureArr[i].arrList = new ArrivalList();
      
   }

   //get input line by line and create the departureArr
   for(int i = 0; i < count; i++) {
      getline(cin, oneLine);
      getDepartureInfo(oneLine, departureArr[i].depAddress,departureArr[i].arrList); //get the departure attributes and then add it
      departureHeap->insert(departureArr[i]);
   }

   //create a Graph object
   Graph* graph = new Graph(count, departureHeap);                //use departure heap to create a new graph
 
   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
   graph->printGraph();
   
   while(answer == "yes"){ //we pre-initialized answer to yes
      cout <<"Enter the departure address: ";
      getline(cin, sourceDepAddress);

      // Run djikstra on the given address
      graph->printDijkstraPath(sourceDepAddress);

      //keep executing program if user enters yes again
      cout << "\nFind shortest path for another departure address(yes or no): ";
      cin >> answer;
      cin.ignore(20, '\n');
   }
   cout << "Program terminate";
}


//******************************************************************************************
//Given such as Y(1803.2/I), this function extracts arrival Address "Y", distance 1803.2
//and roadCategory "I" info. out
void getArrivalInfo(string oneArrivalInfo, string& arrAddress, double& distance, string& roadCategory){
   int pos = oneArrivalInfo.find("(");          //Go to the first parenthses
   string token = oneArrivalInfo.substr(0,pos);
   arrAddress = token;
   oneArrivalInfo.erase(0,pos+1);

   pos = oneArrivalInfo.find("/");           //Go to the middle parantheses.
   token = oneArrivalInfo.substr(0,pos);
   distance = stod(token);
   oneArrivalInfo.erase(0,pos+1);

   pos = oneArrivalInfo.find(")");        //Go to the last parenthses
   token = oneArrivalInfo.substr(0,pos);
   roadCategory = token;
   oneArrivalInfo.erase(0,pos+1);
}

//********************************************************************************
//Give one line in input file, this function extract tokens and get departure address
//and all arrival info.
void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList){
   int pos = oneLine.find(",");
   string token = oneLine.substr(0,pos);
   depAddress = token;                    //First, extract the departure address
   oneLine.erase(0,pos+1);

   string arrAddress;
   double dist;
   string roadCategory;

   while(oneLine.length() != 0){       //loop through the rest of the string
      pos = oneLine.find(",");
      token = oneLine.substr(0,pos);
      int exists = token.find("(");          //If another arrival exists in the string
      if(exists != -1){
         getArrivalInfo(token,arrAddress,dist,roadCategory);     //extract arrival info using helper method
         arrList->addArrival(arrAddress,dist,roadCategory);      //add arrival to the list
      }
      oneLine.erase(0,pos+1);
   }
}

