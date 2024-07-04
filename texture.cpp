#include "texture.hpp"

sf::Vector2i CalculateTile(sf::Vector2i position, sf::Vector2i tileDimentions) {
  int row = position.y / tileDimentions.y + 1;
  int column = position.x / tileDimentions.x + 1;

  return {column, row};
}

Matrix<int> TextureMatrix(Field const& field) {
  int const n_row{field.GetMatrix().GetHeight()};
  int const n_column{field.GetMatrix().GetLength()};
  Matrix<int> intMatrix(n_row, n_column);
  for (int i = 1; i <= n_row; ++i)
    for (int j = 1; j <= n_column; ++j) {
      intMatrix(i, j) = static_cast<int>(field.GetMatrix()(i, j).GetStatus());
    }
  return intMatrix;
}

sf::Vector2i CalculateTileDimensions(sf::Vector2i const& screenDimensions, sf::Vector2i const& fieldDimentions){
    int dimensions = std::min(screenDimensions.x/fieldDimentions.x, screenDimensions.y/fieldDimentions.y);
    dimensions = std::max(dimensions, 1);
    return sf::Vector2i(dimensions, dimensions);
}