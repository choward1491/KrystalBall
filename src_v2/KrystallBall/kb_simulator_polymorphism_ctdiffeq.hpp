#ifndef _kb_sim_polymorphism_ctdiffeq_
#define _kb_sim_polymorphism_ctdiffeq_

#include "kb_monte_carlo_method.hpp"
#include "kb_discrete_model.hpp"
#include "kb_event_handler_fast.hpp"
#include "kb_event_handler_adapt.hpp"

#ifdef _KB_USE_SIM_CRTP_
#define POLYM
#define POLY_CALL(method) static_cast<derived*>(this)->method
#define POLYM_HEADER template<typename num_type, \
							class diffeq_bundle, \
							template<typename,typename> class integrator, \
							class derived, \
							class monte_carlo	= kb::monte_carlo, \
							unsigned int buf	= 50, \
							class event_handler = kb::fast::event_handler<num_type,kb::discrete::model,buf>, \
							typename time_type	= num_type>
#else
#define POLYM virtual
#define POLY_CALL(method) method
#define POLYM_HEADER template<typename num_type, \
							class diffeq_bundle, \
							template<typename,typename> class integrator, \
							class monte_carlo	= kb::monte_carlo, \
							unsigned int buf	= 50, \
							class event_handler = kb::fast::event_handler<num_type,kb::discrete::model,buf>, \
							typename time_type	= num_type>
#endif

#endif
