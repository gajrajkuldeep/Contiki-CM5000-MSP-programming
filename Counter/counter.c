/* This program increases counter value in every 2 secs and display in the console */

#include "contiki.h"

#include <stdio.h> 
/*---------------------------------------------------------------------------*/
PROCESS(timer_process, "counts in every two seconds");
AUTOSTART_PROCESSES(&timer_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;
  
  // why static ask yourself
  static uint16_t count=1;  

  PROCESS_BEGIN();

  

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 2);


  while(1) {

    printf("Hello, world\n");

    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
    
    printf("%d\n",count );
    count++;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
