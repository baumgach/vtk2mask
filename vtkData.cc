
#include <iostream>
#include <fstream>

vtkData::LoadFile(string filename) {
  
  ifstream vtkFile ("Qw_opt_1t_sm.vtk");
  if (!vtkFile.is_open()) { cout << "Couldn't open file"; exit(1); }
  
  string sHeader;
  string sTitle;
  string sDataFormat;
  string sDataType;
  
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
  
  // some temp strings
  string x,y,z,curr;
  int nFieldCounter = 0;
  
  while ( myfile.good() )
  {
    myfile >> curr;
    if (curr == "POINTS") {
      myfile >> curr;
      _nDataSize = atof(&curr[0]);
      myfile >> curr;
      for (int i=0; i<_nDataSize; ++i) {
	myfile >> x;
	myfile >> y;
	myfile >> z;
	_vPoints.push_back(dMake3DPoint(atof(&x[0]), atof(&y[0]), atof(&z[0])));
      }
    } 
//     if (curr == "LINES") { 
//       myfile >> curr;
//       nNumOfFibers = atof(&curr[0]);
//       myfile >> curr;
//       int nTmpSize = atof(&curr[0]);
//       for (int i=0; i<nTmpSize; ++i)
// 	myfile >> curr; //just skip forward
//     }
//     if (curr == "Tensor1") {
//       myfile >> curr;
//       if (curr != "float") { cout << "Script expects tensor data to be of type float"; exit(1); }
//       for (int i=0; i<nDataSize*9; ++i)
// 	myfile >> curr;
//       // use later to calculate trace and whatnot
//     }
      
    if (curr == "FA") {
      myfile >> curr; // 1
      myfile >> curr; // nDataSize
      if (atof(&curr[0]) != _nDataSize) { cout << "The FA Data has the wrong dimensions"; exit(1); }
      myfile >> curr; // data type, should contain float but who cares
      if (curr != "float") { cout << "Script expects FA to be of type float"; exit(1); }
      for (int i=0; i<_nDataSize; ++i) {
	myfile >> curr;
	_vFields[nFieldCounter].push_back(atof(&curr[0])); 
      }
      _vFieldNames.push_back("FA");
      nFieldCounter++;
    }
    if (curr == "FreeWater") {
      myfile >> curr; // 1
      myfile >> curr; // nDataSize
      if (atof(&curr[0]) != _nDataSize) { cout << "The FreeWater Data has the wrong dimensions"; exit(1); }
      myfile >> curr; // data type, should contain float but who cares
      if (curr != "float") { cout << "Script expects FreeWater to be of type float"; exit(1); }
      for (int i=0; i<_nDataSize; ++i) {
	myfile >> curr;
	_vFields[nFieldCounter].push_back(atof(&curr[0])); 
      }
      _vFieldNames.push_back("FreeWater");
      nFieldCounter++;
    }
  }
  
  _nNumOfFields = nFieldCounter;
  
  myfile.close();
  
}