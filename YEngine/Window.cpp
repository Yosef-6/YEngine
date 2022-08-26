#include "Window.h"


YEngine::Core::Window YEngine::Core::Window::activeWindow;
int  YEngine::Core::Window::initCore() {

    if (!glfwInit()) {

        std::cout << "glfw failed to iniitialize" << std::endl;
        return 0;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << " Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    loadShaderConf("res/shader/base.shader");




    return 1;
}
void YEngine::Core::Window::run() {

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

void YEngine::Core::Window::setKeyState(int key, bool state)
{
    keyState[key] = state;
}

const std::string& YEngine::Core::Window::getShaderSource(shaderType type) const
{
    if (shaderSource.find(type) != shaderSource.end())
        return shaderSource.at(type);
    return "";
}

int YEngine::Core::Window::loadShaderConf(const std::string& filename) {
 

    std::ifstream file(filename);
    std::stringstream source;
    std::string buffer;
    shaderType currentShader = shaderType::NONE;
    if (file.is_open()) {

        while (std::getline(file,buffer)) {
            
            if (buffer.find("#shader") != std::string::npos) {
                
                if (currentShader != shaderType::NONE) {

                    shaderSource[currentShader] = source.str();
                    currentShader = shaderType::NONE;
                    source.str(std::string());
                }

                if (buffer.find("vertex") != std::string::npos)
                    currentShader = shaderType::VERTEX_SHADER;
                else if (buffer.find("fragment") != std::string::npos)
                    currentShader = shaderType::FRAGMENT_SHADER;
                else if(buffer.find("end") != std::string::npos)
                    break;
                
            }
            else
            source << buffer << '\n';
            
        }
        file.close();
        
        std::cout << " loaded ->"<<filename<< std::endl;
        return 1;
    }
        std::cout <<"unable to open file:"<<filename << std::endl;
        return 0;
}
void YEngine::Core::Window::processEvents()
{
    if (keyState[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void YEngine::Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // temporary
    using namespace YEngine::Core;
    Window& activeWindow = Window::getActiveWindow();
    if (key <= 265) 
       activeWindow.setKeyState(key, (bool)action);

}

