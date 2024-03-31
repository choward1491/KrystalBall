
#ifndef _kb_test_pendulum_dyn_
#define _kb_test_pendulum_dyn_

#include "kb_differential_model.hpp"
#include <cmath>

namespace kb {
	namespace test {

		template<typename num_type>
		class pendulum_dyn : public differential::model<num_type> {
		public:

			virtual void init() {
				this->q(0) = 3.1415 / 6.0;
				this->q(1) = 0.0;
			}
			virtual unsigned int getNumDoFs() const { return 2; }
			virtual void operator()(num_type* dqdt) {
				const num_type*q = this->qref();
				const num_type c = 0;
				const num_type l = 1;
				const num_type g = 9.81;

				dqdt[0] = q[1];
				dqdt[1] = -(c*q[1] + (g / l)*std::sin(q[0]));
			}
			virtual void update_aux() {
				//printf("time=%lfs | (theta,thetadot) = (%lf, %lf)\n", time(), q(0), q(1));
			}

		};

	}
}


#endif
