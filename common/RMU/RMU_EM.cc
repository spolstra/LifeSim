#include "RMU_EM.h"
#include "simulator.h"
#include "config.hpp"

#include <cmath>
#include <iostream>

CoreInfoEM::CoreInfoEM()
 :  CoreInfo()
 , EM_fits(0.0)
 , EM_base_fits(0.0)
 , EM_inst(0.0)
{
    int num_cores = Sim()->getConfig()->getApplicationCores();

	/*
	*  We are dividing the TOTAL_EM_FITS by the number of cores as it was previously (unit_area / total_area), which is the same as the number of cores in our case
	*/

	EM_base_fits = (Constants_EM::TOTAL_EM_FITS)/(double)num_cores;

	/* Comment from RAMP 2.0 */
	/* Initial FIT values are same as base FIT values */

	EM_fits = (Constants_EM::TOTAL_EM_FITS)/(double)num_cores;
}

CoreInfoEM::~CoreInfoEM()
{
}

/* Note: pv_param is not used in the RAMP2.0 EM code. */
void CoreInfoEM::setPVParam(double process_variation_parameter)
{
	pv_param = process_variation_parameter;
	frequency = pv_param * frequency;
	V = pv_param * V;
}

void CoreInfoEM::updateMTTF()
{
    /* The RAMP2.0 code for the EM failure model */
	float act_ratio;	/* Activity ratio - between base and current sample*/
	float temp_diff;	/* Temperature difference between base and current sample*/
	float rel_exp;		/* exponent in MTTF equation for Electron migration	*/
	float fits_ratio;

// TODO: get a better act value from somewhere. In lifesim these are fixed to 1.0 and stored in the file 'pv-file.txt' */
    float act = 1.0;

	act_ratio = act;
	temp_diff = (1.0/Constants_EM::T_base) - (1.0/T); 
	rel_exp = Constants_EM::EM_Ea_div_k*temp_diff; 
	fits_ratio = ((pow((act_ratio),1.1))*(pow(2.718,rel_exp))/(1.0))*(pow((6.0/6.0),1.1));

	if (hyper_period_number > 1)
	{
		EM_fits =( EM_fits*(hyper_period_number-1) + fits_ratio*EM_base_fits)/hyper_period_number;	/* update running average of FITS */
	}
	
	EM_inst = fits_ratio*EM_base_fits;	/* Instantaneous values of FITS*/

    /* TODO: we use an initial fit value of 4000, that gives a MTTF of 30 years.
     * We could use the max_mttf_years to set the initial fit value. */
//	double max_mttf_years = (double)Sim()->getCfg()->getFloat("general/max_mttf_years");

    /* 
	* Comment from RAMP 2.0
	* The MTTF value of each structure due to each failure mechanism depends on its
 	* FIT value. 1 FIT represents one failure in 10E9 operating hours. Therefore, a
 	* FIT value of 3805.17503 gives an MTTF of 30 years. 
 	*/
 	MTTF = (30.0*3805.17503)/EM_inst;
}
