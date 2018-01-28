#ifndef GATES_H_
#define GATES_H_

#include <arrayfire.h>
namespace QC {
    namespace Gates {
        extern af::array X;
        extern af::array Y;
        extern af::array Z;
        extern af::array H;
        extern af::array Id;
        extern af::array S;
        extern af::array SDagger;
        extern af::array T;
        extern af::array TDagger;
    }

    af::array generateGate(af::array gate, int numQubits, int a);

}

#endif