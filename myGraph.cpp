#include "myGraph.h"
#include <cfloat>
#include <iostream>
#include<iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
#define INF 1000
using namespace std;

//this function creates the weighted graph from a text file and represents the graph 
//in an adjacency matrix
void Graph::createGraph(){
	ifstream infile;
	char fileName[50];
	int vertex;
	int adjacentVertex;
	int weight;
	
	cout << "Enter input file name(the_graph.txt): ";
	cin >> fileName;
	cout << endl;
	infile.open(fileName);
	if (!infile){
		cout << "Invalid file name " << endl;
		return;
		}
	
	
	//initializing every value in the matrix to infinity
	for (int index=0; index< gSize;index++){
		for (int x=0; x < gSize; x++){
			weights[index][x]=INF;
		}
	}
	//reading data according to the file
	while (infile.good()){ //the number of edges
		infile >> vertex;
		infile >> adjacentVertex;
		infile >> weight;
			weights[vertex][adjacentVertex]=weight;
	}
	infile.close();
} 




void Graph::shortestPath(int vertex){
	try{
	
	//initializing array smallest weight with the values from the matrix 
	for (int j = 1; j < gSize; j++)
		smallestWeight[j] = weights[vertex][j];
		bool *weightFound;
		
	weightFound = new bool[gSize];
	//path is the array to store the vertex before the current vertex
	//in the shortest path tree
	path = new int [gSize];

	for (int j = 1; j < gSize; j++){
		weightFound[j] = false;
		path[j]=0;
		path[0]=-1;
		}
	//set the weight found of the source vertex to true because the 
	//shortest distance is already found = 0
	weightFound[vertex] = true;
	smallestWeight[vertex] = 0;
	//dijkstra's algorithm to find shortest path 
	for (int i = 1; i < gSize-1; i++)
		{
		double minWeight = INF;
		int v;
		
		for (int j = 1; j < gSize; j++){
		    
			if (!weightFound[j])
				if (smallestWeight[j] < minWeight)
				{
				v = j;
				minWeight = smallestWeight[v];
				
				}
			}
		weightFound[v] = true;
		
		for (int j = 1; j < gSize; j++){
			//update if there is a path to any adjacent vertex to j
			// via j that can be improved
			if (!weightFound[j]){
				if (minWeight + weights[v][j] < smallestWeight[j]){	
					path[j]=v;	
				
				smallestWeight[j] = minWeight + weights[v][j];
			
			}
			}
			
			}
				
	} 
	
	//calling printShortestDistance to print and write to the csv file
	printShortestDistance(smallestWeight, path, vertex);
	}
	catch(const std::exception & ex ){
		cerr << ex.what() << endl;		
	}
	
	
	
} 


void Graph::printShortestDistance(int smallestWeight[],int path[], int vertex){
	//oopen a csv file to write the calculated shortest distance and path 
	ofstream myfile;
	myfile.open ("path.csv");

	cout << "Source   dest   Shortest_Distance    path" << endl;
	//this loop prints the output on the screen and writes also to the csv file
	for(int i=1 ; i< gSize ;i++){
		cout << vertex << setw(12)<<i << setw(12) << smallestWeight[i] <<
		setw(12)<<vertex;
		printPath(path, i);
		cout<< endl;
		myfile << vertex<<"," << i<< ","<<smallestWeight[i]<<","<< vertex <<",";
		//parent is a queue to store the path for evry vertex
		while(!parent.empty()){
			myfile<< parent.front()<<",";
			parent.pop();
		}
		myfile <<endl;
	}

	myfile.close();
	cout<<"Loading ! Please Wait...."<<endl;
	
} 

//this function recursively push vertices making up the path to the destination
void Graph::printPath(int path[], int dest) { 
	
// Base Case : If j is source
    if (path[dest]==-1)
		return;
	//if the destination is the origin
	else if (path[dest]== 0)
		cout<<"";
		
    printPath(path, path[dest]);
    cout<<" -> "<<dest;
    //push the vertices visited before the dest vertex in the queue for each dest vertex
    parent.push(dest);
    
    	
}
//this function deletes an edge from the text file used to create the graph
void Graph :: deleteLine(std::string filename, int u, int v ){
	try{
		ifstream infile;
		ofstream myfile;
		int count = 0;
		//use vector to store the data read from the file
		//use pairs because there are three values, vertex u, vertex v and weight between the two
		vector< pair<int, pair<int, int> > > myvec; 
		if (filename == "the_graph.txt"){
			myvec.clear();
			infile.open(filename.c_str());
			int b,c,d;
			
			while(infile.good()){
				infile >> b;
				infile >> c;
				infile >> d;
				if((b==u) && (c==v)){//if the edge match any entry from the file ignore it(hence delete)
					
				}
				else{
					myvec.push_back(make_pair(b, make_pair(c, d)));//otherwise push
					count++;
				}
				
			}
			//cout<<"Successfully Deleted!"<<endl;
			infile.close();
			myfile.open ("temp.txt");
			//empty the contents of the vector into a temporary file
			while(count!=0){
				myfile << myvec[count-1].first << " " << myvec[count-1].second.first << " "<<myvec[count-1].second.second <<endl ;
				myvec.pop_back();
				count--;
				
			}
			myfile.close();
			remove("the_graph.txt");//delete original file
			rename("temp.txt","the_graph.txt");//rename temporary file with original name
			return;
			
		}
		
		
		cout<<"file not found!"<<endl;
	}
	catch(const std::exception & ex){
		cout<<"the edges are not in the graph"<<endl;
	}
	
	
	
	
}
//this function adds a new edge to the existing graph
void Graph::insert(int u, int v){

		//check if the vertices are in the graph
		if((gSize<u) || (u<1)){
			cout<<"source node does not exist!"<<endl;
		}
		else if ((gSize<v) || (u<1)){
			cout<<"destination node does not exist!"<<endl;
		}
		else {
			int edgeWeight;
			cout<<"Enter the weight of the edge :"<<endl;
			cin>>edgeWeight;
			weights[u][v]=edgeWeight;
			ofstream myFile ("the_graph.txt", ios::app);
			myFile <<"\n"<< u << " " << v << " " << edgeWeight<<endl;
			myFile.close();
		}
	}
	

//this function deletes an edge in the existing matrix and calls the 
//deleteLine() method which deletes from the file
void Graph::Remove(int u,int v){
	//check if edge exists
    if((gSize<u) || (gSize<v)  || (weights[u][v]==INF)){ 
		cout<<"This edge does not exist !"<<endl;
		return;
    }
    weights[u][v]=INF;
    deleteLine("the_graph.txt", u, v);
    
    
}
//this function searches the graph for an edge
bool Graph :: search(int u, int v){
	if((gSize<u) || (gSize<v)  || (weights[u][v]==INF )){
		cout<<"This edge does not exist !"<<endl;
		return false;
    }
    cout<<"Edge found!, weight ="<<weights[u][v]<<endl;
    return true;

}


//Constructor
Graph::Graph(int size){
	//maxSize is the size of the graph and initialize weights
	//a 2d array to store the adjacency matrix
	gSize = size;
	weights = new int*[size];
	for (int i = 0; i < size; i++)
		weights[i] = new int[size];
	smallestWeight = new int[size];
	
}
//Destructor
Graph::~Graph(){
	//delete the pointers and dynamic arrays
	for (int i = 0; i < gSize; i++){
		delete [] weights[i];
	}
	delete [] weights;
	delete smallestWeight;
	delete path;
	
}

