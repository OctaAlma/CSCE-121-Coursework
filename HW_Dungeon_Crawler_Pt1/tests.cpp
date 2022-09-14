#include <iostream>
#include "logic.h"

using std::cout, std::endl, std::string;

// TODO(student): Write unit tests for the functions in logic.h
//                You should end up with at least 500 lines of test code

/* The thing to compile this thing
g++ -std=c++17 -Wall -Wextra -pedantic-errors -Weffc++ -fsanitize=undefined,address -g *.cpp
*/

void variableCount(char ** mapArr, int maxRow, int maxCol, char charToLookFor, int& charCounter, string fileName){
    charCounter = 0;
    for(int i = 0; i < maxRow; i++){
        for (int j = 0; j < maxCol; j++){
            if (mapArr[i][j] == charToLookFor){
                charCounter += 1;
            }
        }
    }
    cout << "There are " << charCounter << " characters of type " << charToLookFor << " in the map " << fileName << endl;
}

/*
void resetCounters(int& playerCounter,int& treasureCounter, int& doorCounter, 
int& pillarCounter,int& monsterCounter,int& amuletCounter,int& blankTileCounter,
int& exitCounter){
    playerCounter = 0;
    treasureCounter = 0; 
    doorCounter = 0;
    pillarCounter = 0;
    monsterCounter = 0;
    amuletCounter = 0;
    blankTileCounter = 0;
    exitCounter = 0;
}*/

void countCharacters(
    char ** map, int maxRow, int maxCol, int& playerCounter, 
    int& treasureCounter, int& doorCounter, int& pillarCounter, int& amuletCounter,
    int& monsterCounter, int& blankTileCounter, int& exitCounter, string fileName){
    
//    resetCounters(playerCounter, treasureCounter, doorCounter, pillarCounter, monsterCounter, amuletCounter, blankTileCounter,exitCounter);

    variableCount(map, maxRow, maxCol, 'o', playerCounter, fileName);
    variableCount(map, maxRow, maxCol, '$', treasureCounter, fileName);
    variableCount(map, maxRow, maxCol, '?', doorCounter, fileName);
    variableCount(map, maxRow, maxCol, '+', pillarCounter, fileName);
    variableCount(map, maxRow, maxCol, '@', amuletCounter, fileName);
    variableCount(map, maxRow, maxCol, 'M', monsterCounter, fileName);
    variableCount(map, maxRow, maxCol, '-', blankTileCounter, fileName);
    variableCount(map, maxRow, maxCol, '!', exitCounter, fileName);
}

int errorForResizeMap(int oldMaxRow, int maxRow, int oldMaxCol, int maxCol, int playerCounter, int oldMonsterCounter, int monsterCounter, int oldBlankTileCounter, int blankTileCounter, int oldExitCounter, int exitCounter){
    cout << "From inside the errorForResizeMap, the value of oldMaxRow is: " << oldMaxRow << " and maxRow is " << maxRow << endl;
    if ((oldMaxRow*2 == maxRow) && (oldMaxCol*2 == maxCol)){
        if (playerCounter == 1){
            if (oldMonsterCounter*4 == monsterCounter){
                if ((oldBlankTileCounter+1)*4 - 1 == blankTileCounter){
                    if (oldExitCounter*4 == exitCounter){
                        return 0;
                    }
                    else{
                        return 5;
                    }
                }
                else{
                    return 4;
                }
            }
            else{
                return 3;
            }
        }
        else{
            return 2;
        }
    }
    else{
        cout << oldMaxRow*2 << "!=" << maxRow << " or " << oldMaxCol*2 << "!=" << maxCol << endl;
        return 1;
    }
}

void resizeErrorDescription(int e){
    if (e == 1){
        cout << "[FAIL]: oldMaxRow * 2 != maxRow or oldMaxCol * 2 != width!" << endl;
    }
    else if (e == 2){
        cout << "[FAIL]: playerCounter != 1 !" << endl;
    }
    else if (e == 3){
        cout << "[FAIL]: oldMonterCounter * 4 != monsterCounter!" << endl;
    }
    else if (e == 4){
        cout << "[FAIL]: (oldBlankTileCounter+1)*4 + 3 != blankTileCounter)!" << endl;
    }
    else if (e ==5){
        cout << "[FAIL]: oldMonterCounter * 4 != monsterCounter!" << endl;
    }
    else{
        cout << "[FAIL]: resizeMap with with error code: " << e << endl;
    }
}

#define EXPECT_EQ(X,Y) if (!(X == Y)) { cout << "[FAIL] ("<<__FUNCTION__<<":"<<__LINE__<<") expected equality of " << #X << " and " << #Y << endl; }

int main() {
    string fileName = "example.txt";
    int maxRow;
    int maxCol;

    int nextRow;
    int nextCol;

    Player user;
    char ** arr;
    char ** bigArr;

    int oldPlayerCounter = 0;
    int oldTreasureCounter = 0;
    int oldDoorCounter = 0;
    int oldPillarCounter = 0;
    int oldMonsterCounter = 0;
    int oldAmuletCounter = 0;
    int oldBlankTileCounter = 0;
    int oldExitCounter = 0;

    int playerCounter = 0;
    int treasureCounter = 0; 
    int doorCounter = 0;
    int pillarCounter = 0;
    int monsterCounter = 0;
    int amuletCounter = 0;
    int blankTileCounter = 0;
    int exitCounter = 0;

    
    // Happy Paths for loadLevel
    {
    // Load example.txt
    try{
        fileName = "example.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr != nullptr){
                    cout << "[PASS]: loadLevel read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }
    catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel could not read " << fileName << endl;
    }

    //UnhappyPaths for loadLevel
    {
    // Try to put player in a pillar tile
    try{
        fileName = "playerSpawnPillar.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[FAIL]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[PASS]: loadLevel read in " << fileName << endl;
    }

    // Try to spawn player in an exit tile
    try{
        fileName = "playerSpawnExit.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did NOT read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel did read in " << fileName << endl;
    }    

    // Try to load a file with negative maxcols
    try{
        fileName = "loadLevelNegRow.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load a file with negative maxrows
    try{
        fileName = "loadLevelNegCol.txt"; 
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    //Try to load a file with a non-numeric player starting col
    try{
        fileName = "startingColNotNumeric.txt"; 
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    //Try to load a file with a non-numeric player starting row
    try{
        fileName = "startingRowNotNumeric.txt"; 
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load a file with negative player starting col
    try{
        fileName = "playerColNegative.txt"; 
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load a file with a negative player starting row
    try{
        fileName = "playerRowNegative.txt"; 
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to open a file with int32max tiles
    try{
        fileName = "int32maxTiles.txt"; //opens an int32max rows x 1 col file
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }
    
    // Try to open a file that is empty
    try{
        fileName = "absolutelyNothing.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }
    
    // Try to open a file with good headers but empty map
    try{
        fileName = "emptyMap.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Map file attempts to spawn player over the row max
    try{
        fileName = "playerOutOfBounds.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Map file attempts to spawn player over the COL max
    try{
        fileName = "playerOutOfBoundsCol.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load with nonNumeric player col 
    try{
        fileName = "loadLevelUnhappy3.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }
    
    // Try to load with nonNumeric player row
    try{
        fileName = "loadLevelUnhappy4.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load a level with invalid characters in map
    try{
        fileName = "loadLevelUnhappy5.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Try to load a level with a ? and a !
    try{
        fileName = "exitAndDoor.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr != nullptr){
            cout << "[PASS]: loadLevel read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel did not read in " << fileName << endl;
    }

    // Try to load a non-existing file
    try{
        fileName = "nonExistantFile.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    //Try to load a file with misleading headers
    try{
        fileName = "loadLevelUnhappy5.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }

    // Load an array with dimmension of 1 row
    try{
        fileName = "loadLevelUnhappy1.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (maxRow == 1){
            deleteMap(arr, maxRow);
            cout << "[PASS]: loadLevel read in " << fileName << endl;
        }
        else{
            //This is some random error just to catch something
            deleteMap(arr, maxRow);
            throw 1;
        }
    }
    catch(...){
        cout << "[FAIL]: loadLevel could not read " << fileName << endl;
    }

    // Load an array with dimmension of 1 column
    try{
        fileName = "loadLevelUnhappy2.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        deleteMap(arr, maxRow);
        if (maxCol == 1){
            cout << "[PASS]: loadLevel read in " << fileName << endl;
        }
        else{
            //This is some random error just to catch something
            throw 1;
        }
    }
    catch(...){
        cout << "[FAIL]: loadLevel could not read " << fileName << endl;
    }

    // Try to load a level with no exit or doors:
    try{
        fileName = "noDoor.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        if (arr == nullptr){
            cout << "[PASS]: loadLevel did not read in " << fileName << endl;
            deleteMap(arr, maxRow);
        }else{throw 1;}
    }catch(...){
        deleteMap(arr, maxRow);
        cout << "[FAIL]: loadLevel read in " << fileName << endl;
    }


    }//Unhappy paths for loadLevel ends

    }//

    //Happy and Unhappy paths for getDirection
    {
    try{
        fileName = "getDirectionUnhappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        //int colBeforeMove = 1;
        //int rowBeforeMove = 1;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('w',nextRow, nextCol);
        getDirection('a',nextRow, nextCol);
        getDirection('s',nextRow, nextCol);
        getDirection('d',nextRow, nextCol);
        getDirection('e',nextRow, nextCol);
        getDirection('q',nextRow, nextCol);
        
        deleteMap(arr, maxRow);

        if (1 == user.col && 1 == user.row){
            cout << "[PASS]: getDirection player did not move " << fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: getDirection player moved for " << fileName << endl;
    }

    // Player tries to move onto a pillar space
    try{
        fileName = "getDirectionUnhappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        //int colBeforeMove = 1;
        //int rowBeforeMove = 1;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('w',nextRow, nextCol);
        getDirection('a',nextRow, nextCol);
        getDirection('s',nextRow, nextCol);
        getDirection('d',nextRow, nextCol);
        getDirection('e',nextRow, nextCol);
        getDirection('q',nextRow, nextCol);
        
        deleteMap(arr, maxRow);

        if (1 == user.col && 1 == user.row){
            cout << "[PASS]: getDirection player did not move " << fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: getDirection decided the player could move to a pillar in " << fileName << endl;
    }

    // What if the user inputs capital Letters?
    try{
        fileName = "getDirectionHappy.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        //int colBeforeMove = 1;
        //int rowBeforeMove = 1;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('W',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('A',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('S',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('D',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('E',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('Q',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);

        deleteMap(arr, maxRow);

        if (2 == user.col && 2 == user.row){
            cout << "[PASS]: getDirection player did not move with capital letters " << fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: getDirection decided the player could move to a pillar in " << fileName << endl;
    }

    // What if the user inputs an invalid character?
    try{
        fileName = "getDirectionHappy.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('x',nextRow, nextCol);
            doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        //Since invalid char, player should stay in place

        deleteMap(arr, maxRow);

        if (2 == user.col && 2 == user.row){
            cout << "[PASS]: getDirection player did not move with capital letters " << fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: getDirection decided the player could move to a pillar in " << fileName << endl;
    }

    }

    // resizeMap Happy Paths and resizeMap unhappy paths (only a handful)
    {
    try{
        fileName = "example.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        int oldMaxRow = maxRow;
        int oldMaxCol = maxCol;
        cout << "oldMaxRow is " << oldMaxRow << " and oldMaxCol is " << oldMaxCol << endl;

        countCharacters(arr, oldMaxRow, oldMaxCol, oldPlayerCounter, 
                    oldTreasureCounter, oldDoorCounter, oldPillarCounter, oldAmuletCounter,
                    oldMonsterCounter, oldBlankTileCounter, oldExitCounter, fileName);

        bigArr = resizeMap(arr, maxRow,maxCol);
        cout << "maxRow is " << maxRow << " and maxCol is " << maxCol << endl;
        
        countCharacters(bigArr, maxRow, maxCol, playerCounter, 
                        treasureCounter, doorCounter, pillarCounter, amuletCounter,
                        monsterCounter, blankTileCounter, exitCounter, fileName);

        cout << "After deleting, maxRow is " << maxRow << " and maxCol is " << maxCol << endl;
        int error = errorForResizeMap(oldMaxRow, maxRow, oldMaxCol, maxCol, playerCounter, oldMonsterCounter, monsterCounter, oldBlankTileCounter, blankTileCounter, oldExitCounter, exitCounter);
        deleteMap(bigArr, maxRow); //When we delete the map, maxRow is updated to 0
        if (!error){ // If there is no error, errorForResizeMap returns 0. !0 is true
            cout << "[PASS]: resizeMap has passed happy path 1 with " << fileName << endl;
        }
        else{
            throw error;
        }
    }catch(int e){
        resizeErrorDescription(e);
    }

    // Resize a null map
    try{
        arr = nullptr;
        maxRow = 0;
        maxCol = 0;
        bigArr = resizeMap(arr, maxRow,maxCol);
        
        if (bigArr == nullptr){
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            cout << "[PASS]: resize map returns nullptr if it tries to resize a nullptr" << endl;
        }else{
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: resizeMap managed to somehow resize a null pointer" << endl;
    }

    // Resize a map with a negative maxRow
    try{
        fileName = "example.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        int oldMaxRow = maxRow;
        maxRow = -2;
        bigArr = resizeMap(arr, maxRow,maxCol);
        maxRow = oldMaxRow;

        if (bigArr == nullptr){
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            cout << "[PASS]: resizeMap did returned a nullPtr because maxRow was neg " << endl;
        }else{
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            throw 1;
        }
    }catch(...){
        cout << "[PASS]: resizeMap resized a map with a negative maxRow" << endl;
    }

    // Resize a map with a negative maxCol
    try{
        fileName = "example.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        maxCol = -2;
        bigArr = resizeMap(arr, maxRow,maxCol);
        
        if (bigArr == nullptr){
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            cout << "[PASS]: resizeMap did returned a nullPtr because maxCol was neg " << endl;
        }else{
            deleteMap(arr, maxRow); //When we delete the map, maxRow is updated to 0
            throw 1;
        }
    }catch(...){
        cout << "[PASS]: resizeMap resized a map with a negative maxCol" << endl;
    }

    // Try making a resize map that causes tiles to be int32max in try and catch
    }

    //Unhappy Paths for doPlayerMove
    {
    // Player moves into a treasure tile
    try{
        fileName = "playerMovesToTreasure.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);

        deleteMap(arr, maxRow);

        if (user.col != 1){
            throw 1;
        }
        else{
            cout << "[PASS]: Player moved into treasure for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: Player did not move into treasure for "<< fileName << endl;
    }
    
    // Player goes into a question mark/door
    try{
        fileName = "playerMovesToDoor.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);

        deleteMap(arr, maxRow);

        if (user.col != 1){
            throw 1;
        }
        else{
            cout << "[PASS]: Player moved into '?' for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: Player did not move into '?' for "<< fileName << endl;
    }

    // Player goes into a ! with a treasure
    try{
        fileName = "playerMovesToExitWithTreasure.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        user.treasure=1;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        cout << "The player has " << user.treasure << " treasures. It should move into exit." << endl;

        deleteMap(arr, maxRow);

        if (user.col != 2){
            throw 1;
        }
        else{
            cout << "[PASS]: Player moved into '!' with treasure for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: Player did not move into '!' with treasure for "<< fileName << endl;
    }

    // Player goes into a ! without a treasure
    try{
        fileName = "exitLevelNoTreasure.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('s',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('s',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        getDirection('s',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);

        variableCount(arr, maxRow, maxCol, '!', exitCounter, fileName);
        deleteMap(arr, maxRow);

        if (user.row == 2 && user.col == 0){
            cout << "[PASS]: level did not exit without treasure "<< fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove allowed player to proceed without treasure "<< fileName << endl;
    }
    
    // Player tries to move into a monster
    try{
        fileName = "monsterNextToPlayer.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        int posBeforeMove = user.col;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        int posAfterMove = user.col;

        deleteMap(arr, maxRow);

        if (posAfterMove != posBeforeMove){
            throw 1;
        }
        else{
            cout << "[PASS]: doPlayerMove stayed in place for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove didn't stay in place for "<< fileName << endl;
    }
    
    // Go left when on the 0 column
    try{
        fileName = "doPlayerMoveUnhappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        int posBeforeMove = user.col;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('a',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        int posAfterMove = user.col;

        deleteMap(arr, maxRow);

        if (posAfterMove != posBeforeMove){
            throw 1;
        }
        else{
            cout << "[PASS]: doPlayerMove stayed in place for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove didn't stay in place for "<< fileName << endl;
    }

    // Go right on the columns-1 column
    try{
        fileName = "doPlayerMoveUnhappy2.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        int posBeforeMove = user.col;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('d',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        int posAfterMove = user.col;
        deleteMap(arr, maxRow);

        if (posAfterMove != posBeforeMove){
            throw 1;
        }
        else{
            cout << "[PASS]: doPlayerMove stayed in place for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove didn't stay in place for "<< fileName << endl;
    }
    
    // Go up on the 0 row
    try{
        fileName = "doPlayerMoveUnhappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        int posBeforeMove = user.row;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('w',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        int posAfterMove = user.row;
        deleteMap(arr, maxRow);

        if (posAfterMove != posBeforeMove){
            throw 1;
        }
        else{
            cout << "[PASS]: doPlayerMove stayed in place for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove didn't stay in place for "<< fileName << endl;
    }

    // Go down on the row-1 column
    try{
        fileName = "doPlayerMoveUnhappy2.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        int posBeforeMove = user.row;
        nextRow = user.row;
        nextCol = user.col;
        getDirection('s',nextRow, nextCol);
        doPlayerMove(arr, maxRow, maxCol, user, nextRow, nextCol);
        int posAfterMove = user.row;
        deleteMap(arr, maxRow);

        if (posAfterMove != posBeforeMove){
            throw 1;
        }
        else{
            cout << "[PASS]: doPlayerMove stayed in place for "<< fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove didn't stay in place for "<< fileName << endl;
    }
    }

    //Happy Paths for doPlayerMove
    {
    //Stays in place
    try{
        fileName = "doPlayerMoveHappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        // The spawn is 1,1. I want it to stay in place, so next row next col = 1,1
        doPlayerMove(arr,maxRow,maxCol,user,1,1);
        deleteMap(arr,maxRow);
        if ((1 == user.col) && (1 == user.row)){
            cout << "[PASS]: doPlayerMove stayed in place for " << fileName << endl;
        }
        else{
            throw 1;
        }
    }catch(...){
        cout << "[FAIL]: doPlayerMove did NOT stay in place in " << fileName << endl;
    }

    //Go left on some open space
    try{
        fileName = "doPlayerMoveHappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        cout << "AT SPAWN: user.col is "<< user.col << " and user.row is: " << user.row << endl;

        doPlayerMove(arr, maxRow, maxCol, user, 1, 0);
        deleteMap(arr, maxRow);
        cout << "AFTER MOVE user.col is "<< user.col << " and user.row is: " << user.row << endl;
        if (user.col == 0 && user.row == 1){
            cout << "[PASS]: doPlayerMove went left in "<< fileName << endl;
        }
        else{throw 1;}
    }catch(...){
        cout << "user.col is "<< user.col << " and user.row is: " << user.row << endl; 
        cout << "[FAIL]: doPlayerMove didn't go left in "<< fileName << endl;
    }

    //Go right on some open space
    try{
        fileName = "doPlayerMoveHappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        cout << "AT SPAWN: user.col is "<< user.col << " and user.row is: " << user.row << endl;
        doPlayerMove(arr, maxRow, maxCol, user, 1, 2);
        deleteMap(arr, maxRow);
        cout << "AFTER MOVE user.col is "<< user.col << " and user.row is: " << user.row << endl;
        if (user.col == 2 && user.row == 1){ 
            //Player spawns in 1,1. Right makes user.col = 2. user.row should stay the same (1)
            cout << "[PASS]: doPlayerMove went right in "<< fileName << endl;
        }
        else{throw 1;}
    }catch(...){
        cout << "user.col is "<< user.col << " and user.row is: " << user.row << endl;
        cout << "[FAIL]: doPlayerMove didn't go right in "<< fileName << endl;
    }

    //Go up on some open space
    try{
        fileName = "doPlayerMoveHappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        cout << "AT SPAWN: user.col is "<< user.col << " and user.row is: " << user.row << endl;
        doPlayerMove(arr, maxRow, maxCol, user, 0, 1);
        deleteMap(arr, maxRow);
        cout << "AFTER MOVE user.col is "<< user.col << " and user.row is: " << user.row << endl;
        if (user.col == 1 && user.row == 0){
            cout << "[PASS]: doPlayerMove went up in "<< fileName << endl;
        }
        else{throw 1;}
    }catch(...){
        cout << "user.col is "<< user.col << " and user.row is: " << user.row << endl;
        cout << "[FAIL]: doPlayerMove didn't go up in "<< fileName << endl;
    }

    //Go down on some open space
    try{
        fileName = "doPlayerMoveHappy1.txt";
        arr = loadLevel(fileName,maxRow,maxCol,user);
        cout << "AT SPAWN: user.col is "<< user.col << " and user.row is: " << user.row << endl;        

        doPlayerMove(arr, maxRow, maxCol, user, 2, 1);
        deleteMap(arr, maxRow);
        cout << "AFTER MOVE user.col is "<< user.col << " and user.row is: " << user.row << endl;
        if (user.col == 1 && user.row == 2){
            cout << "[PASS]: doPlayerMove went down in "<< fileName << endl;
        }
        else{throw 1;}
    }catch(...){
        cout << "user.col is "<< user.col << " and user.row is: " << user.row << endl;
        cout << "[FAIL]: doPlayerMove didn't go down in "<< fileName << endl;
    }
    }

    //Happy Paths for doMonsterAttack
{
    // There is a monster right in front of player and player does not move
    try{
        fileName = "monsterHappy1.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        nextRow = user.row;
        nextCol = user.col;

        bool playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        
        deleteMap(arr,maxRow);
        EXPECT_EQ(playerDead,true);
        if (playerDead == false){
            throw 1;
        }
        else{
            cout << "[PASS]: Monster attacked for file " << fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: Monster did not attack for file " << fileName << endl;
    }
    //There are pillars surrounding the monster 
    try{
        fileName = "monsterHappy2.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('e', nextRow, nextCol);
        doPlayerMove(arr, maxRow,maxCol, user,nextRow,nextCol);
        bool playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        
        deleteMap(arr,maxRow);
        EXPECT_EQ(playerDead,false);
        if (playerDead){
            throw 1;
        }
        else{
            cout << "[PASS]: Monster did not attack for file " << fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: The monster attacked for file " << fileName << endl;
    }
    // Monsters are all out of sight of player
    try{
        fileName = "monsterHappy3.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('e', nextRow, nextCol);
        doPlayerMove(arr, maxRow,maxCol, user,nextRow,nextCol);
        bool playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        
        deleteMap(arr,maxRow);
        EXPECT_EQ(playerDead,false);
        if (playerDead){
            throw 1;
        }
        else{
            cout << "[PASS]: Monsters did not attack for file " << fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: The monster attacked for file " << fileName << endl;
    }

    // Unhappy paths for doMonsterAttack
    // There is more than 1 monster surrounding the player (4)
    try{
        fileName = "monsterUnhappy1.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        nextRow = user.row;
        nextCol = user.col;
        getDirection('e', nextRow, nextCol);
        doPlayerMove(arr, maxRow,maxCol, user,nextRow,nextCol);
        bool playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        
        deleteMap(arr,maxRow);
        EXPECT_EQ(playerDead,true);
        if (!playerDead){
            throw 1;
        }
        else{
            cout << "[PASS]: Monsters attacked for file " << fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: The monsters did not attack for file " << fileName << endl;
    }

    //4 monsters 2 tiles away from player but they are blocked by an amulet, pillar, door, and exit
    try{
        fileName = "stuffInFrontOfMonster.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        bool playerDead = doMonsterAttack(arr, maxRow, maxCol, user);
        playerDead = doMonsterAttack(arr, maxRow, maxCol, user);

        deleteMap(arr,maxRow);
        EXPECT_EQ(playerDead,true);
        if (!playerDead){
            throw 1;
        }
        else{
            cout << "[PASS]: Monsters attacked for file " << fileName << endl;
        }
    }catch(...){
        cout << "[FAIL]: The monster did not attack for file " << fileName << endl;
    }
}    

    //Unhappy paths for deleteMap
{
    try{
        fileName = "emptyMap.txt";
        arr = loadLevel(fileName, maxRow, maxCol, user);
        deleteMap(arr,maxRow);
        if (arr == nullptr){
            cout << "[PASS] an empty map was deleted." << endl;
        }else{throw 1;}
    }catch(...){
        cout << "[FAIL]: deleteMap did not erase the empty map" << endl; 
    }
}

    return 0;
}
