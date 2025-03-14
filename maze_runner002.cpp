#include <iostream>
#include <vector>

#define MAZE_MAX_SIZE 10

std::string board[MAZE_MAX_SIZE] = {
    "##########",
    "##########",
    "##########",
    "##########",
    "##########",
    "##########",
    "##########",
    "##########",
    "##########",
    "##########"
};

enum CELL_TYPE {
    NONE, START, END,
    PATH, WALL
};

class Cell {
    CELL_TYPE type;
    bool isPathExists;
    public:
    
    Cell(CELL_TYPE _type = NONE) : type(_type), isPathExists(false) {}
    int getType() {return type;}
    void setType(CELL_TYPE _type) {type = _type;}
    void print() {
        if(isPathExists and type == PATH) {
            std::cout << '*';
            return;
        }
        
        switch(type) {
            case START: typeIcon = 'S'; break;
            case END: typeIcon = 'E'; break;
            case PATH: typeIcon = '.'; break;
            case WALL: typeIcon = '#'; break;
            default: typeIcon = 'X'; break;    
        }
        std::cout << typeIcon;
    }
};

class Maze {
    int col;
    int row;
    Cell maze[MAZE_MAX_SIZE][MAZE_MAX_SIZE];
    
    public:
    Maze(int c = MAZE_MAX_SIZE, int r = MAZE_MAX_SIZE, CELL_TYPE _type = WALL) {
        if (c > MAZE_MAX_SIZE || r > MAZE_MAX_SIZE) {
            std::cout << "Maze size is beyond MAZE_MAX_SIZE";
            return;
        }
        col = c;
        row = r;
        for(int i = 0; i < r; i++) 
            for(int j = 0; j < c; j++)
                this->setCell(j, i, _type);
    }
    
    Cell getCell(int c, int r) {return maze[r][c];}
    int getCol() {return col;}
    int getRow() {return row;}
    
    void setCell(int c, int r, CELL_TYPE _type) {
        (&maze[r][c])->setType(_type);
    }
    
    void print() {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                this->getCell(j, i).print();
                if(j + 1 < col) std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
};

void import(Maze& game, std::string b[]) {
    CELL_TYPE _type = NONE;
    for(int i = 0; i < game.getRow(); i++)
        for(int j = 0; j < game.getCol(); j++) {
            switch(b[i][j]) {
                case 'S': _type = START; break;
                case 'E': _type = END; break;
                case '.': _type = PATH; break;
                case '#': _type = WALL; break;
                default: _type = NONE; break;
            }
            game.setCell(j, i, _type);
        }
}

int main() {
    Maze game;
    import(game, board);
    
    
    game.print();
}