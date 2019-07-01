#include <queue>
#include <string>
//using namespace std;

class Graph{
	public:
		//function to create the graph
		void createGraph();
		//function to insert an edge on the esxisting graph
		void insert(int u, int v);
		//function to delete entry from the text file
		void deleteLine(std::string filename,int u, int v);
		//function to remeove an edge
		void Remove(int u, int v );
		//function to search whether an edge exist between two nodes
		bool search(int u, int v);
		//Function to determine the weight of a shortest path
		//from vertex, that is, source, to every other vertex
		//in the graph.
		void shortestPath(int vertex);
		void printShortestDistance(int smallestWeight[],int path[],int vertex);
		void printPath(int path[], int dest);
		//Functions to print the shortest weight from the source vertex
		//to every other vertex in the graph.
		Graph(int size = 0);
		//Constructor
		~Graph();
		//Destructor
		//The storage occupied by the vertices and the arrays
		//weights and smallestWeight is deallocated.
		protected:
		int gSize;
		int **weights;//pointer to the adjacency matrix
		int *smallestWeight; //pointer to create the array to store
		//the smallest weight from source to vertices
		int *path ;
		//to store the path with  the smallest vertex for every vertex in the graph
		std::queue <int> parent; //temporary storage for the path, enables the path
		//to be exported to the csv file
};

