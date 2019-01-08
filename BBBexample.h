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


#include <fstream>      // std::ifstream

Point read_eqep_init();
Point read_eqep();
void write_period_ns(int p);
void write_duty_ns(int d);
void set_run();
void reset_run();
