/**
 * This example program demonstrates the use of the BBB-eQEP library.
 * Copyright (C) 2014 James Zapico <james.zapico@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

#include <bbb-eqep.h>

using std::cout;
using std::endl;
using std::cerr;
using namespace BBB;

int main (int argc, char const *argv[])
{
  struct timeval tv1, tv2;
  int eqep_num;
  uint32_t eqep_pos, eqep0_pos, eqep1_pos, eqep2_pos;

  eQEP eqep(eQEP0);
//  eQEP eqep1(eQEP1);
  eQEP eqep2(eQEP2);


  printf("0000000000000000000000000000000000000000000000000000000000000000000000\n");
  printf("SYSCONFIG 0x%X\n", *(uint32_t*)(eqep.getPWMSSPointer() + PWM_SYSCONFIG));
  printf("CLKCONFIG 0x%X\n", *(uint32_t*)(eqep.getPWMSSPointer()+PWM_CLKCONFIG));
  printf("QEPCTL0   0x%X\n",  eqep.getControl());
  printf("QDECCTL0  0x%X\n",  eqep.getDecoderControl());
  printf("QEINT0    0x%X\n",  eqep.getInterruptEnable());
  printf("QUPRD0    0x%u\n", eqep.getUnitPeriod());
  printf("QPOSMAX0  0x%X\n", eqep.getMaxPos());
  printf("QEPSTS0   0x%X\n",  eqep.getStatus());
  eqep0_pos = eqep;

/*  printf("\n1111111111111111111111111111111111111111111111111111111111111111111111\n");
  printf("SYSCONFIG 0x%X\n", *(uint32_t*)(eqep1.getPWMSSPointer() + PWM_SYSCONFIG));
  printf("CLKCONFIG 0x%X\n", *(uint32_t*)(eqep1.getPWMSSPointer()+PWM_CLKCONFIG));
  printf("QEPCTL0   0x%X\n",  eqep1.getControl());
  printf("QDECCTL0  0x%X\n",  eqep1.getDecoderControl());
  printf("QEINT0    0x%X\n",  eqep1.getInterruptEnable());
  printf("QUPRD0    0x%u\n", eqep1.getUnitPeriod());
  printf("QPOSMAX0  0x%X\n", eqep1.getMaxPos());
  printf("QEPSTS0   0x%X\n",  eqep1.getStatus());
  eqep1_pos = eqep1;
*/
  printf("\n2222222222222222222222222222222222222222222222222222222222222222222222222\n");
  printf("SYSCONFIG 0x%X\n", *(uint32_t*)(eqep2.getPWMSSPointer() + PWM_SYSCONFIG));
  printf("CLKCONFIG 0x%X\n", *(uint32_t*)(eqep2.getPWMSSPointer()+PWM_CLKCONFIG));
  printf("QEPCTL0   0x%X\n",  eqep2.getControl());
  printf("QDECCTL0  0x%X\n",  eqep2.getDecoderControl());
  printf("QEINT0    0x%X\n",  eqep2.getInterruptEnable());
  printf("QUPRD0    0x%u\n", eqep2.getUnitPeriod());
  printf("QPOSMAX0  0x%X\n", eqep2.getMaxPos());
  printf("QEPSTS0   0x%X\n",  eqep2.getStatus());
  eqep2_pos = eqep2;

//time a read-loop to assess speed
  int num_reads = 1000000;
  int i;
  gettimeofday(&tv1,NULL);
  for(i=0;i<num_reads;i++){
    eqep_pos = eqep.getPosition();
 //   eqep1_pos = eqep1.getPosition();
    eqep2_pos = eqep2.getPosition();
  }
  gettimeofday(&tv2,NULL);

  //find difference between start and end time
  unsigned long dt_micros = (1000000 * tv2.tv_sec + tv2.tv_usec)-(1000000 * tv1.tv_sec + tv1.tv_usec);
  float time_per_read = (float)dt_micros/num_reads;
  float change_rate = (float)(num_reads)/((float)(dt_micros)) * 1000;

  printf("Eqep0 last position: %i\n", eqep_pos);
//  printf("Eqep1 last position: %i\n", eqep1_pos);
  printf("Eqep2 last position: %i\n", eqep2_pos);
  printf("micros per read: %f\n", time_per_read);
  printf("quadrature read rate (kHz): %f\n",change_rate);
  printf("Eqep0:revid: 0x%X (should read 44D31103)\n",eqep.getRevisionID());
//  printf("Eqep1:revid: 0x%X (should read 44D31103)\n",eqep1.getRevisionID());
  printf("Eqep2:revid: 0x%X (should read 44D31103)\n",eqep2.getRevisionID());

  for(i=0;i<10000000;i++){
    printf("\reqep0: %zu           eqep2: %zu        ",eqep.getPosition(),eqep2.getPosition() );

    usleep(5000);
  }
  printf("\n");

  return 0;
}
