#include <arrayfire.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    try {
        // Select a device and display arrayfire info
        int device = argc > 1 ? atoi(argv[1]) : 0;
        af::setDevice(device);
        af::info();
        printf("Running QR InPlace\n");
        af::array in = af::randu(5, 8);
        af_print(in);
        af::array qin = in.copy();
        af::array tau;
        qrInPlace(tau, qin);
        af_print(qin);
        af_print(tau);
        printf("Running QR with Q and R factorization\n");
        af::array q, r;
        qr(q, r, tau, in);
        af_print(q);
        af_print(r);
        af_print(tau);
    } catch (af::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
    return 0;
}