#include <arrayfire.h>

#include "kron.h"
#include "gates.h"

using namespace af;

class QuantumRegister {
    private:
       array amplitudes;
       bool measured = false;
    public:
        QuantumRegister(int numQubits) {
            // The number of amplitudes needed is 2^n = 2 << (n - 1),
            // Where N is the number of qubits. The constant(0, n) function
            // Creates an array of n 0s
            amplitudes = constant(0, 2 << (numQubits - 1), c32);
            // Set the probability of getting all zeros when measured to 1
            amplitudes(0) = 1;
        }

        void applyGate(array gate) {
            amplitudes = matmul(gate, amplitudes);
        }

        array measure() {
            array probabilities = pow(abs(amplitudes), 2);
            af_print(probabilities);

            return probabilities;
        }
};

void run() {
    QuantumRegister q(20);
    //q.applyGate(Gates::H);

    q.measure();

    return;
}

int main(int argc, char **argv) {
    // af::info();
    //QuantumRegister q(2);
    //q.measure();
    af_print(kron(Gates::X, Gates::Id));

    return 0;
}