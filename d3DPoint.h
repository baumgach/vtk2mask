#ifndef FIBER_H_
#define FIBER_H_

typedef struct { 
  double _[3]; 
  
} d3DPoint;

inline d3DPoint dMake3DPoint(double x, double y, double z) {
  d3DPoint m = {{x,y,z}};
  return m;
}

#endif