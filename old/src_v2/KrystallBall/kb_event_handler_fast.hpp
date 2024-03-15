
#ifndef _kb_event_handler_fast_
#define _kb_event_handler_fast_

#include "kb_heap.hpp"
#include <utility>
#include <vector>

namespace kb {
	namespace fast {
		template<typename key_t, typename event_t, unsigned int buf = 50>
		class event_handler {
		public:
			typedef event_t Event;
			typedef key_t num_type;
			typedef std::pair<num_type, event_t*> event_p;
			typedef heap<key_t, event_t*, buf> min_heap;

			event_handler() = default;

			// methods to add models to event handler
			inline void addEvent(Event & m, const num_type & current_time = num_type(0.0)) {
				event_list.pushNoFixing(m.nextTime(num_type(current_time)), &m);
			}

			inline void organize() { event_list.organize(); }

			// method to init event handler each simulation run
			inline void reset(const std::vector<Event*> & events) {
				clear_list();
				for (unsigned int i = 0; i < events.size(); ++i) {
					addEvent(*events[i]);
				}
				organize();
			}

			// method to get next event
			event_p				popNextEvent() {
				event_p next_e = { event_list.topKey(), event_list.topData() };
				event_list.pop();
				return next_e;
			}

			// method to get next time
			inline const num_type &	getNextTime() const {
				return event_list.topKey();
			}

			inline unsigned int numEvents() const {
				return event_list.size();
			}
		private:
			min_heap event_list;
			void clear_list() { while (!event_list.empty()) { event_list.pop(); } }
		};
	}
}

#endif

