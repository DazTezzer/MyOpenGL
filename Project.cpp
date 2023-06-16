#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <glm/gtx/compatibility.hpp>
#include <iostream>

using namespace std;

int project()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 color;\n"
        "uniform mat4 model;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = model * vec4(aPos, 1.0);\n"
        "   color = aColor;\n"
        "}\0";

    const char* vertexShaderSource2 = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(color, 1.0);\n"
        "}\n\0";

    // Координаты кривой линии
    std::vector<float> curveVertices;
    const int numPoints = 100; // Количество точек на кривой
    const float amplitude = 0.5f; // Амплитуда кривой
    const float frequency = 3.0f; // Частота кривой
    for (int i = 0; i < numPoints; ++i)
    {
        float t = static_cast<float>(i) / (numPoints - 1);
        float x = t * 2.0f - 1.0f; // Приведение t к диапазону [-1, 1]
        float y = amplitude * sin(frequency * x); // Формула кривой (sin или другая)
        curveVertices.push_back(x);
        curveVertices.push_back(y);
        curveVertices.push_back(0.0f);
    }

    for (const auto& vertex : curveVertices) {
        std::cout << vertex << " ";
    }
    

    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      //
    // Bottom face (red)
    -0.25f, 0.0f,  0.25f,     1.0f, 0.0f, 0.0f,
    -0.25f, 0.0f, -0.25f,     1.0f, 0.0f, 0.0f,
    0.25f, 0.0f, -0.25f,     1.0f, 0.0f, 0.0f,
    0.25f, 0.0f,  0.25f,     1.0f, 0.0f, 0.0f,
    // Front face (green)
    0.25f, 0.0f,  0.25f,     0.0f, 1.0f, 0.0f,
    0.25f, 0.0f, -0.25f,     0.0f, 1.0f, 0.0f,
    0.0f, 0.5f,  0.0f,     0.0f, 1.0f, 0.0f,
    // Right face (blue)
    0.25f, 0.0f, -0.25f,     0.0f, 0.0f, 1.0f,
    -0.25f, 0.0f, -0.25f,     0.0f, 0.0f, 1.0f,
    0.0f, 0.5f,  0.0f,     0.0f, 0.0f, 1.0f,
    // Back face (yellow)
    -0.25f, 0.0f, -0.25f,     1.0f, 1.0f, 0.0f,
    -0.25f, 0.0f,  0.25f,     1.0f, 1.0f, 0.0f,
    0.0f, 0.5f,  0.0f,     1.0f, 1.0f, 0.0f,
    // Left face (purple)
    -0.25f, 0.0f,  0.25f,     1.0f, 0.0f, 1.0f,
    0.25f, 0.0f,  0.25f,     1.0f, 0.0f, 1.0f,
    0.0f, 0.5f,  0.0f,     1.0f, 0.0f, 1.0f,
    };

    // Indices for vertices order
    GLuint indices[] =
    {
    0, 1, 2, // Bottom face
    0, 2, 3,
    4, 5, 6, // Front face
    7, 8, 9, // Right face
    10, 11, 12, // Back face
    13, 14, 15 // Left face
    };


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "MyOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 1920, 1080);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader);
    glLinkProgram(shaderProgram2);



    glDeleteShader(vertexShader);
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO, indi;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &indi);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint curveVAO, curveVBO;
    glGenVertexArrays(1, &curveVAO);
    glGenBuffers(1, &curveVBO);
    glBindVertexArray(curveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    glBufferData(GL_ARRAY_BUFFER, curveVertices.size() * sizeof(float), curveVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(curveVAO);
    glBindVertexArray(0);


    GLuint uniID = glGetUniformLocation(shaderProgram, "scale");

    glm::vec3 red(1.0f, 0.0f, 0.0f);
    glm::vec3 green(0.0f, 1.0f, 0.0f);
    glm::vec3 blue(0.0f, 0.0f, 1.0f);
    glm::vec3 yellow(1.0f, 1.0f, 0.0f);
    glm::vec3 purple(1.0f, 0.0f, 1.0f);
    glm::vec3 myColors[] = { red, green, blue, yellow, purple };

    int numColors = sizeof(myColors) / sizeof(myColors[0]);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // Перемещение треугольника вдоль кривой
        static float t = 0.0f;
        if (t >= 1.0f)
            t = 0.0f;
        t += 0.001f;
        glm::mat4 model = glm::mat4(1.0f);

        // Находим начальную и конечную позиции на кривой
        int startPosIndex = static_cast<int>(t * (curveVertices.size() / 3 - 1)) * 3;
        int endPosIndex = startPosIndex + 3;
        glm::vec3 startPos(curveVertices[startPosIndex], curveVertices[startPosIndex + 1], curveVertices[startPosIndex + 2]);
        glm::vec3 endPos(curveVertices[endPosIndex], curveVertices[endPosIndex + 1], curveVertices[endPosIndex + 2]);

        glm::vec3 position = glm::lerp(startPos, endPos, t);
        model = glm::translate(model, position);

        // Поворот треугольника относительно кривой
        glm::vec3 tangent = glm::normalize(endPos - startPos);
        float angle = atan2(tangent.y, tangent.x); // Угол поворота по оси z

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.25f)); // Центрируем треугольник
        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f)); // Поворот треугольника
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.25f));

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int myColorsLoc = glGetUniformLocation(shaderProgram, "myColors");
        glUniform3fv(myColorsLoc, numColors, glm::value_ptr(myColors[0]));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram2);
        glBindVertexArray(curveVAO);
        glDrawArrays(GL_LINE_STRIP, 0, curveVertices.size() / 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &indi);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}