#ifndef QUANTUM_H_
#define QUANTUM_H_

#include <arrayfire.h>

class QReg {
 private:
  af::array amplitudes;
  int numQubits;
  bool measured;

 public:
  QReg(int n);
  void applyGate(af::array gate, int a);
  int measure();
  af::array getAmplitudes();
};

#endif