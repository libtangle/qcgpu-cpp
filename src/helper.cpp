#include <arrayfire.h>
#include <random>

int select(af::array weights) {
    // Assumes sum of the weights are 1

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float key = dis(gen);

    int index = 0;
    for (; index < weights.dims(0); index++) {
        key = key - weights(index).scalar<float>();

        if (key <= 0) {
            return index;
        }
    }

    return index;
}