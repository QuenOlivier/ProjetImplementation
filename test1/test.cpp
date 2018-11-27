#include "GPIO.h"
#include "PWM.h"

using namespace exploringBB;
using namespace std;

int main(){
  GPIO pin(66);
  pin.setDirection(OUTPUT);
  pin.setValue(HIGH);
  return 1;
}
