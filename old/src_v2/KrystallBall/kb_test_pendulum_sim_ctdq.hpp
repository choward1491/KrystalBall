#ifndef _kb_test_pendulum_sim_ctdq_
#define _kb_test_pendulum_sim_ctdq_

#include "kb_simulator_ctdiffeq.hpp"
#include "kb_test_pendulum_dyn_ctdq.hpp"
#include "kb_variadic_diffeq_bundle.hpp"

namespace kb {
	namespace ct {
		namespace test {
			
#define PARENT simulator<num_type,diffeq_bundle<num_type,Ts...>,integrator,pendulum_sim<num_type,integrator,Ts...>>
			template<typename num_type, template<typename, typename> class integrator, template<typename> class... Ts>
			class pendulum_sim : public PARENT {
			public:
				pendulum_sim() {
					time_step.setFrequency(1000);
					this->getMonteCarloMethod().setMaxMC(100);
				}

			private:
				friend class PARENT;
				discrete::model			time_step;

				bool finishedSimulation() {
					return ((10000.0 - this->getSimTime()) < 1e-8);
				}

				void addModelsToSim() {
					this->addDiscreteModel(time_step);
				}

				void finalizeMonteCarloRun() {
					//std::vector<num_type> & q = getState();
					//printf("Soln = [%lf, %lf]\n", q[0], q[1]);
				}

			};

		}
	}
}


#endif


