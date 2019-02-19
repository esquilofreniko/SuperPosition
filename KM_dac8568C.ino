#include <DA8568C.h>
DA8568C dac;

void dac_setup() {
  dac.init();
  dac.enable_internal_ref();
}

void dac_set(int channel, int voltage) {
  if(voltage<0){voltage = 0;}
  if(voltage>65535){voltage = 65535;}
  dac.write(WRITE_UPDATE_N, channel, voltage);
}
