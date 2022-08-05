#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<list>
#include<string>

using namespace std;

int cylinderSize;
int headPointer;
int queue[20]={};
int queueSize =0;
int temp, ctr = 0; 
char line1 = 218; 
char line2 = 191; 
char line3 = 192; 
char line4 = 217; 
char line5 = 194; 
char line6 = 193; 
char line7 = 195; 
char line8 = 180; 
char line9 = 197; 
char line10 = 196; 
char line11 = 179; 
int proc[20]={};
int defaultproc[20]={};
int n = 0 ;
int i = 0;

void calculatedifference(int request[], int headPointer,
						int diff[][2] ,int n  )
{
	for(int i = 0; i < n; i++)
	{
		diff[i][0] = abs(headPointer - request[i]);
	}
}


int findMIN(int diff[][2], int n)
{
	int index = -1;
	int minimum = 1e9;

	for(int i = 0; i < n; i++)
	{
		if (!diff[i][1] && minimum > diff[i][0])
		{
			minimum = diff[i][0];
			index = i;
		}
	}
	
	return index;
}

void shortestSeekTimeFirst(int request[],
						int headPointer, int n)
{
	if (n == 0)
	{
		return;
	}

	int diff[n][2] = { { 0, 0 } };

	int seekcount = 0;

	int seeksequence[n + 1] = {0};
	
	for(int i = 0; i < n; i++)
	{
		seeksequence[i] = headPointer;
		calculatedifference(request, headPointer, diff, n);
		int index = findMIN(diff, n);
		diff[index][1] = 1;
		

		seekcount += diff[index][0];

		headPointer = request[index];
	}
	seeksequence[n] = headPointer;
	
	

	for(int i=0;i<queueSize+1;i++)
	{		
		for(int j=i+1;j<queueSize+1;j++)
		{
			if(proc[i]>proc[j])
			{
				temp  =proc[i];
				proc[i]=proc[j];
				proc[j]=temp;
			}
		}
	}
	cout<<endl<<"Output:"<<endl<<endl<<"Graph "<<endl<<endl;
	cout<<"0";
	for(int i=0;i<queueSize+1;i++)
	{	
		int space = ((proc[i]- proc[i-1])-2)/2;
		for(int j = 0; j < space; j++){
			cout<< " ";
		}
		cout<<proc[i];
		
	}
	cout<< " "<<cylinderSize;
	cout<<endl;
	cout<<line7;
	ctr = 0;
	for(int i=0;i<queueSize+1;i++)
	{	
		int space = ((proc[i]- proc[i-1])-2)/2;
		for(int j = 0; j < space; j++){
			cout<< line10;
			ctr++;
		}
		if(proc[i]<95){
		cout<<line6<<line10;
		ctr =ctr+2;
		}
		else{
			cout<<line10<<line6<<line10;
			ctr = ctr + 3;
		}
		
	}
	cout <<line10 <<line8;
	cout<< endl;
	
	int m =-1;
	int spaces=0;
	for(int i = 0; i <queueSize+1 ; ++i){
		cout<<line11;
		for(int j = 0; j <queueSize+1 ; ++j){
			if(seeksequence[i]==proc[j]){
				if(seeksequence[i]<99){
				spaces=((seeksequence[i]/2)-1)+j;
				}
				else{
					
				spaces=((seeksequence[i]/2))+j;
				m++;
					for(int k= 0; k< m; k++){
						spaces= spaces+1;
					}
				}		
			}
		}
		
		for(int j = 0; j <spaces ; ++j){
			cout<<" ";
		}
		cout<<"x";
		int row = ctr - spaces;
		for(int j = 0; j <row ; ++j){
			cout<<" ";
		}
		cout<<line11<<endl;
	}
	cout<< line3;
	for(int i = 0; i < ctr+1; i++){
		cout<< line10;
	}
	cout<<line4;
	cout<<endl;
	cout <<endl << "Table"<<endl <<endl;
	cout<<line1;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
	
	cout<<line5;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
	cout<<line2<< endl;
	cout << line11 << " Next Track Accessed " << line11 << " Next Track Traverse " << line11 <<endl;

	cout<<line7;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
		
	cout<<line9;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
	cout<<line8<<endl;
	//table fillings
	int totalDiff=0;
	
	for (int i = 0; i < queueSize+1; ++i)
	{
		
		int diff;
		int count=0, num, num2;
		cout<<line11;
		cout<<"\t" << "  "<<seeksequence[i];
		
		num =seeksequence[i];
		while(num != 0) { //for counting digits
	      num = num / 10;
	      count++;
	    }
		cout<<"\t"<< "      "<<line11;
		
		if(i==0){
			diff=0;
		}else{
			diff=seeksequence[i]-seeksequence[i-1];
		}
		
		num2=diff;
		totalDiff+=diff;
		cout<<"\t" << "\t"<<" "<<abs(diff) << "\t" << "    " << line11;
		cout<<endl;
		cout<<line7;
		for(int i =0; i<21;i++){
			cout<<line10;
		}
		
		cout<<line9;
		for(int i =0; i<21;i++){
			cout<<line10;
		}
		cout<<line8<<endl;
		
	}
	
	double avg = (double)seekcount/n;
	cout<<line11<<"\t"<<" "<<"Total"<<"\t"<<"      "<<line11<<"\t"<<"  "<<seekcount<<" cylinders"<<"\t"<<"    "<<line11<<endl;
	cout<<line7;
		for(int i =0; i<21;i++){
			cout<<line10;
		}
		
		cout<<line9;
		for(int i =0; i<21;i++){
			cout<<line10;
		}
		cout<<line8<<endl;
		
	cout<<line11 <<"\t" << "Average"<<"\t"<<"      "<<line11<<"\t\t"<<avg<<"\t"<<"    "<<line11<<endl;
	//total and average

	cout<<line3;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
	cout<<line6;
	for(int i =0; i<21;i++){
		cout<<line10;
	}
	cout<< line4<<endl;
}

void appendToFile(int request[],
						int headPointer, int n)
{
	if (n == 0)
	{
		return;
	}
	ifstream checker;
	ofstream ofsAppend;
	ofsAppend.open("MP07 Checker.txt", std::ios_base::app);
	// Create array of objects of class node
	int diff[n][2] = { { 0, 0 } };
	
	// Count total number of seek operation
	int seekcount = 0;
	
	// Stores sequence in which disk access is done
	int seeksequence[n + 1] = {0};
	
	for(int i = 0; i < n; i++)
	{
		seeksequence[i] = headPointer;
		calculatedifference(request, headPointer, diff, n);
		int index = findMIN(diff, n);
		diff[index][1] = 1;
		
		// Increase the total count
		seekcount += diff[index][0];
		
		// Accessed track is now new headPointer
		headPointer = request[index];
	}
	seeksequence[n] = headPointer;
	
	
	//sort by ascending
	for(int i=0;i<queueSize+1;i++)
	{		
		for(int j=i+1;j<queueSize+1;j++)
		{
			if(proc[i]>proc[j])
			{
				temp  =proc[i];
				proc[i]=proc[j];
				proc[j]=temp;
			}
		}
	}
	ofsAppend<<endl<<"Output:"<<endl<<endl<<"Graph "<<endl<<endl;
	ofsAppend<<"0";
	for(int i=0;i<queueSize+1;i++)
	{	
		int space = ((proc[i]- proc[i-1])-2)/2;
		for(int j = 0; j < space; j++){
			ofsAppend<< " ";
		}
		ofsAppend<<proc[i];
		
	}
	ofsAppend<< " "<<cylinderSize<<endl;
	ofsAppend <<"+";
	ctr = 0;
	for(int i=0;i<queueSize+1;i++)
	{	
		int space = ((proc[i]- proc[i-1])-2)/2;
		for(int j = 0; j < space; j++){
			ofsAppend << "-";
			ctr++;
		}
		if(proc[i]<95){
		ofsAppend<<"+"<<"-";
		ctr =ctr+2;
		}
		else{
			ofsAppend<<"-"<<"+"<<"-";
			ctr = ctr + 3;
		}
		
	}
	ofsAppend << "-" << "+"<<endl;
	
	
	int m =-1;
	int spaces=0;
	for(int i = 0; i <queueSize+1 ; ++i){
		ofsAppend<< "|";
		for(int j = 0; j <queueSize+1 ; ++j){
			if(seeksequence[i]==proc[j]){
				if(seeksequence[i]<99){
				spaces=((seeksequence[i]/2)-1)+j;
				}
				else{
					
				spaces=((seeksequence[i]/2))+j;
				m++;
					for(int k= 0; k< m; k++){
						spaces= spaces+1;
					}
				}		
			}
		}
		
		for(int j = 0; j <spaces ; ++j){
			ofsAppend<<" ";
		}
		ofsAppend<<"x";
		int row = ctr - spaces;
		for(int j = 0; j <row ; ++j){
			ofsAppend<<" ";
		}
		ofsAppend<<"|"<<endl;

	}
	ofsAppend<< "+";
	for(int i = 0; i < ctr+1; i++){
		ofsAppend<<  "-";
	}
	ofsAppend<< "+";
	ofsAppend<<endl;
	ofsAppend << endl<< "Table" << endl <<endl;
	
	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<<  "-";
	}
	
	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<<  "-";
	}
	ofsAppend<< "+"<<endl;
	ofsAppend << "|" << " Next Track Accessed " << "|" << " Next Track Traverse " << "|" <<endl;

	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<<  "-";
	}
	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<<  "-";
	}
	ofsAppend<< "+"<<endl;
	//table fillings
	int totalDiff=0;
	
	for (int i = 0; i < queueSize+1; ++i)
	{
		
		int diff;
		int count=0, num, num2;
		ofsAppend<<"|";
		ofsAppend<<"\t" << "  "<<seeksequence[i];
		
		num =seeksequence[i];
		while(num != 0) { //for counting digits
	      num = num / 10;
	      count++;
	    }
		ofsAppend<<"\t"<< "      "<<"|";
		
		if(i==0){
			diff=0;
		}else{
			diff=seeksequence[i]-seeksequence[i-1];
		}
		
		num2=diff;
		totalDiff+=diff;
		ofsAppend<<"\t" << "\t"<<" "<<abs(diff) << "\t" << "    " << "|";

		ofsAppend << endl << "+";
		for(int i =0; i<21;i++){
			ofsAppend<< "-";
		}
		
		ofsAppend<< "+";
		for(int i =0; i<21;i++){
			ofsAppend<< "-";
		}
		ofsAppend<< "+";
		ofsAppend<<endl;
		
	}
	
	double avg = (double)seekcount/n;
	ofsAppend<<"|"<<"\t"<<" "<<"Total"<<"\t"<<"      "<<"|"<<"\t"<<"  "<<seekcount<<" cylinders"<<"\t"<<"    "<<"|"<<endl;
	ofsAppend<< "+";
		for(int i =0; i<21;i++){
			ofsAppend<< "-";
		}
		ofsAppend<< "+";
		for(int i =0; i<21;i++){
			ofsAppend<< "-";
		}
		ofsAppend<< "+" <<endl;
		
	ofsAppend<<"|" <<"\t" << "Average"<<"\t"<<"      "<<"|"<<"\t\t"<<avg<<"\t"<<"    "<<"|"<<endl;
	//total and average
	
	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<< "-";
	}
	ofsAppend<< "+";
	for(int i =0; i<21;i++){
		ofsAppend<< "-";
	}
	ofsAppend<< "+"<<endl;
	checker.close();
	ofsAppend.close();
}


int main()
{
	char again;
	do{
	
	ifstream checker;
	
	cout << "Programmed by: Eugenio Emmanuel A. Araullo" << endl
		 << "MP07 - SSTF DISK SCHEDULING ALGORITHM" << endl << endl;

	checker.open("MP07 Checker.txt");
	cout<<"Inputs: "<<endl;
	checker>>cylinderSize;
	cout<<"Max Cylinder Size: "<<cylinderSize<<endl;	
	checker>>headPointer; 
	cout<<"headPointer Pointer Position: "<<headPointer<<endl; 
	
	cout<<"Queue: ";
	queueSize = 0;
	for (int i = 0; i < 10; ++i)
	{	
		checker>>proc[i];
		cout << proc[i] << " ";
		if( proc[i] ==-1){
			proc[i]=headPointer;
			break;
		}
		queueSize++;
	}
	cout<<endl;
	n = queueSize;
	memcpy(defaultproc, proc, 20 * sizeof(int));
	//*defaultproc = *proc;
	shortestSeekTimeFirst(proc, headPointer, n);
	checker.close();
	
		cout << "\n\nDo you want to run again [y/n]: ";
		cin >> again;
		cout << "\n";
		if(again == 'N'|| again == 'n' ){
			ofstream ofsAppend;
			ofsAppend.open("MP07 Checker.txt");
			ofsAppend << cylinderSize << endl;
			ofsAppend << headPointer << endl;
			for (int i = 0; i < n; ++i) {	
				ofsAppend << defaultproc[i] << " ";
			}
			ofsAppend << "-1" << endl;
			ofsAppend << endl << endl << "Programmed by: Eugenio Emmanuel A. Araullo" << endl
		   		  << "MP07 - SSTF DISK SCHEDULING ALGORITHM" << endl << endl;
			ofsAppend << "Inputs: "<<endl;
			ofsAppend << "Max Cylinder Size: " << cylinderSize << endl;	
			ofsAppend << "Head Pointer Position: " << headPointer << endl; 
			
			ofsAppend << "Queue: ";
			for (int i = 0; i < n; ++i) {	
				ofsAppend << defaultproc[i] << " ";
			}
			ofsAppend << "-1" << endl;
			appendToFile(defaultproc, headPointer, n);
			ofsAppend.close();
			
		}
	}while(again == 'Y' || again == 'y');
	return 0;
	
}



