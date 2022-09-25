
#include <iostream>
// GLEW

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include<SOIL2.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
bool keys[1024];
GLfloat lastX = 400;
GLfloat lastY = 300;
bool isFirst = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void Do_Movement();
// Camera
YEngine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));



int main() {

   
    

    if (!glfwInit()) {

        std::cout << "glfw failed to iniitialize" << std::endl;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Learn open Gl", nullptr, nullptr);

    if (window == nullptr) {

        std::cout << "glfw failed to iniitialize" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {

        std::cout << "glew failed to initialize" << std::endl;
        return -1;

    }
    glViewport(0, 0, 1280, 720);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //configure how opengl draws its primitives
//making sure thath each sampler is in the proper location


    YEngine::Resource& resource = YEngine::Resource::getHandle();
    resource.init();
    YEngine::Shader shader(YEngine::shaderType::BASE_VERTEX_SHADER, YEngine::shaderType::BASE_FRAGMNET_SHADER);
    YEngine::Model loadedModel("res/models/nanosuit/nanosuit.obj");

    glm::vec3 pointLightPositions[] = {
    glm::vec3(2.3f, -1.6f, -3.0f),
    glm::vec3(-1.7f, 0.9f, 1.0f)
    };

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    //material 
    while (!glfwWindowShouldClose(window)) {

        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        Do_Movement();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.useProgram();   // <-- Don't forget this one!


        glm::mat4 projection = glm::perspective(camera.m_zoom, 1280.0f/720.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix(); 
        shader.setMat4fv(projection, "projection");
        shader.setMat4fv(view,"view");
        shader.setVec3f(camera.m_position,"viewPos");

        shader.setVec3f(pointLightPositions[0], "pointLights[0].position");
        shader.setVec3f(glm::vec3(0.05f, 0.05f, 0.05f), "pointLights[0].ambient");
        shader.setVec3f(glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[0].diffuse");

        shader.setVec3f(glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[0].specular");
        shader.setScalar1f(1.0f, "pointLights[0].constant");
        shader.setScalar1f(0.009f, "pointLights[0].linear");
        shader.setScalar1f(0.0032f, "pointLights[0].quadratic");
 	
        // Point light 2
        shader.setVec3f(pointLightPositions[1], "pointLights[1].position");
        shader.setVec3f(glm::vec3(0.05f, 0.05f, 0.05f), "pointLights[1].ambient");
        shader.setVec3f(glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[1].diffuse");

        shader.setVec3f(glm::vec3(1.0f, 1.0f, 1.0f), "pointLights[1].specular");
        shader.setScalar1f(1.0f, "pointLights[1].constant");
        shader.setScalar1f(0.009f, "pointLights[1].linear");
        shader.setScalar1f(0.0032f, "pointLights[1].quadratic");
  
#if 0
        shader.setVec3f(camera.m_position, "viewPos");
        shader.setVec3f(glm::vec3(-0.2f, -1.0f, -0.3f), "dirLight.direction");
        shader.setVec3f(glm::vec3(0.0f), "dirLight.ambient");
        shader.setVec3f(glm::vec3(0.8f), "dirLight.diffuse");
        shader.setVec3f(glm::vec3(0.2f), "dirLight.specular");
#endif // 0
        

        // Draw the loaded model
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model,glm::vec3(0.2f,0.2f,0.2f));
        model = glm::rotate(model,(float)glfwGetTime()*30.0f,glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4fv(model,"model");
        loadedModel.Draw(&shader);
        // Swap the buffers
        glfwSwapBuffers(window);



    }
    glfwTerminate();
    return 0;
}
void Do_Movement()
{
    // Camera controls
    if (keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(YEngine::FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(YEngine::BACKWARD, deltaTime);
    if (keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(YEngine::LEFT, deltaTime);
    if (keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(YEngine::RIGHT, deltaTime);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //cout << key << endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;
    if (!isFirst)
        camera.ProcessMouseMovement(xoffset, yoffset);
    else
        isFirst = false;
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}