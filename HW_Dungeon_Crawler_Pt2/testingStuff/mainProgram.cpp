#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using namespace std;

int main(){
    const string fileName = "testHeaderStuff.txt";
    int maxRow;
    int maxCol;
    Player player;
    char ** map = loadLevel(fileName, maxRow, maxCol, player);

    for (int i = 0; i < maxRow; i++){
        for (int j = 0; j < maxCol; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    cout << maxRow << " "<< maxCol << endl;

    char ** bigMap = resizeMap(map,maxRow,maxCol);

    cout << maxRow << " "<< maxCol << endl;

    deleteMap(bigMap, maxRow);

    return 0;
}