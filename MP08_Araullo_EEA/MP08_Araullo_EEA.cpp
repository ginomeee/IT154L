#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	char choice;
  int startWrite = 0;
  int breakDoWhile = 0;
  int n = 0;
  int total = 0;
  double avg = 0;
	do {
		system("CLS");
		ifstream test;
		ofstream ofsAppend;
		stringstream ss;
		int maxCylindSize;
		int headPosStart;
		int cylinderQ[100];
		string strOutput = "";
		
		if (startWrite == 1) ofsAppend.open("MP08 Checker.txt");
		test.open("MP08 Checker.txt");
		if (startWrite == 1){
			ofsAppend<<maxCylindSize << endl;
			ofsAppend<<headPosStart << endl;
			for(int i=0;i<=n;i++){
				if (cylinderQ[i] == -1) break;
	   			ofsAppend<<cylinderQ[i]<< " ";
			}
			ofsAppend << "-1" << endl;
		}
		
		
		// Input values
		test >> maxCylindSize;
		test >> headPosStart;
		n = 0;
		total = 0;
		avg = 0;
		for(int i = 0;  ; ++i){ // Get cylinderQ
	   		test >> cylinderQ[i];
	   		if(cylinderQ[i] == -1)
	        	break;
	        else
	        	n++;
	    }
		
		cout<<"Programmed by: ARAULLO, Eugenio Emmanuel A."<<endl
			<<"MP08 - CLOOK DISK SCHEDULING ALGORITHM"<<endl<<endl;
		if (startWrite == 1) ofsAppend<<"\n\nProgrammed by: ARAULLO, Eugenio Emmanuel A."<<endl
			<<"MP08 - CLOOK DISK SCHEDULING ALGORITHM"<<endl<<endl;

		cout<<"Inputs:"<<endl;
		if (startWrite == 1) ofsAppend<<"Inputs:"<<endl;
		

		cout<<"Max Cylinder Size: "<<maxCylindSize<<endl;
		if (startWrite == 1) ofsAppend<<"Max Cylinder Size: "<<maxCylindSize<<endl;

	    int graphing[n+1];

	    for(int y = 0; y <n; y++){
			graphing[y] = cylinderQ[y];
		}

		cout<<"Head Pointer Position: "<<headPosStart<<"\n";
		if (startWrite == 1) ofsAppend<<"Head Pointer Position: "<<headPosStart<<"\n";

	    cout<<"Queue: ";
	    if (startWrite == 1) ofsAppend<<"Queue: ";

	    for(int i=0;i<=n;i++)
	    {
	    	cout<<cylinderQ[i]<< "  ";
	   		if (startWrite == 1) ofsAppend<<cylinderQ[i]<< "  ";
		}

	    cout<<endl<<endl;
	    if (startWrite == 1) ofsAppend<<endl<<endl;

	    graphing[n] =  headPosStart;
	    n++;

	    int i, j;
        sort(graphing,graphing+n);

	    int headStart_index;
		for(int y = 0; y <n; y++)
			if(headPosStart == graphing[y])
				headStart_index = y;

		int idx=headStart_index;
	    headStart_index++;
		int tn=n+1;
	    int traverse[n];
	    int DStable[n];
        int temp,edge=maxCylindSize-1;
		int k,l;

	    for(int i=idx,k=0; i < n; i++){
	    	traverse[k] = graphing[i];
			k++;
			if(i==n-1){

				l=k;

				for(j=0;j<idx;j++){
					traverse[l]=graphing[j];
					l++;
				}
			}
		}

		for(i=0,j=0;i<=n;i++){
			if(traverse[i]!=edge){
				DStable[j]=traverse[i];
				j++;
			}
		}

	    int diskHole[n + 2];

	    for(int i =0, q=0; i< n+2; i++){
	    	if(i == 0){
		    	diskHole[i] = 0;
			}
			else if(i == n + 1){
				diskHole[i] =  edge;
			}
			else{
				diskHole[i] = graphing[q];
				q++;
			}
		}

		if (startWrite == 1) ofsAppend <<"\n\nOutput:";
		cout<<"\nOutput:\n\n";
		if (startWrite == 1) ofsAppend << "\n\n";

		char horz = 196;
		char vert = 179;
		char uLeft = 218;
		char uRight = 191;
		char dhorz = 194;
		char bLeft = 192;
		char bRight = 217;
		char uhorz = 193;
		char mRight = 180;
		char mLeft = 195;
		char mhorz = 197;

		cout<<"Graph\n\n";
		if (startWrite == 1) ofsAppend << "Graph\n\n";
        int gW = (10*n)-1;

        cout<<uLeft;
        if (startWrite == 1) ofsAppend<<" ";

        for(int i=0; i < gW; i++)
        {
        	cout<<horz;
        	if (startWrite == 1) ofsAppend<<"_";
        	if(i == gW-1)
        	{
        		cout<<uRight;
			}
		}
		cout<<endl;
		if (startWrite == 1) ofsAppend<<endl;

		cout<<vert;
		if (startWrite == 1) ofsAppend<<"|";

		for(int i=0; i<n+2; i++){
			cout<<diskHole[i]<<"\t";
			if (startWrite == 1) ofsAppend<<diskHole[i]<<"\t";
			if(i == n+1)
			{
				cout<<setw(3)<<vert;
				if (startWrite == 1) ofsAppend<<setw(3)<<"|";
			}
		}

		cout<<endl;
		if (startWrite == 1) ofsAppend<<endl;

		cout<<mLeft;
		if (startWrite == 1) ofsAppend<<"|";

		for(int i=0; i < gW; i++)
        {
        	cout<<horz;
        	if (startWrite == 1) ofsAppend<<"_";
        	if(i == gW-1)
        	{
        		cout<<mRight;
        		if (startWrite == 1) ofsAppend<<"|";
			}
		}

		cout<<endl;
		if (startWrite == 1) ofsAppend<<endl;

	    for(int y=0; y<n+1; y++){
	    	cout<<vert;
	    	if (startWrite == 1) ofsAppend<<"|";
	    	for(int x=0, q=0; x<n + 2;x++){
				if(traverse[y] == diskHole[x])
				{
					if(diskHole[x] == 0)
					{
						cout<<" ";
						if (startWrite == 1) ofsAppend<<" ";
					}
					else
					{
						cout<<"X";
						if (startWrite == 1) ofsAppend << "X";
					}

				}
				else
				{
					cout<<" \t";
					if (startWrite == 1) ofsAppend << "\t";
				}

			}

			for(int x=0; x < gW; x++)
		        {
		        	if(x == gW-1)
		        	{
		        		cout<<setw(11)<<vert;
		        		if (startWrite == 1) ofsAppend<<setw(11)<<"|";
					}
				}

			cout<<endl;
			if (startWrite == 1) ofsAppend<<endl;
		}

		cout<<bLeft;
		if (startWrite == 1) ofsAppend<<"|";

		for(int i=0; i < gW; i++)
        {
        	cout<<horz;
        	if (startWrite == 1) ofsAppend<<"_";
        	if(i == gW-1)
        	{
        		cout<<bRight;
        		if (startWrite == 1) ofsAppend<<"|";
			}
		}

		cout<<endl<<endl;
		if (startWrite == 1) ofsAppend <<endl<<endl;


		cout<<"Table\n";
		if (startWrite == 1) ofsAppend << "Table\n";

		int nD = 9;
		cout<<uLeft;
		if (startWrite == 1) ofsAppend <<" ";
		for(int x=0; x<(nD*6) +1; x++){
			if (x == 23)
				cout<< dhorz;
			else
				cout<<horz;
			if (startWrite == 1) ofsAppend << "_";
		}
		cout<<uRight;
		cout<<endl;
		if (startWrite == 1) ofsAppend << "\n";
		cout<<vert<<" Next Track Accesed\t"<<vert<<" Next Track Traversed\t\t"<<vert<<"\n";
		if (startWrite == 1) ofsAppend << "| Next Track Accesed\t|\tNext Track Traversed\t|\n";
		for(int x=0; x<(nD*6)+3; x++){
			if(x==0 || x == ((nD*6) /2 ) - 3 || x == (nD*6) +2){
				if (x == 0)
				{
					cout<<mLeft;
					if (startWrite == 1) ofsAppend<<"|";
				}
				else if (x == ((nD*6) /2 ) - 3)
				{
					cout<<mhorz;
					if (startWrite == 1) ofsAppend<<"_";
				}

				else if (x == (nD*6) +2)
				{
					cout << mRight;
				    if (startWrite == 1) ofsAppend << "|";
				}

			}
			else{
				cout<<horz;
				if (startWrite == 1) ofsAppend << "_";
			}
		}
		cout<<endl;
		if (startWrite == 1) ofsAppend << "\n";

		for(int y = 0; y <n; y++){
			if(y != 0){
				total += abs(DStable[y] - DStable[y-1]);
				avg = total / ((n-1)*1.00);
			}
		}

		for(int y = 0; y <n; y++){
			cout<< vert<<" "<<DStable[y]<<"\t\t\t"<<vert;
			if (startWrite == 1) ofsAppend << "| "<< DStable[y]<< "\t\t\t| ";
			if(y != 0){
				cout<<" "<<abs(DStable[y] - DStable[y-1])<<" "<<"\t\t\t\t"<<vert;
				if (startWrite == 1) ofsAppend << abs(DStable[y] - DStable[y-1])<<" "<<"\t\t\t\t|";
			}
			else{
				cout<<" "<<"\t\t\t\t"<<vert;
				if (startWrite == 1) ofsAppend << " "<< "\t\t\t\t|";
			}
			cout<<endl;
			if (startWrite == 1) ofsAppend << "\n";
			for(int x=0; x<(nD*6)+3; x++){
				if(x==0 || x == ((nD*6) /2 ) - 3 || x == (nD*6) +2){
					if (x == 0)
						cout<<mLeft;
					else if (x == ((nD*6) /2 ) - 3)
						cout<<mhorz;
					else if (x == (nD*6) +2)
						cout << mRight;
					if (startWrite == 1) ofsAppend << "|";
				}
				else{
					cout<<horz;
					if (startWrite == 1) ofsAppend << "_";
				}

			}
			cout<<endl;
			if (startWrite == 1) ofsAppend << "\n";
		}

		cout<< vert<<" Total"<<"\t\t\t"<<vert;
		if (startWrite == 1) ofsAppend << "| Total\t\t\t|";

		cout<<" "<<total<<" Cylinders"<<"\t\t\t"<<vert;
		if (startWrite == 1) ofsAppend<<" "<<total<< " Cylinders\t\t\t|";

		cout<<endl;
		if (startWrite == 1) ofsAppend << "\n";
		for(int x=0; x<(nD*6)+3; x++){
			if(x==0 || x == ((nD*6) /2 ) - 3 || x == (nD*6) +2){
				if (x == 0)
					cout<<mLeft;
				else if (x == ((nD*6) /2 ) - 3)
					cout<<mhorz;
				else if (x == (nD*6) +2)
					cout << mRight;
				if (startWrite == 1) ofsAppend << "|";
			}
			else{
				cout<<horz;
				if (startWrite == 1) ofsAppend << "_";
			}

		}
		cout<<endl;

		if (startWrite == 1) ofsAppend << "\n";
		cout<< vert<<setprecision(2)<<fixed<<" Average\t"<<"\t"<<vert;
		if (startWrite == 1) ofsAppend << "|"<<" Average\t\t| ";

		cout<<" "<<avg<<"\t\t\t\t"<<vert;
		if (startWrite == 1) ofsAppend << setprecision(2)<< fixed<<avg<< " \t\t\t|";

		cout<<endl;
		if (startWrite == 1) ofsAppend << "\n";
		for(int x=0; x<(nD*6)+3; x++){
			if(x==0 || x == ((nD*6) /2 ) - 3 || x == (nD*6) +2){
				if (x == 0)
					cout<<bLeft;
				else if (x == ((nD*6) /2 ) - 3)
					cout<<uhorz;
				else if (x == (nD*6) +2)
					cout << bRight;
				if (startWrite == 1) ofsAppend << "|";
			}
			else{
				cout<<horz;
				if (startWrite == 1) ofsAppend << "_";
			}

		}
		cout<<endl;
		if (startWrite == 1) ofsAppend<<endl;
	    test.close();
		ofsAppend.close();
	if (startWrite == 1) breakDoWhile = 1;
	
	if (breakDoWhile == 0) {
		cout << "\n\nDo you want to run again [y/n]: ";
		cin >> choice;
	} else if (breakDoWhile == 1) {
		system("CLS");
		cout << "Thank you for using my MP08 - CLOOK program" << endl << "ARAULLO, Eugenio Emmanuel A.";
	}
    if (choice == 'N' || choice == 'n') startWrite = 1;
	
	}while(breakDoWhile == 0);

	return 0;
}
