
#include "vtkData.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
// #include <numeric>
// #include <vector>
// #include <string>

using namespace std;

void vtkData::doNothing(int n) {
  ++n;
}

void vtkData::LoadFile(const std::string & filename) {
  
  ifstream vtkFile (&filename[0]);
  if (!vtkFile.is_open()) { cout << "Couldn't open file"; exit(1); }
  
  string sHeader;
  string sTitle;
  string sDataFormat;
  string sDataType;
  
  getline (vtkFile, sHeader);
  getline (vtkFile, sTitle);
  getline (vtkFile, sDataFormat);
  getline (vtkFile, sDataType);
  
  if (sHeader != "# vtk DataFile Version 3.0") { cout << "Wrong File Type"; exit(1); }
  if (sDataFormat != "ASCII") { cout << "Wrong Data Type"; exit(1); }
  if (sDataType != "DATASET POLYDATA") { cout << "Wrong Topology"; exit(1); }
  
  cout << "Loading " << sTitle << "...\n";
  
  // some temp strings
  string x,y,z,curr;
  int nFieldCounter = 0;
  
  while ( vtkFile.good() )
  {
    vtkFile >> curr;
    if (curr == "POINTS") {
      vtkFile >> curr;
      _nDataSize = atof(&curr[0]);
      vtkFile >> curr;
      for (int i=0; i<_nDataSize; ++i) {
	vtkFile >> x;
	vtkFile >> y;
	vtkFile >> z;
	_vPoints.push_back(dMake3DPoint(atof(&x[0]), atof(&y[0]), atof(&z[0])));
      }
    } 
//     if (curr == "LINES") { 
//       vtkFile >> curr;
//       nNumOfFibers = atof(&curr[0]);
//       vtkFile >> curr;
//       int nTmpSize = atof(&curr[0]);
//       for (int i=0; i<nTmpSize; ++i)
// 	vtkFile >> curr; //just skip forward
//     }
//     if (curr == "Tensor1") {
//       vtkFile >> curr;
//       if (curr != "float") { cout << "Script expects tensor data to be of type float"; exit(1); }
//       for (int i=0; i<nDataSize*9; ++i)
// 	vtkFile >> curr;
//       // use later to calculate trace and whatnot
//     }
    
    // LOADING FIELDS
    if (curr == "FA") {
      vtkFile >> curr; // 1
      vtkFile >> curr; // nDataSize
      if (atof(&curr[0]) != _nDataSize) { cout << "The FA Data has the wrong dimensions"; exit(1); }
      vtkFile >> curr; // data type, should contain float but who cares
      if (curr != "float") { cout << "Script expects FA to be of type float"; exit(1); }
      _vFields.resize(nFieldCounter+1);
      for (int i=0; i<_nDataSize; ++i) {
	vtkFile >> curr;
	_vFields[nFieldCounter].push_back(atof(&curr[0])); 
      }
      _vFieldNames.push_back("FA");
      nFieldCounter++;
    }
    if (curr == "FreeWater") {
      vtkFile >> curr; // 1
      vtkFile >> curr; // nDataSize
      if (atof(&curr[0]) != _nDataSize) { cout << "The FreeWater Data has the wrong dimensions"; exit(1); }
      vtkFile >> curr; // data type, should contain float but who cares
      if (curr != "float") { cout << "Script expects FreeWater to be of type float"; exit(1); }
      _vFields.resize(nFieldCounter+1);
      for (int i=0; i<_nDataSize; ++i) {
	vtkFile >> curr;
	_vFields[nFieldCounter].push_back(atof(&curr[0])); 
      }
      _vFieldNames.push_back("FreeWater");
      nFieldCounter++;
    }
  }
  
  _nNumOfFields = nFieldCounter;
  
  vtkFile.close();
  
}