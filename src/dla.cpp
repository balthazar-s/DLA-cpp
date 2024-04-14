#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // For Random number generation
#include <ctime> // For time
#include <string>
#include "../include/dla.hpp"
using namespace std;

vector<int> neighbor_list = {-1, 1};

// Public functions
void DLA_Image::init_image()
{
    // Initial center pixel
    image.create(img_width, img_height, sf::Color::Black);
    image.setPixel((img_width/2),(img_height/2), sf::Color::White);
    sprite.setScale({5, 5});
}


sf::Image DLA_Image::get_image() // Returns sf::Image
{
    return image;
}


void DLA_Image::save_image(string file_path) // Saves image as a png at specified file path
{
    image.saveToFile(file_path + ".jpg");
}


bool DLA_Image::checkNeighbors(const vector<int> coords)
{
    for (int i : neighbor_list) 
    {
        int new_x = coords[0] + i;
        int new_y = coords[1] + i;

        if (new_x >= 0 && new_x < img_width && image.getPixel(new_x, coords[1]) == sf::Color::White) 
        {
            return true;
        }

        else if (new_y >= 0 && new_y < img_height && image.getPixel(coords[0], new_y) == sf::Color::White) 
        {
            return true;
        }
    }
    return false;
}


int DLA_Image::rand_walk()
{
    // Generate random initial coordinates
    int x = rand() % img_width;
    int y = rand() % img_height;

    // Check if coordinates are already occupied
    if (image.getPixel(x, y) == sf::Color::White)
    {
        return -1;
    }

    // Pixel is next to another condition
    bool friend_pixel = false;
    // Check for original location
    friend_pixel = checkNeighbors({x, y});

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
        friend_pixel = checkNeighbors({x, y});           
    }

    // When friend_pixel is true, create new "true" value in list, representing a white pixel
    image.setPixel(x, y, sf::Color::White);

    return 0;
}


sf::Sprite DLA_Image::load_to_sprite()
{
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);
    return sprite;
}
