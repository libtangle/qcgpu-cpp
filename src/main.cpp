#include <arrayfire.h>
#include <iostream>

#include "gates.h"
#include "quantum.h"

using namespace af;

int main(int argc, char** argv) {
  //af::info();

  QC::QReg q(3);

  q.applyGate(QC::Gates::H, 0);
  q.applyGate(QC::Gates::H, 1);
  q.applyGate(QC::Gates::H, 2);

  float results[8] = {0,0,0,0,0,0,0,0};

  for (int i = 0; i < 500; i++) {
    results[q.measure()]++;
  }

  for (int i = 0; i < 8; i++) {
    std::cout << (results[i] / 500) << " ";
  }

  std::cout << std::endl;
  

  return 0;
}