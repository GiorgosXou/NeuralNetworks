/* Python equivalent of randn
def randn():
    randn.state = (1664525 * randn.state + 1013904223) % 2**32
    u1 = randn.state / 2**32
    randn.state = (1664525 * randn.state + 1013904223) % 2**32
    u2 = randn.state / 2**32
    return math.sqrt(-2 * math.log(u1)) * math.cos(2 * math.pi * u2)
*/

float randn() {
  static uint32_t s = 1429;  // 1427
  s = 1664525 * s + 1013904223; float u1 = s / 4294967296.0; 
  s = 1664525 * s + 1013904223; float u2 = s / 4294967296.0; 
  return sqrt(-2 * log(u1)) * cos(6.28318530718 * u2); 
}


float getTemp() {
  static float sum = 0; 
  return 20 + (sum += randn());
}


void initTempSensor() {
  // for (unsigned int i = 0; i < 36; ++i) getTemp(); 
}

