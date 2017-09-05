
#ifndef _kb_differential_model_
#define _kb_differential_model_

#include <vector>

namespace kb {

	class writer;

	namespace differential {

		template<typename num_type>
		class model  {
		public:
			typedef std::vector<num_type> vec;

			virtual ~model() {}
			virtual void			init() {}
			virtual unsigned int	getNumDoFs() const { return 1; }
			virtual void			operator()(num_type* dqdt) {}
			virtual void			update_aux() {}
			virtual void			addVariablesToWrite(writer & writer_) {}
			
			void setState(num_type* q_)				{ state_ref = q_; }
			void setSimTime(num_type* sim_time_)	{ sim_time = sim_time_; }

		protected:
			inline const	num_type &	q(int idx) const { return state_ref[idx]; }
			inline			num_type &	q(int idx) { return state_ref[idx]; }
			inline const	num_type &	time() const { return *sim_time; }
			inline const	num_type *	qref() { return state_ref; }

		private:

			num_type * sim_time;
			num_type * state_ref;
		};

	}
}

#endif