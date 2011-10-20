#include <string>
#include <vector>

// TODO: give d3DPoint a seperat class or something

typedef struct { double _[3]; } d3DPoint;

inline d3DPoint dMake3DPoint(double x, double y, double z) {
  d3DPoint m = {{x,y,z}};
  return m;
}

class vtkData {
  
  private:
    vector<Point3D> 		_vPoints; 
    vector<vector<double> > 	_vFields;
    vector<string> 		_vFieldNames;
    int 			_nNumOfFields;
    int				_nDataSize;
    
  public:
    vtkData() {
      _nNumOfFields = 0;
    };
    ~vtkData() { };
    
    LoadFile(string fn);
    
    // getters
    vector<Point3D> Points();
    vector<vector<double> > Fields();
    vector<string> FieldNames();
    int NumOfFields();

};