#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <sstream>
 
using namespace std;

  // Tansform string to any type of number
template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}

  // String split with delimitor ','
vector<string> stringSplit(string& s)
{
	char* c;
	const int len = s.length();
	c = new char[len+2];
	strcpy(c,s.c_str());

  	const char *sep = ",";
  	char *p;
	vector<string> col;
  	p = strtok(c, sep);

 	while(p)
	{
		col.push_back(p);
	  	p = strtok(NULL, sep);
 	}
	for (int i=0;i<col.size();i++)
	{
        // cout << col.at(i) << " ";
	}
	// cout << endl;

	delete []c;
  	return col;
}

  // Delete space and tab in the string
string Trim(string& str)
{
	str.erase(0,str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

int main()
{
  // Open a data.dat and write in the editing information
	ofstream fout("data_30_1.dat", ios_base::out); 
	if (!fout)
	{
		cout << "Fail to create the .dat file !!!" << endl;
	} 

	fout << "/*********************************************" << endl;
	fout << " * OPL 12.8.0.0 Data" << endl;
	fout << " * Author: Jason" << endl;
	fout << " * Creation Date: Nov 24, 2018 at 9:47:01 PM" << endl;
	fout << " *********************************************/" << endl;

  // Read velocity and capacity from para.csv and write in data.dat
	ifstream fin2("deli_grouped_sample_30_1.csv"); 
	string line2; 
	getline(fin2, line2);
	getline(fin2, line2);

	vector<string> v_n_cp;
	v_n_cp = stringSplit(line2);
	string v = Trim(v_n_cp.at(6));
	string cp = Trim(v_n_cp.at(7));
	string ut = Trim(v_n_cp.at(9));
	string sv = Trim(v_n_cp.at(10));
	// cout << v << endl;
	// cout << cp << endl;

  // Read customoers' demand from para.csv and write in data.dat
	vector<string> dm;
	vector<string> co;
	while (getline(fin2, line2))   
	{
		vector<string> dm_n_co;
		dm_n_co = stringSplit(line2);
		dm.push_back(Trim(dm_n_co.at(1)));
		co.push_back(Trim(dm_n_co.at(9)));
	}

	int c = dm.size();
	fout << "c = " << c+1 << ";" << endl << endl;

	fout << "dm = " << endl << "[" << endl;
	fout << "0" << " ";
	for (int i=0;i<c;i++)
	{
		fout << dm.at(i) << " ";
	}
	fout << endl << "];" << endl << endl;

	fout << "co = " << endl << "[" << endl;
	fout << "0" << " ";
	for (int i=0;i<c;i++)
	{
		float co_f = stringToNum<float>(co.at(i));
		co_f = co_f - 10;
		fout << co_f << " ";
	}
	fout << endl << "];" << endl << endl;

  // Write velocity and capacity in data.dat
	fout << "v = " << v << ";" << endl << endl;

	fout << "cp = " << endl;
	fout << "[" << endl;
	for (int i=1;i<=10;i++)
	{
		fout << cp << " ";
	}
	fout << endl << "];" << endl << endl;
	fout << "ut = " << ut << ";" << endl << endl;
	fout << "sv = " << sv << ";" << endl;

  // Read the distance matrix from distance.csv and write in data.dat
	ifstream fin("distance_matrix_30_1.csv"); 
	string line; 

	fout << endl << "ds = " << endl << "[" << endl;
	getline(fin, line);
	fout <<"["<< line <<"]";
	while (getline(fin, line))
	{	
		fout << "," << endl << "[" << line << "]";
	}	
	fout << endl <<"];"<< endl << endl;


	fout.close();
	return EXIT_SUCCESS;
}
