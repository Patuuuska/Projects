#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <cmath>
#include <math.h>
#include <vector>
#include <cstdlib>
#define M_PI 3.1415926f
using namespace std;


// Vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * model * vec4(position.x, position.y, 0.0f, 1.0);\n"
"}\0";

// Fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"uniform vec4 uColor;\n"
"void main()\n"
"{\n"
"   FragColor = uColor;\n"
"}\0";

const unsigned int window_width = 1000;
const unsigned int window_height = 800;

void processInputKeyboard(GLFWwindow* window);
void krawedz(GLuint shader);

float deltaTime = 0.0f;
const float r = 0.7f;

// pozycja
float pozX = 0.0f;
float pozY = 0.0f;

float sX = 0.0f;
float sY = 0.0f;

// kolor
float colorR = 0.3f;
float colorG = 0.5f;
float colorB = 0.7f;
float color2 = 0.5f;


int main()
{

    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Tworzenie okna
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    //fragment

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

    //kolo
    int n = 100;
    GLfloat promien = 1.0f;
    GLfloat roznica_kata = (2 * M_PI) / (n - 2);
    GLfloat temp_kat = 0.0f;
    //tablica z wierzcholkami
    GLfloat* vertices = new GLfloat[n * 3];

    for (int i = 0; i < n * 3; i++)
        vertices[i] = 0.0f;

    for (int i = 3; i < n * 3; i += 3) {
        vertices[i] = promien * cos(temp_kat);
        vertices[i + 1] = promien * sin(temp_kat);
        vertices[i + 2] = 0.0f;
        temp_kat += roznica_kata;
    }
    //tablica kolejnosci wiezrcholkow
    GLuint* indices = new GLuint[n * 3];

    for (int i = 0; i < n * 3; i += 3) {
        indices[i] = 0;
        indices[i + 1] = 1 + (i / 3);
        indices[i + 2] = 2 + (i / 3);
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * n * 3, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    float previousTime = 0.0f; //znacznik czsu rozpoczecia poprzeniej klatki
    double fpss = 0;
    float timef = 1.0f;
    int fps = 0;

    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);
    glfwSetTime(0.0); //znacznik czasu - ile uplynelo od wejscia w petle zdarzen
   
    srand(time(NULL));

    // pêtla g³ówna
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        fpss++;

        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //ustawianie koloru 
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniform4f(glGetUniformLocation(shaderProgram, "uColor"), colorR, colorG, colorB, color2);


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pozX, pozY, 0.0f));
        model = glm::scale(model, glm::vec3(50.0f, 50.0f, 0.0f));
        glm::mat4 projection;
        projection = glm::ortho(0.0f, static_cast<float>(window_width), 0.0f, static_cast<float>(window_height), -1.0f, 1.0f);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glDrawElements(GL_TRIANGLES, n * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        if (fpss == 0) {
            deltaTime = 1.0f;
        }
        pozX += sX * deltaTime;
        pozY += sY * deltaTime;

        krawedz(shaderProgram);

        processInputKeyboard( window);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (currentTime - timef > 1) {
            fps = fpss;
            timef = currentTime;
            fpss = 0;
            const int bufferSize = 256; // Rozmiar bufora na nowy tytu? okna
            char new_title[bufferSize];
            sprintf_s(new_title, "FPS: %d Czas: %f ", fps, deltaTime);
            glfwSetWindowTitle(window, new_title);
        }
    }

    // Zwolnienie zasobów
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void processInputKeyboard(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        sX = 500.0f;
        sY = 500.0f;
    }
}

void krawedz(GLuint shader) {
    if (pozX - r < 0)
    {
        pozX = r; // Ustawienie kola przy krawêdzi
        sX *= -1; // Odwrócenie kierunku po odbiciu
        if (sX != 0.0f) {
            colorR = static_cast<float>(rand()) / RAND_MAX;
            colorG = static_cast<float>(rand()) / RAND_MAX;
            colorB = static_cast<float>(rand()) / RAND_MAX;
            color2 = static_cast<float>(rand()) / RAND_MAX;
            glUniform4f(glGetUniformLocation(shader, "uColor"), colorR, colorG, colorB, color2);
        }
    }
    else if (pozX + r > window_width)
    {
        pozX = window_width - r; // Ustawienie ko³a przy krawêdzi
        sX *= -1; // Odwrócenie kierunku po odbiciu
        if (sX != 0.0f) {
            colorR = static_cast<float>(rand()) / RAND_MAX;
            colorG = static_cast<float>(rand()) / RAND_MAX;
            colorB = static_cast<float>(rand()) / RAND_MAX;
            color2 = static_cast<float>(rand()) / RAND_MAX;
            glUniform4f(glGetUniformLocation(shader, "uColor"), colorR, colorG, colorB, color2);
        }
    }
    if (pozY - r < 0)
    {
        pozY = r;
        sY *= -1;
        if (sX != 0.0f) {
            colorR = static_cast<float>(rand()) / RAND_MAX;
            colorG = static_cast<float>(rand()) / RAND_MAX;
            colorB = static_cast<float>(rand()) / RAND_MAX;
            color2 = static_cast<float>(rand()) / RAND_MAX;
            glUniform4f(glGetUniformLocation(shader, "uColor"), colorR, colorG, colorB, color2);
        }
    }
    else if (pozY + r > window_height)
    {
        pozY = window_height - r; // Ustawienie ko³a przy krawêdzi
        sY *= -1; // Odwrócenie kierunku po odbiciu
        if (sX != 0.0f) {
            colorR = static_cast<float>(rand()) / RAND_MAX;
            colorG = static_cast<float>(rand()) / RAND_MAX;
            colorB = static_cast<float>(rand()) / RAND_MAX;
            color2 = static_cast<float>(rand()) / RAND_MAX;
            glUniform4f(glGetUniformLocation(shader, "uColor"), colorR, colorG, colorB, color2);
        }
    }
}
