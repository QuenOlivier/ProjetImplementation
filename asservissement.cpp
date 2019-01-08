#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <time.h>
#include "asservissement.h"
#define _USE_MATH_DEFINES
#define TIMESTEP 0.5 //En secondes

//#include "BBB-eQEP-master/src/bbb-eqep.cpp"
//Valeurs bornes : x(0,9), y(3, 14)

using std::cout;
using std::endl;
///using namespace BBB;

Point::Point(){
  this->_x=0;
  this->_y=0;
}

Point::Point(float x, float y){
  this->_x=x;
  this->_y=y;
}

float Point::dist(Point &cible){
  return sqrt((this->_y-cible.getY())*(this->_y-cible.getY())+(this->_x-cible.getX())*(this->_x-cible.getX()));
}

Point mgi(Point &posEffecteur){
  //Valeurs physiques du modele
  float a=0.065;
  float b=0.08;
  //float c=0.015;
  float dx=0.012;
  Point og(-dx/2,0);
  Point od(dx/2,0);

  float y=posEffecteur.getY();
  float x=posEffecteur.getX();
  Point effecteur(x,y);

  float distg=effecteur.dist(og);
  float distd=effecteur.dist(od);

  float thetag=atan2(y,x-og.getX());
  float thetad=atan2(y,x-od.getX());

  //Test fonctionnel precedent non optimise
  /*float betag=acos(( (x-og.getX())*(x-og.getX()) + y*y - a*a - b*b)/(2*a*b));
  float betad=acos(( (x-od.getX())*(x-od.getX()) + y*y - a*a - b*b)/(2*a*b));

  float phig=acos((a + b*cos(betag))/distg);
  float phid=acos((a + b*cos(betad))/distd);*/

  float phig=acos((a*a + distg*distg - b*b)/(2*a*distg));
  float phid=acos((a*a + distd*distd - b*b)/(2*a*distd));

  return Point(thetag+phig,thetad-phid);
}

/*int reachPoint(Point &target){
  Point angleToReach();
  angleToReach=mgi(target);
  //READ ANGLES COURANTS

  //Calcul diff entre angles

  //Calcul vitesse necessaire

  bool reached=false;

  while(!reached){
    //VERIF QUE LE POINT N'A PAS ETE ATTEINT
    //READ ANGLES COURANTS
    if(ANGLE 1 PROCHE ET ANGLE 2 PROCHE){
      reached = true;
    }
    else if(ANGLE 1 SUFFISAMENT PROCHE){
      //RALENTIR MOTEUR 1
    }
    else if(ANGLE 2 SUFFISAMENT PROCHE){
      //RALENTIR MOTEUR 2
    }

  }
  return 1;

}*/

int main(){
  Point one(1.0,1.0);
  Point second(2.0,2.0);
  cout<<"Distance = "<<one.dist(second)<<endl;

  Point test(0,0.1);
  Point res=mgi(test);
  cout<<"Angle :\nAlpha :"<<res.getX()<<", Beta :"<<res.getY()<<endl;

}
