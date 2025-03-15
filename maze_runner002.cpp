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

class Vec {
    int x;
    int y;
    public:
    Vec(int x = 0, int y = 0): x(x), y(y) {}
    void setVec(int _x, int _y) {setX(_x); setY(_y);}
    void setX(int _x) {x = _x;}
    void setY(int _y) {y = _y;}
    int getX() {return x;}
    int getY() {return y;}
    Vec getSum(Vec vec2) {return Vec(x + vec2.getX(), y + vec2.getY());}
    void add(Vec vec2) {x += vec2.getX(); y += vec2.getY();}
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
        
        char typeIcon = ' ';
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
    Vec size;
    Cell maze[MAZE_MAX_SIZE][MAZE_MAX_SIZE];
    
    public:
    Maze(int x = MAZE_MAX_SIZE, int y = MAZE_MAX_SIZE, CELL_TYPE _type = WALL) {
        if (x > MAZE_MAX_SIZE || y > MAZE_MAX_SIZE) {
            std::cout << "Maze size is beyond MAZE_MAX_SIZE";
            return;
        }
        size.setVec(x, y);
        for(int i = 0; i < size.getY(); i++) 
            for(int j = 0; j < size.getX(); j++)
                this->setCell(Vec(j, i), _type);
    }
    
    Cell getCell(Vec vec) {return maze[vec.getY()][vec.getX()];}
    int getSizeX() {return size.getX();}
    int getSizeY() {return size.getY();}
    
    void setCell(Vec vec, CELL_TYPE _type) {
        (&maze[vec.getY()][vec.getX()])->setType(_type);
    }
    
    void print() {
        for(int i = 0; i < size.getY(); i++) {
            for(int j = 0; j < size.getX(); j++) {
                this->getCell(Vec(j, i)).print();
                if(j + 1 < size.getX()) std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
    
    void r(Vec dir, Vec pos int step) {
        const int dirs = 4
        enum DIR {RIGHT, LEFT, UP, DOWN};
        Vec surr[dirs];
        
        if(pos.getX() > 0 &&) surr[RIGHT] = Vec(-1, 0);
        if(pos.getX() + 1 < getSizeX()) surr[LEFT] = Vec(1, 0);
        if(pos.getY() > 0) surr[UP] = Vec(0, -1);
        if(pos.getY() + 1 < getSizeY()) surr[DOWN] = Vec(0, 1);
        
        for(int i = 0; i < dirs; i++)
            surr[i].sum(pos);
    }
};

void import(Maze& game, std::string b[]) {
    CELL_TYPE _type = NONE;
    for(int i = 0; i < game.getSizeY(); i++)
        for(int j = 0; j < game.getSizeX(); j++) {
            switch(b[i][j]) {
                case 'S': _type = START; break;
                case 'E': _type = END; break;
                case '.': _type = PATH; break;
                case '#': _type = WALL; break;
                default: _type = NONE; break;
            }
            game.setCell(Vec(j, i), _type);
        }
}

int main() {
    Maze game;
    import(game, board);
    
    
    game.print();
}
