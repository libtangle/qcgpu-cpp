#include <stdio.h>
#include <arrayfire.h>
#include <math.h>
#include <complex>
using namespace af;

namespace Gates {

    // Pauli-X / Not Gate
    float X_coef[] = {
        0, 0, 1, 0,
        1, 0, 0, 0
    };
    
    static array X = array(2, 2, (cfloat*) X_coef);

    // Pauli-Y Gate
    float Y_coef[] = {
        0, 0, 0, -1,
        0, 1, 0, 0
    };

    static array Y = array(2, 2, (cfloat*) Y_coef);


    // Pauli-Z Gate
    float Z_coef[] = {
        0, 0, 1, 0,
        1, 0, 0, 0
    };

    static array Z = array(2, 2, (cfloat*) Z_coef);

    // Hadamard Gate
    float H_coef[] = {
        1, 0, 1, 0,
        1, 0, -1, 0
    };

    static array H = (1 / sqrt(2)) * array(2, 2, (cfloat*) H_coef);

    // Identity Gate
    float Id_coef[] = {
        1, 0, 0, 0,
        0, 0, 1, 0
    };

    static array Id = array(2, 2, (cfloat*) Id_coef);

    // S Gate
    float S_coef[] = {
        1, 0, 0, 0,
        0, 0, 0, 1
    };

    static array S = array(2, 2, (cfloat*) S_coef);

    // S-Dagger Gate
    float SDagger_coef[] = {
        1, 0, 0, 0,
        0, 0, 0, -1
    };

    static array SDagger = array(2, 2, (cfloat*) SDagger_coef);

    // T / Pi over 8 Gate
    float T_coef[] = {
        1, 0, 0, 0,
        0, 0, 0.7071067811865475244008443621048490393, 0.7071067811865475244008443621048490393
    };

    static array T = array(2, 2, (cfloat*) T_coef);

    // T-Dagger Gate
    float TDagger_coef[] = {
        1, 0, 0, 0,
        0, 0, 0.7071067811865475244008443621048490393, -0.7071067811865475244008443621048490393
    };

    static array TDagger = array(2, 2, (cfloat*) TDagger_coef);
}


// TODO: GPU ACCELERATE THIS FUNCTION
array kron(array A, array B) {
    int m = A.dims(0);
    int n = A.dims(1);
    int p = B.dims(0);
    int q = B.dims(1);
    dim4 dims(m * p, n * q);
    
    array K(dims, c32); 

    for (int i = 0; i < m * p; i++) {
        for (int j = 0; j < n * q; j++) {
            K(i, j) = A(floor(i / p), floor(j / p)) * B(i % p, j % q);
        }  
    }

    return K;
}


int main(int argc, char **argv) {
    af::info();

    float state_coef[] {
        1, 0,
        0, 0
    };

    array state = array(2, (cfloat*) state_coef);

    af_print(matmul(Gates::X, state));
    return 0;
}