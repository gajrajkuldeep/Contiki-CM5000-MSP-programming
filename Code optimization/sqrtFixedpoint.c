/* Floating vs Fixedpoint arithmatic*/

#include "contiki.h"

#include <stdio.h> 

#include <math.h>

/*---------------------------------------------------------------------------*/
PROCESS(sqrt_fixedpoint, "Testing floating point and fixed point execution time");
AUTOSTART_PROCESSES(&sqrt_fixedpoint);
/*---------------------------------------------------------------------------*/

// http://www.azillionmonkeys.com/qed/sqroot.html
uint16_t sqrt_uint32(uint32_t val) {
    uint32_t temp, g=0, b = 0x8000, bshft = 15;
    do {
        if (val >= (temp = (((g << 1) + b)<<bshft--))) {
           g += b;
           val -= temp;
        }
    } while (b >>= 1);
    return (uint16_t) g;
}

PROCESS_THREAD(sqrt_fixedpoint, ev, data)
{
  

  PROCESS_BEGIN();
  uint16_t i, sqrtResult=0,a=43267;
 	uint32_t timeBefore, timeAfter;
  float sqrtResultFloat, frac;

  	timeBefore=RTIMER_NOW() ;
   for (i=0; i<20; i++)
    {
      sqrtResult=sqrt_uint32(a+i);
    }
  	timeAfter=RTIMER_NOW() ;
  	//timeAfter=clock_time() ;

  	printf("\n=======================\n");
    printf("\n Sytem ticks for fixedpoint Operations: %lu \n", timeAfter-timeBefore );
    printf("\n=======================\n");
    printf("%u",sqrtResult);
    

    timeBefore=RTIMER_NOW() ;
    //timeBefore=clock_time() ;
  	 for (i=0; i<20; i++)
    {
    sqrtResultFloat=sqrt((float)a+i);
    }
  	timeAfter=RTIMER_NOW() ;
    
  	//timeAfter=clock_time() ;
    printf("\n=======================\n");
    printf("\n Sytem ticks for floating Operations: %lu \n", timeAfter-timeBefore );
  printf("\n=======================\n");

  	
    
    frac=(sqrtResultFloat-(int)sqrtResultFloat)*100;
       printf("%d.%02u ",(int)sqrtResultFloat, (unsigned int)frac );

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
