#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <tuple> // For std::tuple
#include <cstdlib> // For Random number generation
#include <ctime> // For time

using namespace std;

int WIDTH = 500;
int HEIGHT = 500;

int img_width = 100;
int img_height = 100;

int total_true = 1000;

vector<int> neighbor_list = {-1, 1};

bool checkNeighbors(const sf::Image& image, const vector<int> coords)
{
    for (int i : neighbor_list) {
        int new_x = coords[0] + i;
        int new_y = coords[1];

        if (new_x >= 0 && new_x < img_width && image.getPixel(new_x, coords[1]) == sf::Color(255, 255, 255)) {
            return true;
        }

        new_y = coords[1] + i;

        if (new_y >= 0 && new_y < img_height && image.getPixel(new_x, coords[0]) == sf::Color(255, 255, 255)) {
            return true;
        }
    }

    return false;
}

int main() 
{
    // Window variables
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Adjust the antialiasing level as needed
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids", sf::Style::Titlebar | sf::Style::Close, settings);
    
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create a sample 2D vector of RGB tuples (10x10 image)
    sf::Image image;
    image.create(img_width, img_height);

    // Create Sprite
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sprite.setScale(5, 5);

    // Initial center pixel
    image.setPixel((img_width/2),(img_height/2), sf::Color(255, 255, 255));

    // 2000 random walk pixels
    for (int i = 0; i < total_true; i++)
    {
        // Generate random initial coordinates
        int x = rand() % img_width;
        int y = rand() % img_height;

        // Check if coordinates are already occupied
        if (image.getPixel(x, y) == sf::Color(255, 255, 255))
        {
            i--;
            continue;
        }

        // Pixel is next to another condition
        bool friend_pixel = false;
        // Check for original location
        friend_pixel = checkNeighbors(image, {x, y});

        // Random walk of pixel
        while (!friend_pixel) 
        {
            // Calculate new coordinates based on random movement
            int x_or_y = rand() % 2;

            if (x_or_y == 0) // X axis random movement by one pixel
            {
                x += (rand() % 2 == 0) ? 1 : -1;

                // Clamp to bounds of image
                if (x < 0) x = 0;
                if (x >= img_width) x = img_width - 1;
            }
            else // Y axis random movement by one pixel
            {
                y += (rand() % 2 == 0) ? 1 : -1;

                // Clamp to bounds of image
                if (y < 0) y = 0;
                if (y >= img_height) y = img_height - 1;
            }

            // Update friend_pixel based on the new coordinates
            friend_pixel = checkNeighbors(image, {x, y});           
        }

        // When friend_pixel is true, create new "true" value in list, representing a white pixel
        image.setPixel(x, y, sf::Color(255, 255, 255));
    }

    // Main process
    while (window.isOpen()) {
        // Exit window event
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Clear window
        window.clear();

        //Then, in PlayState::render()
        window.draw(sprite);

        // Display window
        window.display();
    }

    return 0;
}
