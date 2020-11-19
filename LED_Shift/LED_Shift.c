/* LED on and off using timer*/

#include "contiki.h"
//#include "dev/button-sensor.h"
#include "dev/leds.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  //static int16_t count=1,flag=1;
  static struct etimer timer;
  static uint8_t value=0x10;
  PROCESS_BEGIN();
  //SENSORS_ACTIVATE(button_sensor);
  

 etimer_set(&timer, CLOCK_SECOND * 2);

  while(1) {

   
    PROCESS_WAIT_EVENT();
   
    if (etimer_expired(&timer))
    {
     leds_off(value);
     value=value<<1;
     if (value==0x80)
     {
      value=0x10;
       /* code */
     }
    }
    
   leds_on(value);
   
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
