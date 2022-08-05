#include <iostream>
#include <deque>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
using namespace std;

struct Process {
  string id;
  int arrival, burst, rburst, priority, wait, turn, state, classification;
};

struct ProcessDetails {
  string id;
  int start, done;
};

deque<string> tc;
deque< deque<string> > t;

stringstream ss;
int process;
int foregrund;
int backgrund;
deque <Process> notyet;
deque <Process> foreground;
deque <Process> background;
deque <Process> done;
deque <Process> sorting1;
deque <ProcessDetails> pd;
deque <string> pl;
deque <string> output;

void reset();
void fin();
void fout();
void init();
void simulate();
void pdMaker();
void ganttPrinter();
void sort();
void tableMaker();
string spacing(string s, int sp, int c);
void tablePrinter();
///////
int main() {
  while(1) {
    reset();
    fin();
    init();
    simulate();
    pdMaker();
    fout();
    ganttPrinter();
    sort();
    tableMaker();
    tablePrinter();
    cout<<endl;

    string ans;
    while(2) {
      cout<<"Do you want to run again [y/n]: ";
      cin>>ans;
      if(ans == "Y" || ans == "y") {
        break;
      } else if(ans == "N" || ans == "n"){
        exit(0);
      }
    }
    cout<<endl<<endl<<endl<<endl;
  }

  return 0;
}
///////
void fin(){
  ifstream fin;
  fin.open("MP03 Checker.txt");
  int tmp;

  deque <int> arrival;
  deque <int> burst;
  deque <int> priority;
  deque <int> classificasi;

  fin>>process;
  for(int i = 0; i < process; i++) {
    fin>>tmp;
    arrival.push_back(tmp);
  }

  for(int i = 0; i < process; i++) {
    fin>>tmp;
    burst.push_back(tmp);
  }

  for(int i =0; i < process; i++) {
    fin>>tmp;
    priority.push_back(tmp);
  }

  for(int i = 0 ; i < process; i++) {
    fin>>tmp;
    classificasi.push_back(tmp);
  }

  fin>>foregrund;
  fin>>backgrund;

  for(int i = 0; i < process; i++) {
    Process tp;
    ss.clear();
    ss<<(i + 1);
    string tmp;
    ss >> tmp;
    tp.id = "P" + tmp;
    tp.arrival = arrival[i];
    tp.burst = burst[i];
    tp.rburst = burst[i];
    tp.priority = priority[i];
    tp.classification = classificasi[i];
    tp.wait = 0;
    tp.turn = 0;
    tp.state = 0;
    if(tp.arrival > 0) {
      notyet.push_back(tp);
    } else {
      if(tp.classification == 1) {
        foreground.push_back(tp);
      } else {
        background.push_back(tp);
      }
    }
    sorting1.push_back(tp);
  }
  fin.close();
}
///////
void reset() {
  done.clear();
  foreground.clear();
  background.clear();
  notyet.clear();
  output.clear();
  pd.clear();
  pl.clear();
  sorting1.clear();
  t.clear();
  tc.clear();
}
///////
void fout() {
  ofstream fout;

  fout.open("MP03 Checker.txt", std::ios_base::app);
  fout << "\xEF\xBB\xBF";
  string spacing = "\n\n\n";
  fout.write(spacing.data(), spacing.size());

  for(int i = 0; i < output.size(); i++) {
    fout.write(output[i].data(), output[i].size());
  }

  fout.close();
}
///////
void init() {
  string ou = "Programmed by: Eugenio Emmanuel A. Araullo \n";
  ou += "MP03 - MULTILEVEL QUEUE ALGORITHM \n\n";
  ou += "Enter No. of Processes: ";
  string tmpou;
  ss.clear();
  ss << process;
  ss >> tmpou;
  ou += tmpou + "\n";
  ou += "Arrival Time: \n";

  for(int j = 0; j < process; j++) {
    string tmpou2, tmpou3;
    tmpou2 += " " + sorting1[j].id + ": ";
    ss.clear();
    ss << sorting1[j].arrival;
    ss >> tmpou3;
    tmpou2 += tmpou3 + "\n";
    ou += tmpou2;
  }
  ou += "\nBurst Time: \n";

  for(int i = 0; i < process; i++) {
    string tmpou2, tmpou3;
    tmpou2 += " " + sorting1[i].id + ": ";
    ss.clear();
    ss << sorting1[i].burst;
    ss >> tmpou3;
    tmpou2 += tmpou3 + "\n";
    ou += tmpou2;
  }

  ou += "\nPriority Number: \n";
  for(int i = 0; i < process; i++) {
    string tmpou2, tmpou3;
    tmpou2 += " " + sorting1[i].id + ": ";
    ss.clear();
    ss << sorting1[i].priority;
    ss >> tmpou3;
    tmpou2 += tmpou3 + "\n";
    ou += tmpou2;
  }

  ou += "\nClassification(1-FP / 2-BP):\n";
  for(int i = 0; i < process; i++) {
    string tmpou2, tmpou3;
    tmpou2 += " " + sorting1[i].id + ": ";
    ss.clear();
    ss << sorting1[i].classification;
    ss >> tmpou3;
    tmpou2 += tmpou3 + "\n";
    ou += tmpou2;
  }

  ou += "\nAlgorithm Choices: \n";
  ou += " 1. FCFS\n";
  ou += " 2. SJF-P\n";
  ou += " 3. SJF-NP\n";
  ou += " 4. P-P\n";
  ou += " 5. P-NP\n";
  ou += " 6. RR\n";

  ou += "\nForeground Process: ";
  ss.clear();
  ss << foregrund;
  ss >> tmpou;
  ou += tmpou;
  ou += "\nBackground Process: ";
  ss.clear();
  ss << backgrund;
  ss >> tmpou;
  ou += tmpou;
  ou += "\n\n";
  cout<<ou;
  output.push_back(ou);
}
///////
void simulate() {
  int tick = 0;
  int idx = -1;
  int prosel = 0;
  bool idxbool;
  bool state = false;
  bool dprocs = false;

  while(notyet.size() != 0 || foreground.size() != 0 || background.size() != 0) {

    dprocs = false;
    while(dprocs == false) {
      if(notyet.size() != 0) {
        for(int i = 0; i < notyet.size(); i++) {
          if(notyet[i].arrival <= tick) {
            if(notyet[i].classification == 1) {
              foreground.push_back(notyet[i]);
              idx = -1;
              idxbool = true;
            } else {
              background.push_back(notyet[i]);
            }
            notyet.erase(notyet.begin() + i);
            dprocs = false;
            break;
          } else {
            dprocs = true;
          }
        }
      } else {
        dprocs = true;
      }
    }
    dprocs = false;

    if(idx == -1 && foreground.size() > 0) {
      idx = 0;
      int num = foreground[0].priority;
      for(int i = 0; i < foreground.size(); i++) {
        if(foreground[i].priority < num) {
          idx = i;
          num = foreground[i].priority;
        }
      }
      idxbool = true;
      state = true;
      prosel = 1;
    } else if(idx == -1 && background.size() > 0) {
      idx = 0;
      int num = background[0].rburst;

      for(int i = 0; i < background.size(); i++) {
        if(background[i].rburst < num) {
          idx = i;
          num = background[i].rburst;
        }
      }
      idxbool = true;
      state = false;
      prosel = 2;
    }

    if(idx != -1) {
      for(int i = 0; i < foreground.size(); i++) {
        if(prosel == 1 && idx == i) {
          foreground[i].state = 1;
        } else {
          foreground[i].state = 0;
        }
      }
      for(int i = 0; i < background.size(); i++) {
        if(prosel == 2 && idx == i) {
          background[i].state = 1;
        } else {
          background[i].state = 0;
        }
      }
    }

    if(pl.size() == 0) {
      if(idx == -1) {
        pl.push_back("");
      } else {
        if(prosel == 1) {
          pl.push_back(foreground[idx].id);
        } else {
          pl.push_back(background[idx].id);
        }
      }
    } else if(idxbool == true && state == false) {
      if(idx != - 1) {
        if(prosel == 1) {
          pl.push_back(foreground[idx].id);
        } else {
          pl.push_back(background[idx].id);
        }
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

        if(prosel == 1) {
          if(foreground[idx].id != val) {
            pl.push_back(foreground[idx].id);
          } else {
            pl.push_back("-");
          }
        } else if (prosel == 2) {
          if(background[idx].id != val) {
            pl.push_back(background[idx].id);
          } else {
            pl.push_back("-");
          }
        }
      } else {
        pl.push_back("");
      }
    } else {
      pl.push_back("-");
    }
    idxbool = false;

    for(int i = 0; i < foreground.size(); i++) {
      if(foreground[i].state == 0) {
        foreground[i].wait++;
      }
    }

    for(int i = 0; i < background.size(); i++) {
      if(background[i].state == 0) {
        background[i].wait++;
      }
    }

    if(idx != -1) {
      if(prosel == 1) {
        foreground[idx].rburst--;
      } else {
        background[idx].rburst--;
      }
    }

    if(prosel == 1) {
      if(idx != -1 && foreground[idx].rburst == 0) {
        foreground[idx].turn = tick + 1 - foreground[idx].arrival;
        done.push_back(foreground[idx]);
        foreground.erase(foreground.begin() + idx);
      }
      idx = -1;
      idxbool = true;
    } else if(prosel == 2) {
      if(idx != -1 && background[idx].rburst == 0) {
        background[idx].turn = tick + 1 - background[idx].arrival;
        done.push_back(background[idx]);
        background.erase(background.begin() + idx);
        idx = -1;
        idxbool = true;
      }
    }

    tick++;
  }
}
///////
void pdMaker() {
  string tmp = pl[0];
  int beg = 0;
  ProcessDetails pdt;
  for(int i = 1; i < pl.size(); i++) {
    if(pl[i] == "-") {

    } else {
      pdt.id = tmp;
      pdt.start = beg;
      pdt.done = i;
      pd.push_back(pdt);
      tmp = pl[i];
      beg = i;
    }
  }
  pdt.id = tmp;
  pdt.start = beg;
  pdt.done = pl.size();
  pd.push_back(pdt);
}
///////
void ganttPrinter() {
  std::ofstream outfile;
  outfile.open("MP03 Checker.txt", std::ios_base::app);
  deque <int> length;
  cout << "Gantt Chart" << endl;
  outfile << "Gantt Chart" << endl;

  for(int i = 0; i < pd.size(); i++) {
    int tmp = pd[i].done - pd[i].start;
    if(tmp % 2 != 0) {
      tmp--;
    }
    length.push_back(tmp);
  }

  cout << " " << char(218);
  outfile << " " << "+";
  for(int i = 0; i < length.size(); i++){
    int len = spacing(pd[i].id, length[i], 2).length();

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
    string tmp = spacing(pd[i].id, length[i], 2);
    cout << tmp << char(179);
    outfile << tmp << "|";
  }
  cout << endl;
  outfile << endl;
  cout << " " << char(192);
  outfile << " "<< "+";
  for(int i = 0; i < length.size(); i++){
    int len = spacing(pd[i].id, length[i], 2).length();

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
    int len = spacing(pd[i].id, length[i], 2).length();
    string tmp;
    ss.clear();
    ss << pd[i].done;
    ss >> tmp;
    int n = tmp.length()/2;
    for(int j = 0; j <len - n; j++){
      cout << " ";
      outfile << " ";
    }
    cout << pd[i].done;
    outfile << pd[i].done;
  }
  cout << endl << endl;
  outfile << endl << endl;
  outfile.close();
}
///////
void sort() {
  for(int i = 0; i < sorting1.size(); i++) {
    for(int j = 0; j < done.size(); j++) {
      if(sorting1[i].id == done[j].id) {
        sorting1[i].turn = done[j].turn;
        sorting1[i].wait = done[j].wait;
      }
    }
  }
}

string spacing(string s, int sp, int c) {
  int left;
  int right;
  string ss;

  left = (sp - s.length())/2;
  right = (sp - s.length())/2;

  if((left + right + s.length()) != sp) {
    if(sp % 2 == 0) {
      left++;
    } else{
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
///////
void tableMaker() {
  float tt = 0, tw = 0;
  float at = 0.0, aw = 0.0;
  for(int i = 0; i < done.size(); i++) {
    tt += done[i].turn;
    tw += done[i].wait;
  }
  at = tt / done.size();
  aw = tw / done.size();

  tc.push_back("PROCESS");
  tc.push_back("TURNAROUND TIME");
  tc.push_back("WAITING TIME");
  t.push_back(tc);
  tc.clear();

  for(int i = 0; i < sorting1.size(); i++) {
    tc.clear();
    tc.push_back(sorting1[i].id);
    string tmp;
    ss.clear();
    ss << sorting1[i].turn;
    ss >> tmp;
    tc.push_back(tmp);
    ss.clear();
    ss << sorting1[i].wait;
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
///////
void tablePrinter() {
  std::ofstream outfile;
  outfile.open("MP03 Checker.txt", std::ios_base::app);
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
        cout << spacing(t[i][j], sp[j], 0);
        outfile << spacing(t[i][j], sp[j], 0);
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
