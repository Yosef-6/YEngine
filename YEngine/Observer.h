#pragma once
#include "Event.h"

namespace YEngine {
	class Observer
	{
	public :
		virtual ~Observer() {};
		virtual void handle(const Event& e,GLfloat delta) = 0;
	};
}
