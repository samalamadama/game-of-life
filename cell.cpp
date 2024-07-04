#include "cell.hpp"

bool IsDead(Cell const& cell) { return cell.GetStatus() == cell_status::dead; }
bool IsAlive(Cell const& cell) {return cell.GetStatus() == cell_status::alive; }