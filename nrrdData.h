#include <teem/nrrd.h>
#include "d3DPoint.h"
#include <vnl/vnl_matrix.h>

class nrrdData {
  public:
    nrrdData() { };
    ~nrrdData() { };
  
    bool LoadSignal(const std::string& data_file);
  
  private:
  
    d3DPoint _voxel;
  
    vnl_matrix<double> _r2i;
    vnl_matrix<double> _i2r;
    
    Nrrd *_data_nrrd;
  
};