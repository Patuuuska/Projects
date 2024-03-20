#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"out vec3 fragmentPosition;\n"
"out vec3 vertexNormal; \n"
"out vec3 lightPosition; \n"
"out vec3 viewPosition; \n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform vec3 lightposition;\n"
"uniform vec3 viewposition;\n"
"void main()\n"
"{\n"
"    fragmentPosition = vec3(model * vec4(position, 1.0));\n"
"    vertexNormal = mat3(transpose(inverse(model))) * normal;\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    lightPosition = lightposition;\n"
"    viewPosition = viewposition;\n"
"}\0";


const GLchar* fragmentShaderSource =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"in vec3 lightPosition; \n"
"in vec3 fragmentPosition; \n"
"in vec3 vertexNormal; \n"
"in vec3 viewPosition; \n"
"vec3 objectColor = vec3(0.0, 1.0, 0.0);\n"
"vec3 lightColor = vec3(1.0, 1.0, 1.0);\n"
"uniform vec3 light_switch;\n"
"void main()\n"
"{\n"
"   float ambientStrength = 0.15f; \n"
"   vec3 ambientColor = ambientStrength * lightColor * light_switch.x; \n"

"   vec3 normalNormalized = normalize(vertexNormal);\n"
"   vec3 lightDirection = normalize(lightPosition - fragmentPosition);\n"
"   float diffuse = max(dot(normalNormalized, lightDirection), 0.0);\n"
"   vec3 diffuseColor = diffuse * lightColor * light_switch.y;\n"

"   float specularStrength = 0.4f;\n"
"   vec3 viewDirection = normalize(viewPosition - fragmentPosition);\n"
"   vec3 reflectDirection = reflect(-lightDirection, normalNormalized);\n"
"   float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 64);\n"
"   vec3 specularColor = specularStrength * specular * lightColor * light_switch.z;\n"

"   fragmentColor = vec4(objectColor * (ambientColor + diffuseColor + specularColor), 1.0); \n"
"}\0";


const GLchar* vertexShaderSource2 =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\0";

float pitch = 0.0f;
float yaw = -90.0f;

const unsigned int window_width = 1000;
const unsigned int window_height = 800;

float previousX = static_cast<float>(window_width) / 2.0f;
float previousY = static_cast<float>(window_height) / 2.0f;
bool first_window_enter = true;

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.5f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 light_switch = glm::vec3(1.0f, 1.0f, 1.0f);

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (first_window_enter)
    {
        previousX = xpos;
        previousY = ypos;
        first_window_enter = false;
    }

    float xdifference = xpos - previousX;
    float ydifference = previousY - ypos;

    previousX = xpos;
    previousY = ypos;

    const float sensitivity = 0.075f;
    xdifference *= sensitivity;
    ydifference *= sensitivity;

    pitch += ydifference;
    yaw += xdifference;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void processInputKeyboard(GLFWwindow* window)
{
    const float cameraSpeed = 0.005f;
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

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        light_switch.x = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        light_switch.y = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        light_switch.z = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        light_switch.x = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        light_switch.y = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        light_switch.z = 1;
    }
}

int main()
{
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSwapInterval(0);
    // inicjalizacja GLAD
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

    GLuint vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);

    glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader2, 512, NULL, error_message);
        std::cout << "Error (Vertex shader): " << error_message << std::endl;
    }

    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, error_message);
        std::cout << "Error (Fragment shader): " << error_message << std::endl;
    }

    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, error_message);
        std::cout << "Error (Shader program): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram2, vertexShader2);
    glDetachShader(shaderProgram2, fragmentShader2);
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader2);

    GLfloat vertices[] = {
        // vertices coords      // normals 
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f
    };


    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);



    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);
    glEnable(GL_DEPTH_TEST);
    // pêtla zdarzeñ
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO);

       
        float x = glm::sin((float)glfwGetTime()) * 4.0f;
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(x, 2.0f, -5.0f));
        model2 = glm::rotate(model2, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 view2 = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        glm::mat4 projection2 = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);


        glUseProgram(shaderProgram2);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2, "model"), 1, GL_FALSE, glm::value_ptr(model2));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2, "view"), 1, GL_FALSE, glm::value_ptr(view2));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram2, "projection"), 1, GL_FALSE, glm::value_ptr(projection2));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        glm::vec3 cameraFront_new;
        cameraFront_new.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront_new.y = sin(glm::radians(pitch));
        cameraFront_new.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(cameraFront_new);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

        glm::vec3 lightPosition = glm::vec3(x, 2.0f, -5.0f);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3f(glGetUniformLocation(shaderProgram, "lightposition"), lightPosition.x, lightPosition.y, lightPosition.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "viewposition"), cameraPosition.x, cameraPosition.y, cameraPosition.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "light_switch"), light_switch.x, light_switch.y, light_switch.z);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        processInputKeyboard(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);

    glfwTerminate();
    return 0;
}
