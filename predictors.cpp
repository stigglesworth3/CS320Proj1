#include<iostream>
#include<fstream>
#include<string>
#include "Branch.h"

using namespace std;

int gShare(vector<Branch> Bs, int numGHR)
{
	unsigned long long GHR = 0;
	
	string table[2048];
	for (int k=0; k<2048; k++)
	{
		table[k] = "ST";
	}
	int correct = 0;
	for (int i=0; i<Bs.size(); i++)
	{
		int index = Bs[i].getAddr() ^ GHR;
		index = index % 2048;
		string outcome = Bs[i].getBehavior();
		if (outcome == "T")
		{
			if (table[index] == "ST")
			{
				correct++;
			}
			else if (table[index] == "WT")
			{
				correct++;
				table[index] = "ST";
			}
			else if (table[index] == "WNT")
			{
				table[index] = "WT";
			}
			else if (table[index] == "SNT")
			{
				table[index] = "WNT";
			}
			GHR << 1;
			GHR = GHR | 0x00000001;
			if (numGHR == 3)
			{
				GHR = GHR & 0x00000007;
			}
			else if (numGHR == 4)
			{
				GHR = GHR & 0x0000000F;
			}
			else if (numGHR == 5)
			{
				GHR = GHR & 0x0000003F;
			}
			else if (numGHR == 6)
			{
				GHR = GHR & 0x0000007F;
			}
			else if (numGHR == 7)
			{
				GHR = GHR & 0x000000FF;
			}
			else if (numGHR == 8)
			{
				GHR = GHR & 0x000001FF;
			}	
			else if (numGHR == 9)
			{
				GHR = GHR & 0x000003FF;
			}	
			else if (numGHR == 10)
			{
				GHR = GHR & 0x000007FF;
			}
			else if (numGHR == 11)
			{
				GHR = GHR & 0x00000FFF;
			}

		}
		else if (outcome == "NT")
		{
			if (table[index] == "SNT")
			{
				correct++;
			}
			else if (table[index] == "WNT")
			{
				correct++;
				table[index] = "SNT";
			}
			else if (table[index] == "WT")
			{
				table[index] = "WNT";
			}
			else if (table[index] == "ST")
			{
				table[index] = "WT";
			}
			GHR << 1;
			GHR = GHR | 0x00000000;
			if (numGHR == 3)
			{
				GHR = GHR & 0x00000007;
			}
			else if (numGHR == 4)
			{
				GHR = GHR & 0x0000000F;
			}
			else if (numGHR == 5)
			{
				GHR = GHR & 0x0000003F;
			}
			else if (numGHR == 6)
			{
				GHR = GHR & 0x0000007F;
			}
			else if (numGHR == 7)
			{
				GHR = GHR & 0x000000FF;
			}
			else if (numGHR == 8)
			{
				GHR = GHR & 0x000001FF;
			}	
			else if (numGHR == 9)
			{
				GHR = GHR & 0x000003FF;
			}	
			else if (numGHR == 10)
			{
				GHR = GHR & 0x000007FF;
			}
			else if (numGHR == 11)
			{
				GHR = GHR & 0x00000FFF;
			}
		}
	}
	return correct;
}

int doubleBimodal(vector<Branch> Bs, int tableSize)
{
	string table[tableSize];
	for (int j=0; j<tableSize; j++)
	{
		table[j] = "strongly taken";
	}
	unsigned long long mask;
	if (tableSize == 16) //proper size and mask for each case
	{
		mask = 0x0000000F;
	}
	else if (tableSize == 32)
	{
		mask = 0x0000001F;
	}
	else if (tableSize == 128)
	{
		mask = 0x0000007F;
	}
	else if (tableSize == 256)
	{
		mask = 0x000000FF;
	}
	else if (tableSize == 512)
	{
		mask = 0x000001FF;
	}
	else if (tableSize == 1024)
	{
		mask = 0x000003FF;
	}
	else if (tableSize == 2048)
	{
		mask = 0x000007FF;
	}	
	
	int correct = 0;
	for (int i=0; i<Bs.size(); i++)
	{
		int index = Bs[i].getAddr() & mask;
		string outcome = Bs[i].getBehavior();
		
		if (outcome == "T")
		{
			if (table[index] == "strongly taken")
			{
				correct++;
			}
			else if (table[index] == "weakly taken")
			{
				correct++;
				table[index] = "strongly taken";
			}
			else if (table[index] == "weakly not taken")
			{
				table[index] = "weakly taken";
			}
			else if (table[index] == "strongly not taken")
			{
				table[index] = "weakly not taken";
			}
		}
		else if (outcome == "NT")
		{
			if (table[index] == "strongly not taken")
			{
				correct++;
			}
			else if (table[index] == "weakly not taken")
			{
				correct++;
				table[index] = "strongly not taken";
			}
			else if (table[index] == "weakly taken")
			{
				table[index] = "weakly not taken";
			}
			else if (table[index] == "strongly taken")
			{
				table[index] = "weakly taken";
			}
		}
	}
	return correct;
}

int singleBimodal(vector<Branch> Bs, int tableSize)
{
	string table[tableSize];
	for (int j=0; j<tableSize; j++)
	{
		table[j] = "taken";
	}
	unsigned long long mask;
	if (tableSize == 16) //proper size and mask for each case
	{
		mask = 0x0000000F;
	}
	else if (tableSize == 32)
	{
		mask = 0x0000001F;
	}
	else if (tableSize == 128)
	{
		mask = 0x0000007F;
	}
	else if (tableSize == 256)
	{
		mask = 0x000000FF;
	}
	else if (tableSize == 512)
	{
		mask = 0x000001FF;
	}
	else if (tableSize == 1024)
	{
		mask = 0x000003FF;
	}
	else if (tableSize == 2048)
	{
		mask = 0x000007FF;
	}	
	
	int correct = 0;
	for (int i=0; i<Bs.size(); i++)
	{
		int index = Bs[i].getAddr() & mask;
		string outcome = Bs[i].getBehavior();
		if (outcome == table[index])
		{
			correct++;
		}
		//cout << index << endl;
		table[index] = outcome;
		
	}

	//unsigned long long test = Bs[1].getAddr() & mask;
	//cout << test << endl;

	return correct;
}

int alwaysNotTaken(vector<Branch> Bs)
{
	int correct = 0;
	for (int i=0; i<Bs.size(); i++)
	{
		if (Bs.at(i).getBehavior() == "NT")
		{
			correct++;
		}
	}
	return correct;
}


int alwaysTaken(vector<Branch> Bs)
{
	int correct = 0;
	for (int i=0; i<Bs.size(); i++)
	{
		if (Bs.at(i).getBehavior() == "T")
		{
			correct++;
		}
	}
	return correct;
}

int main(int argc, char *argv[])
{
	// Temporary variables
  	unsigned long long addr;
  	string behavior;
  	unsigned long long target;

	// Open file for reading
	ifstream infile(argv[1]);

  	// The following loop will read a hexadecimal number and
  	// a string each time and then output them
	vector<Branch> branches;
  	while(infile >> std::hex >> addr >> behavior >> std::hex >> target) 
	{
		
		Branch b = Branch(addr, behavior, target);
		//cout << b.getAddr() << endl;
		branches.push_back(b);
		
  	}
	//cout << branches.size() << endl;

	int numBs = branches.size();
	int correctPs = 0;

	ofstream outFile;
	outFile.open("output.txt");

	//Always taken
	outFile << alwaysTaken(branches) << "," << numBs << ";" << endl;

	//Always not taken
	outFile << alwaysNotTaken(branches) << "," << numBs << ";" << endl;

	//Single Bit Bimodal
	outFile << singleBimodal(branches, 16) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 32) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 128) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 256) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 512) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 1024) << "," << numBs << "; ";
	outFile << singleBimodal(branches, 2048) << "," << numBs << "; " << endl;

	//Two Bit Bimodal
	outFile << doubleBimodal(branches, 16) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 32) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 128) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 256) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 512) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 1024) << "," << numBs << "; ";
	outFile << doubleBimodal(branches, 2048) << "," << numBs << "; " << endl;

	//gShare
	outFile << gShare(branches, 3) << "," << numBs << "; ";
	outFile << gShare(branches, 4) << "," << numBs << "; ";
	outFile << gShare(branches, 5) << "," << numBs << "; ";
	outFile << gShare(branches, 6) << "," << numBs << "; ";
	outFile << gShare(branches, 7) << "," << numBs << "; ";
	outFile << gShare(branches, 8) << "," << numBs << "; ";
	outFile << gShare(branches, 9) << "," << numBs << "; ";
	outFile << gShare(branches, 10) << "," << numBs << "; ";
	outFile << gShare(branches, 11) << "," << numBs << "; " << endl;


	outFile.close();
  	return 0;
}