#ifndef _kahan_number_
#define _kahan_number_

namespace kb {

	template<typename num_type>
	class kahan_ {
	public:
		kahan_() :num(0.0), compensation(0.0) {}
		kahan_(const num_type & n) :num(n), compensation(0.0) {}

		void add(const num_type & newNum) {
			num_type y = newNum - compensation;
			num_type t = num + y;
			compensation = (t - num) - y;
			num = t;
		}

		void operator=(const num_type & n) {
			this->num = n;
			this->compensation = 0.0;
		}

		operator double() const { return static_cast<double>(num); }
		operator float() const { return static_cast<float>(num); }
		operator num_type*() const { return &num; }

	private:
		num_type num;
		num_type compensation;
	};

}



#endif
