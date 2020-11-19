/* This program interface the button sensor for decreasing/ incrteasing the counter value */

#include "contiki.h"
#include "dev/button-sensor.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static int16_t count=1,flag=1;
  
  static struct etimer timer;
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(button_sensor);
  

 etimer_set(&timer, CLOCK_SECOND * 2);

  while(1) {

     //PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    //PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor);
     PROCESS_WAIT_EVENT();
    if (ev == sensors_event && data == &button_sensor)
    {
     flag=flag*(-1);
    }
    
    printf("%d\n",count );
    count=count+flag;
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
