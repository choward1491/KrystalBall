
#ifndef _kb_rk4_crtp_
#define _kb_rk4_crtp_


namespace kb {
	namespace ct {

		template<typename num_type, class diffeq_obj>
		class rk4 {
		public:
			void init(diffeq_obj & dq_obj) {
				const unsigned int size = dq_obj.getNumDoFs();
				k1.resize(size);
				k2.resize(size);
				k3.resize(size);
				k4.resize(size);
				tmp.resize(size);
			}

			void integrate(num_type dt, num_type* time, std::vector<num_type> & primary_state, diffeq_obj & dq_obj) {

				// init 
				const unsigned int	num_dofs = k1.size();
				unsigned int		sidx = 0;
				num_type *			s = &primary_state[0];
				const num_type		t = *time;

				// compute first step
				dq_obj.operator()(&k1[0]);

				// compute second step
				add_vec(num_dofs, dt, 0.5, s, &k1[0], &tmp[0]);
				*time += 0.5*dt;
				dq_obj.setState(&tmp[0]);
				dq_obj.operator()(&k2[0]);

				// compute third step
				add_vec(num_dofs, dt, 0.5, s, &k2[0], &tmp[0]);
				dq_obj.setState(&tmp[0]);
				dq_obj.operator()(&k3[0]);

				// compute last step
				add_vec(num_dofs, dt, 1.0, s, &k3[0], &tmp[0]);
				*time = t + dt;
				dq_obj.setState(&tmp[0]);
				dq_obj.operator()(&k4[0]);

				// integrate state and update primary state vector
				for (unsigned int i = 0; i < num_dofs; ++i) {
					s[i] += dt*((k1[i] + 2.0*(k2[i] + k3[i]) + k4[i] )/6.0);
				}
				*time = t;

			}
		private:

			static void add_vec(unsigned int size, num_type dt, num_type constant_, const num_type * s, const num_type * kv, num_type* out) {
				for (unsigned int i = 0; i < size; ++i) {
					out[i] = s[i] + dt*(constant_*kv[i]);
				}
			}

			std::vector<num_type> k1;
			std::vector<num_type> k2;
			std::vector<num_type> k3;
			std::vector<num_type> k4;
			std::vector<num_type> tmp;
		};
	}
}


#endif


