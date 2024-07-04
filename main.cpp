#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "TileMap.hpp"
#include "cell.hpp"
#include "field.hpp"
#include "matrix.hpp"
#include "texture.hpp"
#include <iostream>

int main()
{
  try
  {

    auto const delta_t{sf::milliseconds(1)};
    int const fps = 5;

    sf::Vector2i const screenDimensions{500, 500};
    sf::Vector2i fieldDimentions{0, 0};
    sf::Vector2i tileDimentions{0, 0};
    int n_cells{0};

    std::cout << "Inserire numero di righe" << '\n';
    std::cin >> fieldDimentions.y;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in rows selection");
    }
    std::cout << "Inserire numero di colonne" << '\n';
    std::cin >> fieldDimentions.x;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in columns selection");
    }
    std::cout << "Inserire numero di celle vive" << '\n';
    std::cin >> n_cells;
    if (!std::cin.good())
    {
      throw std::runtime_error("error in number of alive cells selection");
    }

    tileDimentions = CalculateTileDimensions(screenDimensions, fieldDimentions);

    sf::RenderWindow window(sf::VideoMode(tileDimentions.x * fieldDimentions.x,
                                          tileDimentions.y * fieldDimentions.y),
                            "game of life",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(100, 30));

    Field field{fieldDimentions.y, fieldDimentions.x, n_cells};
    TileMap tiles;

    // chances of improval here, could make the clock independent of the fps part
    sf::Clock clock;
    sf::Time elapsed;

    bool game_is_on{false};

    // also could check if there where any event and if there weren't not redraw everything
    while (window.isOpen())
    {
      sf::Vector2i mouseTile =
          CalculateTile(sf::Mouse::getPosition(window), tileDimentions);

      sf::Event event;
      while (window.pollEvent(event))
      {
        switch (event.type)
        {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::MouseButtonPressed:
          switch (event.mouseButton.button)
          {
          case sf::Mouse::Right:
            game_is_on = !game_is_on;
            break;
          default:
            break;
          }
          break;
        default:
          break;
        }
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsInRange(field.GetMatrix(), mouseTile.y, mouseTile.x))
      {
        field.SetAlive(mouseTile.y, mouseTile.x);
      }

      elapsed = clock.getElapsedTime();
      if (game_is_on && elapsed > sf::milliseconds(1000 / fps))
      {
        field.evolve();
        clock.restart();
      }

      if (!tiles.load(tileDimentions, TextureMatrix(field)))
        return -1;
      window.clear();
      window.draw(tiles);
      window.display();
    }
  }
  catch (std::runtime_error &error)
  {
    std::cout << error.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (std::out_of_range &error)
  {
    std::cout << error.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cout << "unknown exception occurred";
    return EXIT_FAILURE;
  }
}
