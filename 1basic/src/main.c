#if defined (__AVR_ATmega32U4__)
#include "FreeRTOSVariant.h"
#endif
#include "FreeRTOS.h"
#include "task.h"
#include "common.h"
#include <stdio.h>

void vLedsFloat(void* dummy);
void vLedsFlash(void* dummy);
void vPrintUart(void* dummy);

int main(void){
 volatile int i;
 Usart1_Init(); // inits clock as well
 Led_Init();
 Led_Hi1();

 if (!(pdPASS == xTaskCreate( vLedsFloat, (signed char*) "LedFloat", 64,NULL,1,NULL ))) goto hell;
 if (!(pdPASS == xTaskCreate( vLedsFlash, (signed char*) "LedFlash", 64,NULL,2,NULL ))) goto hell;
 if (!(pdPASS == xTaskCreate( vPrintUart, (signed char*) "Uart",     64,NULL,3,NULL ))) goto hell;

 vTaskStartScheduler();
hell:              // should never be reached
	while(1);
    return 0;
}

void vLedsFloat(void* dummy)
{while(1){
  Led_Hi1();
  vTaskDelay(120/portTICK_RATE_MS);
  Led_Lo1();
  vTaskDelay(120/portTICK_RATE_MS);
 }
}

void vLedsFlash(void* dummy)
{while(1){
  Led_Hi2();
  vTaskDelay(301/portTICK_RATE_MS);
  Led_Lo2();
  vTaskDelay(301/portTICK_RATE_MS);
 }
}

/* Writes each 500 ms */
void vPrintUart(void* dummy)
{char c[32];
 portTickType last_wakeup_time;
 last_wakeup_time = xTaskGetTickCount();
 while(1){sprintf(c,"\nHello World\r\n");
          uart_puts(c);
          //uart_puts("\nHello World\r\n");
//#define configUSE_TRACE_FACILITY        1
//#define configUSE_STATS_FORMATTING_FUNCTIONS    1
          //vTaskList(c);
          //uart_puts(c);
          //uart_putc('0');
          //uart_putc('\r');
          //uart_putc('\n');
	  vTaskDelayUntil(&last_wakeup_time, 500/portTICK_RATE_MS);
	}
}
