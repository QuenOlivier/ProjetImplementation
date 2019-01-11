#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOManager.h"
#include "BeagleBoneBlack-GPIO-master/GPIO/GPIOConst.h"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include<stdio.h>
#include <string>
#include <math.h>
#include "asservissement.h"

#include "BBB-eQEP-master/src/bbb-eqep.cpp"
#define REDUC (10/19)
#define MAX_SPEED 6680


#include <fstream>      // std::ifstream

void read_eqep_init();
void initialisation_pins();
double read_eqep();
void write_period_ns(int p);
void write_duty_ns(int d);
void set_run();
void reset_run();
void sens_rotation(int moteur, int sens);
void set_speed(Point speeds);
