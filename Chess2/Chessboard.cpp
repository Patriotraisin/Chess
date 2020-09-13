#include "Piece.hpp"
#include "Chessboard.hpp"
#include "Arbiter.hpp"

Chessboard::Chessboard(){
}

void Chessboard::emptySquare(int x, int y){
    chessboard[x][y].define(0, 0, ((10*y)+x), "  ", 0);
}

void Chessboard::printBoard(){
    cout << "\n\n\n\n" << endl;
    for (int y = 8; y >=1; y--){
        cout << " ==================================" << endl;
        cout << y << "||";
        for (int x = 1; x <= 8; x++){
            cout << chessboard[x][y].pieceName << "||";
            
        }
        
        cout << "\n";
    }
    cout << "  A   B   C   D   E   F   G   H" << endl;
    
}

void Chessboard::initialize(){
        for (int y = 1; y <= 8; y++){
            for (int x = 1; x <= 8; x++){
                emptySquare(x,y);
            }
        }
        for (int y = 1; y <= 8; y++){
            for (int x = 1; x <= 8; x++){
                if (y == 1){ // white minor / major pieces
                    if ((x == 1) || (x == 8)){
                        chessboard[x][y].define(4, 1, ((10*y)+x), "WR", 5); // white rooks
                    }
                    if ((x == 2) || (x == 7)){
                        chessboard[x][y].define(3, 1, ((10*y)+x), "WN", 3); // white knights
                    }
                    if ((x == 3) || (x == 6)){
                        chessboard[x][y].define(2, 1, ((10*y)+x), "WB", 3.25); // white bishops
                    }
                    if (x == 5){
                        chessboard[x][y].define(6, 1, ((10*y)+x), "WK", 1000); // white king
                    }
                    if (x == 4){
                        chessboard[x][y].define(5, 1, ((10*y)+x), "WQ", 9); // white queen
                    }
                }
                
                if (y == 8){ // black minor / major pieces
                    if ((x == 1) || (x == 8)){
                        chessboard[x][y].define(4, -1, ((10*y)+x), "BR", 5); // black rooks
                    }
                    if ((x == 2) || (x == 7)){
                        chessboard[x][y].define(3, -1, ((10*y)+x), "BN", 3); // black knights
                    }
                    if ((x == 3) || (x == 6)){
                        chessboard[x][y].define(2, -1, ((10*y)+x), "BB", 3.25); // black bishops
                    }
                    if (x == 5){
                        chessboard[x][y].define(6, -1, ((10*y)+x), "BK", 1000); // black king
                    }
                    if (x == 4){
                        chessboard[x][y].define(5, -1, ((10*y)+x), "BQ", 9); // black queen
                    }
                }
                
                // pawns
                if (y == 2){
                    chessboard[x][y].define(1, 1, ((10*y)+x), "WP", 1); // white pawn
                }
                if (y == 7){
                    chessboard[x][y].define(1, -1, ((10*y)+x), "BP", 1); // black pawn
                }
                
            }
        }
}

void Chessboard::move(int isWhite){
    string move;
    string piece;
    float value = 0;
    int pawnVar = 0;
    int pawnUpperBound = 0;
    int pawnLowerBound = 0;
    bool isLegal = 0;
    int newX = 0, newY = 0, oldX = 0, oldY = 0; // positional variables
    
    // pawn variable
    if (isWhite == 1){
        pawnVar = 1;
    }
    else if (isWhite == -1){
        pawnVar = 8;
    }
    // end of pawn variable
    while (!isLegal){
        if (isWhite == 1){
            cout << "White to move. ";
        }
        else if (isWhite == -1){
            cout << "Black to move. ";
        }
        else{
            cout << "error detected." << endl;
            break;
        }
        //
        cout << "Input move (correct syntax, case-sensitive):" << endl;
        cin >> move;
        if (move.length() < 5){ //
            if (!(isupper(move[0]))){ // pawn move.
                isLegal = 1;
                value = 1;
                if(isWhite == 1){
                    pawnUpperBound = 9;
                    pawnLowerBound = 2; // 2
                    piece = "WP";
                }
                else if (isWhite == -1){
                    pawnUpperBound = 7; // 7
                    pawnLowerBound = 0;
                    piece = "BP";
                }
                else{
                    piece = "error";
                }
                
                if (move[1] == 'x'){ // if captures
                    oldX = (int(move[0]) - 96);
                    newX = (int(move[2]) - 96);
                    newY = (int(move[3]) - 48);
                    //cout << "ISWHITE + PAWNVAR = " << isWhite + pawnVar << endl;
                    for (int count = (newY+isWhite); count != (/*isWhite + */pawnVar); count -= isWhite){
                        if ((chessboard[oldX][count].parity == isWhite) && (chessboard[oldX][count].pieceValue == 1)){
                            oldY = count;
                            //cout << "pawn detected at " << move[0] << oldY << "." << endl; // DEBUGLINE
                            break;
                        }
                        else{
                            //cout << "pawn not detected at Y level" << count << endl;
                        }
                    }
                    //cout << "you are playing pawn captures " << newX <<  newY << " or pawn captures on " << move[2] << move[3] << "." << endl; // DEBUGLINE
                    //cout << "old:" << oldX << oldY << "\nnew: " << newX << newY << "\ndifference Y:" << abs(newY-oldY) << endl;
                    if (chessboard[newX][newY].pieceValue == 0){ // cant capture nothing!
                        isLegal = AB.error(4);
                    }
                    else if (newY == oldY or newX == oldX){
                        isLegal = AB.error(4);
                    }
                    else if (abs(newX-oldX) != 1){
                        isLegal = AB.error(4);
                    }
                    else if (abs(newY-oldY) >= 2){ // you cant move more than these squares.
                        cout << "illegal move: square " << move[0] << newY << " is not a possible destination for " << chessboard[oldX][oldY].pieceName << " on " << move[0] << oldY << endl;
                        isLegal = AB.error(2);
                    }
                    
                } // end of captures.
                else{ // or forward move.
                    newX = (int(move[0]) - 96);
                    newY = (int(move[1]) - 48);
                    oldX = newX;
                    for (int count = newY; count != pawnVar; count -= isWhite){ // scanned to find the location of the old piece
                        if ((chessboard[newX][count].pieceValue == 1) && (chessboard[newX][count].parity == isWhite)){  // finding nearest pawn that is the one which is moved
                            oldY = count;
                            cout << "pawn detected at " << move[0] << oldY << "." << endl;
                            break;
                        }
                    }
                    if ( !((pawnLowerBound < newY) and (newY < pawnUpperBound)) ){ // cant go beyond certain preset boundaries. goes for every pawn move.
                        //cout << "illegal move: not between " << pawnLowerBound << " and " << pawnUpperBound << "." << endl;
                        //cout << move[0] << move[1] << "not within allowed limits." << endl;
                        //cout << "lower bound:" << pawnLowerBound << "upper bound:" << pawnUpperBound << endl;
                        //cout << "error: " << "pawn lower bound is " << pawnLowerBound << " should be < newY = " << newY << endl;
                        //cout << "error: " << "pawn upper bound is " << pawnUpperBound << " should be > newY = " << newY << endl;
                        isLegal = AB.error(2);
                    }
                    //cout << "\ndifference in Y values from new destination to old: " << abs(newY-oldY) << "\nstarting Y value: " << pawnVar+isWhite << "\nnewY:" << newY << "\noldY: " << oldY << "\npawn var: " << pawnVar << "\nis white (1 = white, -1 = black)" << isWhite << endl;
                    else if ((abs(newY-oldY) > 2) && (oldY == (pawnVar+isWhite)) ){ // starting square.
                        //cout << "illegal move: square " << move[0] << newY << " is not a possible destination for " << chessboard[oldX][oldY].pieceName << " on " << move[0] << oldY << endl;
                        isLegal = AB.error(2);
                    }
                    else if ((abs(newY-oldY) > 1) && !(oldY == (pawnVar+isWhite))){
                        isLegal = AB.error(2);
                    }
                    else if (oldY == newY){ // cant go to same square
                        isLegal = AB.error(3);
                        //cout << "illegal move. can't move to same square." << endl;
                    }
                    else if (chessboard[newX][newY].pieceValue != 0){
                        isLegal = AB.error(4);
                        //cout << "illegal move. you cant capture straight." << endl;
                    }
                    else if ((oldY != ((isWhite) + pawnVar)) && (abs(newY-oldY) >= 2)){
                        isLegal = AB.error(2);
                        //cout << oldY << "test" << ((isWhite) + pawnVar)<< "." << endl;
                        //cout << "your coefficient is" << isWhite + pawnVar << endl;
                        //cout << "illegal move. pawns can only move 2 squares on first turn." << endl;
                    }
                } // end of forward move.
            } // end of pawn move
            
            
            
            else if (isupper(move[0])){ // different piece moves.
                cout << "not a pawn move" << endl;
                
                if (move[0] == 'N'){ // knight move
                    // presets
                    isLegal = 1;
                    value = 3;
                    if(isWhite == 1){
                        piece = "WN";
                    }
                    else if (isWhite == -1){
                        piece = "BN";
                    }
                    else{
                        piece = "error";
                    }
                    // end of presets
                    
                    if (move[1] == 'x'){ // if captures
                        newX = (int(move[2]) - 96);
                        newY = (int(move[3]) - 48);
                        cout << "you are planning knight captures on " << newX << newY << " or Nx" << move[2] << move[3] << "." << endl;
                        isLegal = knight_moves(*this, newX, newY, isWhite, &oldX, &oldY); // basic movement vetting
                        if (chessboard[newX][newY].pieceValue == 0){
                            isLegal = AB.error(1);
                        }
                        else if (chessboard[newX][newY].parity == isWhite){
                            isLegal = AB.error(4);
                        }
                        cout << "knight detected at " << oldX << oldY << "." << endl;
                    }
                    else{ // or normal move
                        newX = (int(move[1]) - 96);
                        newY = (int(move[2]) - 48);
                        cout << "you are planning knight " << newX << newY << " or N" << move[1] << move[2] << "." << endl;
                        isLegal = knight_moves(*this, newX, newY, isWhite, &oldX, &oldY); // basic movement vetting
                        if (chessboard[newX][newY].pieceValue != 0){ // if you move you cannot capture.
                            isLegal = AB.error(1);
                        }
                        else if ((newX == oldX) && (newY == oldY)){ // cant attempt to move skip by staying in the same place
                            isLegal = AB.error(3);
                        }
                        else if (chessboard[newX][newY].parity == isWhite){ // cant capture own pieces
                            isLegal = AB.error(4);
                        }
                        cout << "knight detected at " << oldX << oldY << "." << endl;
                    }
                } // end of knight move
                
                else if (move[0] == 'B'){ // bishop move
                    // presets
                    isLegal = 1;
                    value = 3.25;
                    if(isWhite == 1){
                        piece = "WB";
                    }
                    else if (isWhite == -1){
                        piece = "BB";
                    }
                    else{
                        piece = "error";
                    }
                    // end of presets
                    
                    if (move[1] == 'x'){ // if captures
                        newX = (int(move[2]) - 96);
                        newY = (int(move[3]) - 48);
                        cout << "you are planning bishop captures on " << newX << newY << " or Bx" << move[2] << move[3] << "." << endl;
                        
                    }
                    else{ // or normal move
                        newX = (int(move[1]) - 96);
                        newY = (int(move[2]) - 48);
                        cout << "you are planning bishop " << newX << newY << " or B" << move[1] << move[2] << "." << endl;
                    }
                } // end of bishop move
                
                else if (move[0] == 'R'){ // rook move
                    isLegal = 1;
                    value = 5;
                    if (move[1] == 'x'){ // if captures
                        newX = (int(move[2]) - 96);
                        newY = (int(move[3]) - 48);
                        cout << "you are planning rook captures on " << newX << newY << " or Rx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        newX = (int(move[1]) - 96);
                        newY = (int(move[2]) - 48);
                        cout << "you are planning rook " << newX << newY << " or R" << move[1] << move[2] << "." << endl;
                    }
                } // end of rook move
                
                else if (move[0] == 'Q'){ // queen move
                    isLegal = 1;
                    value = 9;
                    if (move[1] == 'x'){ // if captures
                        newX = (int(move[2]) - 96);
                        newY = (int(move[3]) - 48);
                        cout << "you are planning Queen captures on " << newX << newY << " or Qx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        newX = (int(move[1]) - 96);
                        newY = (int(move[2]) - 48);
                        cout << "you are planning Queen " << newX << newY << " or Q" << move[1] << move[2] << "." << endl;
                    }
                } // end of queen move
                else if (move[0] == 'K'){ // king move
                    isLegal = 1;
                    if (move[1] == 'x'){ // if captures
                        newX = (int(move[2]) - 96);
                        newY = (int(move[3]) - 48);
                        cout << "you are planning king captures on " << newX << newY << " or Kx" << move[2] << move[3] << "." << endl;
                    }
                    else{ // or normal move
                        newX = (int(move[1]) - 96);
                        newY = (int(move[2]) - 48);
                        cout << "you are planning king " << newX << newY << " or K" << move[1] << move[2] << "." << endl;
                    }
                } // end of king move
                
                else{ // invalid syntax move
                    cout << "illegal move: invalid syntax" << endl;
                    isLegal = 0;
                } // invalid syntax
                
            } // end of different piece moves.
            
        } // end of < 4
        else{
            isLegal = AB.error(10);
        }
    } // end of while is legal
    // TODO: WRITE MOVE TO FILE
    
    
    cout << oldX << oldY << endl;
    emptySquare(oldX, oldY);
    chessboard[newX][newY].define(1, isWhite, ((10*newY)+newX), piece, value);
    
    
    
} // end of void move


int Chessboard::knight_moves(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY){ // function to calculate possible knight moves, obtain OldX and OldY values.
    const static int offsets[][2]= {{-2,-1},{-2,1}, {-1,-2}, {-1, 2}, {1,-2}, {1,2}, {2,1}, {2,-1},};
    for (int i = 0; i < 8; i++){ // take out invalid squares.
        //cout << (newX+offsets[i][0]) << (newY+offsets[i][1]) << endl;
        if ( (newX+offsets[i][0]) > 8  or (newX+offsets[i][0]) < 1 or (newY+offsets[i][1]) > 8 or (newY+offsets[i][1]) < 0 ){
            //cout << (newX+offsets[i][0]) << (newY+offsets[i][1]) << endl;
        }
        else{ // scan for pieces.
            //cout << "N" <<    char((newX+offsets[i][0])+96)   <<    (newY+offsets[i][1])    << endl;
            /*if ((chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].parity == isWhite)){
             cout << "white piece found at " << (newX+offsets[i][0]) << (newY+offsets[i][1]) << "." << endl;
             }
             if ((chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].pieceValue == 3)){
             cout << "3.0 piece found at " << (newX+offsets[i][0]) << (newY+offsets[i][1]) << "." << endl;
             }*/
            if ((CB.chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].parity == isWhite) && (CB.chessboard[(newX+offsets[i][0])][(newY+offsets[i][1])].pieceValue == 3)){ // if knight
                *oldX = (newX+offsets[i][0]);
                *oldY = (newY+offsets[i][1]);
                return 1;
            }
        } // end of else
    } // end of for loop.
    AB.error(2);
    return 0;
}

int Chessboard::bishop_moves(Chessboard CB, unsigned int newX, unsigned int newY, int isWhite, int* oldX, int* oldY){
    //for (int count == newX)
    return 0;
}



