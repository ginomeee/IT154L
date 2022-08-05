#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
// Set Global Variables for easy access to functions
int rSize, frameSize, *referenceString, pageFaults, temp, rep, rem;
rewrite(){
  char choice;
  bool init, same, error;
  std::ofstream outfile;
  outfile.open("MP05 Checker.txt");
  outfile << rSize << endl;
  for(int ctr = 0; ctr < rSize; ctr++){
    outfile<<referenceString[ctr]<<" ";
  }
  outfile << endl << frameSize << endl;
  outfile<<"\nProgrammed by: ARAULLO, Eugenio Emmanuel A.\n" << "MP05 - LRU PAGE REPLACEMENT\n\n\n";
  outfile<<"Enter reference string size: "<<rSize<<endl;
  outfile<<"Enter reference string: ";
  for(int ctr = 0; ctr < rSize; ctr++){
    outfile<<referenceString[ctr]<<" ";
  }
  outfile<<endl;

  outfile<<"Frame Size: "<<frameSize<<endl;
  int val[frameSize][rSize];
  int out[frameSize][rSize];
  pageFaults = 0;

  for(int ctr = 0; ctr < frameSize; ctr++) {
    for(int ctr1 = 0; ctr1 < rSize; ctr1++)
    {
      val[ctr][ctr1] = -1;
    }
  }

  for(int ctr = 0; ctr < frameSize; ctr++) {
    for(int ctr1 = frameSize-1; ctr1 >= ctr; ctr1--) {
      val[ctr][ctr1] = referenceString[ctr];
    }
    pageFaults++;
  }

  for(int ctr = frameSize; ctr < rSize; ctr++) {
    for(int ctr5 = 0; ctr5 < frameSize; ctr5++) {
      val[ctr5][ctr] = val[ctr5][ctr - 1];
    }
    for(int ctr1 = 0; ctr1 < frameSize; ctr1++) {
      if(referenceString[ctr] == val[ctr1][ctr]) {
        init = true;
        break;
      } else  {
        init = false;
      }
    }
    if(init == true)
    {
      continue;
    }
    else
    {
      for(int ctr2 = 0; ctr2 < frameSize; ctr2++)
      {
        for(int ctr3 = ctr - 1; ctr3 >= 0; ctr3--)
        {
          if(val[ctr2][ctr] == referenceString[ctr3])
          {
            if(ctr2 == 0)
            {
              temp = ctr3;
              rep = temp;
              rem = ctr2;
              break;
            }
            else
            {
              temp = ctr3;
              if(temp < rep)
              {
                rep = temp;
                rem = ctr2;
                break;
              }
              else
              {
                break;
              }
            }
          }
          else
          {
            continue;
          }
        }
      }
      val[rem][ctr] = referenceString[ctr];
      pageFaults++;
    }
  }
  for(int ctr = 0; ctr < frameSize; ctr++)
  {
    for(int ctr1 = 0; ctr1 < rSize; ctr1++)
    {
      out[ctr][ctr1] = val[ctr][ctr1];
    }
  }
  for(int ctr = 1; ctr < rSize; ctr++)
  {
    same = false;
    for(int ctr1 = 0; ctr1 < frameSize; ctr1++)
    {
      if(val[ctr1][ctr] == val[ctr1][ctr - 1])
      {
        same = true;
      }
      else
      {
        same = false;
        break;
      }
    }
    if(same == true)
    {
      for(int ctr2 = 0; ctr2 < frameSize; ctr2++)
      {
        out[ctr2][ctr] = -1;
      }
    }
  }
  outfile<<"\n";
  outfile<<"Page Replacement Table \n\n";
  for(int ctr = 0; ctr < rSize; ctr++)
  {
    if(ctr == rSize - 1)
    outfile<<" "<<referenceString[ctr]<<" ";
    else
    {
      outfile<<" "<<referenceString[ctr]<<"    ";
    }
  }
  outfile<<"\n";
  for(int ctr = 0; ctr < rSize; ctr++)
  if(ctr == rSize - 1)
  outfile<<"___";
  else
  outfile<<"______";
  outfile<<"\n";
  for(int ctr = 0; ctr < frameSize; ctr++)
  {
    for(int ctr1 = 0; ctr1 < rSize; ctr1++)
    {
      if(ctr1 == rSize - 1)
      {
        if(out[ctr][ctr1] == -1)
        outfile<<"[ ]";
        else
        outfile<<"["<<out[ctr][ctr1]<<"]";
      }
      else
      {
        if(out[ctr][ctr1] == -1)
        outfile<<"[ ]   ";
        else
        outfile<<"["<<out[ctr][ctr1]<<"]   ";
      }
    }
    outfile<<"\n";
  }
  outfile<<"\nDisplay Page Fault: "<<pageFaults<<"\n";
}
int main() {
  bool again;

  do {
    char choice;
    bool init, same, error;
    again = false;
    cout<<"\nProgrammed by: ARAULLO, Eugenio Emmanuel A.\n"
    <<"MP05 - LRU PAGE REPLACEMENT\n\n\n";
    ifstream rfile;
    rfile.open("MP05 Checker.txt");

    rfile>>rSize;
    cout<<"Enter reference string size: "<<rSize<<endl;
    referenceString = new int[rSize];
    cout<<"Enter reference string: ";
    for(int ctr = 0; ctr < rSize; ctr++)
    {
      rfile>>referenceString[ctr];
      cout<<referenceString[ctr]<<" ";
    }
    cout<<endl;

    rfile>>frameSize;
    cout<<"Frame Size: "<<frameSize<<endl;
    int val[frameSize][rSize];
    int out[frameSize][rSize];
    pageFaults = 0;

    for(int ctr = 0; ctr < frameSize; ctr++){
      for(int ctr1 = 0; ctr1 < rSize; ctr1++) {
        val[ctr][ctr1] = -1;
      }
    }

    for(int ctr = 0; ctr < frameSize; ctr++){
      for(int ctr1 = frameSize-1; ctr1 >= ctr; ctr1--){
        val[ctr][ctr1] = referenceString[ctr];
      }
      pageFaults++;
    }

    for(int ctr = frameSize; ctr < rSize; ctr++) {
      for(int ctr5 = 0; ctr5 < frameSize; ctr5++) {
        val[ctr5][ctr] = val[ctr5][ctr - 1];
      }
      for(int ctr1 = 0; ctr1 < frameSize; ctr1++) {
        if(referenceString[ctr] == val[ctr1][ctr]) {
          init = true;
          break;
        } else {
          init = false;
        }
      }
      if(init == true) {
        continue;
      } else {
        for(int ctr2 = 0; ctr2 < frameSize; ctr2++) {
          for(int ctr3 = ctr - 1; ctr3 >= 0; ctr3--) {
            if(val[ctr2][ctr] == referenceString[ctr3]) {
              if(ctr2 == 0) {
                temp = ctr3;
                rep = temp;
                rem = ctr2;
                break;
              } else {
                temp = ctr3;
                if(temp < rep) {
                  rep = temp;
                  rem = ctr2;
                  break;
                } else {
                  break;
                }
              }
            } else {
              continue;
            }
          }
        }
        val[rem][ctr] = referenceString[ctr];
        pageFaults++;
      }
    }
    for(int ctr = 0; ctr < frameSize; ctr++) {
      for(int ctr1 = 0; ctr1 < rSize; ctr1++) {
        out[ctr][ctr1] = val[ctr][ctr1];
      }
    }
    for(int ctr = 1; ctr < rSize; ctr++)  {
      same = false;
      for(int ctr1 = 0; ctr1 < frameSize; ctr1++) {
        if(val[ctr1][ctr] == val[ctr1][ctr - 1]) {
          same = true;
        } else {
          same = false;
          break;
        }
      }
      if(same == true) {
        for(int ctr2 = 0; ctr2 < frameSize; ctr2++) {
          out[ctr2][ctr] = -1;
        }
      }
    }
    cout<<"\n";
    cout<<"Page Replacement Table \n\n";
    for(int ctr = 0; ctr < rSize; ctr++) {
      if(ctr == rSize - 1)
      cout<<" "<<referenceString[ctr]<<" ";
      else
      {
        cout<<" "<<referenceString[ctr]<<"    ";
      }
    }
    cout<<"\n";
    for(int ctr = 0; ctr < rSize; ctr++)
    if(ctr == rSize - 1)
    cout<<"___";
    else
    cout<<"______";
    cout<<"\n";
    for(int ctr = 0; ctr < frameSize; ctr++)
    {
      for(int ctr1 = 0; ctr1 < rSize; ctr1++)
      {
        if(ctr1 == rSize - 1)
        {
          if(out[ctr][ctr1] == -1)
          cout<<"[ ]";
          else
          cout<<"["<<out[ctr][ctr1]<<"]";
        }
        else
        {
          if(out[ctr][ctr1] == -1)
          cout<<"[ ]   ";
          else
          cout<<"["<<out[ctr][ctr1]<<"]   ";
        }
      }
      cout<<"\n";
    }
    cout<<"\nDisplay Page Fault: "<<pageFaults<<"\n";
    do{
      error = false;
      cout<<"\nDo you want to run again? [y/n]: ";
      cin>>choice;
      choice = toupper(choice);
      if(choice == 'Y')
      {
        again = true;
      }
      else if(choice == 'N')
      {
        rewrite();
        continue;
      }
      else
      {
        cout<<"INVALID INPUT. PLEASE CHOOSE 'Y' OR 'N' ONLY.";
        error = true;
      }
    }while(error);
  }while(again);
}
