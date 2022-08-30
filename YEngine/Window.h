#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"



namespace YEngine {
	namespace Core {
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;


		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		class Window {
		public: 
			Window(const Window&) = delete;
			inline static Window& getActiveWindow(){
				return m_activeWindow;
			};
			int initCore();
			void run();
			void setKeyState(int, bool);
			
		private:
			
			Window() {};
			void processEvents();
		private:
			bool m_keyState[266];
			GLFWwindow* m_window;
			static Window m_activeWindow;
			

		};
	}
}

