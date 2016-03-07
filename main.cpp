#include "mbed.h"
#include "XBee.h"
#include "rcv.h"

#define Duty 0.5

#define DBG(...) printf(__VA_ARGS__)

#define ANALOG_OFFSET 20

XBee xbee(p28, p27);

//DigitalOut led1(LED1), led2(LED2), led3(LED3), led4(LED4);

int main() {
	xbee.begin(57600);

	Rx16IoSampleResponse io_sample = Rx16IoSampleResponse();

	while(1){
		bool sw1, sw2;
		int analogX, analogY;

		if(xbee.readPacket(100)){
			switch(xbee.getResponse().getApiId()){
			case RX_16_IO_RESPONSE:
				xbee.getResponse().getRx16IoSampleResponse(io_sample);

				sw1 = !io_sample.isDigitalOn(0,0);
				sw2 = !io_sample.isDigitalOn(1,0);

				analogX = io_sample.getAnalog(2,0) - 512;
				analogY = io_sample.getAnalog(3,0) - 512;

				analogX = (-ANALOG_OFFSET < analogX && analogX < ANALOG_OFFSET) ? 0 : analogX;
				analogY = (-ANALOG_OFFSET < analogY && analogY < ANALOG_OFFSET) ? 0 : analogY;

				DBG("(x, y) = ( %4d, %4d), SW1 = %3s, SW2 = %3s\r\n",
					analogX, analogY, sw1 ? "ON" : "OFF", sw2 ? "ON" : "OFF");
				break;
			}
		}else{
			switch(xbee.getResponse().getErrorCode()){
			case NO_ERROR:
				DBG("Error : TIMEOUT\r\n");
				break;

			case CHECKSUM_FAILURE:
				DBG("Error : CHECKSUM_FAILURE\r\n");
				break;

			case PACKET_EXCEEDS_BYTE_ARRAY_LENGTH:
				DBG("Error : PACKET_EXCEEDS_BYTE_ARRAY_LENGTH\r\n");
				break;

			case UNEXPECTED_START_BYTE:
				DBG("Error : UNEXPECTED_START_BYTE\r\n");
				break;
			}

			sw1 = false;
			sw2 = false;
			analogX = 0;
			analogY = 0;
		}

		Drive(analogX, analogY, sw1, sw2);
	}
}
