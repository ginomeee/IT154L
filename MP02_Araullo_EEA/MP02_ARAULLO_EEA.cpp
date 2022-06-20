#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main(){
	char tryAgain;
	int numOfProcesses=0;
	int burstTimesSum=0;
	int millisecond=0;

		cout<<"Programmed by: Eugenio Emmanuel A.  Araullo"<<endl
			<<"MP02 - PRIORITY Preemptive"<<endl<<endl
			<<"Enter No. of Processes: ";
    // SCAN THE FILE
    ifstream scan;
    int scan = 0;
    int line[3];
    scan.open ("MP02 Checker.txt");
    for (int i=0; i<3; i++){
      getline (scan, line[i]);
    }
    numOfProcesses = line[0]
    cout << "Processes: " << numOfProcesses << endl;

    // New array per process
		int** process= new int*[numOfProcesses];
		for(int i = 0; i < numOfProcesses; i++){
      process[i] = new int[3];
    }
		/*
    Legend:
		[x][0]=arrival times
		[x][1]=burst times
		[x][2]=priority numbers
		[x][3]=current burst times
		*/

    // Explode string to tokens
    stringstream ssin(line[1]);
    while (ssin.good() && i < 4){
        ssin >> arr[i];
        ++i;
    }

		// Get arrival times
		cout<<"Arrival Time: "<<endl;
		for(int i=0, arrivalTime=0; i<numOfProcesses;i++){
      cout<<" P"<<i+1<<": ";
			scan>>arrivalTime;
      cout << arrivalTime << endl;
			process[i][0]=arrivalTime;
		}

		// Get burst times
		cout<<"Burst Time: "<<endl;
		for(int i=0, burstTime; i<numOfProcesses;i++){
			cout<<" P"<<i+1<<": ";
			scan>>burstTime;
      cout << burstTime << endl;
			process[i][1]=burstTime;
			process[i][3]=burstTime;
			burstTimesSum+=burstTime;
		}
		//cout<<"DEBUG 1============================"<<endl;
		//for(int i=0;i<burstTimesSum;i++){
		//	cout<<"laman: "<<ganttSequence[i]<<", ";
		//	cout<<"index: "<<i<<endl;
		//}

		///get priority numbers
		cout<<"Priority Number: "<<endl;
		for(int i=0, arrivalTime=0; i<numOfProcesses;i++){
			cout << " P"<<i+1<<": ";
			scan >> arrivalTime;
      cout << arrivalTime << endl;
			process[i][2]=arrivalTime;
		}
		//////////////////////////////////////////////////////////////

		double ganttUnits=10.00/(double)burstTimesSum;

		////get smallest arrival number
		int smallestArrivalNumber=101, smallestArrivalNumberIndex=0;
		for(int i=0; i<numOfProcesses;i++){
			if(process[i][0]<smallestArrivalNumber){
				smallestArrivalNumber=process[i][0];
				millisecond=smallestArrivalNumber;
				smallestArrivalNumberIndex=i;
			}
		}
		//debug
		//cout<<"SMALLEST ARRIVAL: "<<smallestArrivalNumber<<endl;
		//cout<<"ms: "<<millisecond<<endl;
		int ganttSequence[burstTimesSum+smallestArrivalNumber];
		///form gantt sequence
		for(int i=0;i<smallestArrivalNumber;i++){
			ganttSequence[i]=9999;
		}
		int lowestPriority=101;
		ganttSequence[smallestArrivalNumber]=smallestArrivalNumberIndex;
		//cout<<"DEBUG 2============================"<<endl;
		//for(int i=0;i<burstTimesSum;i++){
		//	cout<<"laman"<<ganttSequence[i]<<", ";
		//	cout<<"index: "<<i<<endl;
		//}
		for(int i=smallestArrivalNumber;i<burstTimesSum+smallestArrivalNumber;i++){
			for(int z=0;z<numOfProcesses;z++){
				if(i==burstTimesSum+smallestArrivalNumber){
					if(process[z][2]<lowestPriority //lowest priority
					&& millisecond>=process[z][0] //has arrived
					){
						ganttSequence[i]=z;
						lowestPriority=process[z][2];
					}
				}
				if(
					process[z][2]<lowestPriority //lowest priority
					&& millisecond>=process[z][0] //has arrived
					&& process[z][1]!=0 //has burst time remaining
				){
					ganttSequence[i]=z;
					lowestPriority=process[z][2];

				}
			}
			process[ganttSequence[i]][1]--;
			lowestPriority=101;
			millisecond++;
		}

		//debug
		//
		//for(int i=0;i<=burstTimesSum+smallestArrivalNumber;i++){
		//	cout<<"value: "<<ganttSequence[i]+1<<", ";
		//	cout<<"index: "<<i<<endl;
		//}

		//count number of entries in gantt chart
		int numOfEntries=-1;
		for(int i=smallestArrivalNumber;i<=burstTimesSum+smallestArrivalNumber;i++){
			if(ganttSequence[i]!=ganttSequence[i-1])
				numOfEntries++;
		}
		if(smallestArrivalNumber==0){
			numOfEntries++;
		}

		//form organized gantt chart

		int ganttBursts[numOfEntries];
		int organizedGantt[numOfEntries-1];

		ganttBursts[numOfEntries]=burstTimesSum;
		for(int i=0;i<numOfEntries;){
			for(int z=smallestArrivalNumber; z<burstTimesSum+smallestArrivalNumber; z++){
			//	cout<<"crr: "<<ganttSequence[z]+1<<", index: "<<z
			//		<<"; pre: "<<ganttSequence[z-1]+1<<endl;
				if(z==0){
				//	if(smallestArrivalNumber==0){

				//	}
				//	else{
						organizedGantt[i]=ganttSequence[z];
						ganttBursts[i]=z;
						i++;
				//	}
				}
				else if(ganttSequence[z]!=ganttSequence[z-1]){
					//cout<<"passed==="<<endl;
					organizedGantt[i]=ganttSequence[z];
					//cout<<"organt "<<i+1<<": "<<organizedGantt[i]<<endl;
					//cout<<"index"<<z<<endl;
					ganttBursts[i]=z;
					i++;
				}
			}
		}
		ganttBursts[numOfEntries]=burstTimesSum+smallestArrivalNumber;

		//cout<<"numents: "<<numOfEntries<<endl;
		//debug
		//for(int i=0;i<=numOfEntries;i++){
		//	cout<<"value gantt: "<<organizedGantt[i]+1<<", ";
		//	cout<<"indeex: "<<i<<endl;
		//}cout<<"++++++++++++"<<endl;
		//for(int i=0;i<=numOfEntries+1;i++){
		//	cout<<"value burst: "<<ganttBursts[i]<<", ";
		//	cout<<"indeex: "<<i<<endl;
		//}
		cout<<endl<<"Gantt Chart"<<endl;

		//draw upper line
		cout<<" --";
		for(int i=0; i<numOfEntries;i++){
			for(int z=0; z<(ganttBursts[i+1]-ganttBursts[i])*ganttUnits;z++){
				cout<<"---";
			}
			if(i==numOfEntries-1)
				cout<<" ";
			else
			cout<<" --";
		}

		//draw middle line
		bool moveBack=false;
		cout<<endl<<"|";
		for(int i=0; i<numOfEntries;i++){
			if((organizedGantt[i]+1)%10!=organizedGantt[i]+1){
				moveBack=true;
				cout<<"P"<<organizedGantt[i]+1;
			}
			else
				cout<<"P"<<organizedGantt[i]+1;
			for(int z=0; z<(ganttBursts[i+1]-ganttBursts[i])*ganttUnits;z++){
				if(moveBack){
					cout<<"  ";
					moveBack=false;
				}
				else
					cout<<"   ";
			}cout<<"|";
			moveBack=false;
		}

		//draw bottom line
		cout<<endl<<" --";
		for(int i=0; i<numOfEntries;i++){
			for(int z=0; z<(ganttBursts[i+1]-ganttBursts[i])*ganttUnits;z++){
				cout<<"---";
			}
			if(i==numOfEntries-1)
				cout<<" ";
			else
				cout<<" --";
		}
		//draw 2nd bottom line
		cout<<endl<<"|  ";
		for(int i=0; i<numOfEntries;i++){
			for(int z=0; z<(ganttBursts[i+1]-ganttBursts[i])*ganttUnits;z++){
				cout<<"   ";
			}
			if(i==numOfEntries-1)
				cout<<"|";
			else
			cout<<"|  ";
		}
		//draw labels

		cout<<endl<<ganttBursts[0]<<"  ";
		for(int i=0; i<numOfEntries;i++){
			for(int z=0; z<(ganttBursts[i+1]-ganttBursts[i])*ganttUnits;z++){
				cout<<"   ";
			}
			//if(i==numOfEntries-1){
			//	cout<<burstTimesSum+smallestArrivalNumber;
			//}
			//else{
				if(ganttBursts[i+1]%10==ganttBursts[i+1])
					cout<<ganttBursts[i+1]<<"  ";
				else if(ganttBursts[i+1]%100==ganttBursts[i+1])
					cout<<ganttBursts[i+1]<<" ";
				else
					cout<<ganttBursts[i+1];
			//}
		}

		// TABLE
		int turnAround=0, waitingTime=0, turnAroundTotal=0, waitingTotal=0;
		cout<<endl<<endl<<"Table"<<endl
			<<"=========================================================="<<endl
			<<"Process		Turnaround Time		Waiting time"<<endl
			<<"=========================================================="<<endl;

		for(int i=0; i<=numOfProcesses;i++){
			for(int z=burstTimesSum+smallestArrivalNumber-1; z>0;z--){
				//cout<<"z: "<<z<<", gantt: "<<ganttSequence[z]<<endl;
				if(i==ganttSequence[z]){
					turnAround=(z+1)-process[i][0];
					int occurences=0;
					for(int y=0; y<burstTimesSum+smallestArrivalNumber; y++){
						if(i==ganttSequence[y]){
							occurences++;
						}
					}
					waitingTime=turnAround-occurences;
					turnAroundTotal+=turnAround;
					waitingTotal+=waitingTime;
					cout<<left<<"P"<<setw(15)<<i+1<<setw(24)<<turnAround<<waitingTime<<endl;
					z=0;
				}
			}
		}
		float turnAroundAverage=(float)turnAroundTotal/(float)numOfProcesses;
		float waitingAverage=(float)waitingTotal/(float)numOfProcesses;
		printf("%-16s", "Total");printf("%-24i", turnAroundTotal);printf("%-24i", waitingTotal);
		cout<<endl;
		printf("%-16s", "Average");printf("%-24.2f", turnAroundAverage);printf("%-24.2f", waitingAverage);
		cout<<endl<<endl<<"Do you want to run again [y/n]: ";
		cin>>tryAgain;
		tryAgain = tolower(tryAgain);
		system("cls");
		if(tryAgain != 'n'){
			main();
		}
}
