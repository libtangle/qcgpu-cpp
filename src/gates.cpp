#include <arrayfire.h>
#include <complex>

float X_coef[] = {
    0, 0, 1, 0,
    1, 0, 0, 0
};

float Y_coef[] = {
    0, 0, 0, -1,
    0, 1, 0, 0
};
float Z_coef[] = {
    0, 0, 1, 0,
    1, 0, 0, 0
};

float H_coef[] = {
    1, 0, 1, 0,
    1, 0, -1, 0
};

float Id_coef[] = {
    1, 0, 0, 0,
    0, 0, 1, 0
};

float S_coef[] = {
    1, 0, 0, 0,
    0, 0, 0, 1
};

float SDagger_coef[] = {
    1, 0, 0, 0,
    0, 0, 0, -1
};

float T_coef[] = {
    1, 0, 0, 0,
    0, 0, 0.7071067811865475244008443621048490393, 0.7071067811865475244008443621048490393
};

float TDagger_coef[] = {
    1, 0, 0, 0,
    0, 0, 0.7071067811865475244008443621048490393, -0.7071067811865475244008443621048490393
};

namespace Gates {
    // Pauli-X / Not Gate
    af::array X = af::array(2, 2, (af::cfloat*) X_coef);

    // Pauli-Y Gate
    af::array Y = af::array(2, 2, (af::cfloat*) Y_coef);

    // Pauli-Z Gate
    af::array Z = af::array(2, 2, (af::cfloat*) Z_coef);

    // Hadamard Gate
    af::array H = (1 / sqrt(2)) * af::array(2, 2, (af::cfloat*) H_coef);

    // Identity Gate
    af::array Id = af::array(2, 2, (af::cfloat*) Id_coef);

    // S Gate
    af::array S = af::array(2, 2, (af::cfloat*) S_coef);

    // S-Dagger Gate
    af::array SDagger = af::array(2, 2, (af::cfloat*) SDagger_coef);

    // T / Pi over 8 Gate
    af::array T = af::array(2, 2, (af::cfloat*) T_coef);

    // T-Dagger Gate
    af::array TDagger = af::array(2, 2, (af::cfloat*) TDagger_coef);
}