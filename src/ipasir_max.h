#ifndef ipasir_max_h_INCLUDED
#define ipasir_max_h_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Add current clause as a soft clause with given weight.
 */
void ipasir_add_soft (void * solver, double weight);

/**
 * get the weight of the current solution.
 */
double ipasir_weight (void * solver);

#ifdef __cplusplus
}
#endif

#endif
