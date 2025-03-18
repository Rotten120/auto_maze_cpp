#include <iostream>
#include <vector>

#define MAZE_MAX_SIZE 10

std::string board[MAZE_MAX_SIZE] = {
    "##########",
    "##########",
    "##.....###",
    "##.###.###",
    "##.#..E###",
    "##.#######",
    "##.....###",
    "####.#####",
    "####S#####",
    "##########"
};

enum CELL_TYPE {
    NONE, START, END,
    PATH, WALL
};

bool orGate(bool arr[], const int size) {
    bool result = false;

    for(int i = 0; i < size; i++) {
        result = result || arr[i];
    }
    return result;
}

class Vec {
    int x;
    int y;
    public:
    Vec(int val = 0): x(val), y(val) {}
    Vec(int x, int y): x(x), y(y) {}
    void setX(int _x) {x = _x;}
    void setY(int _y) {y = _y;}
    int getX() {return x;}
    int getY() {return y;}
    
    Vec operator + (Vec vec2) {
        return Vec(x + vec2.getX(), y + vec2.getY());
    }
    
    bool operator == (Vec vec2) {
        return (x == vec2.getX() && y == vec2.getY());
    }
    
    Vec getRev() {
        return Vec(x * -1, y * -1);
    }
};

class Cell {
    CELL_TYPE type;
    bool isPathExists;

    public:
    Cell(CELL_TYPE _type = NONE) : type(_type), isPathExists(false) {}
    CELL_TYPE getType() {return type;}
    void setType(CELL_TYPE _type) {type = _type;}
    void setPath(bool _isPathExists) {isPathExists = _isPathExists;}
    bool isPath() {return isPathExists;}

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
        size = Vec(x, y);
        for(int i = 0; i < size.getY(); i++) 
            for(int j = 0; j < size.getX(); j++)
                this->setCellType(Vec(j, i), _type);
    }

    Cell getCell(Vec vec) {return maze[vec.getY()][vec.getX()];}
    int getSizeX() {return size.getX();}
    int getSizeY() {return size.getY();}

    void setCellType(Vec vec, CELL_TYPE _type) {
        (&maze[vec.getY()][vec.getX()])->setType(_type);
    }

    void setCellPath(Vec vec, bool _isPathExists) {
        (&maze[vec.getY()][vec.getX()])->setPath(_isPathExists);
    }

    void print() {
        for(int i = 0; i < size.getY(); i++) {
            for(int j = 0; j < size.getX(); j++) {
                getCell(Vec(j, i)).print();
                if(j + 1 < size.getX()) std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool isOutofBounds(Vec pos) {
        return (!(
            pos.getX() > 0 || pos.getX() + 1 < getSizeX() ||
            pos.getY() > 0 || pos.getY() + 1 < getSizeY()
            ));
    }

    bool findPathInit() {
        Vec startPos;
        Vec initDir;

        for(int i = 0; i < size.getY(); i++) {
            for(int j = 0; j < size.getX(); j++) {
                startPos = Vec(j, i);
                if(getCell(startPos).getType() == START) {
                    return findPath(initDir, startPos);
                }
            }
        }

        return false;
    }

    bool findPath(Vec dir, Vec pos) {
        CELL_TYPE posType = getCell(pos).getType();

        if(posType == END) return true;
        if (!(posType == PATH || posType == START)) return false;

        const int dirs = 4;
        bool pathExists[4] = {false, false, false, false};

        Vec delta[dirs] = {
                Vec(-1, 0), Vec(1, 0),
                Vec(0, -1), Vec(0, 1)
            };

        for(int idx = 0; idx < dirs; idx++) {
            Vec targetCellPos = pos + delta[idx];
            if(isOutofBounds(targetCellPos) || (delta[idx].getRev() == dir))
                continue;

            Cell targetCell = getCell(targetCellPos);
            setCellPath(targetCellPos, true);
            pathExists[idx] = true;

            if(!findPath(delta[idx], targetCellPos))
                pathExists[idx] = false;
        }

        bool anyPathsExists = orGate(pathExists, dirs);
        if (!anyPathsExists)
            setCellPath(pos, false);
        return anyPathsExists;
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
            game.setCellType(Vec(j, i), _type);
        }
}

int main() {
    Maze game;
    import(game, board);

    if(!game.findPathInit()) {
        std::cout << "UNSOLVABLE";
    } else {
        game.print();
    }
}