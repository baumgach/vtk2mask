#include <string>
#include <vector>
#include "d3DPoint.h"

class vtkData {
  
  private:
    std::vector<d3DPoint>	 	_vPoints; 
    std::vector<std::vector<float> > 	_vFields;
    std::vector<std::string> 		_vFieldNames;
    int 				_nNumOfFields;
    int					_nDataSize;
    
  public:
    vtkData() {
      _nNumOfFields = 0;
    };
    ~vtkData() { };
    
    bool LoadFile(const std::string & fn);
    
    // getters
    std::vector<d3DPoint> Points() { return _vPoints; }
    std::vector<float> Fields(int n) { return _vFields[n]; }
    std::string FieldNames(int n) { return _vFieldNames[n]; }
    int NumOfFields() { return _nNumOfFields; }
    int DataSize() { return _nDataSize; }

};