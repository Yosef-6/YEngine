#include "Window.h"


Yengine::Core::Window Yengine::Core::Window::activeWindow;
int  Yengine::Core::Window::initCore() {

    if (!glfwInit()) {

        std::cout << "glfw failed to iniitialize" << std::endl;
        return 0;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn open Gl", nullptr, nullptr);
    if (window == nullptr) {

        std::cout << "glfw failed to iniitialize" << std::endl;
        glfwTerminate();
        return 0;

    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {

        std::cout << "glew failed to initialize" << std::endl;
        return 0;

    }
    glViewport(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT);
    glfwSetKeyCallback(window, key_callback);

    loadShaderSource(shaderType::VERTEX_SHADER, "shaderSource/vertexShader.txt");
    loadShaderSource(shaderType::VERTEX_SHADER, "shaderSource/fragmentShader.txt");




    return 1;
}
void Yengine::Core::Window::run() {

    while (!glfwWindowShouldClose(window)) {

        processEvents();
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw calls here
        glfwSwapBuffers(window);

    }
        glfwTerminate();
}

void Yengine::Core::Window::setKeyState(int key, bool state)
{
    keyState[key] = state;
}

int Yengine::Core::Window::loadShaderSource(shaderType type, const std::string& filename) {
 

    std::ifstream file(filename);
    std::string source;
    std::string buffer;
    if (file.is_open()) {

        while (std::getline(file,buffer)) {
            source += buffer;
        }
        file.close();
        shaderSource[type] = source;
        std::cout << " loaded ->"<<filename<< std::endl;
        return 1;
    }
        std::cout <<"unable to open file:"<<filename << std::endl;
        return 0;
}
void Yengine::Core::Window::processEvents()
{
    if (keyState[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void Yengine::Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // temporary
    using namespace Yengine::Core;
    Window& activeWindow = Window::getActiveWindow();
    if (key <= 265) 
       activeWindow.setKeyState(key, (bool)action);


    

#if 0
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
#endif // 0

}

