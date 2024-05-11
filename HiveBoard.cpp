#include "HiveBoard.hpp"

using namespace std;

// begin coord

    coord coord::returnDirection(string direction){
        if(direction == "NE"){
            return returnNE();
        }
        else if(direction == "E"){
            return returnE();
        }
        else if(direction == "SE"){
            return returnSE();
        }
        else if(direction == "SW"){
            return returnSW();
        }
        else if(direction == "W"){
            return returnW();
        }
        else if(direction == "NW"){
            return returnNW();
        }
        else{
            cout << "Invalid direction" << endl;
            return coord();
        }
    }

    int coord::rightScore(){
        if(z % 2 == 0){//if even
            return x + (z / 2);
        }else{//if odd, get NE
            return x + ((z + 1) / 2);
        }
    }
    int coord::leftScore(){
        if(z % 2 == 0){//if even
            return x + (z / 2);
        }else{//if odd
            return (x - 1) + ((z + 1) / 2);
        }
    }

    void coord::printCoord(){
        printf("(%+03d, %+03d, %+03d)\n", x, y, z);
    }

/*
          (-02, +00, +02)BP   (-01, -01, +02)BP   (+00, -02, +02)WP
(-02, +01, +01)WP   (-01, +00, +01)WP
 
*/
// end coord

// begin HivePiece

    //constructors
    HivePiece::HivePiece(){
        color = false;
        type = 'E';
        c = coord();

        numAdj = 0;
        numWhiteAdj = 0;
        numBlackAdj = 0;
    }

// end HivePiece

// begin HiveBoard

    //constructor
    HiveBoard::HiveBoard(){
        size = NUM_PIECES + 1;
        farLeft, farRight, top, bottom = 0;

        board = makeBoard(size);
    }

    //move functions, NE explains the process
    void HiveBoard::moveNE(HivePiece* tile){
        //make newcoord variable, because it is used twice
        coord newCoord = tile->c.returnNE();
        //move the tile
        getTile(newCoord) = tile;
        //set the old tile to nullptr
        getTile(tile->c) = nullptr;
        //set the tile's coord to the new coord
        tile->c = newCoord;

    }
    void HiveBoard::moveE(HivePiece* tile){
        coord newCoord = tile->c.returnE();
        getTile(newCoord) = tile;
        getTile(tile->c) = nullptr;
    }
    void HiveBoard::moveSE(HivePiece* tile){
        coord newCoord = tile->c.returnSE();
        getTile(newCoord) = tile;
        getTile(tile->c) = nullptr;
    }
    void HiveBoard::moveSW(HivePiece* tile){
        coord newCoord = tile->c.returnSW();
        getTile(newCoord) = tile;
        getTile(tile->c) = nullptr;
    }
    void HiveBoard::moveW(HivePiece* tile){
        coord newCoord = tile->c.returnW();
        getTile(newCoord) = tile;
        getTile(tile->c) = nullptr;
    }
    void HiveBoard::moveNW(HivePiece* tile){
        coord newCoord = tile->c.returnNW();
        getTile(newCoord) = tile;
        getTile(tile->c) = nullptr;
    }

    //whole board functions
    void HiveBoard::printBoard(){
        //get top left using far left
        coord TopLeft = coord(farLeft - (top / 2), -farLeft - (top / 2), top);

        if(top % 2 == 1){//if top is odd
            if(top > 0){//positive
                TopLeft.x--;
            }else{//negative
                TopLeft.y++;
            }
        }

        //get top right using far right
        coord TopRight = coord(farLeft - (top / 2), -farLeft - (top / 2), top);

        if(top % 2 == 1){//if top is odd
            if(top > 0){//positive
                TopLeft.y--;
            }else{//negative
                TopLeft.x++;
            }
        }

        
        // we now have top right and top left coords. print each row while row != bottom - 1
        int row = top;
        bool in = true;
        coord curr;
        HivePiece* tile;
        while(curr.z != bottom - 1){
            //print the row
            if(in){//if this is an in row, print the extra spaces
                cout << "         ";//9 spaces
            }
            //always runs, just prints coords and piece info of a row
            while(curr != TopRight.returnE()){
                tile = getTile(curr);
                curr.printCoord();//prints coord
                tile->Color();//prints color
                cout << tile->type;//prints type
                cout << "   ";//3 spaces

                curr = curr.returnE();
            }

            //goes to next row based on if in or out
            if(in){
                in = false;
                TopLeft = TopLeft.returnSW();
                TopRight = TopRight.returnSE();
                curr = TopLeft;
            }else{
                in = true;
                TopLeft = TopLeft.returnSE();
                TopRight = TopRight.returnSW();
                curr = TopLeft;
            }
        }        
    }
/*
            (-2, 0, 2) (-1, -1, 2) (0, -2, 2)
        (-2, 1, 1) (-1, 0, 1) (0, -1, 1) (1, -2, 1)
   (-2, 2, 0) (-1, 1, 0) (0, 0, 0) (1, -1, 0) (2, -2, 0)
       (-1, 2, -1) (0, 1, -1) (1, 0, -1) (2, -1, -1)
              (0, 2, -2) (1, 1, -2) (2, 0, -2)
*/

/*
          (-02, +00, +02)BP   (-01, -01, +02)BP   (+00, -02, +02)WP
(-02, +01, +01)WP   (-01, +00, +01)WP
 
*/
    HivePiece**** HiveBoard::makeBoard(int size){
        board = new HivePiece***[size];
        for(int i=0; i<size; i++){
            board[i] = new HivePiece**[size];
            for(int j=0; j<size; j++){
                board[i][j] = new HivePiece*[size];
                for(int k=0; k<size; k++){
                    board[i][j][k] = new HivePiece();
                }
            }
        }
    }

    void HiveBoard::updateBoard(coord c){
        //don't do anything if new coord doesn't go past edge
        if(abs(c.x) < size && abs(c.y) < size && abs(c.z) < size){
            return;
        }
    }
    //setters
    bool movePiece(coord start, coord end);
    bool placePiece(coord tile); 

    //checkers for game rules
    bool canPlace(coord tile);
    bool canRemove(coord tile);

// end HiveBoard

