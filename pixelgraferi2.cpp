#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int AXIS_PADDING = 20;
const float PI = 3.14159265359;
const float AMPLITUDE = 50.0f;
const float FREQUENCY = 0.1f;
const sf::Color COLOR = sf::Color::White;

void drawSineWave(sf::RenderWindow& window, float time, int xOffset, int yOffset) {
    std::vector<sf::Vector2f> sinePoints;
    for (int x = 0; x < SCREEN_WIDTH - AXIS_PADDING; ++x) {
        float radians = static_cast<float>(x + xOffset) * FREQUENCY * (2 * PI) / (SCREEN_WIDTH - AXIS_PADDING);
        int y = static_cast<int>(AMPLITUDE * std::sin(radians + time) + yOffset);
        sinePoints.push_back(sf::Vector2f(x + AXIS_PADDING, SCREEN_HEIGHT / 2 - y));
    }

    sf::VertexArray vertexArray(sf::LineStrip, sinePoints.size());
    for (size_t i = 0; i < sinePoints.size(); ++i) {
        vertexArray[i].position = sinePoints[i];
        vertexArray[i].color = COLOR;
    }

    window.draw(vertexArray);
}

void drawAxes(sf::RenderWindow& window) {
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(AXIS_PADDING, SCREEN_HEIGHT / 2);
    xAxis[1].position = sf::Vector2f(SCREEN_WIDTH - 1, SCREEN_HEIGHT / 2);
    xAxis[0].color = COLOR;
    xAxis[1].color = COLOR;
    window.draw(xAxis);

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(SCREEN_WIDTH / 2, 0);
    yAxis[1].position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 1);
    yAxis[0].color = COLOR;
    yAxis[1].color = COLOR;
    window.draw(yAxis);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sine Wave Animation");
    window.setFramerateLimit(60);

    float time = 0.0f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Draw axes
        drawAxes(window);

        // Draw the sine wave with specified parameters and time-based animation
        drawSineWave(window, time, 0, 0);

        window.display();

        // Increase time for animation
        time += 0.05f; // You can adjust the speed of the animation by changing this value
    }

    return 0;
}

//compilo:
//g++ pixelgraferi2.cpp -o pixelgraferi2 -I /msys64/mingw64/include -L /msys64/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system
