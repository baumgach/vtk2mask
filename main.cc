#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <numeric>

#include "Array3D.h"

using namespace std;

int main() {
  
  string line;
  ifstream myfile ("Qw_opt_1t_sm.vtk");
  
  if (!myfile.is_open()) { cout << "Couldn't open file"; exit(1); }
  
  string curr;
  double dTest;
  int nDataSize;
  int nNumOfFibers;
  
  string sHeader;
  string sTitle;
  string sDataFormat;
  string sDataType;
  
  const int NX=144;
  const int NY=144;
  const int NZ=52;
  
  vector<double> ***matFA;
  vector<double> ***matFreeWater;
  double ***matdFA;	 
  
  getline (myfile, sHeader);
  getline (myfile, sTitle);
  getline (myfile, sDataFormat);
  getline (myfile, sDataType);
  
  if (sHeader != "# vtk DataFile Version 3.0") { cout << "Wrong File Type"; exit(1); }
  if (sDataFormat != "ASCII") { cout << "Wrong Data Type"; exit(1); }
  if (sDataType != "DATASET POLYDATA") { cout << "Wrong Topology"; exit(1); }
  
  
  vector<double> 	vecFA;
  vector<double> 	vecFreeWater;
  vector<string> 	vecNames;
  vector<d3DPoint> 	vecPoints;
  
  while ( myfile.good() )
    //for (int i=0; i<20; ++i)
  {
    string x,y,z;
    myfile >> curr;
    if (curr == "POINTS") {
      myfile >> curr;
      nDataSize = atof(&curr[0]);
      myfile >> curr;
      
      for (int i=0; i<nDataSize; ++i) {
	//store points
	myfile >> x;
	myfile >> y;
	myfile >> z;
	//cout << x << " " << y << " " << z << endl;
	vecPoints.push_back(dMake3DPoint(atof(&x[0]), atof(&y[0]), atof(&z[0])));
      }
    } 
    //if (curr == "LINES") { 
      //	myfile >> curr;
      //	nNumOfFibers = atof(&curr[0]);
      //	myfile >> curr;
      //	int nTmpSize = atof(&curr[0]);
      //	for (int i=0; i<nTmpSize; ++i)
      //		myfile >> curr; //just skip forward
      //}
      if (curr == "Tensor1") {
	myfile >> curr;
	if (curr != "float") { cout << "Script expects tensor data to be of type float"; exit(1); }
	for (int i=0; i<nDataSize*9; ++i)
	  myfile >> curr;
	// use later to calculate trace and whatnot
      }
      if (curr == "FA") {
	vecNames.push_back("FA");
	myfile >> curr; // 1
	myfile >> curr; // nDataSize
	if (atof(&curr[0]) != nDataSize) { cout << "The FA Data has the wrong dimensions"; exit(1); }
	myfile >> curr; // data type, should contain float but who cares
	if (curr != "float") { cout << "Script expects FA to be of type float"; exit(1); }
	for (int i=0; i<nDataSize; ++i) {
	  // record FA
	  myfile >> curr;
	  vecFA.push_back(atof(&curr[0])); 
	}
      }
      if (curr == "FreeWater") {
	vecNames.push_back("FreeWater");
	myfile >> curr; // 1
	myfile >> curr; // nDataSize
	if (atof(&curr[0]) != nDataSize) { cout << "The free water data has wrong dimensions"; exit(1); }
	myfile >> curr; // data type, should contain float but who cares
	if (curr != "float") { cout << "Script expects FreeWater to be of type float"; exit(1); }
	for (int i=0; i<nDataSize; ++i) {
	  // record FreeWater
	  myfile >> curr;
	  vecFreeWater.push_back(atof(&curr[0])); 
	}
      }
  }
  int x_max = 0;
  int y_max = 0, z_max = 0;
  int x_min = 1000, y_min=1000, z_min=1000;
  
  myfile.close();
  
  int x,y,z;
  for (int i=0; i<nDataSize; ++i) {
    x = (int)(vecPoints[i]._[0] + 0.5)+144/2;
    y = (int)(vecPoints[i]._[1] + 0.5)+144/2;
    z = (int)(vecPoints[i]._[2] + 0.5)-52/2+7;
    //cout << x << " " << y << " " << z << endl;
    if (x_max < x) x_max = x;
	    if (y_max < y) y_max = y;
	    if (z_max < z) z_max = z;
	    if (x_min > x) x_min = x;
	    if (y_min > y) y_min = y;
	    if (z_min > z) z_min = z;
	    //cout << x << endl;
    
    //cout << "dim1:" << sizeof(matFA) << " dim2: " << sizeof(matFA[0]) << " dim3" << sizeof(matFA[0][0]) << endl;
	    matFA[x][y][z].push_back(vecFA[i]);
	    
  }
  
  cout << "max:" << x_max << " " << y_max << " " << z_max << endl;
  cout << "min:" << x_min << " " << y_min << " " << z_min << endl;
  
  double avg;
  int size;
  
  for (x = 0; x < NX; ++x) {
    for (y=0;y<NY;++y) {
      for (z=0;z<NZ;++z) {
	//matdFA[x][y][z] = std::accumulate(matFA[x][y][z].begin(),matFA[x][y][z].end(),0)/matFA[x][y][z].size();
	avg = std::accumulate(matFA[x][y][z].begin(),matFA[x][y][z].end(),0);
	size = matFA[x][y][z].size();
	matdFA[x][y][z] = avg/size;
      }
    }
  }
  
  return 0;
  
}