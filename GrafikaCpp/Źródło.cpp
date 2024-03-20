#include <glad/glad.h>  // musi byc dolaczony jako pierwszy
#include <GLFW/glfw3.h>

#include <iostream>

const GLchar* vertexShaderSource =
// vertex shader
"#version 330 core\n" // wersja GLSL
"layout(location = 0) in vec3 position; \n" // deklaracja wejscia (wierzcholek)
"layout(location = 1) in vec3 color; \n"// deklaracja wejscia (kolor)
"out vec3 vertexColor; \n"// deklaracja wyjscia (kolor)
"void main() { \n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0f); \n"// przypisanie pozycji wierzcholka do zmiennej gl_Position
"    vertexColor = color; \n"// przypisanie koloru wierzcholka do zmiennej vertexColor
"} \0";

const GLchar* fragmentShaderSource =
// fragment shader
"#version 330 core\n" // wersja GLSL
"in vec3 vertexColor; \n"// deklaracja wejscia (kolor)
"out vec4 fragmentColor; \n"// deklaracja wyjscia (kolor)
"void main() { \n"
"    fragmentColor = vec4(vertexColor, 1.0); \n"// przypisanie koloru wierzcholka do zmiennej vertexColor
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

    // tablica z danymi wierzcholkow 
    GLfloat vertices[] = {
        // coordinates      //colors
        -0.8f, 0.6f, 0.0f,  0.0f, 1.0f, 0.0f,   //triangle 1, vertex 1, triangle 2, vertex 1        
        -0.8f, -0.6f, 0.0f, 0.0f, 1.0f, 0.0f,   //triangle 1, vertex 2
        0.8f, -0.6f, 0.0f,  0.0f, 1.0f, 0.0f,   //triangle 1, vertex 3 triangle 2, vertex 2
        //-0.8f, 0.6f, 0.0f,  0.0f, 1.0f, 0.0f,   //triangle 2, vertex 1 dublujacy sie wierzcholek
        //0.8f, -0.6f, 0.0f,  0.0f, 1.0f, 0.0f,   //triangle 2, vertex 2 dublujacy sie wierzcholek
        0.8f, 0.6f, 0.0f,    0.0f, 1.0f, 0.0f,   //triangle 2, vertex 3
    };

    // tablica z indeksami wierzcholkow
    GLuint indices[] = {
        0, 1, 2, //triangle 1
        0, 2, 3, //triangle 2
    };

    //tworzymy VAO - vertex array object, przechowuje konfiguracje vertex attributes
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // tworzenie VB0 - vertex buffer object, przechowuje dane wierzcholkow
    // tworzymy zmienna przechowujaca id bufora
    GLuint VBO;
    // tworzymy bufor
    glGenBuffers(1, &VBO);
    // bindujemy bufor
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // przekazujemy dane do bufora
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tworzenie EBO - element buffer object, przechowuje indeksy wierzcholkow
    // tworzymy zmienna przechowujaca id bufora
    GLuint EBO;
    // tworzymy bufor
    glGenBuffers(1, &EBO);
    // bindujemy bufor
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // przekazujemy dane do bufora
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // tworzenie shaderow - programy uruchamiane na GPU. napisane w jêzyku GLSL
    // 1. vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
        std::cout << "ERROR::SHADER::VERTEX:" << error_message << std::endl;
    }

    //2. fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
        std::cout << "ERROR::SHADER::FRAGMENT:" << error_message << std::endl;
    }


    // tworzenie programu shaderowego, linkowanie shaderow ze soba
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader); // dolaczamy shadery do programu
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // linkujemy program

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, error_message);
        std::cout << "ERROR::SHADER::PROGRAM:" << error_message << std::endl;
    }

    // usuwamy shadery, bo juz nie sa potrzebne
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glUseProgram(shaderProgram); // uzywamy programu shaderowego

    // wspolrzedne
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0); //zdefiniowany atrybut wspolrzednych
    glEnableVertexAttribArray(0); // wlaczamy atrybut wspolrzednych

    //kolory
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); //zdefiniowany atrybut koloru
    glEnableVertexAttribArray(1); // wlaczamy atrybut koloru

    glBindVertexArray(0);

    glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

    // pêtla zdarzeñ
    while (!glfwWindowShouldClose(window))
    {
        // renderowanie trojkata
        glClearColor(0.298f, 0.141f, 0.141f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //zwolnienie pamieci
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}