#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <tuple> // For std::tuple

// Define a type alias for RGB tuple
using RGBTuple = std::tuple<uint8_t, uint8_t, uint8_t>;

// Function to create an SFML image from a 2D vector of RGB tuples
sf::Image createImageFromRGBVector(const std::vector<std::vector<RGBTuple>>& pixels) {
    // Get dimensions of the input vector
    size_t width = pixels.size(); // Number of rows
    size_t height = (width > 0) ? pixels[0].size() : 0; // Number of columns (assuming rectangular structure)

    // Create SFML image object
    sf::Image image;

    if (width > 0 && height > 0) {
        // Create a new blank image with the specified dimensions
        image.create(width, height);

        // Iterate over each pixel in the vector
        for (size_t x = 0; x < width; ++x) {
            for (size_t y = 0; y < height; ++y) {
                // Extract RGB components from the tuple
                auto [r, g, b] = pixels[x][y];

                // Set the pixel color in the SFML image
                image.setPixel(x, y, sf::Color(r, g, b));
            }
        }
    }

    return image;
}

int main() {
    // Example usage:
    // Create a sample 2D vector of RGB tuples (10x10 image)
    std::vector<std::vector<RGBTuple>> pixels(1000, std::vector<RGBTuple>(1000, {0, 0, 0}));

    // Set some example pixel values (e.g., a gradient)
    for (size_t x = 0; x < 1000; ++x) {
        for (size_t y = 0; y < 1000; ++y) {
            uint8_t value = static_cast<uint8_t>(x * 25); // Example gradient
            pixels[x][y] = {value, value, value};
        }
    }

    // Create SFML image from the 2D vector of RGB tuples
    sf::Image image = createImageFromRGBVector(pixels);

    // Save the image to a file (optional)
    if (image.saveToFile("out/output_image.png")) {
        std::cout << "Image saved successfully!" << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
    }

    return 0;
}
