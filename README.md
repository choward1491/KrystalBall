## Purpose
The purpose of **KrystalBall** is to provide a flexible and efficient simulation framework for tackling discrete, differential, and/or Monte Carlo simulations.

The goal of this framework is to allow a user to quickly be able to build a clean, functional simulation all bundled into a class entity for modular use and potential usage in black box functions for, say, optimization routines.

## Key Features
Some interesting features about the simulation framework are the following:
- Framework uses compile-time polymorphism to remove the run-time overhead for choices in one's integration scheme
- Framework uses a precise integer-based timer to maintain perfect times no matter what frequency your simulation models operates at, in turn maintaining good time accuracy and removing accumulation of round off errors
- Framework uses generalized integrator class structure that creates a complete and efficient integration scheme by just handing it a Butcher Tableau. This currently works for both normal and Adaptive explicit schemes that can be represented by a Butcher Tableau.
- Framework handles managing data for simulation variables under the good, providing a simple interface for users to use in the models
- Framework has functionality built in for writing data to files and handling the scheduling of discrete events in simulation time

## Things to Do
- Implement Implicit scheme builder based on Butcher Tableau
- Modify discrete models to allow them to output a time step that changes over time, instead of requiring each model to specify a time step that will be constant over the time of the simulation