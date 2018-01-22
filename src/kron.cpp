#include <arrayfire.h>

using namespace af;

array kron(array A, array B) {
    int m = A.dims(0);
    int n = A.dims(1);
    int p = B.dims(0);
    int q = B.dims(1);
    dim4 dims(m * p, n * q);
    
    array K(dims, c32); 

    for (int i = 0; i < m * p; i++) {
        gfor(seq j, n * q) {
            K(i, j) = A(floor(i / p), floor(j / p)) * B(i % p, j % q);
        }
    }

    return K;
}