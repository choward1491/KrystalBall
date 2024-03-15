
#ifndef _kb_base_integration_
#define _kb_base_integration_

#include "kb_differential_model.hpp"

namespace kb {

	template<typename num_type>
	class integrator {
	public:
		
		virtual ~integrator() {}
		virtual void init(std::vector<differential::model<num_type>*> & diffeq_models) = 0;
		virtual void integrate(num_type dt, std::vector<num_type> & primary_state, std::vector<differential::model<num_type>*> & diffeq_models) = 0;

	};

}

#endif