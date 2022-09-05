#pragma once
#include <GLFW/glfw3.h>
#include <tuple>
namespace YEngine {
	class Event
	{
	public :
		using eventType = const char*;
		virtual ~Event() {};
		virtual const bool* getKeyData()const { return nullptr; }
		virtual const eventType& getType() const = 0;
	
		virtual const std::tuple<GLfloat, GLfloat> getCursorData() const { return { 0.0f,0.0f };}
		virtual const std::tuple<GLfloat, GLfloat> getScrollData() const { return {0.0f,0.0f}; }
	};

}