#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <tuple> // For std::tuple
#include <cstdlib> // For Random number generation


using namespace std;

int width = 250;
int height = 250;

// Function to create an SFML image from a 2D vector of RGB tuples
sf::Image createImage(const std::vector<std::vector<bool>>& pixels) {
    // Create SFML image object
    sf::Image image;

    if (width > 0 && height > 0) {
        // Create a new blank image with the specified dimensions
        image.create(width, height);

        // Iterate over each pixel in the vector
        for (size_t x = 0; x < width; ++x) {
            for (size_t y = 0; y < height; ++y) {
                if (pixels[x][y])
                {
                    image.setPixel(x, y, sf::Color(255, 255, 255));
                }
                else
                {
                    image.setPixel(x, y, sf::Color(0, 0, 0));
                }
            }
        }
    }

    return image;
}

int main() {
    // Example usage:
    // Create a sample 2D vector of RGB tuples (10x10 image)
    std::vector<std::vector<bool>> pixels(width, std::vector<bool>(height, false));

    pixels[width/2][height/2] = true;

    for (int i = 0; i < 10000; i++)
    {
        pixels[rand()%width][rand()%height] = true;
    }

    // Create SFML image from the 2D vector of RGB tuples
    sf::Image image = createImage(pixels);

    // Save the image to a file (optional)
    if (image.saveToFile("out/output_image.png")) {
        std::cout << "Image saved successfully!\n";
    } else {
        std::cerr << "Failed to save image!\n";
    }

    return 0;
}
