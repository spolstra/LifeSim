#ifndef __RMU_EM_BLACKS_H
#define __RMU_EM_BLACKS_H

#include "RMU.h"
#include "reliability.h"

/*
* Class for calculating the EM related MTTF using the Blacks equation.
* NOTE : We are not overriding the updateAging() because we are not simulating the aging.
*/
class CoreInfoEM_blacks : public CoreInfo
{
    const long double ZERO_CEL_IN_KELVIN = 273.15;
    Rmodel rmodel;

	public:
		CoreInfoEM_blacks();
		~CoreInfoEM_blacks();
		void setPVParam(double process_variation_parameter);
		void updateMTTF();
};
#endif

