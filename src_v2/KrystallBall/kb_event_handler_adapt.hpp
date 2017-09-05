
#ifndef _kb_event_handler_adapt_
#define _kb_event_handler_adapt_

#include "kb_discrete_model.hpp"
#include <queue>
#include <utility>

namespace kb {
	namespace adapt {

		template<typename key_t, typename event_t>
		class event_handler {
		public:
			typedef event_t Event;
			typedef key_t num_type;
			typedef std::pair<num_type, event_t*> event_p;

			event_handler() :event_list() {
				std::vector<event_p> v; v.reserve(512);
				event_list = min_heap(greater(), std::move(v));
			}

			// methods to add models to event handler
			void addEvent(Event & m, const num_type & current_time = num_type(0.0)) {
				event_p event_ = { m.nextTime(num_type(current_time)), &m };
				event_list.push(event_);
			}

			inline void organize() { }

			// method to init event handler each simulation run
			void reset(const std::vector<Event*> & events) {
				clear_list();
				for (unsigned int i = 0; i < events.size(); ++i) {
					addEvent(*events[i]);
				}
			}

			// method to get next event
			event_p popNextEvent() {
				event_p next_e = event_list.top();
				event_list.pop();
				return next_e;
			}

			// method to get next time
			const num_type &	getNextTime() const {
				return event_list.top().first;
			}

			unsigned int numEvents() const {
				return event_list.size();
			}
		private:
			struct greater {
				bool operator()(event_p & p1, event_p & p2) { return p1.first > p2.first; }
			};

			typedef std::priority_queue<event_p, std::vector<event_p>, greater> min_heap;
			min_heap event_list;

			void clear_list() { while (!event_list.empty()) { event_list.pop(); } }

		};
	}
}

#endif
