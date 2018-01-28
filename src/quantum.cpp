#include "quantum.h"

#include <arrayfire.h>

#include "gates.h"
#include "helper.h"
namespace QC {
  QReg::QReg(int n) 
    : numQubits(n) {
      amplitudes = af::constant(0, 2 << (n - 1), c32);
      amplitudes(0) = 1;
      measured = false;
  }

  void QReg::applyGate(af::array gate, int a) {
    amplitudes = af::matmul(generateGate(gate, numQubits, a), amplitudes);
  }

  int QReg::measure() {
    af::array probabilities = af::pow(af::abs(amplitudes), 2);

    return select(probabilities);
  }

  af::array QReg::getAmplitudes() {
    return amplitudes;
  }
}


