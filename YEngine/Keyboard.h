#pragma once
#include "Event.h"
#include <iostream>
namespace YEngine {
	class Keyboard : public YEngine::Event
	{
	private:
		bool* keyInfo;
	public:
		static constexpr eventType type = "keyboard";
		
	public:

		Keyboard(bool *info):keyInfo(info){}
		~Keyboard() {  };
		const eventType& getType() const override {
			return type;
		}
	    
		virtual const bool* getKeyData() const override {

			return keyInfo;
		}
	
	};

}
