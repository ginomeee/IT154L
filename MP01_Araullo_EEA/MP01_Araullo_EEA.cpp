#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main(){
  // Input =======================================================
  system("cls");
  int numproc;
  cout << "Enter Number of Processes: ";
  cin >> numproc;
  int *arrival = new int[numproc];
  int *burst = new int[numproc];
  cout << endl << "Arrival Time" << endl;
  for (int i=0;i<numproc;i++){
    cout << "Enter Process [" << i << "] Arrival Time: ";
    cin >> arrival[i];
  }
  cout << endl;
  for (int i=0;i<numproc;i++){
    cout << "Enter Process [" << i << "] Burst Time: ";
    cin >> burst[i];
  }

  // Processing =======================================================
  for(int x=0;x<numproc;x++){
    if (arrival[0] == 1){

    }
    for (int i=0;i<burst[x];i++){
      cout<<"-";
    }
    cout << " ";
  }
}
