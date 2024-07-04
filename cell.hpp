#ifndef CELL_HPP
#define CELL_HPP


enum class cell_status { dead, alive};

class Cell {
 public:
  Cell() : status_{cell_status::dead} {}
  Cell(cell_status status) :status_{status} {}
  cell_status GetStatus() const { return status_; }
  void SetStatus(cell_status status) { status_ = status; }
  bool evolve (int near_alive) {
    bool success{true};
    switch(status_){
      case cell_status::alive:
        switch(near_alive){
          case 0:
          case 1:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
          SetStatus(cell_status::dead);
          break;
          case 2:
          case 3:
          break;
          default:
          success=false;
          break;
        }
      break;
      case cell_status::dead:
        switch(near_alive){
          case 0:
          case 1:
          case 2:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
          break;
          case 3:
          SetStatus(cell_status::alive);
          break;
          default:
          success=false;
          break;
        }
      break;
      default:
      success=false;
    }
    return success;
  }
 private:
  cell_status status_;
};

bool IsDead(Cell const& cell);
bool IsAlive(Cell const& tcell);

#endif