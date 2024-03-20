#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
const GLchar* vertexSource =
// vertex shader
"#version 330 core\n" // wersja GLSL
"layout(location = 0) in vec3 position; \n" // deklaracja wejscia (wierzcholek)
"layout(location = 1) in vec3 color; \n"// deklaracja wejscia (kolor)
"out vec3 Color; \n"// deklaracja wyjscia (kolor)
"void main() { \n"
"    gl_Position = vec4(position, 1.0); \n"// przypisanie pozycji wierzcholka do zmiennej gl_Position
"    Color = color; \n"// przypisanie koloru wierzcholka do zmiennej vertexColor
"} \0";

const GLchar* fragmentSource =
// fragment shader
"#version 330 core\n" // wersja GLSL
"in vec3 Color; \n"// deklaracja wejscia (kolor)
"out vec4 outColor; \n"// deklaracja wyjscia (kolor)
"uniform vec3 uColor = vec3(1.0, 1.0, 1.0); \n" //uniform-zmienna globalna shaderow, mozna modyfikowac 
"void main() { \n"
"    outColor = vec4(uColor, 1.0);\n"
"} \0";


GLuint VBO;

void draw(int points, unsigned int VBO)
{
    float* vertices = new float[points * 6];
    float alfa = 0.0;
    float alfapom = 2 * M_PI / points;
    float R = 0.5;

    for (int i = 0; i < points * 6; i += 6)
    {
        vertices[i] = R * cos(alfa); //x
        vertices[i + 1] = R * sin(alfa); //y
        vertices[i + 2] = 0;

        vertices[i + 3] = 1.0; //barwa red
        vertices[i + 4] = 1.0; //barwa green
        vertices[i + 5] = 1.0; //barwa blue
        alfa += alfapom;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Pierwszy parametr funkcji (GL_ARRAY_BUFFER) oznacza 
    //typ buforu, z którym wi??emy ID. Wysy?amy dane wierzcho?ków
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points * 6, vertices, GL_STATIC_DRAW);
    //mamy: typ buforu, rozmiar tablicy vertices[] w bajtach, tablic? vertices[], sposób
    // wykorzystania danych(GL_STATIC_DRAW oznacza, ?e dane s? wysy?ane raz, a u?ywane wiele razy)
    delete [] vertices;
}
 
int points = 3;
GLint prymityw = GL_TRIANGLE_FAN;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { //funkcja wywolan zwrotnych
    
    
    if (yoffset > 0) {
        points++;
        cout << points << endl;
        
    }
    
    else if (yoffset < 0) {
        if (points <= 3) return;
        points--;
        cout << points << endl;
        
}
    draw(points, VBO);

}
GLint uColorLocation;
void processInputKeyboard(GLFWwindow* window) //zapytania polling
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        
        glUniform3f(uColorLocation, 1.0f, 0.0f, 0.0f);
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glUniform3f(uColorLocation, 0.0f, 1.0f, 0.0f);
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
       glUniform3f(uColorLocation, 0.0f, 0.0f, 1.0f);
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
    const unsigned int window_width = 800;
    const unsigned int window_height = 800;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Grafika", NULL, NULL);
    glfwMakeContextCurrent(window);


    // inicjalizacja GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //tworzymy VAO - vertex array object, przechowuje glVertexAttribPointer 
    //i wywo?ania funkcji glEnableVertexAttribArray powi?zania mi?dzy atrybutami 
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // tworzenie VB0 - vertex buffer object, b?dzie przechowywa? dane 
    // //wierzcho?ków znajduj?ce si? w tablicy vertices[]
   // tworzymy zmienna przechowujaca id bufora
   // GLuint VBO;
    // tworzymy bufor 



    glGenBuffers(1, &VBO); //ilosc wygenerowanych id i przypisanie

    //figura pocz?tkowa: trójk?t 
    points = 3;
    draw(points, VBO);

    // tworzenie shaderow - programy uruchamiane na GPU. napisane w jêzyku GLSL
    // 1. vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
        std::cout << "ERROR::SHADER::VERTEX:" << error_message << std::endl;
    }



    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
        std::cout << "ERROR::SHADER::FRAGMENT:" << error_message << std::endl;
    }
    // tworzenie programu shaderowego, linkowanie shaderow ze soba
    GLuint shaderProgram = glCreateProgram();
   GLint uColorLocation = glGetUniformLocation(shaderProgram, "uColor"); //musimy zlokalizować (pobrać ID) wektor uColor
    
    glAttachShader(shaderProgram, vertexShader); // dolaczamy shadery do programu
   

    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram); // linkujemy program
    glUseProgram(shaderProgram); // uzywamy programu shaderowego
  
    
    // wspolrzedne
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);  //zdefiniowany atrybut wspolrzednych
    glEnableVertexAttribArray(posAttrib); // wlaczamy atrybut wspolrzednych

    //kolory
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); //zdefiniowany atrybut koloru
    glEnableVertexAttribArray(colAttrib); // wlaczamy atrybut koloru


   // glfwSetKeyCallback(window, keyboardCallback);
    


    // Glówna petla programu
    bool running = true;
    while (running) {
       
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            running = false;
        }
        glfwSetScrollCallback(window, scroll_callback);

        processInputKeyboard(window);
       
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(prymityw, 0, points);
        glfwSwapBuffers(window);


    }

    //zwolnienie pamieci
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    
    glfwTerminate();
    return 0;

}
