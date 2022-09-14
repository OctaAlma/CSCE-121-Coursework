#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

/*
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ *.cpp
*/

using namespace std;

// TODO Write this function
//DO NOT TOUCH IT'S PERFECT
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

  int energyY = redGradY*redGradY + blueGradY*blueGradY + greenGradY*greenGradY;

  int energyGradient = energyY + energyX;

  return energyGradient;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
  /*
  returns two things
  Returns an int of the total energy
  It also updates the array of the fifth argument of the function to hold 
  the indexes of the column in that seam
  */
  //Think of the index as the row
  //Think of the index's corresponding element as the column
  int currRow;
  int totalEnergy = 0;
  int currColumn = start_col;

  int PixLeftX;
  int PixRightX;
  int PixForwardX;

  int energyLeft;
  int energyForward;
  int energyRight;

  for (currRow = 0; currRow < height; currRow++){
    
    //New Stuff that hopefully doesn't break the code begins
    //In the case that there is only one column, it will do the following instructions:
    if (width == 1){
      for (currRow = 0; currRow < height; currRow++){
        if (currRow == 0){
          totalEnergy += energy(image,start_col,0,width,height);
          seam[currRow] = (start_col);
        }
        else{
          PixForwardX = currColumn;
          energyForward = energy(image,PixForwardX,currRow,width,height);
          totalEnergy+=energyForward;
          seam[currRow] = PixForwardX;
        }
      }
      return totalEnergy;
    }
    //New stuff that hopefully doesn't break the code ends. 
    //If this doesn't work make sure to remove the "else" in the "else if" below
    
    else if (currRow == 0){
      totalEnergy += energy(image,start_col,0,width,height);
      seam[currRow] = (start_col);
      continue;
    }

    else{
      if (currColumn == 0){
        PixForwardX = currColumn;
        PixRightX = currColumn+1;

        energyForward = energy(image, PixForwardX, currRow, width, height);
        energyRight = energy(image, PixRightX, currRow, width, height);

        if(energyForward <= energyRight){
          seam[currRow] = PixForwardX;
          currColumn = PixForwardX;
          totalEnergy += energyForward;
          continue;
        }
        else{
          seam[currRow] = PixRightX;
          currColumn = PixRightX;
          totalEnergy += energyRight;
          continue;
        }
      }

      else if (currColumn == width - 1){
        PixForwardX = currColumn;
        PixLeftX = currColumn-1;

        energyForward = energy(image, PixForwardX, currRow, width, height);
        energyLeft = energy(image, PixLeftX, currRow, width, height);

        if(energyForward <= energyLeft){
          seam[currRow] = PixForwardX;
          currColumn = PixForwardX;
          totalEnergy += energyForward;
          continue;
        }
        else{
          seam[currRow] = PixLeftX;
          currColumn = PixLeftX;
          totalEnergy += energyLeft;
          continue;
        }
      }

      else{
        PixForwardX = currColumn;
        PixLeftX = currColumn + 1;
        PixRightX = currColumn - 1;

        energyForward = energy(image, PixForwardX, currRow, width, height);
        energyLeft = energy(image, PixLeftX, currRow, width, height);         
        energyRight = energy(image, PixRightX, currRow, width, height);

        /*
        In the case that two energies are equal:
        Forward takes priority, then left, then right
        */

        if (energyForward <= energyLeft && energyForward <= energyRight){
          //When energy of the pixel below is the smallest OR
          //smaller than or equal to both left and right
          seam[currRow] = PixForwardX;
          currColumn = PixForwardX;
          totalEnergy += energyForward;
          cout << "In row " << currRow << " we have " << seam[currRow] << endl;
          continue;
        } 
        else if (energyLeft < energyForward && energyLeft <= energyRight){
          //When energy of the lower left pixel is the smallest, OR
          //Smaller than energy below and smaller than or equal to energy right
          seam[currRow] = PixLeftX;
          currColumn = PixLeftX;
          totalEnergy += energyLeft;
          cout << "In row " << currRow << " we have " << seam[currRow] << endl;
          continue;
        } 
        else{
          //Energy of the right is the smallest
          seam[currRow] = PixRightX;
          currColumn = PixRightX;
          totalEnergy += energyRight;
          cout << "In row " << currRow << " we have " << seam[currRow] << endl;
          continue;
        }       
      }
    }
  }
  return totalEnergy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  //Make your width -1, then store the column you want to remove
  //create a variable that will store the column that you want remove
  /*
  nested for loop: first loop goes through rows until the value you want to remove
  Second for loop goes through columns
  */
  width = width - 1;
  for (int i = 0; i < height; i++){
    int indexToRemove = verticalSeam[i];
    for (int j = indexToRemove; j < width; j++){
      image[j][i] = image[j+1][i];
    }
  }
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
  int a = image[0][0].r;
  int b = width;
  seam[0] = 1;
  int c = a + b + height + seam[0] + start_row;
  c += 1;
  return 0;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
  int a = image[0][0].r;
  int b = width;
  horizontalSeam[0] = 1;
  int c = a + b + height + horizontalSeam[0];
  c+= 1;
  return;
}


int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}