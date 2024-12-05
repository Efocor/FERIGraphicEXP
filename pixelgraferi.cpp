#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int AXIS_PADDING = 20;
const float PI = 3.14159265359;
const float AMPLITUDE = 50.0f;
const float FREQUENCY = 0.1f;
const unsigned char COLOR = 0xFF;

struct Point {
    int x;
    int y;
};

void drawPixel(int x, int y, unsigned char color) {
    glRasterPos2i(x, y);
    glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
}

void drawBlock(int x, int y, int size, unsigned char color) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            drawPixel(x + i, y + j, color);
        }
    }
}

void drawFigure(const std::vector<Point>& figure, unsigned char color) {
    for (const Point& point : figure) {
        drawBlock(point.x, point.y, 3, color); // Adjust the block size as needed
    }
}

void drawSineWave(float time, int xOffset, int yOffset) {
    std::vector<Point> sinePoints;
    for (int x = 0; x < SCREEN_WIDTH - AXIS_PADDING; ++x) {
        float radians = static_cast<float>(x + xOffset) * FREQUENCY * (2 * PI) / (SCREEN_WIDTH - AXIS_PADDING);
        int y = static_cast<int>(AMPLITUDE * std::sin(radians + time) + yOffset);
        sinePoints.push_back({x + AXIS_PADDING, SCREEN_HEIGHT / 2 - y});
    }
    drawFigure(sinePoints, COLOR);
}

void drawAxes() {
    for (int x = AXIS_PADDING; x < SCREEN_WIDTH; ++x) {
        drawPixel(x, SCREEN_HEIGHT / 2, COLOR);
    }

    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        drawPixel(SCREEN_WIDTH / 2, y, COLOR);
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sine Wave Animation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    float time = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw axes
        drawAxes();

        // Draw the sine wave with specified parameters and time-based animation
        drawSineWave(time, 0, 0);

        // Draw additional figures here (example):
        // std::vector<Point> customFigure = {{100, 100}, {110, 120}, {120, 100}};
        // drawFigure(customFigure, COLOR);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Increase time for animation
        time += 0.05f; // You can adjust the speed of the animation by changing this value
    }

    glfwTerminate();
    return 0;
}

//g++ -o pixelgraferi.exe pixelgraferi.cpp -I"C:\msys64\mingw64\include\GLFW" -L"C:\msys64\mingw64\lib" -lglfw3 -lopengl32
