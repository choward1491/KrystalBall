#ifndef _kb_explicit_euler_crtp_
#define _kb_explicit_euler_crtp_

#include <vector>

namespace kb {
	namespace ct {

		template<typename num_type, class diffeq_obj>
		class explicit_euler {
		public:
			void init(diffeq_obj & dq_obj) {
				k1.resize(dq_obj.getNumDoFs());
			}
			void integrate(num_type dt, num_type* time, std::vector<num_type> & primary_state, diffeq_obj & dq_obj) {

				// init 
				const unsigned int	num_dofs = k1.size();
				unsigned int		sidx = 0;
				num_type *			s = &primary_state[0];

				// compute dqdt
				dq_obj.operator()(&k1[0]);

				// integrate state and update primary state vector
				for (unsigned int i = 0; i < num_dofs; ++i) {
					s[i] += dt*k1[i];
				}

			}
		private:
			std::vector<num_type> k1;
		};
	}
}


#endif

