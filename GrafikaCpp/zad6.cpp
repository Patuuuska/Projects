
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
using namespace std;
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec2 texture;\n"
"out vec2 vertexTexture;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vertexTexture = texture; \n"
"}\0";


const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"in vec2 vertexTexture;\n"
"out vec4 fragmentColor;\n"
"uniform sampler2D Texture;\n"
"void main()\n"
"{\n"
"    fragmentColor = texture(Texture, vertexTexture);\n"
"}\0";


float pitch = 0.0f;
float yaw = -90.0f;

const unsigned int window_width = 1000;
const unsigned int window_height = 800;

float previousX = static_cast<float>(window_width) / 2.0f;
float previousY = static_cast<float>(window_height) / 2.0f;

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool first_window_enter = true;
float deltaTime = 0.0f;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {



    if (first_window_enter) //zapobieganie duzemu skokowi kamery
    {
        previousX = xpos;
        previousY = ypos;
        first_window_enter = false;
    }


    float xdifference = xpos - previousX; //roznica wspó?rzednych nastepujacych klatakch
    float ydifference = previousY - ypos;

    previousX = xpos;
    previousY = ypos;

    const float sensitivity = 0.075f; //szybkosc obrotu kamery
    xdifference *= sensitivity;
    ydifference *= sensitivity;

    pitch += ydifference; //aktualizujemy k?ty
    yaw += xdifference;

    if (pitch > 89.0f) //ograniczenie - zapobieganie b??dom w lookAt
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 cameraFront_new; //obliczamy nowy wektor cameraFront
    cameraFront_new.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront_new.y = sin(glm::radians(pitch));
    cameraFront_new.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(cameraFront_new);

}

void processInputKeyboard(GLFWwindow* window)
{
    const float cameraSpeed = 2.00f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // inicjalizacja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "grafika komputerowa", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
   

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


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

    GLfloat vertices[] = {
        // vertices coords     // texture coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f
    };

    GLuint indices[] = {
 0, 1, 2, 3, 4, 5,
 6, 7, 8, 9, 10, 11,
 12, 13, 14, 15, 16, 17,
 18, 19, 20, 21, 22, 23,
 24, 25, 26, 27, 28, 29,
 30, 31, 32, 33, 34, 35

    };

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load("image/bobik.jpg", &width, &height, &nrChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


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


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSwapInterval(0); //wylaczenie v-sync
  
    float previousTime = 0.0f; //znacznik czsu rozpoczecia poprzeniej klatki
    double fpss = 0;
    float timef = 1.0f;
    int fps = 0;

    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);
    glfwSetTime(0.0); //znacznik czasu - ile uplynelo od wejscia w petle zdarzen
    // pêtla zdarzeñ
    while (!glfwWindowShouldClose(window))
    {
        fpss++; //ilosc klatek animacji 
        float currentTime = glfwGetTime(); //aktualny znacznik czasu
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        
        glEnable(GL_DEPTH_TEST); ///wlaczenie z bufora
        
        glClearColor(0.066f, 0.09f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie w kazdej kaltce
        

        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(sin((float)glfwGetTime()), 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f ), glm::vec3(1.0f, 1.0f, 1.0f));

        cout << fps << "\t" << deltaTime << endl;

        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);


        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        processInputKeyboard(window);
        glfwSwapBuffers(window);
        glfwPollEvents();

        
        if (currentTime - time > 1) {
            fps = fpss;
            timef = currentTime;
            fpss = 0;
            const int bufferSize = 256; // Rozmiar bufora na nowy tytu? okna
            char new_title[bufferSize];
            sprintf_s(new_title, "FPS: %d Czas: %f ", fps, deltaTime);
            glfwSetWindowTitle(window, new_title);
        }
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}