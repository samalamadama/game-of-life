#include "field.hpp"

#include <algorithm>

#include "cell.hpp"
#include "matrix.hpp"

int Field::near_alive(int y, int x) const
{
  int counter = 0;
  int n_row = field_.GetHeight();
  int n_column = field_.GetLength();

  for (int i = std::max(y - 1, 1); i <= std::min(y + 1, n_row); ++i)
  {
    for (int j = std::max(x - 1, 1); j <= std::min(x + 1, n_column); ++j)
    {
      if (IsAlive(field_(i, j)) && (i != y || j != x))
        ++counter;
    }
  }
  return counter;
}

bool Field::evolve()
{
  Field const initial_state{field_};
  int near_alive_cells{0};
  bool success{true};
  for (int i = 1; i <= field_.GetHeight(); ++i)
    for (int j = 1; j <= field_.GetLength(); ++j)
    {
      if (success)
      {
        near_alive_cells = initial_state.near_alive(i, j);
        success =
            field_(i, j).evolve(near_alive_cells);
      }
    };
  return success;
}