
#define _ORIG_
#include <stdio.h>

#ifdef _ORIG_
#include "kb_test_pendulum_sim.hpp"
#include "kb_monte_carlo_method.hpp"
#include "kb_explicit_euler.hpp"
#else
#include "kb_explicit_euler_crtp.hpp"
#include "kb_test_pendulum_sim_ctdq.hpp"
#endif

void solvePendulum(double q10, double q20, double* soln) {

	const double c = 0, g = 9.81, l = 1;
	double time = 0.0;
	double dt	= 1e-3;
	double q[2] = { q10, q20 };
	double dqdt[2] = { 0.0 };

	while (!((10000.0 - time) < 1e-8)) {
		dqdt[0] = q[1];
		dqdt[1] = -(c*q[1] + (g/l)*std::sin(q[0]));
		q[0] += (dt*dqdt[0]);
		q[1] += (dt*dqdt[1]);
		time += dt;
	}

	soln[0] = q[0];
	soln[1] = q[1];
	printf("Soln = [%lf, %lf]\n", soln[0], soln[1]);
}

int main(int argc, char** argv) {

//#define USE_CLASS
#ifndef USE_CLASS
#ifdef _ORIG_
	kb::test::pendulum_sim<double> psim;
	kb::explicit_euler<double> ee;
	kb::monte_carlo mc;
	mc.setMaxMC(100);
	psim.setIntegrationMethod(ee);
	psim.setMonteCarloMethod(mc);
	psim.run();
#else
	namespace _p = kb::ct;
	_p::test::pendulum_sim<double, _p::explicit_euler, _p::test::pendulum_dyn> psim;
	psim.run();
#endif
	
	
#else
	double soln[2] = { 0.0 };
	for (int i = 0; i < 100; ++i) {
		solvePendulum(3.1415 / 6.0, 0.0, soln);
	}
#endif

	return 0;
}