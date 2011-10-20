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
    
    void LoadFile(const std::string & fn);
    void doNothing(int a);
    
    // getters
    std::vector<d3DPoint> Points() { return _vPoints; }
    std::vector<std::vector<float> > Fields();
    std::vector<std::string> FieldNames();
    int NumOfFields();

};