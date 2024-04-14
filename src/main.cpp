#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // For Random number generation
#include <ctime> // For time
#include "../include/dla.hpp"

using namespace std;

int WIDTH = 1000;
int HEIGHT = 1000;

int img_width = 200;
int img_height = 200;

int total_true = 2000;

int main() 
{
    // Window variables
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DLA generation", sf::Style::Titlebar | sf::Style::Close, settings);
    
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    bool generated = false;

    // Main process
    while (window.isOpen()) 
    {   
        // Create image
        DLA_Image image(img_width, img_height);
        image.init_image();
        
        // Exit window event
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!generated)
        {
            // Random walk pixels
            for (int i = 0; i < total_true; i++)
            {
                i += image.rand_walk();
                
                // Clear window
                window.clear();

                // Draw sprite (image) to screen
                window.draw(image.load_to_sprite());

                // Display window
                window.display();
            }

            generated = true;
        }
    }

    return 0;
}
