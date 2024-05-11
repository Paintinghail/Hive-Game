#ifndef HIVEBOARD_HPP
#define HIVEBOARD_HPP

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cstdlib>

const int QUEEN = 1;
const int SOLDIER_ANT = 3;
const int SPIDER = 2;
const int GRASSHOPPER = 3;
const int BEETLE = 2;

const string directions[6] = {"NE", "E", "SE", "SW", "W", "NE"};

const int NUM_PIECES = (QUEEN + SOLDIER_ANT + SPIDER + GRASSHOPPER + BEETLE)*2;

using namespace std;
/*
            (-2, 0, 2) (-1, -1, 2) (0, -2, 2)
        (-2, 1, 1) (-1, 0, 1) (0, -1, 1) (1, -2, 1)
   (-2, 2, 0) (-1, 1, 0) (0, 0, 0) (1, -1, 0) (2, -2, 0)
       (-1, 2, -1) (0, 1, -1) (1, 0, -1) (2, -1, -1)
              (0, 2, -2) (1, 1, -2) (2, 0, -2)

*/

struct coord
{
    //constructors
    coord(){x = 0; y = 0; z = 0;}
    coord(int x, int y, int z) : x(x), y(y), z(z) {}

    //direction functions
    coord returnDirection(string direction);
    coord returnNE(){return coord(x, y - 1, z + 1);}
    coord returnE(){return coord(x + 1, y - 1, z);}
    coord returnSE(){return coord(x + 1, y, z - 1);}
    coord returnSW(){return coord(x, y + 1, z - 1);}
    coord returnW(){return coord(x - 1, y + 1, z);}
    coord returnNW(){return coord(x - 1, y, z + 1);}

    // Overload the equality operator
    bool operator==(const coord& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Overload the inequality operator
    bool operator!=(const coord& other) const {
        return !(*this == other); // Utilize the already defined equality operator
    }

    //for printBoard. The int returned is for the x.
    int rightScore();
    int leftScore();
    void printCoord();

    int x;
    int y;
    int z;

};

struct HivePiece{
    bool color;
    char type;//E = empty, Q = queen, A = ant, S = spider, G = grasshopper, B = beetle
    coord c;

    int numAdj;
    int numWhiteAdj;
    int numBlackAdj;
    unordered_map<string, HivePiece*> adj = {
        {"NE", nullptr},
        {"E", nullptr},
        {"SE", nullptr},
        {"SW", nullptr},
        {"W", nullptr},
        {"NW", nullptr}
    };

    HivePiece* below; //for beetle

    //constructors
    HivePiece();
    HivePiece(bool color, char type, coord c) : color(color), type(type), c(c) {}

    //getters
    HivePiece* getAdj(string direction){ return adj[direction]; }


};

class HiveBoard{
    public:
        //constructor
        HiveBoard();
        //getter
        //has to account for arrays starting at 0. coord can be negative, but this function will return the correct tile
        HivePiece*& getTile(const coord& tile) {return board[tile.x + 11][tile.y + 11][tile.z + 11];}

        //direction move functions
        void moveNE(HivePiece* tile);
        void moveE(HivePiece* tile);
        void moveSE(HivePiece* tile);
        void moveSW(HivePiece* tile);
        void moveW(HivePiece* tile);
        void moveNW(HivePiece* tile);

        //whole board functions
        void printBoard();
        void doubleBoard();
        HivePiece**** constructBoard(int size);
        void destructBoard();

        //setters
        bool movePiece(coord start, coord end);
        bool placePiece(coord tile); 

        //checkers for game rules
        bool canPlace(coord tile);
        bool canRemove(coord tile);

    private:
        //for arr double
        HivePiece**** board;
        int size;
        

        int farLeft, farRight, top, bottom;


        unordered_map<char, int> blackPieces = {
            {'Q', QUEEN},
            {'A', SOLDIER_ANT},
            {'S', SPIDER},
            {'G', GRASSHOPPER},
            {'b', BEETLE}
        };
        unordered_map<char, int> whitePieces = {
            {'Q', QUEEN},
            {'A', SOLDIER_ANT},
            {'S', SPIDER},
            {'G', GRASSHOPPER},
            {'b', BEETLE}
        };
};

/*
            (-2, 0, 2) (-1, -1, 2) (0, -2, 2)
        (-2, 1, 1) (-1, 0, 1) (0, -1, 1) (1, -2, 1)
   (-2, 2, 0) (-1, 1, 0) (0, 0, 0) (1, -1, 0) (2, -2, 0)
       (-1, 2, -1) (0, 1, -1) (1, 0, -1) (2, -1, -1)
              (0, 2, -2) (1, 1, -2) (2, 0, -2)
*/

/*
HivePiece
    bool color
    char type
    int x, y, z
    unordered_map<string, HivePiece*> adj
    int numAdj
    int numBlackAdj
    int numWhiteAdj

What to check for place tile?
    false if numAdj = 0
    false if numEnemyAdj !=0

    and make sure that the move is a legal move for a certain piece

What to check for remove tile?
    true if numAdj = 1, 5, 6
    false if an adj tile's numAdj = 1
    if numAdj == 2, 3, 4
        NE, E, SE, SW, W, NW
        loop until you get to an empty tile
        you'll loop 6 more times, including the tile you're on
        if it == 1, add to search vector
        turn boolean on
        if you get another 1 and the boolean's on, don't add it to the vector
        once you hit another 0, turn boolean off
        loop til you get to all 6 adj tiles

        true if vector.size = 1

        dfs if vector size = 2 or 3

***CENTER BOARD NEW***
    Array doubling
    Now an O(n) operation doesn't have to be preformed constantly, a player has to actively try to break the board
    Because this operation takes place at after at least 2n moves, it feels like a O(1) operation
    Now to center the board, you can simply update the center pointer to the new center

    have HiveBoard keep track of the board size
    change the board variable to HivePiece** board bc it points to an array of pointers

*/
#endif