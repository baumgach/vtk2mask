#include "nrrdData.h"
#include <vnl/vnl_inverse.h>
#include <string>
#include <iostream>

bool nrrdData::LoadSignal(const std::string& data_file) {
  
  //Nrrd *tempNrrd = nrrdNew() ;
  _data_nrrd = nrrdNew();

  char *err;
  if (nrrdLoad(_data_nrrd, data_file.c_str(), NULL)) {
    err = biffGetDone(NRRD);
    std::cout << "Trouble reading " << data_file << ": " << err << std::endl;
    delete err;
    return true;
  }


  // Voxel spacing.
  double space_dir[NRRD_SPACE_DIM_MAX];
  double spacing1, spacing2, spacing3;
  nrrdSpacingCalculate(this->_data_nrrd, 1, &spacing1, space_dir);
  nrrdSpacingCalculate(this->_data_nrrd, 2, &spacing2, space_dir);
  nrrdSpacingCalculate(this->_data_nrrd, 3, &spacing3, space_dir);
  
  _voxel = dMake3DPoint(spacing3, spacing2, spacing1);	//NOTE that the _voxel here is in reverse axis order!

  // Dimensions
  //NOTICE that the _dim is in reverse axis order!
  //_dim = dMake3DPoint(_data_nrrd->axis[3].size, _data_nrrd->axis[2].size, _data_nrrd->axis[1].size);


  //Get the measurement frame.
  vnl_matrix<double> measurement_frame(3,3);
  
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      measurement_frame(i, j) = _data_nrrd->measurementFrame[i][j] ;
    }
  }

  //Get the ijk->RAS transform matrix
  _i2r.set_size(4,4);
  
  _i2r(0, 0) = _data_nrrd->axis[1].spaceDirection[0] ;
  _i2r(1, 0) = _data_nrrd->axis[1].spaceDirection[1] ;
  _i2r(2, 0) = _data_nrrd->axis[1].spaceDirection[2] ;
  _i2r(0, 1) = _data_nrrd->axis[2].spaceDirection[0] ;
  _i2r(1, 1) = _data_nrrd->axis[2].spaceDirection[1] ;
  _i2r(2, 1) = _data_nrrd->axis[2].spaceDirection[2] ;
  _i2r(0, 2) = _data_nrrd->axis[3].spaceDirection[0] ;
  _i2r(1, 2) = _data_nrrd->axis[3].spaceDirection[1] ;
  _i2r(2, 2) = _data_nrrd->axis[3].spaceDirection[2] ;
  _i2r(0, 3) = _data_nrrd->spaceOrigin[0];
  _i2r(1, 3) = _data_nrrd->spaceOrigin[1];
  _i2r(2, 3) = _data_nrrd->spaceOrigin[2];
  _i2r(3, 3) = 1.0;

  
  // RAS->ijk.
  _r2i = vnl_inverse(_i2r);
  
  std::cout << "_i2r:\n" << _i2r << std::endl;
  std::cout << "_r2i:\n" << _r2i << std::endl;
  std::cout << "measurement_frame:\n" << measurement_frame << std::endl;
  
  
  // Transform gradients.
  vnl_matrix<double> R(3,3);
  R = _i2r.extract(3,3);
  // The gradient should not be affected by voxel size, so factor out the voxel sizes
  // This is equivalent to normalizing the space directions
  double vox_x_inv = 1.0 / _voxel._[2] ;
  double vox_y_inv = 1.0 / _voxel._[1] ;
  double vox_z_inv = 1.0 / _voxel._[0] ;
  
  R(0, 0) *=  vox_x_inv ;
  R(1, 0) *=  vox_x_inv ;
  R(2, 0) *=  vox_x_inv ;	//R(0,0), R(1,0), R(2,0) is a unit vector, and is just the normalized spacedirection of axis 1
  R(0, 1) *=  vox_y_inv ;
  R(1, 1) *=  vox_y_inv ;
  R(2, 1) *=  vox_y_inv ;
  R(0, 2) *=  vox_z_inv ;
  R(1, 2) *=  vox_z_inv ;
  R(2, 2) *=  vox_z_inv ;
  
  vnl_matrix<double> tmp_mat = vnl_inverse(R)*measurement_frame;
  
  std::cout << "R-1*MF:\n" << tmp_mat;
//   
//   int count = _gradients.size();
//   vnl_vector<double> u(3), u_new(3); // u - old gradients
//   
//   u_new = tmp_mat*u;

  return false;
}