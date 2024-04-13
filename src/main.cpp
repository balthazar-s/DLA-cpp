#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <tuple> // For std::tuple
#include <cstdlib> // For Random number generation
#include <ctime> // For time


using namespace std;

int width = 250;
int height = 250;

int total_true = 5000;

vector<int> neighbor_list = {-1, 1};

// Function to create an SFML image from a 2D vector of RGB tuples
sf::Image createImage(const std::vector<std::vector<bool>>& pixels) 
{
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

bool checkNeighbors(const vector<vector<bool>>& pixels, const vector<int> coords)
{
    for (int i : neighbor_list) {
        int new_x = coords[0] + i;
        int new_y = coords[1];

        if (new_x >= 0 && new_x < width && pixels[new_x][coords[1]]) {
            return true;
        }

        new_y = coords[1] + i;

        if (new_y >= 0 && new_y < height && pixels[coords[0]][new_y]) {
            return true;
        }
    }

    return false;
}

int main() 
{
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create a sample 2D vector of RGB tuples (10x10 image)
    std::vector<std::vector<bool>> pixels(width, std::vector<bool>(height, false));

    // Initial center pixel
    pixels[width/2][height/2] = true;


    // 2000 random walk pixels
    for (int i = 0; i < total_true; i++)
    {
        // Generate random initial coordinates
        int x = rand() % width;
        int y = rand() % height;

        // Check if coordinates are already occupied
        if (pixels[x][y])
        {
            i--;
            continue;
        }

        // Pixel is next to another condition
        bool friend_pixel = false;
        // Check for original location
        friend_pixel = checkNeighbors(pixels, {x, y});

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
                if (x >= width) x = width - 1;
            }
            else // Y axis random movement by one pixel
            {
                y += (rand() % 2 == 0) ? 1 : -1;

                // Clamp to bounds of image
                if (y < 0) y = 0;
                if (y >= height) y = height - 1;
            }

            // Update friend_pixel based on the new coordinates
            friend_pixel = checkNeighbors(pixels, {x, y});           
        }

        // When friend_pixel is true, create new "true" value in list, representing a white pixel
        pixels[x][y] = true;
        int percentage = (i * 100 / (total_true)) + 1;
        cout << percentage << "%\n";
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
