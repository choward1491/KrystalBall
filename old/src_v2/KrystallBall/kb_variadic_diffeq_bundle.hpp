
#ifndef _variadic_diffeq_bundle_
#define _variadic_diffeq_bundle_

namespace kb {

	class writer;

	// define a default baseline diffeq_bundle class
	template<typename num_type, template<typename> class... Ts>
	class diffeq_bundle {
	public:
		inline void init() {}
		inline void update() {}
		inline void operator()(num_type* dqdt) {}
		inline void update_aux() {}
		inline void addVariablesToWrite(writer & writer_) {}
		inline void setState(num_type* q) {}
		inline void setSimTime(num_type* sim_time) {}
		inline unsigned int getNumDoFs() const { return 0; }
	};

	// define the compile-time recursive diffeq_bundle variadic class
	template<typename num_type, template<typename> class T, template<typename> class... Ts>
	class diffeq_bundle<num_type, T, Ts...> : public diffeq_bundle<num_type, Ts...> {
	public:

		// define useful typedefs
		typedef			diffeq_bundle<num_type, Ts...>	parent;
		typedef const	diffeq_bundle<num_type, Ts...>* cparent_ref;

		// define ctors
		diffeq_bundle() : diffeq_bundle<num_type,Ts...>(), tail() {}
		diffeq_bundle(T<num_type> t, Ts<num_type>... ts) : diffeq_bundle<num_type,Ts...>(ts...), tail(t) {}

		// define methods that will use variadic compile-time optimizations
		inline void init() {
			tail.init();
			static_cast<parent*>(this)->init();
		}

		inline void update() {
			tail.update();
			static_cast<parent*>(this)->update();
		}

		inline void operator()(num_type* dqdt) {
			tail.operator()(dqdt);
			dqdt += tail.getNumDoFs();
			static_cast<parent*>(this)->operator()(dqdt);
		}

		inline void update_aux() {
			tail.update_aux();
			static_cast<parent*>(this)->update_aux();
		}
		inline void addVariablesToWrite(writer & writer_) {
			tail.addVariablesToWrite(writer_);
			static_cast<parent*>(this)->addVariablesToWrite(writer_);
		}

		inline void setState(num_type* q) {
			tail.setState(q);
			q += tail.getNumDoFs();
			static_cast<parent*>(this)->setState(q);
		}

		inline void setSimTime(num_type* sim_time) {
			tail.setSimTime(sim_time);
			static_cast<parent*>(this)->setSimTime(sim_time);
		}

		inline unsigned int getNumDoFs() const { 
			return tail.getNumDoFs() + static_cast<cparent_ref>(this)->getNumDoFs();
		}

		T<num_type> tail;
	};




	// define bundle type class 
	template <size_t k, typename num_type, template<typename> class T, template<typename> class... Ts>
	struct bundle_type {
		typedef typename bundle_type<k - 1, num_type, Ts...>::type type;
	};
	
	template <typename num_type, template<typename> class T, template<typename> class... Ts>
	struct bundle_type<0, num_type, T, Ts...> {
		typedef T<num_type> type;
	};




	// define get function
	template<size_t k, typename num_type, template<typename> class T, template<typename> class... Ts>
	typename std::enable_if<
		k != 0,
		typename bundle_type<k, num_type, T, Ts...>::type&>::type

		get(diffeq_bundle<num_type, T, Ts...> & db) {
		diffeq_bundle<num_type, Ts...> & base = db;
		return get<k-1>(base);
	}

	template<size_t k, typename num_type, template<typename> class... Ts>
	typename std::enable_if<
		k == 0, 
		typename bundle_type<0, num_type, Ts...>::type&>::type
		
		get(diffeq_bundle<num_type, Ts...> & db) {
		return db.tail;
	}
	

	



}

#endif