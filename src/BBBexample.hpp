#ifndef BBBEX
#define BBBEX

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include<stdio.h>
#include <string>
#include <math.h>
#include "asservissement.hpp"

#define REDUC (10/19)
#define MAX_SPEED 6680
#define MOTOR_TWO 2
#define PERIOD 100000


#include <fstream>      // std::ifstream

Point read_eqep_init();
void initialisation_pins();
double read_eqep(int moteur, Point &PosInit);
void write_period_ns(int moteur, int p);
void write_duty_ns(int moteur, int d);
void set_run();
void reset_run();
void sens_rotation(int moteur, int sens);
#endif
