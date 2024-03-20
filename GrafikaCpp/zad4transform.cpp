#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"    gl_Position = model * vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

const GLchar* fragmentShaderSource =
// fragment shader
"#version 330 core\n" // wersja GLSL
"in vec3 Color; \n"// deklaracja wejscia (kolor)
"out vec4 outColor; \n"// deklaracja wyjscia (kolor)
"uniform vec3 uColor = vec3(1.0, 1.0, 1.0); \n" //uniform-zmienna globalna shaderow, mozna modyfikowac 
"void main() { \n"
"    outColor = vec4(uColor, 1.0);\n"
"} \0";

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

    
    // vertex data
    GLfloat vertices[] = {
        // coordinates          // colors
        0.0f,  0.8f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1 vertex 1, triangle 2 vertex 1
        -0.4f, -0.2f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1   vertex 2
         0.4f, -0.2f, 0.0f,     1.0f, 0.0f, 0.0f, // triangle 1 vertex 3, triangle 2 vertex 2
        
    };

    GLuint indices[] = {
        0, 1, 2,    // triangle 1
    };
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // uniforms
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint uColorLocation = glGetUniformLocation(shaderProgram, "uColor"); //musimy zlokalizowa? (pobra? ID) wektor uColor


    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // p?tla zdarze?
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // transformations
        //1 gorny lewy obraca sie dookola
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(uColorLocation, 0.0f, 1.0f, 0.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //2 dolny lewy w linii chodzi
        glm::mat4 model2 = glm::mat4(1.0f);  
        model2 = glm::translate(model2, glm::vec3(cos(glfwGetTime()) * 0.2 - 0.4, -0.4f, 0.0));
        model2 = glm::rotate(model2, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = glm::scale(model2, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
        glUniform3f(uColorLocation, 0.0f, 1.0f, 1.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //trojkat 3 skalowanie
        float zmienna = (sin(glfwGetTime()) + 2.0f) * 0.2f; //+ wieksze od 1 zeby nie znikalo a 0.2 mniejszy zakres
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(0.4f, 0.4f, 0.0f));
        model3 = glm::rotate(model3, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model3 = glm::scale(model3, glm::vec3(zmienna, zmienna, zmienna));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
        glUniform3f(uColorLocation, 1.0f, 1.0f, 0.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //trojkat 4 wszystkie funkcje
        glm::mat4 model4 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(0.4f, -0.4f, 0.0f));
        model4 = glm::translate(model4, glm::vec3(sin(glfwGetTime())*0.2 +0.4, -0.4f, 0.0f));
        model4 = glm::rotate(model4, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        model4 = glm::scale(model4, glm::vec3(zmienna, zmienna, zmienna));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
        glUniform3f(uColorLocation, 1.0f, 0.0f, 1.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        //
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