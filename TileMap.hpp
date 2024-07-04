#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "matrix.hpp"

sf::Color CalculateColor(int const& tileNumber){
  sf::Color color;
  switch(tileNumber){
    case 0:
    color = sf::Color::White;
    break;
    case 1:
    color=sf::Color::Magenta;
    break;
    default:
    color=sf::Color::Cyan;
    break;
  }
  return color;
}

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
  bool load(sf::Vector2i tileMapSize,
            const int *tilesType, unsigned int width, unsigned int heigth)
  {

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * heigth * 4);

    for (unsigned int i = 0; i < width; ++i)
      for (unsigned int j = 0; j < heigth; ++j)
      {
        int tileNumber = tilesType[i + j * width];
        sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(i * tileMapSize.x, j * tileMapSize.y);
        quad[1].position =
            sf::Vector2f((i + 1) * tileMapSize.x, j * tileMapSize.y);
        quad[2].position =
            sf::Vector2f((i + 1) * tileMapSize.x, (j + 1) * tileMapSize.y);
        quad[3].position =
            sf::Vector2f(i * tileMapSize.x, (j + 1) * tileMapSize.y);

        sf::Color color = CalculateColor(tileNumber);

        // define its 4 texture coordinates
        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
      }
    return true;
  }

  bool load(sf::Vector2i tileMapSize,
            Matrix<int> matrix)
  {
    const int *tilesType = &matrix(1, 1);
    unsigned int width = matrix.GetLength();
    unsigned int heigth = matrix.GetHeight();
    return load(tileMapSize, tilesType, width, heigth);
  }

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    states.transform *= getTransform();
    target.draw(m_vertices, states);
  }

  sf::VertexArray m_vertices;
};

#endif