#include <cmath>
#include <iostream>

#include "RMU_EM_blacks.h"
#include "simulator.h"
#include "config.hpp"

#include "core_manager.h"
#include "performance_model.h"


CoreInfoEM_blacks::CoreInfoEM_blacks()
 :  CoreInfo(), rmodel(new EM_model())
{
} 

CoreInfoEM_blacks::~CoreInfoEM_blacks()
{
}

void CoreInfoEM_blacks::setPVParam(double process_variation_parameter)
{
    // TODO
}

void CoreInfoEM_blacks::updateMTTF()
{
    // get this from config
    const int epoch_length_h = 30*24;
    std::cout << "DEBUG: " << hyper_period_number << std::endl;
    long double R = rmodel.add_measurement(T - ZERO_CEL_IN_KELVIN, (hyper_period_number + 1) * epoch_length_h);
 	MTTF = R;
}
