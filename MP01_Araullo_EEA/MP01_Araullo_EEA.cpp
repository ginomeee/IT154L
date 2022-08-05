#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/////////////////Structure
class process_set{
	public:
		string index;
		int arrive;
		int burst;
		int start;
		int end;
		int waiting;
		int turnA;
};

class process{
	public:
		string index;
		int arrive;
		int burst;
};
int *arrival_time;
int *burst_time;
int process_setess;



//////////////////////////////FUNCTION
void FirstCFS(int arrival_time[],int  burst_time[], int process_setess,char choice);
void Gantt_Total_table(process_set process_setessing[],int process_setess);
void Total_table(process_set process_setessing[],int process_setess);
void write_file(process_set process_setessing[],int process_setess);


int main (){
	//Scanning the File
	char choice='Y';
	do {

	cout<< "Programmed by: ARAULLO, Eugenio Emmanuel A."<<endl;
	cout<< "MP01 - FCFS"<<endl<<endl;

	////////SCANNING FILE
	ifstream scan;
	scan.open ("MP01 Checker.txt");
			scan   >>   process_setess; 
	arrival_time = new int[process_setess];
	burst_time = new int[process_setess];

	for(int i = 0; i < process_setess; i++){
				scan >> arrival_time[i];
		}
	for(int i = 0; i < process_setess; i++){
				scan >> burst_time[i];
		}

	//Arrival
	cout<<"Enter No. of Process: "<<process_setess<<endl;
	cout<<endl;
	cout<<"Arrival Time:"<<endl;
	for(int i = 0; i<sizeof(*arrival_time);i++){
		cout<<"P"<<i+1<<":"<<arrival_time[i]<<endl;
	}

	//Burst
	cout<<endl;
	cout<<"Burst Time:"<<endl;
	for(int i = 0; i<sizeof(*burst_time);i++){
		cout<<"P"<<i+1<<":"<<burst_time[i]<<endl;
	}

	cout<<endl<<endl;
	FirstCFS(arrival_time, burst_time, process_setess,choice);

	cout<<endl<<endl;


	//////LOOP REPEAT
	cout<< "Do you want to try Again? (Y/N) ";
	cin>>choice;
	choice = toupper(choice);
	if(choice == 'N'){
		FirstCFS(arrival_time, burst_time, process_setess,choice);
		return 0;
		}
	if(choice == 'Y'){
		continue;
	}

	}while(choice== 'Y');
}

/////////// FCFS METHOD
void FirstCFS(int arrival_time[],int burst_time[],int process_setess, char choice){
	process_set p;
	process pd;
	process_set process_setessing[process_setess];
	process process_setDet[process_setess];
	int loop = process_setess;
	int i=0;
	int num;
	int num2;
	int num_set = 0;
	process numPD;

	for(i=0; i<process_setess; i++){

		stringstream ss;
		ss << i+1;
		string s;
		ss>>s;
		pd.index = s;
		pd.arrive = arrival_time[i];
		pd.burst = burst_time[i];
		process_setDet[i] = pd;
	}

	for(int i=0; i<process_setess;i++){
		for(int j=i+1;j<process_setess;j++){
			if(process_setDet[i].arrive > process_setDet[j].arrive){
				numPD = process_setDet[i];
				process_setDet[i] = process_setDet[j];
				process_setDet[j]= numPD;
			}
		}
	}
	int currentTime = process_setDet[0].arrive;
	for(int i=0; i<process_setess; i++){
		p.index = process_setDet[i].index;
		p.arrive = process_setDet[i].arrive;
		p.burst = process_setDet[i].burst;
		p.start = currentTime;
		p.end = currentTime + p.burst;
		currentTime = p.end;
		p.turnA = p.end - p.arrive;
		p.waiting =  p.start-p.arrive;
		process_setessing[i] = p;
	}
	if(choice == 'Y'){
		cout<<"Gantt Chart"<<endl;
		Gantt_Total_table(process_setessing, process_setess);
		cout<<endl<<endl;
		cout<<"Table"<<endl;
		Total_table(process_setessing, process_setess);
	}
	else{
		write_file(process_setessing, process_setess);
	}
}

//////////////////////// GANTT CHART
void Gantt_Total_table(process_set process_setessing[],int process_setess){
	int length = process_setessing[process_setess-1].end*3;



	int i, j;
    cout<<" ";
    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst; j++) cout<<"__";
        cout<<" ";
    }
    cout<<"\n|";


    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst - 1; j++) cout<<" ";
        cout<<"P"<<process_setessing[i].index;
        for(j=0; j<process_setessing[i].burst - 1; j++) cout<<" ";
        cout<<"|";
    }
    cout<<"\n ";

    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst; j++) cout<<"__";
        cout<<" ";
    }
    cout<<"\n";

    cout<<process_setessing[0].start;;
    for(i=0; i<process_setess; i++) {

        for(j=0; j<process_setessing[i].burst; j++) cout<<"  ";
        if(process_setessing[i].turnA > 9) cout<<"\b";
        cout<<process_setessing[i].end;

    }

    cout<<"\n";
}

///////////////////////////////// TOTAL TABLE CHART
void Total_table(process_set process_setessing[],int process_setess){
	double totalturnA=0;
	for(int i=0; i<process_setess;i++){
		totalturnA=totalturnA+process_setessing[i].turnA;
	}

	double totalwaiting=0;
	for(int i=0; i<process_setess; i++){
		totalwaiting=totalwaiting+process_setessing[i].waiting;
	}
	cout <<"__________________________________________\n";
 	cout <<"|     |                 |                 |\n";
	cout <<"|  P  | Turnaround Time | Waiting Time    |\n";
	cout <<"|_____|_________________|_________________|\n";

	for(int i = 0; i < process_setess; i++) {
		if(process_setessing[i].turnA > 9){
			cout <<"|     |                 |                 |\n";
			cout <<"|  "<< process_setessing[i].index << "  |        " << process_setessing[i].turnA << "       |       "<< process_setessing[i].waiting<< "         |\n";
			cout <<"|_____|_________________|_________________|\n";
		}
		else{
		cout <<"|     |                 |                 |\n";
		cout <<"|  "<< process_setessing[i].index << "  |        " << process_setessing[i].turnA << "        |       "<< process_setessing[i].waiting<< "         |\n";
		cout <<"|_____|_________________|_________________|\n";
		}



	}
	cout <<"|     |                 |                 |\n";
	cout <<fixed<<setprecision(0)<<"|TOTAL|      " << totalturnA<<"      \t|     " << totalwaiting << "      \t|\n";
    cout <<"|_____|_________________|_________________|\n";
    cout <<"|     |                 |                 |\n";
    cout <<fixed<<setprecision(2)<<"| AVE |       " << totalturnA/process_setess <<"      |      " << totalwaiting/process_setess << "       |\n";
    cout <<"|_____|_________________|_________________|\n";



}

// WRITE FILE TO CHECKER
void write_file(process_set process_setessing[],int process_setess){
	double totalturnA=0;
	for(int i=0; i<process_setess;i++){
		totalturnA=totalturnA+process_setessing[i].turnA;
	}

	double totalwaiting=0;
	for(int i=0; i<process_setess; i++){
		totalwaiting=totalwaiting+process_setessing[i].waiting;
	}
	//append
    ofstream ofs;
 	ofs.open("MP01 Checker.txt");
 	ofs << process_setess << endl;
 	for(int i = 0; i < process_setess; i++){
				ofs << arrival_time[i] << " ";
		}
	ofs << endl;
	for(int i = 0; i < process_setess; i++){
				ofs << burst_time[i] << " ";
	}
 	ofs << endl << endl;
 	ofs <<"Programmed by: ARAULLO, Eugenio Emmanuel A." << endl;
 	ofs <<"MP01 - FCFS" << endl;
 	ofs <<"Enter No. of Processes: " << process_setess << endl << endl;
 	ofs <<"Arrival Time:" << endl;
 	for(int i = 0; i < process_setess; i++){
 		ofs <<"P" << i+1 << ": " << arrival_time[i] << endl;
	}
 	ofs << endl << "Burst Time:" << endl;
 	for(int i = 0; i < process_setess; i++){
 		ofs <<"P" << i+1 << ": " << burst_time[i] << endl;
	}
	// START GANTT
	
	int length = process_setessing[process_setess-1].end*3;
	int i, j;
 	ofs<<endl<<endl;
 	ofs<<"Gantt Chart" << endl;
    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst; j++) ofs<<"__";
        ofs<<" ";
    }
    ofs<<"\n|";


    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst - 1; j++) ofs<<" ";
        ofs<<"P"<<process_setessing[i].index;
        for(j=0; j<process_setessing[i].burst - 1; j++) ofs<<" ";
        ofs<<"|";
    }
    ofs<<"\n ";

    for(i=0; i<process_setess; i++) {
        for(j=0; j<process_setessing[i].burst; j++) ofs<<"__";
        ofs<<" ";
    }
    ofs<<"\n";


    ofs<<"0";
    for(i=0; i<process_setess; i++) {

        for(j=0; j<process_setessing[i].burst; j++) ofs<<"  ";
        if(process_setessing[i].turnA > 9) ofs<<"\b";
        ofs<<process_setessing[i].end;
    }
	
	// END GANTT
	ofs << "\n\nTable\n";
	ofs <<"__________________________________________\n";
 	ofs <<"|     |                 |                 |\n";
	ofs <<"|PROC |Turnaround       |     Waiting     |\n";
	ofs <<"|_____|_________________|_________________|\n";

	for(int i = 0; i < process_setess; i++) {
		if(process_setessing[i].turnA > 9){
			ofs <<"|     |                 |                 |\n";
			ofs <<"|  "<< process_setessing[i].index << "  |        " << process_setessing[i].turnA << "       |       "<< process_setessing[i].waiting<< "         |\n";
			ofs <<"|_____|_________________|_________________|\n";
		}
		else{
		ofs <<"|     |                 |                 |\n";
		ofs <<"|  "<< process_setessing[i].index << "  |        " << process_setessing[i].turnA << "        |       "<< process_setessing[i].waiting<< "         |\n";
		ofs <<"|_____|_________________|_________________|\n";
		}



	}
	ofs <<"|     |                 |                 |\n";
	ofs <<fixed<<setprecision(0)<<"|TOTAL|        " << totalturnA <<"      \t|        " << totalwaiting << "       |\n";
    ofs <<"|_____|_________________|_________________|\n";
    ofs <<"|     |                 |                 |\n";
    ofs <<fixed<<setprecision(2)<<"| AVE |       " << totalturnA/process_setess <<"      |      " << totalwaiting/process_setess << "       |\n";
    ofs <<"|_____|_________________|_________________|\n";

}
