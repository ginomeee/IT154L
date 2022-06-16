#include <iostream>
#include <fstream>
using namespace std;
struct studentdb{
  double number;
  string fname;
  string lname;
  double quiz[2];
  double midex;
  double finex;
  double fg;
  char grade;
} student;
void RECSAVE();
void final();
void READREC(string filename);
int main(){
  string filename;
  int i;
  cout << "Enter student number: ";
  cin >> student.number;
  cout << "Enter first name: ";
  cin >> student.fname;
  cout << "Enter last name:";
  cin >> student.lname;
  cout << "Enter 2 quizzes" << endl;
  for (i=0;i<2;i++){
    cout << "Quiz[" << i << "]:";
    cin >> student.quiz[i];
  }
  cout << "Enter midterm: ";
  cin >> student.midex;
  cout << "Enter finals: ";
  cin >> student.finex;
  RECSAVE();
  cout << endl << endl << "FULL DATABASE:";
  final();
}
void RECSAVE(){
  ofstream fout;
  string filename;
  filename=student.fname + ".txt";
  fout.open(filename.c_str());
  if (fout.fail()) exit(0);
  student.fg = (student.midex*.25) + (student.finex*.5) + ((((student.quiz[0]+student.quiz[1])/20)*100)*.25);
  if (student.fg >= 90) student.grade='A';
  else if (student.fg>=80) student.grade='B';
  else if (student.fg>=70) student.grade='C';
  else if (student.fg>=60) student.grade='D';
  else if (student.fg<60) student.grade='F';
  cout << student.number << "\t" << student.fname << " " << student.lname << "\t" << student.quiz[0] << "\t" << student.quiz[1] << "\t" << student.midex << "\t" << student.finex << "\t" << student.fg << "\t" << student.grade << endl;
  fout << student.number << "\t" << student.fname << " " << student.lname << "\t" << student.quiz[0] << "\t" << student.quiz[1] << "\t" << student.midex << "\t" << student.finex << "\t" << student.fg << "\t" << student.grade << endl;
  fout.close();

  ofstream all;
  all.open("studentrec.txt",ios::app);
  if (all.fail()) exit(0);
  all << student.number << "\t" << student.fname << " " << student.lname << "\t" << student.quiz[0] << "\t" << student.quiz[1] << "\t" << student.midex << "\t" << student.finex << "\t" << student.fg << "\t" << student.grade << endl;
  all.close();

}

void READREC(string filename){
  ifstream fin;
  filename += ".txt";
  fin.open(filename.c_str());
  if (fin.fail()) exit(0);
  fin >> student.number >> student.fname >> student.lname >> student.quiz[0] >> student.quiz[1] >> student.midex >> student.finex >> student.fg >> student.grade;
  fin.close();
}

void final(){
  ifstream fin;
  string data;
  fin.open("studentrec.txt");
  while(!fin.eof()){
    fin >> student.number >> student.fname >> student.lname >> student.quiz[0] >> student.quiz[1] >> student.midex >> student.finex >> student.fg >> student.grade;
    if (!fin.good()) break;
    cout << student.number << "\t" << student.fname << " " << student.lname << "\t" << student.quiz[0] << "\t" << student.quiz[1] << "\t" << student.midex << "\t" << student.finex << "\t" << student.fg << "\t" << student.grade << endl;
  }
  fin.close();
}
