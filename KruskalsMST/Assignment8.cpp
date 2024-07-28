//************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Joel Hudgens
// 1224491216
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
//**************************************************************************
#include "Graph.h"
using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);
int searchCity(City* oneCityArray, int size, string oneCityName);

int main()
{
   int V = 0;
   int E = 0;        //number of vertices and edges

   //cout << "Enter number of vertices and edges: " << endl;
   cin >> V >> E;
   cin.ignore(20, '\n');

   //a City array used to store all vertices (Cities) of the graph
   City* cityArray = new City[V];

   //an array used to store all edges of the graph
   Edge* edgeArray = new Edge[E];

   int citySize = 0;
   int edgeSize = 0;

   //local variables
   City* city1;
   City* city2;

   string oneLine;

   //cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);
   string delim;

   while(oneLine.compare("End") != 0)
   {
      //get one line of the input, extract the first token
      //create a City object if it does not exist in cityArray,
      //insert it inside the cityArray. This will be first vertex of the 'aNewEdge'
      int pos = oneLine.find(",");          //Find the comma
      string city1Name = oneLine.substr(0,pos);
      int city1Index = 0;
      
      int found = searchCity(cityArray,V,city1Name);

      if(found == -1){                         //If city is not in array
         cityArray[citySize] = City(city1Name);       //create a new city and add it in the array
         city1Index = citySize;
         citySize++;
      } else{
        // city1 = &cityArray[result];
         city1Index = found;                  //Otherwise, save the index of city1
      }

      oneLine.erase(0,pos+1);    //erase comma

      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point of the 'aNewEdge'
      while(oneLine.length() > 0){       //loop through the rest of the string
         double city2Distance;

         pos = oneLine.find(",");
         string city2Name = oneLine.substr(0,pos);
         if(city2Name.length() > 0){            //while we havent reached the end of the string 
            getArrCityInfo(city2Name,city2Name,city2Distance);
            int city2Index = searchCity(cityArray,citySize,city2Name);

            if(city2Index == -1){                     //create new city2 and add to end of city array
               city2 = new City(city2Name);
               cityArray[citySize] = City(city2Name);
               city2Index = citySize;
               citySize++;
            }
            
            Edge* newEdge = new Edge(&cityArray[city1Index],&cityArray[city2Index],city2Distance); //Ew. But create a new edge.
            edgeArray[edgeSize] = *newEdge;                                                        //Each city is the value(&) found in the array of cities
            edgeSize++;                                                                            //Based off the index we have saved.
         }
         oneLine.erase(0,pos+1);
      }

      //get next line
      getline(cin, oneLine);
   } //repeat until the 'End'

   // cout<<"num cities: "<<citySize<<"\n";
   // cout<<"num edges: "<<edgeSize<<"\n";

   // for (int i = 0; i<V; i++){                      //remove
   //    cout<< cityArray[i].cityName<<"\n";
   // }
   // for (int i = 0; i<E; i++){ 
   //    Edge* currEdge = &edgeArray[i];
   //    currEdge->printEdge();                       //remove

   // }
      //Create a Graph object by using cityArray and edgeArray
   Graph* graph = new Graph(V,E,cityArray,edgeArray);


   //Run Kruskal MST algorithm on above graph
   graph->MST_Kruskal();
   
   delete graph;
}

//****************************************************************
//By giving a string, for example 'Dallas(1456.5)', this function
//extract the arrival city name 'Dallas' and distance '1456.5'
//Note: the delimiter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance){
   int pos;
   string token;

   pos = oneArrCityInfo.find("(");          //Go to the first parenthses
   token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;
   oneArrCityInfo.erase(0,pos+1);

   pos = oneArrCityInfo.find(")");          //Go to the second paretheses
   token = oneArrCityInfo.substr(0,pos);
   distance = stod(token);
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName) {
   for(int i = 0; i < arraySize; i++){
      if(oneCityArray[i].cityName == oneCityName) {
         return i; //found
      }
   }
   return -1; //Not found
}