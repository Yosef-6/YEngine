
#include "EventManager.h"

#if 0
YEngine::EventManager YEngine::EventManager::m_managerInstance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    using namespace YEngine;
    EventManager& handle = EventManager::getHandle();
    if (action == GLFW_PRESS)
        YEngine::EventManager::getHandle().setKeys(key, true);
    else if (action == GLFW_RELEASE)
        YEngine::EventManager::getHandle().setKeys(key, false);

    handle.post(Keyboard(handle.getKeyinfo()));
};
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    using namespace YEngine;
    EventManager& handle = EventManager::getHandle();
    GLfloat xoffset = xpos - std::get<0>(handle.getCursor());
    GLfloat Yoffset = std::get<1>(handle.getCursor()) - ypos;
    handle.setCursor(xpos, ypos);


}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{


}


void YEngine::EventManager::subscribe(const Event::eventType& type, slot&& slot)
{
    m_observers[type].pus(slot);
}

void YEngine::EventManager::unSubscribe()
{

}

void YEngine::EventManager::post(const Event& e) const
{
    if (m_observers.find(e.getType()) != m_observers.end()) {

        auto&& observers = m_observers.at(e.getType());
        for (auto&& observer : observers) {
            observer(e, m_delta);
        }
    }

}

void YEngine::EventManager::processEvent(GLfloat delta)
{
    m_delta = delta;
    glfwPollEvents();

}
void YEngine::EventManager::init(GLfloat m_cursorX, GLfloat m_cursorY, GLFWwindow* m_window)
{
    glfwSetKeyCallback(m_window, key_callback);
    this->m_cursorX = m_cursorX;
    this->m_cursorY = m_cursorY;
    this->m_window = m_window;
}




#endif // 
