#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include<windows.h>

using namespace std;

//functions initialized
void calcProcSeq();
void assignValToGantt(int &prevProc);
void plotGantt();
void plotTable();
void showMainScreen();
int getPrioProc(int currTime);
int getGanttSize(int &prevProc);
int cntDigit(int num);

void tborder(string b);
void tbrdr(char h, char l, char r);
void printof();
void sin(string s);
void prepOut(string s);

void replaceBorders();
void overwritechar (int i, char a, char b);

int numProc, minArriv, ganttSize;

int *arriv, *burstCPU, *copyBurstCPU, *wait, *prio, *proc, *outTime, *procSeqPerSec, *procGantt, *burstCPUGantt;

int totBurstCPU;

float aveWait, copyAveWait, aveTurnArnd, totTurnArnd, totWait;
ifstream fin;
ofstream fout;
stringstream ss;
vector<string> gOut;

//borders
char horz = 0xC4, vert = 0xB3;
char uLeft = 218, uRight = 191, dhorz = 194;
char bLeft = 192, bRight = 217, uhorz = 193;
char mLeft = 195,  mRight = 180, mhorz = 197;

int tw=56,tdiv1=16,tdiv2=40;

void printof(){
  //Flush for ofstream------------------------
  int i;
  fout.open("MP04 Checker.txt", ios_base::trunc);
  if (fout.is_open()){
    fout << "";
    fout.close();
  }//ofstream flush end-----------------
  fout.open("MP04 Checker.txt");
  //end of ofstream initialization--------------
  for(int i=0;i < gOut.size();i++){
    fout<<gOut[i]<<endl;
  }

  fout.close();
}

void overwritechar (char a, char b){
  //gOut.size() gives you the total size of the entire vector.
  for(int i=0; i < gOut.size() ; i++)//traverses through the gOut vector
  replace( gOut[i].begin(), gOut[i].end(), a, b );
}
//magic badi
void replaceBorders(){
  overwritechar(horz, '_' );
  overwritechar(uLeft, '_' );
  overwritechar(uRight, '_' );
  overwritechar(dhorz, '_' );
  overwritechar(vert, '|' );
  overwritechar(mhorz, '|' );
  overwritechar(mLeft, '|' );
  overwritechar(mRight, '|' );
  overwritechar(bLeft, '|' );
  overwritechar(bRight, '|' );
  overwritechar(uhorz, '|' );
}
//gets the target output, displays it and appends to the gOut[] for ofstream
void sin(string s){
  cout << s << endl;
  prepOut(s);
}

void prepOut(string s){
  gOut.push_back(s);
  ss.str("");
}

void tborder(string b){
  if(b == "top")
  tbrdr(dhorz,uLeft,uRight);
  else if (b == "mid")
  tbrdr(mhorz, mLeft, mRight);
  else if (b == "bot")
  tbrdr(uhorz, bLeft, bRight);
}
void tbrdr(char h, char l, char r){
  for (int i = 0; i < tw; i++) {
    if (i == tdiv1 || i == tdiv2){
      ss<< h;
    }
    else if (i == 0){
      ss<< l;
    }
    else if (i == tw-1){
      ss<< horz << r;
    }
    else
    ss<< horz;
  }
  sin(ss.str());
}

int main()
{
  char isCont;

  do{
    ganttSize = 1;
    totBurstCPU = 0;
    minArriv = 2147483647; //always initialize to default value
    showMainScreen();
    do{
      cout<<endl<<endl<<"Try again? [y/n]: ";
      cin>>isCont;
      isCont = tolower(isCont);
    }
    while(isCont != 'y' && isCont != 'n');
    gOut.clear();
    system("cls");
  }
  while(isCont == 'y');

  return 0;
}

void showMainScreen()
{

  fin.open("MP04 Checker.txt");
  cout<<"Programmed by: Eugenio Emmanuel A. Araullo"<<endl;
  cout<<"MP04 - SJF Preemptive"<<endl<<endl;
  fin>>numProc;
  cout <<"Enter no. of processes: ";
  ss << numProc;
  sin(ss.str());

  arriv =        (int*)malloc(sizeof(int)*numProc);
  burstCPU =     (int*)malloc(sizeof(int)*numProc);
  copyBurstCPU = (int*)malloc(sizeof(int)*numProc);
  proc =         (int*)malloc(sizeof(int)*numProc);
  wait =         (int*)malloc(sizeof(int)*numProc);
  prio =         (int*)malloc(sizeof(int)*numProc);
  outTime =      (int*)malloc(sizeof(int)*numProc);

  cout<<"Arrival Time:"<<endl;
  for(int i=0; i<numProc; i++)
  {
    wait[i] = 0;
    proc[i] = i;
    fin>>arriv[i];
    cout <<"P"<<i+1<<": "<< arriv[i] << endl;
    ss << arriv[i] << " ";
    if(minArriv > arriv[i])
    minArriv = arriv[i];
  }
  prepOut(ss.str());
  cout<<endl<<"Burst Time"<<endl;
  for(int i=0; i<numProc; i++)
  {
    fin>>burstCPU[i];
    cout <<"P"<<i+1<<": " << burstCPU[i] << endl;
    ss << burstCPU[i] << " ";
    totBurstCPU += burstCPU[i];
  }
  prepOut(ss.str());
  cout<<endl<<"Priority"<<endl;
  for(int i=0; i<numProc; i++)
  {
    fin>>prio[i];
    cout <<"P"<<i+1<<": " << prio[i] << endl;
    ss << prio[i] << " ";
    copyBurstCPU[i] = burstCPU[i];
  }
  ss << "\n\n\nProgrammed by: Eugenio Emmanuel A. Araullo";
  ss << "\nMP04 - SJF Preemptive\n";
  ss << "\nEnter number of processes: " << numProc;

  ss << "\nArrival Time:\n";
  for(int i=0; i<numProc; i++)
  {
    ss <<"P"<<i+1<<": "<< arriv[i] << endl;
  }

  ss<<endl<<"Burst Time:"<<endl;
  for(int i=0; i<numProc; i++)
  {
    ss <<"P"<<i+1<<": " << burstCPU[i] << endl;
  }

  ss<<endl<<"Priority Number:"<<endl;
  for(int i=0; i<numProc; i++)
  {
    ss <<"P"<<i+1<<": " << prio[i] << endl;
  }

  prepOut(ss.str());
  fin.close();
  procSeqPerSec = (int*)malloc(sizeof(int)*totBurstCPU);
  calcProcSeq();
  plotGantt();
  plotTable();
  //janky converter for ascii borders
  replaceBorders();
  printof();
}

void calcProcSeq()
{
  int prevProc, prioProc, time;
  for(time=minArriv; time < totBurstCPU + minArriv; time++)
  {
    prioProc = getPrioProc(time);
    procSeqPerSec[time-minArriv] = prioProc;
    burstCPU[prioProc]--;

    //calculate waiting time per process
    for(int j=0; j<numProc;j++)
    {
      if(burstCPU[j] != 0 && arriv[j] <= time && j != prioProc)
      wait[j]++;
    }
  }

  ganttSize = getGanttSize(prevProc);

  //allocate size of gantt chart
  procGantt = (int*)malloc(sizeof(int)*ganttSize);
  burstCPUGantt = (int*)malloc(sizeof(int)*ganttSize);

  assignValToGantt(prevProc);

  //calculate ave waiting and ave turnaround
  aveWait = 0;
  aveTurnArnd = 0;
  totTurnArnd = 0;
  totWait = 0;
  for(int i=0; i < numProc; i++)
  {
    aveWait += wait[i];
    aveTurnArnd += wait[i] + copyBurstCPU[i];
    totWait += wait[i];
    totTurnArnd += wait[i] + copyBurstCPU[i];
  }
  aveWait = aveWait/(float)numProc;
  aveTurnArnd = aveTurnArnd/(float)numProc;
}

void assignValToGantt(int &prevProc)
{
  int tempBurstCPU = 0, ctr = 0;
  prevProc = procSeqPerSec[0];

  for(int i=0; i<totBurstCPU; i++)
  {
    if(prevProc != procSeqPerSec[i])
    {
      procGantt[ctr] = prevProc;
      burstCPUGantt[ctr] = tempBurstCPU;
      ctr++;
      tempBurstCPU = 0;
    }
    tempBurstCPU++;
    prevProc = procSeqPerSec[i];
  }

  burstCPUGantt[ganttSize - 1] = tempBurstCPU;
  procGantt[ganttSize - 1] = prevProc;
}

void plotGantt()
{
  const int MAX_WIDTH = totBurstCPU;
  int scalingFactor, ctr = 0, tempi = 0, currTime;
  scalingFactor = MAX_WIDTH/totBurstCPU;
  int ganttlimit = scalingFactor * totBurstCPU + 2 + ganttSize;

  ss << endl << endl <<"Gantt Chart"<<endl;
  sin(ss.str());
  //top border
  for(int i=0; i < ganttlimit; i++){
    if(i == 0)
    ss <<uLeft<<horz;
    else if(i==burstCPUGantt[ctr] * scalingFactor + tempi + 1 && i != ganttlimit-1){
      ctr++;
      tempi=i;
      if(i < ganttlimit -2)//I don't know why but 2 fuckin works
      ss <<dhorz;//border between processes
    }
    else if (i == ganttlimit-1)
    ss << uRight;
    else if (i < ganttlimit -2)
    ss <<horz;
    // cout<<" ";
  }
  sin(ss.str());
  ctr = 0;
  tempi = 0;
  copyAveWait = aveWait;
  //process labels
  for(int i=0; i<scalingFactor * totBurstCPU; i++)
  {
    if(i==burstCPUGantt[ctr] * scalingFactor + tempi)
    {
      ctr++;
      tempi=i;
      ss <<vert;//border between processes
    }
    else if(i == (burstCPUGantt[ctr] * scalingFactor) / 2 + tempi)
    ss <<"P"<<procGantt[ctr]+1;
    else if (i == 0)
    ss << vert << " ";
    else if (i == scalingFactor * totBurstCPU - 1)
    ss << " " << vert ;
    else
    ss <<" ";
  }
  sin(ss.str());
  //end border
  ctr = 0;
  tempi = 0;
  for(int i=0; i < ganttlimit; i++){
    if(i == 0)
    ss << bLeft << horz;
    else if(i==burstCPUGantt[ctr] * scalingFactor + tempi + 1 && i != ganttlimit-1){
      ctr++;
      tempi=i;
      if(i < ganttlimit -2)//I don't know why but 2 fuckin works
      ss << uhorz;//border between processes
    }
    else if (i == ganttlimit-1)
    ss << bRight;
    else if (i < ganttlimit -2)
    ss << horz;
  }
  sin(ss.str());
  //plot time labels of gantt chart
  ctr = 0;
  tempi = 0;
  currTime = minArriv;
  ss << currTime;
  for(int i=0; i<scalingFactor * totBurstCPU; i++){
    if(i == burstCPUGantt[ctr] * scalingFactor + tempi)
    {
      tempi = i;
      currTime += burstCPUGantt[ctr];
      aveWait += currTime;
      ctr++;

      for(int i = 1; i <= cntDigit(currTime); i++)
      if(i == 1)
      ss <<" ";
      else
      i+=3;

      ss <<currTime;
    }
    else
    ss <<" ";
  }
  currTime += burstCPUGantt[ctr];
  ss << currTime;
  sin(ss.str());
}

void plotTable()
{
  ss<< endl << endl <<"Table";
  sin(ss.str());
  tborder("top");
  ss<< vert << " Process\t" << vert << " Turnaround Time\t" << vert << " Waiting Time\t" << vert;
  sin(ss.str());
  tborder("mid");

  for(int i=0; i<numProc; i++)
  {
    outTime[i] = wait[i] + copyBurstCPU[i];

    ss<< vert <<" P"<<i+1<<"\t\t" << vert << " " <<outTime[i]<<"\t\t\t" << vert << " " <<wait[i] <<"\t\t" << vert;
    sin(ss.str());
    tborder("mid");
  }

  ss << vert <<" Total\t\t"<< vert << " " <<totTurnArnd<<"\t\t\t" << vert << " " <<totWait << "\t\t" << vert;
  sin(ss.str());
  tborder("mid");
  ss << vert <<" Average\t" << vert << " " << aveTurnArnd << "\t\t\t" << vert << " " << copyAveWait << "\t\t" << vert ;
  sin(ss.str());
  tborder("bot");
}

int getPrioProc(int currTime)
{
  int min=2147483647, prioProc;
  for(int i=0; i<numProc; i++)
  {
    if(arriv[i]<=currTime && min>copyBurstCPU[i] && burstCPU[i] != 0)
    {
      min = copyBurstCPU[i];
      prioProc = i;
    }
  }

  return prioProc;
}

int getGanttSize(int &prevProc)
{
  prevProc = procSeqPerSec[0];
  for(int i=0; i<totBurstCPU; i++)
  {
    if(prevProc != procSeqPerSec[i])
    ganttSize++;
    prevProc = procSeqPerSec[i];
  }

  return ganttSize;
}

int cntDigit(int num)
{
  int cnt = 0;
  while(num != 0)
  {
    num = num / 10;
    cnt++;
  }
  return cnt;
}
