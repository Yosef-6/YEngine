#include "Window.h"

using namespace  YEngine::Core;
int main()
{   
    Window& window = Window::getActiveWindow();
   if (window.initCore()) {

       std::cout << " Core iniitialized" << std::endl;
       window.run();
   }

   
#if 0

    if (!glfwInit()) {

        std::cout << "glfw failed to iniitialize" << std::endl;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
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


    //vertex shader source
    std::string vertexSource =
        "#version 410 core\nlayout (location = 0)\nout vec4 vertexColor;  \nin vec3 position;\nvoid main(){gl_Position = vec4(position,1.0f);vertexColor = vec4(0.5, 0.0, 0.0, 1.0);}";
    const GLchar* vSource = vertexSource.c_str();
    //init vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSource, NULL);
    glCompileShader(vertexShader);
    //vertexshader compile log
    GLint vSuccess;
    GLchar vInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);


    if (!vSuccess) {

        glGetShaderInfoLog(vertexShader, 512, NULL, vInfoLog);
        std::cout << "SHADER::VERTEX::COMPILATION FAILED\n" << vInfoLog << std::endl;

    }
    //fragment shader source
    std::string fragmentShaderSource =
        "#version 410 core\nin vec4 vertexColor;\nout vec4 color;void main(){color = vertexColor;}\n";
    const GLchar* fSource = fragmentShaderSource.c_str();
    // init fragmentShader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSource, NULL);
    glCompileShader(fragmentShader);
    // fragment shader compile log
    GLint fSuccess;
    GLchar fInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);

    if (!fSuccess) {

        glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
        std::cout << "SHADER::FRAGMENT::COMPILATION FAILED\n" << fInfoLog << std::endl;

    }
    //shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check link process
    GLint linkSuccess;
    GLchar linkInfo[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess) {

        glGetProgramInfoLog(shaderProgram, 512, NULL, linkInfo);
        std::cout << "SHADER_PROGRAM::COMPILATION FAILED\n" << linkInfo << std::endl;

    }

    //we dont have a vertex shader that is simple thaths why we are writing directly to the normalized device coordinates
    GLfloat vertices[] = {

        0.5f,  0.5f, 0.0f, // Top Right
        0.5f, -0.5f, 0.0f, // Bottom Right
       -0.5f, -0.5f, 0.0f, // Bottom Left
       -0.5f,  0.5f, 0.0f  // Top Left

    };
    GLuint indices[] = {

        0,1,3,
        1,2,3
    };
    // generate a vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // vertex data
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //the 4th param describes how we want the graphics card to manage the given data
    //GL_STATIC_DRAW
    //GL_DYNAMIC_DRAW
    //GL_STREAM_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //create ELement buffer obj
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




    // telling open gl how to interpreat the vertex attributes
    //the last parammater is the offset to witch vertex attribute begins in the buffer for now this is o
    // The vertex shader thus requires an extra layout specification for its inputs so
   // we can link it with the vertex data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
    //vertex attribute 0 is now associated with its vertex data. since our  vbo is currently bound to GL_ARRAY_BUFFER
    //enable vertex attribute vertex attributes are disabled by default.
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // unbind the vao configured
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vbo used for current object  and  vertex attrib conofiguration
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO); // we can delete both 2 buffers there interna context is stored inside vao non need to keep them inside v
    glDeleteBuffers(1, &ebo);

    // ..::Drawing code(in Game loop) :: ..
    // 5. Draw the object
   //  glUseProgram(shaderProgram);
   //  glBindVertexArray(VAO);
   //  someOpenGLFunctionThatDrawsOurTriangle();
  ///  glBindVertexArray(0);

    // delete shaders no longer need them b/c there copid to shader program object
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //configure how opengl draws its primitives
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);

    }
    glfwTerminate();

#endif // 0





    return 0;
}