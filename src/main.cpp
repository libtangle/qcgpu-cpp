#include <arrayfire.h>
#include <iostream>

#include "gates.h"
#include "quantum.h"

using namespace af;

int main(int argc, char** argv) {
  //af::info();

  float pi = 3.14159265358979323846;

  QC::QReg q(3);

  q.applyGate(QC::generateUnitaryGate(pi / 2, 0, pi), 0);
  q.applyGate(QC::generateUnitaryGate(pi / 2, 0, pi), 1);
  q.applyGate(QC::generateUnitaryGate(pi / 2, 0, pi), 2);

  float results[8] = {0,0,0,0,0,0,0,0};

  for (int i = 0; i < 5000; i++) {
    results[q.measure()]++;
  }

  for (int i = 0; i < 8; i++) {
    std::cout << (results[i] / 5000) << " ";
  }

  std::cout << std::endl;

  return 0;
}