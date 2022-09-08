
#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <GLFW/glfw3.h>
#include "Event.h"
#include "Keyboard.h"
#if 0
namespace YEngine {



	class EventManager
	{
	public:
		using  slot = std::function<void(const Event&, GLfloat)>;

		EventManager(const EventManager&) = delete;
		void subscribe(const Event::eventType&, slot&&);
		void unSubscribe();
		void post(const Event&) const;
		void processEvent(GLfloat delta);
		void init(GLfloat m_cursorX, GLfloat m_cursorY, GLFWwindow* m_window);
		inline constexpr static EventManager& getHandle() {

			return m_managerInstance;
		}
		inline void setKeys(int key, bool state) {
			if (key < 1024)
				m_keys[key] = state;

		}
		inline void setCursor(GLfloat cursorX, GLfloat cursorY) {

			m_cursorX = cursorX;
			m_cursorY = cursorY;
		}
		inline constexpr std::tuple<GLfloat, GLfloat> getCursor() {

			return { m_cursorX, m_cursorY };
		}
		inline constexpr bool* getKeyinfo() {

			return m_keys;
		}
	private:
		EventManager() {};
		bool m_keys[1024];
		GLfloat m_cursorX;
		GLfloat m_cursorY;
		GLfloat m_delta;
		GLFWwindow* m_window;
		std::unordered_map<Event::eventType, std::vector<slot>> m_observers;
		static EventManager m_managerInstance;

	};
}


#endif // 
