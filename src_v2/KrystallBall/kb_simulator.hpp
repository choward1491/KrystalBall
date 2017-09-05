
#ifndef _kb_simulator_
#define _kb_simulator_

#include "kb_discrete_model.hpp"
#include "kb_differential_model.hpp"
#include "kb_monte_carlo_method.hpp"
#include "kb_base_integration.hpp"
#include "kb_simulator_polymorphism.hpp"
#include <vector>
#include <string>
#include <array>


namespace kb {

	POLYM_HEADER
	class simulator {
	private:

		// methods to overwrite using CRTP/polymorphism
		POLYM void addModelsToSim()			{}
		POLYM void connectModelsTogether()	{}
		POLYM bool finishedSimulation()		{ return true; }
		POLYM void finalizeMonteCarloRun()	{}
		POLYM void finalizeSimulation()		{}
		POLYM void setupTimeIntegration()	{
			int_method->init(diffeq_models);
		}


		// method to initialize models at the start of some monte carlo run
		inline void initModels() {

			// tmp var to represent starting index location for a diffeq model's state
			unsigned int start = 0;

			// initialize state for diffeq models
			differential::model<num_type> * dyn_model = nullptr;
			for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
				dyn_model = *iter;
				dyn_model->setState(&state[start]);
				start += dyn_model->getNumDoFs();
				dyn_model->init();
				dyn_model->setSimTime(&sim_time);
			}

			// initialize any auxilary variables in diffeq models
			for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
				(*iter)->update_aux();
			}
		}

		// method to initialize simulation
		inline void init() {
			if (hasNotInitialized) {
				num_dofs = 0;
				discrete_models.clear();
				diffeq_models.clear();
				POLY_CALL(addModelsToSim());
				POLY_CALL(connectModelsTogether());
				POLY_CALL(setupTimeIntegration());
				for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
					num_dofs += (*iter)->getNumDoFs();
				}
				state.resize(num_dofs);
				hasNotInitialized = false;
			} // end if
		}// end init

		inline void runMonteCarloSim() {

			// init vars to be used over and over
			time_type ctime = 0.0, ntime = 0.0;
			num_type dt = 0.0;
			discrete::model* disc_m = nullptr;
			unsigned int num_events_used = 0;

			while ( !POLY_CALL(finishedSimulation()) ) {
				// get current sim time
				ctime	= sim_time;

				// get next time
				ntime	= event_handler_.getNextTime();
				dt		= static_cast<num_type>(ntime - ctime);

				// get next set of events 
				while (event_handler_.numEvents() != 0 && event_handler_.getNextTime() == ntime) {
					event_list[num_events_used++] = event_handler_.popNextEvent().second;
				}
				
				// integrate differential models up to next set of events
				int_method->integrate(dt, state, diffeq_models);

				// compute auxilary variables in differential models at new time
				for (auto iter = diffeq_models.begin(); iter != diffeq_models.end(); ++iter) {
					(*iter)->update_aux();
				}

				// execute set of events and add back to priority queue
				for (unsigned int i = 0; i < num_events_used; ++i) {
					disc_m = event_list[i];
					disc_m->update(ntime);
					event_handler_.addEvent(*disc_m, ntime);
					event_list[i] = nullptr;
				}
				num_events_used		= 0;
				sim_time			= ntime;
				sim_time_precise	= ntime;
				
			} // end while
		} // end runMonteCarloSim


		// internal storage
		time_type									sim_time_precise;
		num_type									sim_time;
		std::vector<discrete::model*>				discrete_models;
		std::vector<differential::model<num_type>*>	diffeq_models;
		std::vector<num_type>						state;
		event_handler								event_handler_;
		std::array<discrete::model*, buf>			event_list;
		monte_carlo*								mc_method;
		integrator<num_type>*						int_method;
		bool										hasNotInitialized;

	protected:

		// methods to add models to simulation
		void addDiscreteModel(discrete::model & m)						{ discrete_models.push_back(&m); }
		void addDifferentialModel(differential::model<num_type> & m)	{ diffeq_models.push_back(&m); }
				num_type &		getSimTime()		{ return sim_time; }
		const	num_type &		getSimTime() const	{ return sim_time; }
		std::vector<num_type> & getState()			{ return state; }
		unsigned int num_dofs;

	public:

		simulator() :hasNotInitialized(true),mc_method(nullptr),int_method(nullptr),num_dofs(0){}
		virtual ~simulator()										{}
		void doWriteData(bool choice)								{}
		void addConfiguration(const std::string & config_filename)	{}
		void setMonteCarloMethod(monte_carlo & mc_method_)			{ mc_method = &mc_method_; }
		void setIntegrationMethod(integrator<num_type> &int_method_){ int_method = &int_method_; }
		monte_carlo * getMonteCarloMethod()							{ return mc_method; }
		integrator<num_type> * getIntegrationMethod()				{ return int_method; }

		// primary run method for simulation
		void run() {

			if( !mc_method )	{ /* throw error */}
			if (!int_method)	{ /* throw error */ }

			// init simulation
			init();
			mc_method->reset();

			// run MC simulations
			while (!mc_method->isDone()) {
				sim_time			= 0.0;
				sim_time_precise	= 0.0;
				event_handler_.reset(discrete_models);
				initModels();
				runMonteCarloSim();
				POLY_CALL(finalizeMonteCarloRun());
				mc_method->update();
			}

			// finalize simulation
			POLY_CALL(finalizeSimulation());

		}

		// reset sim
		virtual void reset() { hasNotInitialized = true; }

	
	};
}


#endif
