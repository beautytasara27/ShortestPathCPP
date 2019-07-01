#include "myGraph.h"
#include <iostream>
using namespace std;
int main(){
	int source, size, input;
	
	bool cont = true;
	cout<<"Enter the size of the graph(11) :"<<endl;
	cin>>size;
	Graph wgt(size+1);
	wgt.createGraph();
	while(cont){
		cout<<" 1.VISUALIZE \n 2.ADD EDGES \n 3.DELETE EDGES \n 4.SEARCH EDGE \n 5.EXIT "<<endl;
		
		cin>>input;
		switch(input){
			case 1: {
				bool status;
				bool option= true;
				char choice;
				while(option){
					do{
						cout<<"enter the source vertex between 1 and "<<size<<endl;
						cin>>source;
						if(source>0 && source<=size){
							status = true;
							wgt.shortestPath(source);
							system("viz.py");
							
						}
						else{
							cout<<"the source is invalid, try again"<<endl;
							status = false;
						}
						
					}while(status==false);
					do{
					    cout<<"do you want to calculate from another source?(Y/N) :"<<endl;
						cin>>choice;
						if (choice=='N' || choice == 'n'){
							option= false;
						}
						else if(choice=='Y' || choice=='y'){
							option = true;
						}
						else {
							option=false;
							cout<<"invalid option"<<endl;
							
						}
						}while(option==false && !(choice=='n' || choice=='N'));
				}
				system("pause");
				system("cls");
		
		
				
				break;
			}
			case 2 : {
				int u,v;
				cout<<"Please Enter source node :";
				cin>>u;
				cout<<endl;
				cout<<"Please Enter destination node :";
				cin>>v;
				cout<<endl;
				wgt.insert(u,v);
				system("pause");
				system("cls");
				break;
			}
			case 3 :{
				int u,v;
				cout<<"Please Enter source :";
				cin>>u;
				cout<<endl;
				cout<<"Please Enter destination :";
				cin>>v;
				cout<<endl;
				wgt.Remove(u,v);
				cout<<"Successfully Deleted!"<<endl;
				system("pause");
				system("cls");
				break;
			}
			case 4 :{
				int u,v;
				cout<<"Please Enter source :";
				cin>>u;
				cout<<endl;
				cout<<"Please Enter destination :";
				cin>>v;
				cout<<endl;
				wgt.search(u,v);
				system("pause");
				system("cls");
				break;
			}
			default :{
				exit(0);
				break;
				
			}
		}
	}
	
}

