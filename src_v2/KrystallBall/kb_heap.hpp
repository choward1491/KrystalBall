#ifndef _kb_heap_
#define _kb_heap_

namespace kb {

	template<typename key_t>
	struct less_than {
		static inline bool compare(const key_t & k1, const key_t & k2) { return k1 < k2; }
	};

	template<typename key_t, typename data_t, unsigned int buf = 50, template<typename> class compare_func = less_than >
	class heap {
	private:

		unsigned int		indices[buf];
		key_t				keys[buf];
		data_t				data[buf];
		unsigned int		used_space;

		void swapDown(unsigned int idx) {
			unsigned int ir = 0, il = 0, ib = 0, tmp = 0;

			while (true) {
				ir = 2 * (idx + 1);
				il = 2 * idx + 1;
				ib = 0;

				if (ir >= used_space && il >= used_space) { break; }
				else if (ir >= used_space) { ib = il; }
				else {
					if (compare_func<key_t>::compare(keys[indices[il]], keys[indices[ir]])) { ib = il; }
					else { ib = ir; }
				}

				if (compare_func<key_t>::compare(keys[indices[ib]], keys[indices[idx]])) {
					tmp				= indices[ib];
					indices[ib]		= indices[idx];
					indices[idx]	= tmp;
					idx				= ib;
				}
				else { break; }
			}
		}

		void push_helper(unsigned int idx) {
			
			unsigned int parent = 0, tmp = 0;
			while (idx != 0) {
				if (idx % 2 == 0)	{ parent = (idx - 2) / 2; }
				else				{ parent = (idx - 1) / 2; }

				if (compare_func<key_t>::compare(keys[indices[idx]],keys[indices[parent]]) ) {
					tmp					= indices[parent];
					indices[parent]		= indices[idx];
					indices[idx]		= tmp;
					idx					= parent;
				}
				else { break; }
			}
		}

	public:

		heap():used_space(0) {
			for (unsigned int i = 0; i < buf; ++i) { indices[i] = i; }
		}
		~heap() = default;

		bool empty() const { return !(used_space != 0); }
		void push( const key_t & k, const data_t & d ){
			keys[indices[used_space]]	= k;
			data[indices[used_space]]	= d;
			push_helper(used_space++);
		}

		void pushNoFixing(const key_t & k, const data_t & d) {
			keys[indices[used_space]]	= k;
			data[indices[used_space++]] = d;
		}

		void organize() {
			int ic = used_space / 2 - 1;
			for (; ic >= 0; ic--) { swapDown(ic); }
		}

		void pop() {
			unsigned int tmp	= indices[--used_space];
			indices[used_space] = indices[0];
			indices[0]			= tmp;
			swapDown(0);
		}

		inline const key_t & topKey()	const { return keyAt(indices[0]); }
		inline const data_t& topData()	const { return dataAt(indices[0]); }

		inline const data_t &	dataAt(int idx) const	{ return data[idx]; }
		inline data_t &			dataAt(int idx)			{ return data[idx]; }
		inline const key_t &	keyAt(int idx) const	{ return keys[idx]; }
		inline key_t &			keyAt(int idx)			{ return keys[idx]; }

		unsigned int size() const { return used_space; }
	};
}

#endif
