#include <iostream>
#include "Array3D.h"
#include "vtkData.h"
#include "nrrdData.h"


using namespace std;

int main() {
  
  string nrrdPath = "/projects/schiz/3Tdata/case01045/diff/01045-dwi-filt-Ed.nhdr";
  
  vtkData data;
//   data.LoadFile("/projects/schiz/guest/baumgach/ukftractography_freewater/trunk/results/fb_1t_sm_fw.vtk");
  data.LoadFile("Qw_opt_1t_sm.vtk");
  
  cout << "Field Name: " << data.FieldNames(1);
  vector<float> freewater = data.Fields(1);
  
  float max = -10000;
  float min = 10000;
  float avg = 0;
  
  for (int i = 0; i < data.DataSize(); ++i) {
    if (freewater[i] > max) max = freewater[i];
    if (freewater[i] < min) min = freewater[i];
    avg += freewater[i];
  }
  
  avg /= data.DataSize();
  
  cout << endl;
  cout << "Max FW: " << max << endl;
  cout << "Min FW: " << min << endl;
  cout << "Avg FW: " << avg << endl;
  
  nrrdData nerd;
  nerd.LoadSignal(nrrdPath);
  
  // CONVERSION STUFF 

//   const int NX=144;
//   const int NY=144;
//   const int NZ=52;
//   
//   int x_max = 0;
//   int y_max = 0, z_max = 0;
//   int x_min = 1000, y_min=1000, z_min=1000;
//   
//   int x,y,z;
//   for (int i=0; i<nDataSize; ++i) {
//     x = (int)(vecPoints[i]._[0] + 0.5)+144/2;
//     y = (int)(vecPoints[i]._[1] + 0.5)+144/2;
//     z = (int)(vecPoints[i]._[2] + 0.5)-52/2+7;
//     //cout << x << " " << y << " " << z << endl;
//     if (x_max < x) x_max = x;
// 	    if (y_max < y) y_max = y;
// 	    if (z_max < z) z_max = z;
// 	    if (x_min > x) x_min = x;
// 	    if (y_min > y) y_min = y;
// 	    if (z_min > z) z_min = z;
// 	    //cout << x << endl;
//     
//     //cout << "dim1:" << sizeof(matFA) << " dim2: " << sizeof(matFA[0]) << " dim3" << sizeof(matFA[0][0]) << endl;
// 	    matFA[x][y][z].push_back(vecFA[i]);
// 	    
//   }
//   
//   cout << "max:" << x_max << " " << y_max << " " << z_max << endl;
//   cout << "min:" << x_min << " " << y_min << " " << z_min << endl;
//   
//   double avg;
//   int size;
//   
//   for (x = 0; x < NX; ++x) {
//     for (y=0;y<NY;++y) {
//       for (z=0;z<NZ;++z) {
// 	//matdFA[x][y][z] = std::accumulate(matFA[x][y][z].begin(),matFA[x][y][z].end(),0)/matFA[x][y][z].size();
// 	avg = std::accumulate(matFA[x][y][z].begin(),matFA[x][y][z].end(),0);
// 	size = matFA[x][y][z].size();
// 	matdFA[x][y][z] = avg/size;
//       }
//     }
//   }
//   
  return 0;
  
}