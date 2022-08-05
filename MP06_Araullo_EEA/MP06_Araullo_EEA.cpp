#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int findMRU(int time[], int n)
{
	int i, maximum = time[0], pos = 0;

	for (i = 1; i < n; ++i)
	{
		if (time[i] > maximum)
		{
			maximum = time[i];
			pos = i;
		}
	}

	return pos;
}

int main()
{
	char again;
	ifstream checker;
	ofstream output;

	char horz = 196;
	char vert = 179;
	char uLeft = 218;
	char uRight = 191;
	char bLeft = 192;
	char bRight = 217;
	char dhorz = 194;
	char uhorz = 193;
	char mRight = 180;
	char mLeft = 195;
	char mhorz = 197;

	do
	{
		system("CLS");
		int frameSize, stringSize, *frames, *pages, *temp, *time, counter = 0, flag1, flag2, flag3, i, j, k, pos, max, faults = 0, *faultFlag;

		cout << "Programmed by: ARAULLO, Eugenio Emmanuel A." << endl;
		cout << "MP06 - MRU PAGE REPLACEMENT" << endl
			 << endl;
		checker.open("MP06 Checker.txt");

		checker >> stringSize;
		int fstat[stringSize];
		cout << "Enter reference string size: " << stringSize << endl;

		faultFlag = new int[stringSize];
		pages = new int[stringSize];

		for (int f = 0; f < stringSize; f++)
			faultFlag[f] = 0;

		cout << "Enter reference string: ";
		for (i = 0; i < stringSize; ++i)
		{
			fstat[i] = 1;
			checker >> pages[i];
			cout << pages[i] << " ";
		}

		checker >> frameSize;
		cout << "\nFrame Size: " << frameSize;

		frames = new int[frameSize];
		temp = new int[frameSize];
		time = new int[frameSize];
		int **container = new int *[frameSize];

		for (int i = 0; i < frameSize; i++)
			container[i] = new int[stringSize];

		for (i = 0; i < frameSize; ++i)
		{
			frames[i] = -1;
		}

		for (i = 0; i < stringSize; ++i)
		{
			flag1 = flag2 = 0;

			for (j = 0; j < frameSize; ++j)
			{
				if (frames[j] == pages[i])
				{
					counter++;
					time[j] = counter;
					flag1 = flag2 = 1;
					break;
				}
			}

			if (flag1 == 0)
			{
				for (j = 0; j < frameSize; ++j)
				{
					if (frames[j] == -1)
					{
						counter++;
						faults++;
						frames[j] = pages[i];
						time[j] = counter;
						flag2 = 1;
						break;
					}
				}
			}

			if (flag2 == 0)
			{
				pos = findMRU(time, frameSize);
				counter++;
				faults++;
				frames[pos] = pages[i];
				time[pos] = counter;
			}
			// Populate Container
			for (j = 0; j < frameSize; ++j)
			{
				if (frames[j] == -1)
					container[j][i] = -1;
				else
					container[j][i] = frames[j];
			}
		}

		for (int i = 1; i < stringSize; i++)
		{
			for (int j = 0; j < frameSize; j++)
			{
				//Check if two frames are equal
				if (container[j][i] == container[j][i - 1])
				{
					faultFlag[i] += 1;
					//file fault flag
				}
			}
		}

		for (int i = 1; i < stringSize; i++)
		{
			if (faultFlag[i] == frameSize) //if two pages are the same
			{
				//puts a fault flag
				fstat[i] = 0;
				for (int k = 0; k < frameSize; k++)
					container[k][i] = -1;
				//empties a frame
			}
		}

		output.open("MP06 Checker.txt");
		if (output.is_open())
		{
			output << stringSize << endl;
			for (i = 0; i < stringSize; ++i) {
				output << pages[i] << " ";
			}
			output << endl << frameSize;
			output << "\n\n";
			cout << "\n\nPage Replacement Table:\n\n";
			output << "Programmed by: ARAULLO, Eugenio Emmanuel A." << endl;
			output << "MP06 - MRU PAGE REPLACEMENT" << endl << endl;
			output << "Enter reference string size: " << stringSize << endl;
			output << "Enter reference string: ";
			for (i = 0; i < stringSize; ++i) {
				output << pages[i] << " ";
			}
			output << "\nFrame Size: " << frameSize << endl << endl;
			
			//Page Label
			for (int j = 0; j < stringSize; j++)
			{
				cout << "  " << pages[j] << "  "
					 << "  ";
				output << "  " << pages[j] << "  "
					   << "  ";
			}

			cout << endl;
			output << endl;
			//Top Border
			for (int j = 0; j < stringSize; j++)
			{
				if (fstat[j] == 1)
				{
					cout << uLeft << horz << horz << horz << uRight << "  ";
					output << "_____  ";
				}
				else
				{
					cout << "     "
						 << "  ";
					output << "       ";
				}
			}

			cout << endl;
			output << endl;

			for (i = 0; i < frameSize; i++)
			{
				for (j = 0; j < stringSize; j++)
				{
					if (fstat[j] == 1)
					{
						if (container[i][j] == -1)
						{
							cout << vert << "   " << vert << "  ";
							output << "|   |  ";
						}
						else
						{
							cout << vert << " " << container[i][j] << " " << vert << "  ";
							output << "| " << container[i][j] << " |  ";
						}
					}
					else
					{
						if (container[i][j] == -1)
						{
							cout << "     "
								 << "  ";
							output << "       ";
						}
						else
						{
							cout << "     "
								 << "  ";
							output << "|   |  ";
						}
					}
				}
				cout << endl;
				output << endl;

				for (j = 0; j < stringSize; j++)
				{ //lower borders
					if (fstat[j] == 1)
					{
						if (i < frameSize - 1)
						{ //middle border
							cout << mLeft << horz << horz << horz << mRight << "  ";
							output << "|___|  ";
						}
						else
						{
							cout << bLeft << horz << horz << horz << bRight << "  ";
							output << "|___|  ";
						}
					}
					else
					{
						cout << "     "
							 << "  ";
						output << "       ";
					}
				}

				cout << endl;
				output << endl;
			}

			cout << " " << endl
				 << endl;
			output << " " << endl
				   << endl;
			cout << "Display Page Faults: " << faults;
			output << "Display Page Faults: " << faults;
			output.close();
		}
		else
			cout << "Unable to open file";

		cout << "\n\nDo you want to run again [y/n]: ";
		cin >> again;
		cout << endl;
		checker.close();
	} while (again == 'Y' || again == 'y');

	return 0;
}
