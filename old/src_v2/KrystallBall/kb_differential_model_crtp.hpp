
#ifndef _kb_differential_model_crtp_
#define _kb_differential_model_crtp_

#include <vector>

namespace kb {

	class writer;

	namespace ct {
		namespace differential {

			template<typename num_type, template<typename> class derived>
			class model {
			public:
				typedef std::vector<num_type> vec;

				~model() {}

				//methods you must define
				void			init() {}
				unsigned int	getNumDoFs() const { return 1; }
				void			operator()(num_type* dqdt) {}
				void			update_aux() {   }
				void			addVariablesToWrite(writer & writer_) {  }


				void setState(num_type* q_) { state_ref = q_; }
				void setSimTime(num_type* sim_time_) { sim_time = sim_time_; }

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
}

#endif
