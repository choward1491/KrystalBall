

#ifndef _kb_monte_carlo_method_
#define _kb_monte_carlo_method_

namespace kb {

	class monte_carlo {
	public:

		monte_carlo() :max_mc(1), num_mc_completed(0) {}
		virtual ~monte_carlo()		{}
		int numCompleted() const	{ return num_mc_completed; }
		virtual bool isDone() const { return num_mc_completed >= max_mc; }
		virtual void update() { ++num_mc_completed; }

		void reset() { num_mc_completed = 0; }
		void setMaxMC(unsigned int max_mc_) { max_mc = max_mc_; }

	protected:
		unsigned int max_mc;
		unsigned int num_mc_completed;
	};

}

#endif
