#ifndef SP_MCP4922_h
#define SP_MCP4922_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class SP_MCP4922{
  public:
    SP_MCP4922(int LDAC, int SDI, int SCK,int CS, boolean DAC);
    void setValue(int Value);

  private:
    int _LDAC;
    int _DATAOUT;
    int _SPICLOCK;
    int _SLAVESELECT;
    boolean _DAC;
    
    void sendSPIHeader();
    void sendIntValueSPI(int value);
    void sendSPIClock();
};

#endif
