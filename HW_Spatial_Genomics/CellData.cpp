/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#include <iostream>
#include <string>
#include "CellData.h"

using std::cout;
using std::string;
using std::endl;

CellData::CellData():id("-1"),fov(-1), volume(-1), center_x(-1), center_y(-1), 
min_x(-1), min_y(-1), max_x(-1),max_y(-1){} //initialize everything

CellData::CellData(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y):
id(id), fov(fov), volume(volume), center_x(center_x), center_y(center_y),
min_x(min_x), min_y(min_y), max_x(max_x), max_y(max_y){} //initialize everything


CellData::~CellData() {} // You should not need to implement this

bool CellData::operator<(const CellData& b) {
    //return (this->fov < b.fov) || (this->id < b.id);
    // Implement this
    if (this->fov < b.fov){
        return true;
    }else if (this->fov > b.fov){
        return false;
    }

    return this->id < b.id;

    /*

    // If we get to this point their fov are equal. Check the size of their ids

    if (this->id.size() < b.id.size()){
        return true;

    }else if (this->id.size() > b.id.size()){
        return false;

    }else if (this->id.size() == b.id.size()){ // If IDs are the same size, compare each individual digit

        for (int i = 0; i < b.id.size(); i++){
            // They have the same length, so the first digit
            // that they have different determines everything
            if (this->id.at(i) < b.id.at(i)){
                return true;
            }else if (this->id.at(i) > b.id.at(i)){
                return false;
            }
            // if digits are equal, it will continue
        }
    }
    return false;
    */
}

bool CellData::operator==(const CellData& b)
{
    // Implement this
    if ((this->id == b.id) && (this->fov == b.fov) && (this->volume == b.volume)
    && (this->center_x == b.center_x) && (this->center_y == b.center_y)
    && (this->min_x == b.min_x) && (this->min_y == b.min_y) 
    && (this->max_x == b.max_x) && (this->max_y == b.max_y)){
        return true;
    }
    return false;
}

