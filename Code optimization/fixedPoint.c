/* Floating vs Fixedpoint arithmatic*/

#include "contiki.h"

#include <stdio.h> 
#define fracPart 4  // Qm.n here m=12 and n=fracPart
/*---------------------------------------------------------------------------*/
PROCESS(fixedpoint, "Testing floating point and fixed point execution time");
AUTOSTART_PROCESSES(&fixedpoint);
/*---------------------------------------------------------------------------*/

uint16_t multiply(uint16_t a, uint16_t b)
{
  
  uint32_t result;
  uint16_t out;
  result= (uint32_t) a * (uint32_t) b; // typecast to avoid oveflow error 

  result= result>>fracPart;  // bring back to the Qm.n formate  

  out=result;
   return out;
}

PROCESS_THREAD(fixedpoint, ev, data)
{
  

  PROCESS_BEGIN();

  	float a=2.3, b=7.8, c[256],frac;
  	uint16_t i, aFi=0x0025, bFi=0x007d, cFi[256];
 	uint32_t timeBefore, timeAfter;
  	timeBefore=RTIMER_NOW() ;
  	//timeBefore=clock_time() ;
  	for (i=0; i<256; i++)
  	{
  		a=a+1;
  		c[i]=a*b;
  	}
  	timeAfter=RTIMER_NOW() ;
  	//timeAfter=clock_time() ;

  	printf("\n=======================\n");
    printf("\n Sytem ticks for floating Operations: %lu \n", timeAfter-timeBefore );
	printf("\n=======================\n");
    for (i=0; i<256; i++)
  	{
  		frac=(c[i]-(int)c[i])*100;
  		 printf("%d.%02u ",(int)c[i], (unsigned int)frac );
  	}
   
    timeBefore=RTIMER_NOW() ;
    //timeBefore=clock_time() ;
  	for (i=0; i<256; i++)
  	{
  		aFi=aFi+0x0010;    // 1 fixedpoint is 0x0010 for Q12.4
  		cFi[i]=multiply(aFi, bFi);
  	}
  	timeAfter=RTIMER_NOW() ;
  	//timeAfter=clock_time() ;
  	printf("\n=======================\n");
    printf("\n Sytem ticks for fixedpoint Operations: %lu \n", timeAfter-timeBefore );
    printf("\n=======================\n");
     for (i=0; i<256; i++)
  	{
  		 printf("%x ",cFi[i] );
  	}


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
