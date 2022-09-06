#ifndef __RMU_EM_H
#define __RMU_EM_H

#include "RMU.h"

/*
* These are the constants used in the calculation of reliability using the Electromigration mechanism
*/

class Constants_EM
{
	public:
        // TODO check T_base value with paper
		static constexpr double T_base = 345.0;	/* Qualification temperature. At this value, the total processor FIT value will be 4000. By changing this temperature, we can model processors with different reliability qualification costs (Higher implies more expensive).*/ 

        /* 4000 ~ 30 years, we only model EM failure here. */
		static constexpr double TOTAL_EM_FITS = 4000.0;

        static constexpr double EM_Ea_div_k = (0.9/(8.62e-5)); 	/* EM activation energy [1]*/
};

/*
* Class for calculating the EM related MTTF
* NOTE : We are not overriding the updateAging() because we are not simulating the aging.
*/
class CoreInfoEM : public CoreInfo
{
	double EM_fits;
	double EM_base_fits;
	double EM_inst;

	public:
		CoreInfoEM();
		~CoreInfoEM();
		void setPVParam(double process_variation_parameter);
		void updateMTTF();
};
#endif
