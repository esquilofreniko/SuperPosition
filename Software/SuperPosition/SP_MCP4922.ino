#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SP_MCP4922.h"

SP_MCP4922::SP_MCP4922(int LDAC, int SDI, int SCK, int CS, boolean DAC){
  _LDAC = LDAC;
  _DATAOUT = SDI;
  _SPICLOCK = SCK;
  _SLAVESELECT = CS;
  _DAC = DAC;

  pinMode(_DATAOUT,OUTPUT);
  pinMode(_SPICLOCK,OUTPUT);
  pinMode(_SLAVESELECT,OUTPUT);
  pinMode(_LDAC,OUTPUT);
  digitalWrite(_LDAC,LOW);

}

void SP_MCP4922::setValue(int Value) {
  sendIntValueSPI(Value);
}

void SP_MCP4922::sendSPIClock() {
  digitalWrite(_SPICLOCK, HIGH);
  digitalWrite(_SPICLOCK, LOW);
}

void SP_MCP4922::sendSPIHeader() {
 					// bit 15
					// 0 write to DAC_A 
					// 1 write to DAC_B
  digitalWrite(_DATAOUT,_DAC);
  sendSPIClock();
					// bit 14 Vref input buffer control
					// 0 unbuffered
					// 1 buffered
  digitalWrite(_DATAOUT,LOW);
  sendSPIClock();
					// bit 13 Output Gain selection
					// 0 2x
					// 1 1x
  digitalWrite(_DATAOUT,HIGH);
  sendSPIClock();
					// bit 12 Output shutdown control bit
					// 0 Shutdown the device
					// 1 Active mode operation *
  digitalWrite(_DATAOUT,HIGH);
  sendSPIClock();
}
 
void SP_MCP4922::sendIntValueSPI(int value) {
 // initiate data transfer with 4922
 digitalWrite(_SLAVESELECT,LOW);

 // send 4 bit header
 sendSPIHeader();
 
  // send data
  for(int i=11;i>=0;i--){
    digitalWrite(_DATAOUT,((value&(1<<i)))>>i);
    sendSPIClock();
  }
 
  // finish data transfer
  digitalWrite(_SLAVESELECT,HIGH);
} 