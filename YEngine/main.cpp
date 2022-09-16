
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
#include "Resource.h"
#include "Shader.h"
#include "Texture.h"

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
bool keys[1024];
GLfloat lastX = 400;
GLfloat lastY = 300;
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn open Gl", nullptr, nullptr);

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
    glViewport(0, 0, 800, 600);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //configure how opengl draws its primitives
//making sure thath each sampler is in the proper location

    GLfloat vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    GLuint indices[] = {

        0,1,2,
        3,0,2

    };
    glm::vec3 pos[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    glm::vec3 pointLightColors[] = {
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.3f, 0.1f, 0.1f)
    };

    YEngine::Resource& resource = YEngine::Resource::getHandle();
    resource.init();

    YEngine::Shader lightingShader(YEngine::shaderType::VERTEX_SHADER,  YEngine::shaderType::FRAGMENT_SHADER);
    YEngine::Shader lampShader(YEngine::shaderType::VERTEX_SHADER, YEngine::shaderType::LIGHT_FRAGMENT_SHADER);
    // diffuse map  specular map
    YEngine::Texture diffuse("res/textures/container2.png","material.diffuse");
    YEngine::Texture specular("res/textures/container2Specular.png", "material.specular");
    YEngine::Texture emisson("res/textures/matrix.jpg","material.emission");
    
    
    diffuse.attachTexture(&lightingShader);
    specular.attachTexture(&lightingShader);
    emisson.attachTexture(&lightingShader);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint vao[2];
    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[0]);

    //configure attrib pointers for vao1

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(vao[1]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);



    // dont forget to use the shader before settinhg a uniform

    // send the ligthposition for difuse calculations
    lightingShader.useProgram();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    //material 
    diffuse.bindTexture();
    specular.bindTexture();
    emisson.bindTexture();
    while (!glfwWindowShouldClose(window)) {

        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        Do_Movement();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
        
        // lightPos.x = sin(glfwGetTime())*5.0f;
        // lightPos.y = sin(glfwGetTime()) * 5.0f;
        // lightPos.z = cos(glfwGetTime())*5.0f;


      
        lightingShader.useProgram();
        glm::mat4 model;
        glm::mat3 normalMatrix;
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 proj = glm::perspective(camera.m_zoom, (GLfloat)(800) / (GLfloat)(600), 0.1f, 100.0f);

        lightingShader.setVec3f(camera.m_position, "viewPos");
        lightingShader.setMat4fv(view, "view");
        lightingShader.setMat4fv(proj, "projection");

    
        lightingShader.setScalar1f(32.0f, "material.shiny");
        // material end
        // lights
        lightingShader.setVec3f(glm::vec3(-0.2f, -1.0f, -0.3f), "dirLight.direction");
        lightingShader.setVec3f(glm::vec3(0.0f), "dirLight.ambient");
        lightingShader.setVec3f(glm::vec3(0.05f), "dirLight.diffuse");
        lightingShader.setVec3f(glm::vec3(0.2f), "dirLight.specular");
        //pointLights
         // Point light 1
        lightingShader.setVec3f(pointLightPositions[0], "pointLights[0].position");
        lightingShader.setVec3f(pointLightColors[0]*0.1f, "pointLights[0].ambient");
        lightingShader.setVec3f(pointLightColors[0], "pointLights[0].diffuse");
        lightingShader.setVec3f(pointLightColors[0], "pointLights[0].specular");
        lightingShader.setScalar1f(1.0f, "pointLights[0].constant");
        lightingShader.setScalar1f(0.14f, "pointLights[0].linear");
        lightingShader.setScalar1f(0.07f, "pointLights[0].quadratic");
        // lights end
                 // Point light 2
        lightingShader.setVec3f(pointLightPositions[1], "pointLights[1].position");
        lightingShader.setVec3f(pointLightColors[1] * 0.1f, "pointLights[1].ambient");
        lightingShader.setVec3f(pointLightColors[1], "pointLights[1].diffuse");
        lightingShader.setVec3f(pointLightColors[1], "pointLights[1].specular");
        lightingShader.setScalar1f(1.0f, "pointLights[1].constant");
        lightingShader.setScalar1f(0.14f, "pointLights[1].linear");
        lightingShader.setScalar1f(0.07f, "pointLights[1].quadratic");

        // lights end
                 // Point light 3
        lightingShader.setVec3f(pointLightPositions[2], "pointLights[2].position");
        lightingShader.setVec3f(pointLightColors[2] * 0.1f, "pointLights[2].ambient");
        lightingShader.setVec3f(pointLightColors[2], "pointLights[2].diffuse");
        lightingShader.setVec3f(pointLightColors[2], "pointLights[2].specular");
        lightingShader.setScalar1f(1.0f, "pointLights[2].constant");
        lightingShader.setScalar1f(0.14f, "pointLights[2].linear");
        lightingShader.setScalar1f(0.07f, "pointLights[2].quadratic");
        // lights end
                 // Point light 4
        lightingShader.setVec3f(pointLightPositions[3], "pointLights[3].position");
        lightingShader.setVec3f(pointLightColors[3] * 0.1f, "pointLights[3].ambient");
        lightingShader.setVec3f(pointLightColors[3], "pointLights[3].diffuse");
        lightingShader.setVec3f(pointLightColors[3], "pointLights[3].specular");
        lightingShader.setScalar1f(1.0f, "pointLights[3].constant");
        lightingShader.setScalar1f(0.14f, "pointLights[3].linear");
        lightingShader.setScalar1f(0.07f, "pointLights[3].quadratic");
        //spotLight
        lightingShader.setVec3f(camera.m_position, "spotLight.position");
        lightingShader.setVec3f(camera.m_front, "spotLight.direction");
        lightingShader.setVec3f(glm::vec3(0.0f), "spotLight.ambient");
        lightingShader.setVec3f(glm::vec3(1.0f), "spotLight.diffuse");
        lightingShader.setVec3f(glm::vec3(1.0f), "spotLight.specular");
        lightingShader.setScalar1f(1.0f, "spotLight.constant");
        lightingShader.setScalar1f(0.009f, "spotLight.linear");
        lightingShader.setScalar1f(0.0032f, "spotLight.quadratic");
        lightingShader.setScalar1f(glm::cos(glm::radians(10.0f)), "spotLight.cutOff");
        lightingShader.setScalar1f(glm::cos(glm::radians(18.5f)), "spotLight.outerCutOff");
        // lights end
        glBindVertexArray(vao[0]);
        for (GLuint i = 0; i < 10; i++) {
            
            glm::mat4 modelObj;
            modelObj = glm::translate(modelObj, pos[i]);
            GLfloat angle = 20.0f * i;
            modelObj = glm::rotate(modelObj, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelObj)));
            lightingShader.setMat3fv(normalMatrix, "normalMatrix");
            lightingShader.setMat4fv(modelObj, "model");
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
       
        glBindVertexArray(0);

        lampShader.useProgram();

        lampShader.setMat4fv(view, "view");
        lampShader.setMat4fv(proj, "projection");
        glBindVertexArray(vao[1]);
        for (int i = 0; i < 4; i++) {
            model = glm::mat4();
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lampShader.setMat4fv(model, "model");
            lampShader.setVec3f(pointLightColors[i],"lampColor");
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
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
    if (keys[GLFW_KEY_DOWN])
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}