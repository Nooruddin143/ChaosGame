// Include important C++ libraries here
// Team Isabella and Nooruddin
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

// Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    srand(time(0));

    // Create a video mode object
    VideoMode vm(1000, 800);

    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game with Hexagon!!", Style::Default);

    // Initialize vectors to store vertices and points
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Load font
    Font font;
    if (!font.loadFromFile("Bubblegum.ttf")) {
        cout << "Error loading font" << endl;
        return -1; // Exit if font loading fails
    }

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the player's input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "The left button was pressed" << endl;
                    cout << "Mouse x: " << event.mouseButton.x << endl;
                    cout << "Mouse y: " << event.mouseButton.y << endl;

                    if (vertices.size() < 6)
                    {
                        // Store up to 6 vertices for hexagon
                        vertices.push_back(Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));
                    }
                    else if (points.size() == 0)
                    {
                        // After 6 vertices, start with an initial point for chaos game
                        points.push_back(Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));
                    }
                }
            }
        }

        // Handle exit on pressing ESC key
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */
        if (points.size() > 0)
        {
            // Generate more points
            int vert = rand() % 6; // Choose one of the 6 vertices
            Vector2f randVert = vertices.at(vert);

            // Calculate midpoint between random vertex and the last point
            Vector2f lastPoint = points.back();
            Vector2f newPoint(
                (2 * randVert.x + lastPoint.x) / 3.0f,
                (2 * randVert.y + lastPoint.y) / 3.0f
            );

            // Push back the newly generated coordinate
            points.push_back(newPoint);
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // Display the text guide
        Text text("Click six points to form a hexagon, then another to begin the chaos!", font);
        text.setCharacterSize(24);
        text.setFillColor(Color::Red);
        text.setPosition(10, 10); // Position it at the top of the screen

        window.draw(text);

        // Draw vertices as hexagons
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(3, 3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }

        //display points
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(1, 1));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Display everything on the window
        window.display();
    }

    return 0;
}
