
#ifndef _kb_test_pendulum_sim_
#define _kb_test_pendulum_sim_

#include "kb_simulator.hpp"
#include "kb_test_pendulum_dyn.hpp"

namespace kb {
	namespace test {

#ifdef _KB_USE_SIM_CRTP_
#define PARENT simulator<num_type,pendulum_sim<num_type>>
#define FRIEND_STATEMENT friend class PARENT
#else
#define PARENT simulator<num_type>
#define FRIEND_STATEMENT
#endif

		template<typename num_type>
		class pendulum_sim : public PARENT {
		public:
			pendulum_sim() {
				time_step.setFrequency(1000);
			}


		private:
			FRIEND_STATEMENT;
			pendulum_dyn<num_type>	pmodel;
			discrete::model			time_step;

			bool finishedSimulation() {
				return ((10000.0 - this->getSimTime()) < 1e-8);
			}

			void addModelsToSim() {
				this->addDifferentialModel(pmodel);
				this->addDiscreteModel(time_step);
			}

			void finalizeMonteCarloRun() {
			}

		};

	}
}


#endif

