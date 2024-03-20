
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>


const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"layout(location = 2) in vec2 texture;\n"
"out vec3 vertexColor;\n"
"out vec2 vertexTexture;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"    vertexTexture = texture;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 vertexTexture;\n"
"out vec4 fragmentColor;\n"
"uniform sampler2D uTexture;\n"

"uniform vec3 uColor = vec3(1.0, 1.0, 1.0);\n"
"void main()\n"
"{\n"
//"    fragmentColor =texture(uTexture, vertexTexture) * vec4(vertexColor, 1.0);\n"
"fragmentColor = mix(texture(uTexture, vertexTexture), vec4(0.0, 0.0, 1.0, 1.0), uColor.x); \n"
"}\0";

int n;
void kwadrat() {

    GLfloat vertices[] = {
        // coordinates          // colors           // texture coordinates
        0.2f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // gorny lewy
        0.2f, -0.7f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // dolny lewy
         0.8f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // gorny prawy
         0.8f,  -0.7f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f  // dolny prawy

    };
    GLuint indices[] = {
    0, 1, 3,    // triangle 1
    0, 3, 2 // triangle 2

    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
}
void trojkat() {

    GLfloat vertices[] = {
        // coordinates          // colors           // texture coordinates
      -0.5f,  0.7f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // triangle 1 vertex 1, triangle 2 vertex 1
      -0.5f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // triangle 1 vertex 2
       -0.8f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // triangle 1 vertex 3, triangle 2 vertex 2
       -0.2f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f  // triangle 2 vertex 3


    };
    GLuint indices[] = {

       0, 2, 1,
        0, 3, 1

    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //delete[] vertices;
    //delete[] indices;

}
void processInputKeyboard(GLFWwindow* window) //zapytania polling
{
  
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        n=1;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
       n=2;
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
       n=3;
    }

}

float intensywnosc;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) {
        intensywnosc += 0.05;
    }
    else if (yoffset < 0) {
        if (intensywnosc <= 0) {
            intensywnosc = 0;
        }
        intensywnosc -= 0.05;
    }

}


int main()
{
    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Tworzenie okna
    const unsigned int window_width = 1000;
    const unsigned int window_height = 800;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // shadery
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
        std::cout << "Error (Vertex shader): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
        std::cout << "Error (Fragment shader): " << error_message << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();

    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, error_message);
        std::cout << "Error (Shader program): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glfwSetScrollCallback(window, scroll_callback);

    // texture kwadrat
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load("image/first.jpg", &width, &height, &nrChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
   
   
    //texture trojkat

    int width2, height2, nrChannels2;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data2 = stbi_load("image/second.jpg", &width2, &height2, &nrChannels2, 0);
  
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

    GLint uColorLocation = glGetUniformLocation(shaderProgram, "uColor"); //musimy zlokalizowa? (pobra? ID) wektor uColor
    

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
   

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);



    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // p?tla zdarzen
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       // glBindTexture(GL_TEXTURE_2D, texture);
        //glBindTexture(GL_TEXTURE_2D, texture2);
        processInputKeyboard(window);
        glUseProgram(shaderProgram);

        glUniform3f(uColorLocation, intensywnosc, 0.0f, 1.0f);

        if (n == 1) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);
            kwadrat();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else if (n == 2) {
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(VAO);
            trojkat();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

        }
        else if (n == 3) {

            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);
            kwadrat();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(VAO);
            trojkat();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
  
    glfwTerminate();
    return 0;
}