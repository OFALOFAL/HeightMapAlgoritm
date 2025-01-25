//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <thread>
#include <synchapi.h>
#include <mutex>
#include <windows.h>
#include <conio.h>

#include "../header/c_VBO.h"
#include "../header/c_VAO.h"
#include "../header/c_EBO.h"
#include "../header/c_Shader.h"
#include "../header/c_Camera.h"
#include "../header/c_Texture.h"
#include "../header/yAxisAlg.h"

namespace fs = std::experimental::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;

const int numOfPoints = 225;

float vertices[11 * numOfPoints] = {};

const int numOfTriangles = 2 * 14 * 14 * 3 + 13 * 2 * 3;

// Indices for vertices order
unsigned int indices[2 * 14 * 14 * 3 + 13 * 2 * 3] = {};

GLfloat lightVertices[24] {
        7.0f, 3.0f, 7.1f,
        7.2f, 3.0f, 7.1f,
        7.2f, 3.2f, 7.0f,
        7.0f, 3.2f, 7.0f,
        7.0f, 3.0f, 7.1f,
        7.2f, 3.0f, 7.1f,
        7.2f, 3.2f, 7.0f,
        7.0f, 3.2, 7.0f
};

GLuint lightIndices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
        };

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//Object to add Height Values
yAxisAlg yNum(7, 0.2,7);
//array to hold yValues
std::array<float, 15*15> yAxis;

void exit(){
    system("CLS");
    std::cout << "Exiting....";
    Sleep(200);
}

void ERRexit(){
    system("CLS");
    std::cout << "ERROR ACCURED\nExiting....";
    Sleep(200);
}

//set hVal
std::string Menu(){
    int heightDevider = 1;
    int showPointsInfo = 0;
    bool isInMenu = true;
    HWND consoleWindowHandle = GetConsoleWindow();
    while (isInMenu){
        ShowWindow(consoleWindowHandle, SW_NORMAL);
        int menuOption;
        system("CLS");
        SetConsoleTitle("Menu");
        std::cout << "Choose Option by typing coresponding number:\n"
                     "1)Choose from Library\n"
                     "2)Manual\n"
                     "3)Help\n"
                     "4)Render\n"
                     "0)Quit\n";
        menuOption = getch();
        switch (menuOption) {
            case int('1'): {
                bool isInLibrary = true;
                while (isInLibrary) {
                    system("CLS");
                    SetConsoleTitle("Library");
                    std::cout << "High values:\n";
                    std::cout << "X  Z  Y\n";
                    for (auto x:yNum.gethVals()) {
                        for (auto v:x) {
                            std::cout << std::left << std::setw(3) << v ;
                        }
                        std::cout << "\n";
                    }

                    std::cout << "1)Default\n"
                                 "2)Wide Hill 1\n"
                                 "3)Wide Hill 2\n"
                                 "4)Tall Mountain\n"
                                 "5)Canyon\n"
                                 "6)Mountain valey\n"
                                 "0)Quit\n";

                    menuOption = getch();;
                    switch (menuOption) {
                        case int('1'): {
                            yNum.clearhVals();
                            yNum.addhVal(7, 0.2, 7);
                            heightDevider = 0;
                            break;
                        }

                        case int('2'):{
                            yNum.clearhVals();
                            yNum.addhVal(7, 1, 7);
                            yNum.addhVal(0, 0.5, 7);
                            yNum.addhVal(14, 0.6, 7);
                            heightDevider = 1;
                            break;
                        }

                        case int('3'): {
                            yNum.clearhVals();
                            yNum.addhVal(7, 1, 7);
                            yNum.addhVal(0, 1.5, 7);
                            yNum.addhVal(14, 1, 7);
                            yNum.addhVal(7, 0.6, 14);
                            heightDevider = 1;
                            break;
                        }

                        case int('4'): {
                            yNum.clearhVals();
                            yNum.addhVal(7, 2.1, 7);
                            yNum.addhVal(0, 3, 7);
                            yNum.addhVal(14, 1.8, 7);
                            yNum.addhVal(7, 1, 14);
                            heightDevider = 0;
                            break;
                        }
                        case int('5'): {
                            yNum.clearhVals();
                            yNum.addhVal(12, 2, 0);
                            yNum.addhVal(12, 2, 14);

                            yNum.addhVal(7, -1, 0);
                            yNum.addhVal(7, -1, 14);

                            yNum.addhVal(2, 2, 0);
                            yNum.addhVal(2, 2, 14);
                            heightDevider = 0;
                            break;
                        }
                        case int('6'):{
                            yNum.clearhVals();
                            yNum.addhVal(4, 1, 10);
                            yNum.addhVal(4, 1, 4);
                            yNum.addhVal(7, -0.5, 7);
                            yNum.addhVal(8, 1, 8);

                            heightDevider = 0;
                            break;
                        }

                        case int('0'): {
                            isInLibrary = false;
                        }
                    }
                }
                break;
            }

            case int('2'): {
                bool isInManualSetupMenu = true;
                while (isInManualSetupMenu) {

                    system("CLS");
                    SetConsoleTitle("Manual Setup Menu");
                    std::cout << "High values:\n";
                    std::cout << "X Z Y\n";
                    for (auto x:yNum.gethVals()) {
                        for (auto v:x) {
                            std::cout << v << " ";
                        }
                        std::cout << "\n";
                    }

                    std::cout << "Choose Option by typing coresponding number:\n"
                                 "1)Add high Value\n"
                                 "2)Clear high Values\n"
                                 "3)Change Height Devider\n"
                                 "0)Quit\n";
                    menuOption = getch();
                    switch (menuOption) {
                        case int('1'): {
                            system("CLS");

                            std::cout << "High values:\n";
                            std::cout << "X Z Y\n";
                            for (auto x:yNum.gethVals()) {
                                for (auto v:x) {
                                    std::cout << v << " ";
                                }
                                std::cout << "\n";
                            }

                            float coords[3];

                            do {
                                std::cout << "Note:Type spaces between numbers\nX Y Z\n";
                                std::cin >> coords[0] >> coords[1] >> coords[2];
                            }while (std::isnan(coords[0]), std::isnan(coords[1]), std::isnan(coords[2]));

                            yNum.addhVal(coords[0], coords[1], coords[2]);
                            break;
                        }

                        case int('2'): {
                            bool notSure = true;
                            while (notSure){
                                system("CLS");
                                std::cout << "Don't leave high values vector empty\nAre you sure you want to clear?\n(Type)\nY/N\n";
                                int sure;
                                sure = getch();

                                if (toupper(int(sure)) == int('Y')) {
                                    yNum.clearhVals();
                                    notSure = false;
                                } else if (toupper(int(sure)) == int('N')) {
                                    notSure = false;
                                }
                            }
                            break;
                        }

                        case int('3'): {
                            bool notSure = true;
                            while (notSure){
                                system("CLS");
                                std::cout << "Height Devider sets how diffrend hight values are to the lowest point\n\n"
                                             "Set to:\n"
                                             "0 - rought terrain\n"
                                             "1 - default\n"
                                             "2> - more shallow and more random terrain\n"
                                             ">10 - allmost flat terrain with small hills\n"
                                             "Note1:  Dont set value to lower than 0\n"
                                             "Note2:  Height value changes every setup slightly diffrently\n"
                                             "\tso you just have to look for what you desire :)\n\n"
                                             "Are you sure you want to change it?\n(Type)\nY/N\n";
                                int sure;
                                sure = getch();

                                if (toupper(int(sure)) == int('Y')) {
                                    system("CLS");
                                    std::cout << "Height Devider:\n";
                                    std::cin >> heightDevider;
                                    notSure = false;
                                } else if (toupper(int(sure)) == int('N')) {
                                    notSure = false;
                                    break;
                                }
                            }
                            break;
                        }

                        case int('0'): {
                            isInManualSetupMenu = false;
                        }
                    }
                }
                break;
            }

            case int('3'): {
                bool isInHelpMenu = true;
                SetConsoleTitle("Help Menu");
                system("CLS");
                std::cout << "README!\n"
                             "\t1)This program generates grid of 15x15 points\n"
                             "\t2)height value is point on grid that the mountain generation bases on\n"
                             "\t3)Height devider is a number that changes how diffrent are height\n"
                             "\t  values to the bottom\n"
                             "\n"
                             "Help:\n"
                             "\t1)To change any value, first type it than press enter\n"
                             "\t2)Set X and Z coordinets to intiger beetwen 0 and 14 to specify\n"
                             "\t  point on the grid\n"
                             "\t3)Set Y coordinates to any number beedtween -50 and 50\n"
                             "\t  BUT you will probably only need to use numbers from -10 to 10\n"
                             "\t4)Movment: WSAD and Ctrl to go DOWN and Space to go UP\n"
                             "About:\n"
                             "\tAuthor: Olaf Lewandowski\n"
                             "\tCode is open source feel free to copy it and use in your own projects <3\n"
                             "\n"
                             "Type '0' to quit\n";
                while (isInHelpMenu) {
                    int done;
                    done = getch();
                    if (done == int('0')) {
                        isInHelpMenu = false;
                    }
                }
                break;
            }

            case int('4'): {
                bool notSure = true;
                while (notSure) {
                    system("CLS");
                    SetConsoleTitle("Render Menu");
                    std::cout << "Note: Press ESC key to quit render window\n\nDo you want to show points menuInfo\n(Type)\nY/N\n";
                    int sure;
                    sure = getch();
                    if (toupper(int(sure)) == int('Y')) {
                        system("CLS");
                        std::cout << "Wait....";
                        showPointsInfo = 1;
                        isInMenu = false;
                        notSure = false;
                    } else if (toupper(int(sure)) == int('N')) {
                        system("CLS");
                        std::cout << "Wait....";
                        showPointsInfo = 0;
                        isInMenu = false;
                        notSure = false;
                    }
                }
                break;
            }
            case int('0'):
                system("CLS");
                std::atexit(exit);
                std::exit(0);
        }
    }

    //concatinate info to one string
    std::stringstream ss;
    ss << heightDevider << showPointsInfo;
    std::string menuInfo = ss.str();

    return menuInfo;
}

void setCoordinates(int heightDevider = 1){
    yAxis = yNum.yAxisGet(heightDevider);

    for (int i = 1, j {}; j < yAxis.size(); i += 11, j++) {
        vertices[i] = yAxis.at(j);
    }

    float x;
    for (int i = 0; i < 225; ++i) {
        x += 0.5;
        if (i % 15 == 0/*one row size*/)
            x = 0;
        vertices[i*11] = x;
    }

    //set z
    float z;
    for (int i = 0; i < 225; ++i) {
        if (i % 15 == 0/*one column size*/)
            z += 0.5;
        vertices[(i*11)+2] = z - 0.5;
    }

    //set color
    for (int i = 0; i < 225; ++i) {
        float c[3] = {vertices[(i*11)], vertices[(i*11)+1], vertices[(i*11)+2]};
        vertices[(i*11)+3] = c[1];
        vertices[(i*11)+4] = c[2];
        vertices[(i*11)+5] = c[0];
    }
    bool border;
    //set indicies
    for (int i{}, j{}, k {}; i < 2 * 14 * 14 * 3 + 13 * 2 * 3; i+=3, k++) {
        if (i % 2 == 0) {
            indices[i] = j;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 15;//i + size of one column
            j++;
            //calculate normal

            float b[3] = {vertices[(j * 11)], vertices[(j * 11) + 1], vertices[(j * 11) + 2]};
            float r[3] = {vertices[((j + 1) * 11)], vertices[((j + 1) * 11) + 1], vertices[((j + 1) * 11) + 2]};
            float s[3] = {vertices[((j + 15) * 11)], vertices[((j + 15) * 11) + 1], vertices[((j + 15) * 11) + 2]};

            float QR[3] = {r[0] - b[0], r[1] - b[1], r[2] - b[2]};
            float QS[3] = {s[0] - b[0], s[1] - b[1], s[2] - b[2]};

            float normal[3] = {(QR[0] * QS[0]) / 2, (QR[1] * QS[1]) / 2, (QR[2] * QS[2]) / 2};

            vertices[(j * 11) + 7] = normal[0];
            vertices[(j * 11) + 8] = normal[1];
            vertices[(j * 11) + 9] = normal[2];

            vertices[((j + 1) * 11) + 7] = normal[0];
            vertices[((j + 1) * 11) + 8] = normal[1];
            vertices[((j + 1) * 11) + 9] = normal[2];

            vertices[((j + 15) * 11) + 7] = normal[0];
            vertices[((j + 15) * 11) + 8] = normal[1];
            vertices[((j + 15) * 11) + 9] = normal[2];
        } else {
            indices[i] = j;
            indices[i + 1] = j + 15 - 1;
            indices[i + 2] = j + 15;

            //calculate normal

            float b[3] = {vertices[(j * 11)], vertices[(j * 11) + 1], vertices[(j * 11) + 2]};
            float r[3] = {vertices[((j + 15 - 1) * 11)], vertices[((j + 15 - 1) * 11) + 1],
                          vertices[((j + 15 - 1) * 11) + 2]};
            float s[3] = {vertices[((j + 15) * 11)], vertices[((j + 15) * 11) + 1], vertices[((j + 15) * 11) + 2]};

            float QR[3] = {r[0] - b[0], r[1] - b[1], r[2] - b[2]};
            float QS[3] = {s[0] - b[0], s[1] - b[1], s[2] - b[2]};

            float normal[3] = {QR[0] * QS[0], QR[1] * QS[1], QR[2] * QS[2]};

            vertices[(j * 11) + 7] = normal[0];
            vertices[(j * 11) + 8] = normal[1];
            vertices[(j * 11) + 9] = normal[2];

            vertices[((j + 15 - 1) * 11) + 7] = normal[0];
            vertices[((j + 15 - 1) * 11) + 8] = normal[1];
            vertices[((j + 15 - 1) * 11) + 9] = normal[2];

            vertices[((j + 15) * 11) + 7] = normal[0];
            vertices[((j + 15) * 11) + 8] = normal[1];
            vertices[((j + 15) * 11) + 9] = normal[2];
        }
    }


    // hide all "floor" indices (points where indice goes from back to front of the grid making floor lol)
    //first point starts at 28 iteration so i find 28th indicy (indicy has 3 points so 28 * 3)
    //next points are in 15 spaces beteen so i add 15*3 to i
    //size to iterate is 14 * 15 * 2 * 3  : 14 times 28 (14 * 2) indices of size 3
    for (int i = 28 * 3; i < 14 * 14 * 2 * 3; i+=15*3) {

        //bool to check if value is on list of indices to hide
        bool isIn = false;

        //set hide-indices-list
        int arr[14];
        for (int j = 43, l{}; l < 15; j+=30, l++) {
            arr[l] = j;
        }
        //get i in arr
        for (auto x:arr) {
            if (i / 3 == x){
                isIn = true;
                break;
            }
        }

        //set floor indicies to self[0] to hide them
        if (!isIn){
            //indicy 1
            indices[i] = indices[i];
            indices[i + 1] = indices[i];
            indices[i + 2] = indices[i];
            //indicy 2
            indices[i + 3] = indices[i];
            indices[i + 4] = indices[i];
            indices[i + 5] = indices[i];
        }
    }
}

void runProgram(int menuInfo_showPInfo){
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "RenderHeightMap", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        system("CLS");
        std::atexit(ERRexit);
        std::exit(0);
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);

    // Generates Vertex Array Object and binds it
    c_VAO VAO1;
    VAO1.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    c_VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    c_EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAtrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAO1.LinkAtrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAtrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAtrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Generates Shader object using shaders defualt.vert and default.frag
    c_Shader shaderProgram("../Shaders/default.vert", "../Shaders/default.frag");


    // Shader for light cube
    c_Shader lightShader("../Shaders/light.vert", "../Shaders/light.frag");
    // Generates Vertex Array Object and binds it
    c_VAO lightVAO;
    lightVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    c_VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    c_EBO lightEBO(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO.LinkAtrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    //set light model
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(3.0f, 4.0f, 3.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    //set terrain model
    glm::vec3 terrainPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 terrainModel = glm::mat4(1.0f);
    terrainModel = glm::translate(terrainModel, terrainPos);


    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(terrainModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    c_Texture texture("../Textures/brick.png");
    texture.Bind();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 0);

    glEnable(GL_DEPTH_TEST);

    c_Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    //print vertices and inices
    if (menuInfo_showPInfo == 1){
        system("CLS");
        std::cout << "Vertices:\n"
                     "******************\n";
        for (int v{}; v < sizeof(vertices); v++) {
            if ((v + 1) % 11 == 1)
                std::cout << v << ": {";
            std::cout << vertices[v] << ", ";
            if ((v + 1) % 11 == 0)
                std::cout << " }\n";
        }
        std::cout << "\nIndices:\n"
                     "******************\n";
        for (auto x:indices) {
            std::cout << int(x) << "\t";
        }
    }

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        glfwSetKeyCallback (window, key_callback);
        if (menuInfo_showPInfo == 0)
            ShowWindow(GetConsoleWindow(), SW_HIDE);
        else
            ShowWindow(GetConsoleWindow(), SW_SHOW);
        //glfwSetKeyCallback(window, key_callback);
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        camera.Inputs(window);

        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        camera.Matrix(shaderProgram, "camMatrix");

        // Tells OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Exports the camera Position to the Fragment Shader for specular lighting
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        // Export the camMatrix to the Vertex Shader of the pyramid
        camera.Matrix(shaderProgram, "camMatrix");

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        // Tells OpenGL which Shader Program we want to use
        lightShader.Activate();
        // Export the camMatrix to the Vertex Shader of the light cube
        camera.Matrix(lightShader, "camMatrix");
        // Bind the VAO so OpenGL knows to use it
        lightVAO.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    //reset console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    // Delete all the objects we've created
    VAO1.Delete();
    EBO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);

    }
}

int main()
{
    // set console
    HWND consoleWindowHandle = GetConsoleWindow();
    RECT rect = {600, 100, 1300, 500};
    MoveWindow(consoleWindowHandle, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,TRUE);

    //show window on top and without scrollbar
    SetWindowPos(consoleWindowHandle,HWND_TOPMOST,0, 0,0, 0,SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ShowWindow(consoleWindowHandle, SW_NORMAL);
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

    EnableScrollBar(consoleWindowHandle, SB_BOTH,ESB_DISABLE_BOTH);
    SetWindowLong(consoleWindowHandle, GWL_STYLE, GetWindowLong(consoleWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    while (true){
        std::string menuInfo = Menu();
        std::reverse(menuInfo.begin(), menuInfo.end());
        char showPInfo = {menuInfo[0]};

        std::reverse(menuInfo.begin(), menuInfo.end());
        menuInfo.pop_back();
        std::string heightDevider = menuInfo;

        setCoordinates(std::stoi(heightDevider));
        runProgram((int)showPInfo - (int)'0');
    }
}
