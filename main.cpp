#define MBED_HEAP_STATS_ENABLED 1
#include <stdio.h>

#include "mbed.h"
#include "mbed_stats.h"
#include "mbed-os/rtos/Thread.h"

#include <Console.h>
#include "rs485.h"
#include "c_msg.h"
#include "hdlc_framer.h"
#include "nodes.h"

Serial pc(SERIAL_TX, SERIAL_RX, 115200);
Serial sBus(BUS485_TX, BUS485_RX, 9600);
DigitalOut sBusEn(BUS485_EN);
DigitalOut myled(LED1);

Thread ledThread;

void ledWorker()
{
	while(1)
	{
		myled = SET; // LED is ON
		wait(0.1); // 200 ms
		myled = RESET; // LED is OFF
		wait(0.2); // 1 sec
		myled = SET; // LED is ON
		wait(0.1); // 200 ms
		myled = RESET; // LED is OFF
		wait(1); // 200 ms
	}
}


Console::cmd_list_t *Console::mCmdTable[] =
{
		(cmd_list_t*)shellCommands,
		(cmd_list_t*)nodeCommands,
        0
};

RS485 *rs485;
cHDLCframer *framer;

int main()
{
	RS485::init(&sBus, &sBusEn);
//	printf("pc : %s\n\r", pc.getBaud());
	printf("Serial Console demo\r\n");
	Console::init(&pc, GREEN("master"));

	printf("Start Thread\r\n");
	ledThread.start(ledWorker);



	while(1) {
	    //		printf("main tick\r\n");

	}
}
