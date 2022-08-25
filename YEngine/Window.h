#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>



namespace Yengine {
	namespace Core {
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;

		enum class shaderType {

			VERTEX_SHADER,
			FRAGMENT_SHADER
		};
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		class Window {
		public: 
			Window(const Window&) = delete;
			inline static Window& getActiveWindow() {
				return activeWindow;
			};
			int initCore();
			void run();
			void setKeyState(int, bool);
		private:
			
			Window() {};
			int loadShaderSource(shaderType type, const std::string& filename);
			void processEvents();
		private:
			bool keyState[266];
			std::unordered_map <shaderType, std::string> shaderSource;
			GLFWwindow* window;
			static Window activeWindow;
			

		};
	}
}

