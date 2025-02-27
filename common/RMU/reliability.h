#include <cmath>
#include <iostream>
#include <stdexcept>

#include "em_model.h"

class Rmodel {
   public:
    /* We take ownership of alpha here. */
    Rmodel(Wearout_model *alpha)
        : current_R(1), current_time_stamp(0), current_sum(0), alpha(alpha){};

    ~Rmodel(void) {
        delete alpha; /* We own alpha, so we need to free it here. */
    };

    /* Calculate the new R value.
     * temp in celsius
     * new_time_stamp in ms

       We use equation (5) from the paper [1] (equation (11) in [2]):
       R(t) = exp(-pow((sum(T_j / alpha(T_j))), beta))

       [1] : "Lightweight and Open-source Framework for the Lifetime Estimation
       of Multicore Systems" 2014 by Cristiana Bolchini et al.
       [2] : "System-level reliability modeling for MPSoCs" by Yan Xiang.
       */
    long double add_measurement(long double temp, long double new_time_stamp) {
        long double delta_t = new_time_stamp - current_time_stamp;
        current_time_stamp = new_time_stamp;

        if (delta_t < 0) {
            throw std::runtime_error("Negative delta_t is not allowed");
        }

        // Add measurement to the stored 'current_sum': sum(T_j / alpha(T_j))
        current_sum += delta_t / (*alpha)(temp);

        long double new_R = exp(-1 * pow(current_sum, BETA));
        if (new_R > current_R) {
            throw std::runtime_error("Reliability cannot increase over time");
        }
        current_R = new_R;
        // std::cerr << "sum: " << current_sum << std::endl;
        return new_R;
    }

    long double get_R(void) { return current_R; }

   private:
    long double current_R;
    long double current_time_stamp;
    long double current_sum;
    Wearout_model *alpha;

    const long double BETA = 2;  // weibull scaling parameter
};
