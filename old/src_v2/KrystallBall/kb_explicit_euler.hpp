
#ifndef _kb_explicit_euler_
#define _kb_explicit_euler_

#include "kb_base_integration.hpp"

namespace kb {

	template<typename num_type>
	class explicit_euler : public integrator<num_type> {
	public:
		virtual void init(std::vector<differential::model<num_type>*> & diffeq_models) {
			unsigned int num_dofs = 0;
			for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
				num_dofs += (*iter)->getNumDoFs();
			}
			k1.resize(num_dofs);
		}
		virtual void integrate(num_type dt, std::vector<num_type> & primary_state, std::vector<differential::model<num_type>*> & diffeq_models) {
			
			// init 
			const unsigned int	num_dofs	= k1.size();
			unsigned int		sidx		= 0;
			num_type *			s			= &primary_state[0];
			differential::model<num_type>* model = nullptr;

			// compute dqdt
			num_type * k1_ref = &k1[0];
			for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
				model = *iter;
				model->operator()(k1_ref);
				k1_ref += model->getNumDoFs();
			}

			// integrate state and update primary state vector
			for (unsigned int i = 0; i < num_dofs; ++i) {
				s[i] += dt*k1[i];
			}

		}
	private:
		std::vector<num_type> k1;
	};

}


#endif
