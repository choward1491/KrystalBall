#ifndef _kb_sim_polymorphism_
#define _kb_sim_polymorphism_

#include "kb_discrete_model.hpp"
#include "kb_event_handler_fast.hpp"
#include "kb_event_handler_adapt.hpp"

#ifdef _KB_USE_SIM_CRTP_
#define POLYM
#define POLY_CALL(method) static_cast<derived*>(this)->method
#define POLYM_HEADER template<typename num_type, \
							class derived, \
							unsigned int buf	= 50,\
							class event_handler = kb::fast::event_handler<num_type, kb::discrete::model, buf>, \
							typename time_type	= num_type>
#else
#define POLYM virtual
#define POLY_CALL(method) method
#define POLYM_HEADER template<typename num_type, \
								unsigned int buf	= 50,  \
								class event_handler = kb::fast::event_handler<num_type, kb::discrete::model, buf>, \
								typename time_type	= num_type>
#endif

#endif