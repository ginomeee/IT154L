#include<iostream>
#include<deque>
#include<sstream>
#include<fstream>
#include<iomanip>
#include <cmath>
using namespace std;

struct ProcessDetails{
	string id;
	int start;
	int finish;
};

struct Process{
	string id;
	int arrival;
	int burst;
	int rburst;
	int priority;
	int wait;
	int turn;
	int state;
};

deque < deque<string> > t;
deque <string> tc;

stringstream ss;
int process;
deque <Process> notyet;
deque <Process> here;
deque <Process> finish;
deque <Process> sorted;
deque <ProcessDetails> pd;
deque <string> pl;
deque <string> output;

void fin();
void init();
void simulate();
void pdMaker();
void ganttPrinter();
void sort();
void tableMaker();
string spacer(string s, int sp, int c);
void tablePrinter();

int main(){
	char choice;

    do{
    notyet.clear();
    here.clear();
    finish.clear();
    sorted.clear();
    pd.clear();
    tc.clear();
    t.clear();
    pl.clear();
    output.clear();
    system("CLS");
    fin();
    init();
    simulate();
    pdMaker();
    ganttPrinter();
    sort();
    tableMaker();
    tablePrinter();

    do{
        cout<<"\nDo you want to run again [y/n]: ";
        cin>>choice;
        cout<<endl;
        choice=tolower(choice);
        if(choice!='y'&&choice!='n') {
            cout<<"invalid choice"<<endl;
        }
    }while(choice!='y'&&choice!='n');
    }while(choice=='y');
    return 0;
}

void fin(){
    ifstream fin;
    fin.open("MP02 Checker.txt");
    int tmp;

    deque <int> arrival;
    deque <int> burst;
    deque <int> priority;

    fin>>process;
    for(int i=0; i<process; i++) {
        fin>>tmp;
        arrival.push_back(tmp);
    }

    for(int i=0; i<process; i++) {
        fin>>tmp;
        burst.push_back(tmp);
    }

    for(int i=0; i<process; i++) {
    	fin>>tmp;
    	priority.push_back(tmp);
	}

    for(int i=0; i<process; i++) {
    	Process tp;
    	ss.clear();
    	ss<<(i + 1);
    	string tmp;
    	ss>>tmp;
    	tp.id = "P" + tmp;
    	tp.arrival = arrival[i];
    	tp.burst = burst[i];
    	tp.rburst = burst[i];
    	tp.priority = priority[i];
    	tp.wait = 0;
    	tp.turn = 0;
    	tp.state = 0;
    	if(tp.arrival > 0) {
    		notyet.push_back(tp);
		} else {
			here.push_back(tp);
		}
    	sorted.push_back(tp);
	}
	fin.close();
}

void init(){
	std::ofstream outfile;
  	outfile.open("MP02 Checker.txt");
	string ou="Programmed by: Eugenio Emmanuel A. Araullo\n";
	ou+="MP02 - PRIORITY Preemptive \n\n";
	ou+="Enter No. of Processes: ";
	string tmpou;
	ss.clear();
	ss<<process;
	ss>>tmpou;
	ou+=tmpou + "\n";
	ou+="Arrival Time: \n";

	for(int j=0; j<process; j++) {
		string tmpou2, tmpou3;
		tmpou2+=" "+sorted[j].id+": ";
		ss.clear();
		ss<<sorted[j].arrival;
		ss>>tmpou3;
		tmpou2+=tmpou3+"\n";
		ou+=tmpou2;
	}
	ou+="\nBurst Time: \n";

	for(int i=0; i<process; i++) {
		string tmpou2, tmpou3;
		tmpou2+=" "+sorted[i].id+": ";
		ss.clear();
		ss<<sorted[i].burst;
		ss>>tmpou3;
		tmpou2+=tmpou3+"\n";
		ou+=tmpou2;
	}

	ou+="\nPriority Number: \n";
	for(int i=0; i<process; i++) {
		string tmpou2, tmpou3;
		tmpou2+=" "+sorted[i].id+": ";
		ss.clear();
		ss<<sorted[i].priority;
		ss>>tmpou3;
		tmpou2+=tmpou3+"\n";
		ou+=tmpou2;
	}
	
	// Write input to file
	ou+="\n";
	cout<<ou;
	outfile << process << endl; // Process
	for(int i=0; i<process; i++) {
		outfile << sorted[i].arrival << " ";
	}
	outfile << endl;
	for(int i=0; i<process; i++) {
		outfile << sorted[i].burst << " ";
	}
	outfile << endl;
	for(int i=0; i<process; i++) {
		outfile << sorted[i].priority << " ";
	}
	outfile<<endl<<endl;
	outfile<<ou; // Name output
	outfile.close();
	output.push_back(ou);
}

void simulate() {
	int tick = 0;
	int idx = -1;
	bool idxbool;
	bool state = true;

	while(notyet.size() != 0 || here.size() != 0) {

		for(int i = 0; i < notyet.size(); i++) {
			if(notyet[i].arrival <= tick) {
				here.push_back(notyet[i]);
				notyet.erase(notyet.begin()+i);
			}
		}

		if(idx == -1 && here.size() > 0) {
			idx = 0;
			int num = here[0].priority;
			for(int i = 0; i < here.size(); i++) {
				if(here[i].priority < num) {
					idx = i;
					num = here[i].priority;
				}
			}
			for(int i = 0; i < here.size(); i++) {
				if(idx != i) {
					here[i].state = 0;
				} else {
					here[i].state = 1;
				}
			}
			idxbool = true;
		}

		if(pl.size() == 0) {
			if(idx == -1) {
				pl.push_back("");
			} else {
				pl.push_back(here[idx].id);
			}
		} else if(idxbool == true && state == false) {
			if(idx != - 1) {
				pl.push_back(here[idx].id);
			} else {
				pl.push_back("");
			}
		} else if(idxbool == true && state == true) {
			if(idx != -1) {
				string val = pl[0];
				for(int i = 0; i < pl.size(); i++) {
					if(pl[i] != "-") {
						val = pl[i];
					}
				}
				if(here[idx].id != val) {
					pl.push_back(here[idx].id);
				} else {
					pl.push_back("-");
				}
			} else {
				pl.push_back("");
			}
		} else {
			pl.push_back("-");
		}
		idxbool = false;

		for(int i = 0; i < here.size(); i++) {
			if(here[i].state == 0) {
				here[i].wait++;
			}
		}

		if(idx != -1) {
			here[idx].rburst--;
		}

		if(idx != -1 && here[idx].rburst == 0) {
			here[idx].turn = tick + 1 - here[idx].arrival;
			finish.push_back(here[idx]);
			here.erase(here.begin() + idx);
		}
		idx = -1;
		idxbool = true;

		tick++;
	}
}

void pdMaker() {
	string tmp = pl[0];
	int beg = 0;
	ProcessDetails pdt;
	for(int i = 1; i < pl.size(); i++) {
		if(pl[i] == "-") {

		} else {
			pdt.id = tmp;
			pdt.start = beg;
			pdt.finish = i;
			pd.push_back(pdt);
			tmp = pl[i];
			beg = i;
		}
	}

	pdt.id = tmp;
	pdt.start = beg;
	pdt.finish = pl.size();
	pd.push_back(pdt);
}

void ganttPrinter(){
	std::ofstream outfile;
	outfile.open("MP02 Checker.txt", std::ios_base::app);
	deque <int> length;
	cout << "Gantt Chart" << endl;
	outfile << "Gantt Chart" << endl;

	for(int i = 0; i < pd.size(); i++) {
		int tmp = pd[i].finish - pd[i].start;
		if(tmp % 2 != 0) {
			tmp--;
		}
		length.push_back(tmp);
	}

	cout << " " << char(218);
	outfile << " " << "+";
	for(int i = 0; i < length.size(); i++){
		int len = spacer(pd[i].id, length[i], 2).length();

		for(int j = 0; j <len; j++){
			cout << char(196);
			outfile << "-";
		}
		if(i != length.size() -1){
			cout << char(194);
			outfile << "+";
		}
	}
	cout << char(191);
	outfile << "+";
	cout << endl;
	outfile << endl;
	for(int i = 0; i < length.size(); i++) {
		if(i == 0) {
			cout << " " << char(179);
			outfile << " |";
		}
		string tmp = spacer(pd[i].id, length[i], 2);
		cout << tmp << char(179);
		outfile << tmp << "|";
	}
	cout << endl;
	outfile << endl;
	cout << " " << char(192);
	outfile << " "<< "+";
	for(int i = 0; i < length.size(); i++){
		int len = spacer(pd[i].id, length[i], 2).length();

		for(int j = 0; j <len; j++){
			cout << char(196);
			outfile << "-";
		}
		if(i != length.size() -1){
			cout << char(193);
			outfile << "+";
		}
	}
	cout << char(217);
	outfile << "+";
	cout << endl;
	outfile << endl;

	cout << " " << pd[0].start;
	outfile << " " << pd[0].start;

	for(int i = 0; i < length.size(); i++){
		int len = spacer(pd[i].id, length[i], 2).length();
		string tmp;
		ss.clear();
		ss << pd[i].finish;
		ss >> tmp;
		int n = tmp.length()/2;
		for(int j = 0; j <len - n; j++){
			cout << " ";
			outfile << " ";
		}
		cout << pd[i].finish;
		outfile << pd[i].finish;
	}
	cout << endl << endl;
	outfile << endl << endl;
	outfile.close();
}

void sort(){
	for(int i = 0; i < sorted.size(); i++){
		for(int j = 0; j < finish.size(); j++){
			if(sorted[i].id == finish[j].id){
				sorted[i].turn = finish[j].turn;
				sorted[i].wait = finish[j].wait;
			}
		}
	}
}

string spacer(string s, int sp, int c){
	int left;
	int right;
	string ss;
	left = (sp - s.length())/2;
	right = (sp - s.length())/2;

	if((left + right + s.length()) != sp){
		if(sp % 2 == 0){
			left++;
		}
		else {
			right++;
		}
	}
	left = left + c;
	right = right + c;

	for(int i = 0; i < left; i++) {
		ss += " ";
	}
	ss += s;

	for(int i = 0; i < right; i++) {
		ss += " ";
	}
	return ss;
}

void tableMaker() {
	float tt = 0, tw = 0;
	float at = 0.0, aw = 0.0;
	for(int i = 0; i < finish.size(); i++) {
		tt += finish[i].turn;
		tw += finish[i].wait;
	}
	at = tt / finish.size();
	aw = tw / finish.size();

	tc.push_back("PROCESS");
	tc.push_back("TURNAROUND TIME");
	tc.push_back("WAITING TIME");
	t.push_back(tc);
	tc.clear();

	for(int i = 0; i < sorted.size(); i++) {
		tc.clear();
		tc.push_back(sorted[i].id);
		string tmp;
		ss.clear();
		ss << sorted[i].turn;
		ss >> tmp;
		tc.push_back(tmp);
		ss.clear();
		ss << sorted[i].wait;
		ss >> tmp;
		tc.push_back(tmp);
		t.push_back(tc);
	}

	tc.clear();
	tc.push_back("TOTAL");
	string tmp;
	ss.clear();
	ss << fixed << setprecision(0) << tt;
	ss >> tmp;
	tc.push_back(tmp);
	ss.clear();
	ss << fixed << setprecision(0) << tw;
	ss >> tmp;
	tc.push_back(tmp);
	t.push_back(tc);

	tc.clear();
	tc.push_back("AVERAGE");

	ss.clear();
	if(ceil(at) != floor(at)) {
		ss << fixed << setprecision(2) << at;
	} else {
		ss << fixed << setprecision(0) << at;
	}
	ss >> tmp;
	tc.push_back(tmp);

	ss.clear();
	if(ceil(aw) != floor(aw)) {
		ss << fixed << setprecision(2) << aw;
	} else {
		ss << fixed << setprecision(0) << aw;
	}
	ss >> tmp;
	tc.push_back(tmp);
	t.push_back(tc);
}

void tablePrinter(){
	std::ofstream outfile;
	outfile.open("MP02 Checker.txt", std::ios_base::app);
	int rc;
	int cc = 0;
	deque<int> sp;
	int topleft = 218;
	int topmid = 194;
	int topright = 191;
	int hor = 196;
	int ver = 179;
	int midleft = 195;
	int midmid = 197;
	int midright = 180;
	int botleft = 192;
	int botmid = 193;
	int botright = 217;

	rc = t.size();

	for(int i = 0; i < t.size(); i++) {
		if(cc < t[i].size()) {
			cc = t[i].size();
		}
	}

	for(int i = 0; i < cc; i++) {
		sp.push_back(0);

	}

	for(int i = 0; i < t.size(); i++){
		for(int j = 0; j < t[i].size(); j++){
			if(sp[j] < t[i][j].size()){
				sp[j] = t[i][j].size();
			}
		}
	}
	cout << "Table" << endl;
	outfile << "Table" << endl;
	cout << " " << char(topleft);
	outfile << " +";
	for(int i = 0; i < sp.size(); i++){
		for(int j = 0; j < sp[i]; j++){
			cout << char(hor);
			outfile << "-";
		}
		if(i != sp.size() -1){
			cout << char(topmid);
			outfile << "+";
		}
	}
	cout << char(topright) << endl;
	outfile << "+" << endl;

	for(int i = 0; i < t.size(); i++){
		cout << " " << char(ver);
		outfile << " |";
		for(int j = 0; j < sp.size(); j++){
			if(j > t[i].size() - 1) {
				for(int k = 0; k < sp[j]; k++){
					cout << " ";
					outfile << " ";
				}
			}
			else {
				cout << spacer(t[i][j], sp[j], 0);
				outfile << spacer(t[i][j], sp[j], 0);
			}
			cout << char(ver);
			outfile << "|";
		}
		cout << endl;
		outfile << endl;
		if(i != t.size() - 1) {
			cout << " " << char(midleft);
			outfile << " +";
			for(int j = 0; j < sp.size(); j++){
				for(int k = 0; k < sp[j]; k++){
					cout << char(hor);
					outfile << "-";
				}
				if(j != sp.size() -1){
					cout << char(midmid);
					outfile << "+";
				}
			}
			cout << char(midright) << endl;
			outfile << "+" << endl;
		}
	}

	cout << " " << char(botleft);
	outfile << " +";
	for(int i = 0; i < sp.size(); i++){
		for(int j = 0; j < sp[i]; j++){
			cout << char(hor);
			outfile << "-";
		}
		if(i != sp.size() -1){
			cout << char(botmid);
			outfile << "+";
		}
	}
	cout << char(botright) << endl;
	outfile << "+" << endl;
	outfile.close();
}
