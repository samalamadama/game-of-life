#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

#include "cell.hpp"
#include "matrix.hpp"
#include "field.hpp"


sf::Vector2i CalculateTile(sf::Vector2i position, sf::Vector2i tileDimentions);

Matrix<int> TextureMatrix(Field const& field);

sf::Vector2i CalculateTileDimensions(sf::Vector2i const& screenDimensions, sf::Vector2i const& fieldDimentions);
#endif