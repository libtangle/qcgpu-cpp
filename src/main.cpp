#include <arrayfire.h>

#include "kron.h"
#include "gates.h"
#include "helper.h"

using namespace af;

class QuantumRegister {
    private:
       array amplitudes;
       int numQubits;
       bool measured = false;
    public:
        QuantumRegister(int n) {
            numQubits = n;
            // The number of amplitudes needed is 2^n = 2 << (n - 1),
            // Where N is the number of qubits. The constant(0, n) function
            // Creates an array of n 0s
            amplitudes = constant(0, 2 << (n - 1), c32);
            // Set the probability of getting all zeros when measured to 1
            amplitudes(0) = 1;
        }

        void applyGate(array gate) {
            amplitudes = matmul(gate, amplitudes);
        }

        int measure() {
            array probabilities = pow(abs(amplitudes), 2);

            return select(probabilities);
        }
};

int main(int argc, char **argv) {
    // af::info();
    int count = 0;

    QuantumRegister q(1);
    q.applyGate(Gates::H);
    count += q.measure();
    

    return 0;
}