#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // For Random number generation
#include <ctime> // For time
#include <string>
using namespace std;

#ifndef DLA_HPP
#define DLA_HPP

class DLA_Image {
  public:
    // Public variables  
    int img_width;
    int img_height;
    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;

    // Constructor to initialize position and velocity
    DLA_Image(const int img_width, const int img_height) : img_width(img_width), img_height(img_height) {};

    // Public functions
    sf::Image get_image(); // Returns sf::Image

    void init_image();

    void save_image(string file_path); // Saves image as a png at specified file path

    bool checkNeighbors(const vector<int> coords);

    int rand_walk();

    sf::Sprite load_to_sprite();
};

#endif