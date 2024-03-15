
#ifndef _kb_discrete_model_
#define _kb_discrete_model_


namespace kb {

	class writer;

	namespace discrete {

		class model {
		public:
			typedef double num_type;

			virtual				~model()	{}
			virtual void		init()		{}
			virtual void		update(num_type time)	{}
			virtual void		addVariablesToWrite(writer & writer_) {}
			virtual num_type	nextTime(const num_type & current_time) { return current_time + dt; }
			void				setFrequency(const num_type & freq_) { freq = freq_; dt = 1.0 / freq; }
			const num_type &	getFrequency() const { return freq; }
			

		private:
			num_type freq;
			num_type dt;
		};

	}
}

#endif
