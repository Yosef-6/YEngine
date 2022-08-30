#include "Window.h"
#include "Graphics.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace  YEngine::Core;
int main()
{




    #if 0
        Window& window = Window::getActiveWindow();
        if (window.initCore()) {

            window.run();

        }
    #endif
   

#if 1

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

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans;

    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

    vec = trans * vec;
   
    std::cout << vec.x << vec.y << vec.z << vec.w << std::endl;



    //vertex shader source
    std::string vertexSource =
        "#version 410 core\nlayout (location = 0) in vec3 position;\nlayout (location = 1) in vec3 color;\nlayout (location = 2) in vec2 texCoord;\nout vec3 ourColor;\nout vec2 TexCoord;\nuniform vec4 c;  \nvoid main(){gl_Position = vec4(position.xyz,1.0f);ourColor=color;TexCoord=vec2(1.0f-texCoord.x,texCoord.y);}";
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
        "#version 410 core\nin vec3 ourColor;\nin vec2 TexCoord;\nuniform sampler2D ourTexture1;\nuniform vec4 c;\nuniform sampler2D ourTexture2;\nout vec4 color;void main(){color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),c.y);}\n";
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


     //feeding unifom values
    GLfloat greenValue = (sin(glfwGetTime())) / 2 + 0.5;
    GLint vloc = glGetUniformLocation(shaderProgram,"c");
    
    // check link process
    GLint linkSuccess;
    GLchar linkInfo[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess) {

        glGetProgramInfoLog(shaderProgram, 512, NULL, linkInfo);
        std::cout << "SHADER_PROGRAM::COMPILATION FAILED\n" << linkInfo << std::endl;

    }

    
    int width, height;
    unsigned char* image = SOIL_load_image("res/textures/container.jpg", &width, &height,0, SOIL_LOAD_RGB);
    std::cout << width << "  " << height << std::endl;
    GLuint texture[2];
    glGenTextures(2, texture);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    
    // specify texure wraping
   // OpenGL will set its texture wrapping option on the currently active texture with
   // GL_MIRRORED_REPEAT 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // for gl_clamp_to_edge
    //
    //float color[] = { 1.0f,1.0f,0.0f,1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

    //filtering method for mag and minfying operations
    // when a texel covers more than one pixel(texure coorinate) then magnification is occuring 
    //the texures mag filtering is used
    //texel/pixel <1
    // one pixel contains more than one texel thisi is minification
    //texures min filter is used
    //When not setting the min filter   Instead the default of GL_NEAREST_MIPMAP_LINEAR and expects minmaap texure layers
    // GL_TEXTURE_MAG_FILTER doesn't have mipmapping modes and when you don't set it, it uses the default of GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
    


    // generating a texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
    width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    glGenerateMipmap(GL_TEXTURE_2D);

    //
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    int width2, height2;
    image = SOIL_load_image("res/textures/awesomeface.png", &width2, &height2, 0, SOIL_LOAD_RGB);
    std::cout << width2 << "  " << height2 << std::endl;

    
   
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
    width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    //we dont have a vertex shader that is simple thaths why we are writing directly to the normalized device coordinates
   
   // glDeleteTextures(2,texture); delete textures allocated stored 
    
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,1- 1.0f,  // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f,1- 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f,1- 0.0f, //  Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,1- 1.0f //   Top Left
    };


    GLuint indices[] = {

        0,1,2,
        3,0,2
      
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);  // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3* sizeof(GLfloat)));  // color
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));  // texcoords
    //vertex attribute 0 is now associated with its vertex data. since our  vbo is currently bound to GL_ARRAY_BUFFER
    //enable vertex attribute vertex attributes are disabled by default.
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

   




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
    std::cout << vertexSource;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //configure how opengl draws its primitives
    //making sure thath each sampler is in the proper location
  
   
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
      
        glUseProgram(shaderProgram);

        //the gl bind texture will send texture to active texture unit (location 0) sampler
       // to send multiple textures first we must activate textre unit then bind the texture 
      //  we can activate texture units using glActiveTexture passing in the texture unit we’d like to use :
     //   Texture unit GL_TEXTURE0 is always by default activated
        //glBindTexture(GL_TEXTURE_2D, texture);
       
#if 0
        using namespace YEngine::Graphics;
        const char* textures[] = { "res/textures/awesomeface.png","res/textures/container.jpg" };
        Resource::getResourceHandle().init();
        Shader shader(shaderType::VERTEX_SHADER, shaderType::FRAGMENT_SHADER);
        Texture tex(textures, 2);
        GLfloat greenValue = (sin(glfwGetTime())) / 2 + 0.5;
        GLint vloc = glGetUniformLocation(shader.getProgram(), "c");
        std::cout << vloc << std::endl;
#endif // 0


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

        glUniform4f(vloc, 0.0f, greenValue, 0.5f, 1.0f);
        greenValue = (sin(glfwGetTime())) / 2 + 0.5;
       
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);

    }
    glfwTerminate();

#endif // 0





    return 0;
}