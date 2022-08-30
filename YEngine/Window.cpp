#include "Window.h"


YEngine::Core::Window YEngine::Core::Window::m_activeWindow;


int  YEngine::Core::Window::initCore() {

    if (!glfwInit()) {

        std::cerr << "glfw failed to iniitialize\n";;
        return 0;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn open Gl", nullptr, nullptr);
    if (m_window == nullptr) {
       
        std::cerr << " failed to retrive an active opengl context \n";
        glfwTerminate();
        return 0;

    }
    glfwMakeContextCurrent(m_window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {

        std::cerr << "glew failed to initialize\n";
        return 0;

    }
    glViewport(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT);
    glfwSetKeyCallback(m_window, key_callback);

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout<< " Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    
    // there should be a resource manager 
    YEngine::Graphics::Resource& resource = YEngine::Graphics::Resource::getResourceHandle();
    resource.init();



    return 1;
}
void YEngine::Core::Window::run() {
    using namespace YEngine::Graphics;
    Shader m_shader(shaderType::VERTEX_SHADER,shaderType::FRAGMENT_SHADER);

    while (!glfwWindowShouldClose(m_window)) {

        processEvents();
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw calls here
        m_shader.useProgram();
       
        glfwSwapBuffers(m_window);

    }
        glfwTerminate();
}

void YEngine::Core::Window::setKeyState(int key, bool state)
{
    m_keyState[key] = state;
}

void YEngine::Core::Window::processEvents()
{
    if (m_keyState[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(m_window, GL_TRUE);
}
void YEngine::Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // temporary
    using namespace YEngine::Core;
    Window& activeWindow = Window::getActiveWindow();
    if (key <= 265) 
       activeWindow.setKeyState(key, (bool)action);

}

