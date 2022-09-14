#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

//#include <iomanip>

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

    // We gotta check if the file exists/the file is valid. If not, return nullptr
    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open()){
        cout << "File: " << fileName << " does not exist." << endl;
        return nullptr;
    }

    //Now that we know the file exists, we can check the file. For nitty-gritty stuff

    // We have to check if there are valid maxRow, maxCol, and player spawn before we do anything
    for (int i = 0; i < 2; i++){
        if (i == 0){
            inputFile >> maxRow;
            if (inputFile.fail()){
                cout << "There is not a valid maxRow value" << endl;
                return nullptr;
            }
            inputFile >> maxCol;
            if (inputFile.fail()){
                cout << "There is not a valid maxCol value" << endl;
                return nullptr;
            }
        }
        else{
            inputFile >> player.row;
            if (inputFile.fail()){
                cout << "There is not a valid player.row value" << endl;
                return nullptr;
            }
            inputFile >> player.col;
            if (inputFile.fail()){
                cout << "There is not a valid player.col value" << endl;
                return nullptr;
            }
        }
    }

    // Now we have to check if maxRow, maxCol and player spawn are valid

    // We have to check if they are numeric or not. 
    string strMaxRow = std::to_string(maxRow);
    string strMaxCol = std:: to_string(maxCol);
    string strPlayerRow = std::to_string(player.row);
    string strPlayerCol = std::to_string(player.col);

    for (int i = 0; i < strMaxCol.size(); i++){
        if ((strMaxCol.at(i) >= 48 && strMaxCol.at(i) <= 57) || strMaxCol.at(i) == '-'){
            continue;
        }
        else{
            cout << "Not a valid numeric value for maxCol" << endl;
            return nullptr;
        }
    }

    for (int i = 0; i < strMaxRow.size(); i++){
        if ((strMaxRow.at(i) >= 48 && strMaxRow.at(i) <= 57) || strMaxRow.at(i) == '-'){
            continue;
        }
        else{
            cout << "Not a valid numeric value for maxRow" << endl;
            return nullptr;
        }
    }

    for (int i = 0; i < strPlayerCol.size(); i++){
        if ((strPlayerCol.at(i) >= 48 && strPlayerCol.at(i) <= 57) || strPlayerCol.at(i) == '-'){
            continue;
        }
        else{
            cout << "Not a valid numeric value for player spawn col" << endl;
            return nullptr;
        }
    }

    for (int i = 0; i < strPlayerRow.size(); i++){
        if ((strPlayerRow.at(i) >= 48 && strPlayerRow.at(i) <= 57) || strPlayerRow.at(i) == '-'){
            continue;
        }
        else{
            cout << "Not a valid numeric value for player spawn row" << endl;
            return nullptr;
        }
    }

    // We check if they are 0 or negative
    if (maxRow <= 0){
        cout << "maxRow is less than or equal to 0" << endl;
        return nullptr;
    }
    if (maxCol <= 0){
        cout << "maxCol is less than or equal to 0" << endl;
        return nullptr;
    }

    // We check if they will produce <=INT32_MAX tiles
    if (INT32_MAX/double(maxRow) <= double(maxCol)){
        cout << "You will have more than or exactly INT32_MAX tiles!" << endl;
        return nullptr;
    }

    if (player.row < 0 || player.row >= maxRow){
        cout << "Invalid player spawn row" << endl;
        return nullptr;
    }
    if (player.col < 0 || player.col >= maxRow){
        cout << "Invalid player spawn col" << endl;
        return nullptr;
    }
    cout << "Reading row x col dimmensions..." << endl;

    char ** map = new char*[maxRow];
    for (int row = 0; row < maxRow; row++){
        map[row] = new char [maxCol];
    }

    char currentChar;
    bool invalidChar = false;

    for (int row = 0; row < maxRow; row ++){
        for (int col = 0; col < maxCol; col++){
            inputFile >> currentChar;
            if (currentChar != TILE_OPEN && currentChar != TILE_TREASURE && currentChar != TILE_AMULET && currentChar != TILE_MONSTER && currentChar != TILE_PILLAR && currentChar != TILE_DOOR && currentChar != TILE_EXIT ){
                cout << "There is an invalid character in the map!" << endl;
                invalidChar = true;
                break;
            }
            else{
                map[row][col] = currentChar;
            }
        }
        if (invalidChar){
            break;
        }
    }
    if (invalidChar){
        for (int row = 0; row < maxRow; row++){
            delete [] map[row];
        }
        delete [] map;
        map = nullptr;
    }
    else{
        if (map[player.row][player.col] == '!' || map[player.row][player.col] == '?'){
            cout << "Player will get placed on an exit!" << endl;
            for (int row = 0; row < maxRow; row++){
                delete [] map[row];
            }
            delete [] map;
            map = nullptr;
        }
        else{
            map[player.row][player.col] = TILE_PLAYER;
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if (input == 'W' || input == 'w'){
        nextRow = nextRow - 1;
        return;
    }
    else if (input == 'S' || input == 's'){
        nextRow = nextRow + 1;
        return;
    }
    else if (input == 'A' || input == 'a'){
        nextCol = nextCol - 1;
        return;
    }
    else if (input == 'D' || input == 'd'){
        nextCol = nextCol + 1;
        return;
    }
    else{
        return;
    }
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char ** map = new char*[maxRow];
    for (int row = 0; row < maxRow; row++){
        map[row] = new char [maxCol];
    }
    for (int row = 0; row < maxRow; row++){
        for (int col = 0; col < maxCol; col++){
            map[row][col] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr){
        maxRow = 0;
        return;
    }

    for (int row = 0; row < maxRow; row++){
        delete [] map[row];
    }
    delete [] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr){
        return nullptr;
    }

    //We gonna take out the player and put him back in the end
    int playerRow;
    int playerCol;
    bool playerFound = false;
    //Let's look for the player in the map
    for (int row = 0; row < maxRow; row++){
        for (int col = 0; col < maxCol; col ++){
            if (map[row][col] == 'o'){
                playerCol = col;
                playerRow = row;
                map[row][col] = '-';
                playerFound = true;
                break;
            }
        }
        if (playerFound){
            break;
        }
    }

    char ** bigMap = createMap(maxRow*2,maxCol*2);

    int smallRow;
    int smallCol;
    
    for (int row = 0; row < maxRow*2; row++){
        for (int col = 0; col < maxCol*2; col ++){
            smallRow = row;
            smallCol = col;
            if (row >= maxRow){
                smallRow = row-maxRow;
            }
            if (col >= maxCol){
                smallCol = col-maxCol;
            }
            bigMap[row][col] = map[smallRow][smallCol]; 
        }
    }

    for (int row = 0; row < maxRow*2; row++){
        for (int col = 0; col < maxCol*2; col ++){
            cout << bigMap[row][col] << endl;
        }
    }

    // We delete the small map and set a temp val for maxRow since it will be set to 0
    int tempMaxRow = maxRow;
    deleteMap(map,maxRow);

    // We double the sizes of maxRow and maxCol
    maxRow = tempMaxRow*2;
    maxCol = maxCol*2;

    //We gotta put the player back
    bigMap[playerRow][playerCol] = 'o';
    return bigMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    return false;
}
