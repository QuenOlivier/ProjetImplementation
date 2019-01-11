#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <list>
#include "BBBexample.h"

class Point{
  private:
    float _x;
    float _y;

  public:
    Point();
    Point(float x, float y);
    void setX(float x){this->_x=x;}
    void setY(float y){this->_y=y;}
    void set(float x, float y){
      this->_y=y;
      this->_x=x;
    }
    float getX(){return this->_x;}
    float getY(){return this->_y;}
    float dist(Point &cible);
};

Point mgi(Point &posEffecteur);
int reach_point(Point &target);
int follow_path(std::list<Point> path);
