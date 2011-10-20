
template <class T>
class Array3D {
  private:
    int _nDimX, _nDimY, _nDimZ;
  
  public:
    T ***_;
    
    Array3D(int x, int y, int z) {
      _nDimX=x; _nDimY=y; _nDimZ=z;
      _ = new T**[_nDimX];
      for (int i = 0; i < _nDimX; ++i) {
	_[i] = new T*[_nDimY];
	for (int j = 0; j < _nDimY; ++j)
	  _[i][j] = new T[_nDimZ];
      }
    }
    
    ~Array3D() { };
    
    int dimX() { return _nDimX; }
    int dimY() { return _nDimY; }
    int dimZ() { return _nDimZ; }

};

