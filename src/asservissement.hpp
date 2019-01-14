#ifndef SERVO
#define SERVO

#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <list>

#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "../BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include "../eQEP/bbb-eqep.h"
#define _USE_MATH_DEFINES
#define TIMESTEP 0.5 //En secondes

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
int reach_point(Point &target, Point &PosInit);
int follow_path(std::list<Point> path, Point &PosInit);

void set_speed(Point speeds);


#endif
