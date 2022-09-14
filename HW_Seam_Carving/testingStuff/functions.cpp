#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int energy(const Pixel *const*image, int col, int row, int width, int height)
{
  //You call a specific pixel using image[col][row], think [x][y]
  //First col is 0, last col is width - 1
  //First row is 0, last col is height - 1
  //(0,0) is at the top left, (width - 1, height - 1) is in bottom right

  int XleftPix; //Same row, different col
  int XrightPix; //Same row, different col
  int YtopPix; //Different Col, same row
  int YbottomPix; // Different Col, same row

  if (col == 0){
    XleftPix = width-1;
  }
  else{
    XleftPix = col - 1;
  }

  if (col == width-1){
    XrightPix = 0;
  }
  else{
    XrightPix = col + 1;
  }

  if (row == 0){
    YtopPix = height - 1;
  }
  else {
    YtopPix = row - 1;
  }

  if (row == height - 1){
    YbottomPix = 0;
  }
  else{
    YbottomPix = row + 1;
  }

  int redGradX = abs(image[XleftPix][row].r - image[XrightPix][row].r);
  int blueGradX = abs(image[XleftPix][row].b - image[XrightPix][row].b);
  int greenGradX = abs(image[XleftPix][row].g - image[XrightPix][row].g);

  int energyX = redGradX*redGradX + blueGradX*blueGradX + greenGradX*greenGradX;

  int redGradY = abs(image[col][YtopPix].r - image[col][YbottomPix].r);
  int blueGradY = abs(image[col][YtopPix].b - image[col][YbottomPix].b);
  int greenGradY = abs(image[col][YtopPix].g - image[col][YbottomPix].g);

  int energyY = redGradY*redGradY + blueGradY*blueGradY + greenGradX*greenGradX;

  int energyGradient = energyY + energyX;

  return energyGradient;
}
