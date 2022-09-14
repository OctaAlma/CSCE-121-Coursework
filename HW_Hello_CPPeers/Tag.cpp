/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks

  // Check if the length of tagName is less than 2
  if(tagName.length() < 2){
    throw std::invalid_argument("Tag name length is less than 2");
  }

  // The first character of tagname should be #
  if (tagName.at(0) != '#'){
    throw std::invalid_argument("The first character of tag name is not '#'");
  }

  // Check that the second character is a lowercase letter (ascii from 97-122)
  if (tagName.at(1) < 97 || tagName.at(1) > 122){
    throw std::invalid_argument("The second character is not a lower case letter!");
  }

  //Go through each character of tagName
  for(int i = 0; i < tagName.length(); i++){
    if (i != 0){ //tagName.at(0) is the # symbol
      // We have to check if there is a capital letter A has ascii 65 and Z has ascii 90
      if (tagName.at(i) >= 65 && tagName.at(i) <= 90){
        throw std::invalid_argument("There is a capital letter in the tag name");
      }

      // Check if there is one or more punctuation at the end of the tagName
      // If there is one at the end, this will run
      if (i == tagName.length()-1){
        if (tagName.at(i) == '!' || tagName.at(i) == '?' || tagName.at(i) == ',' || tagName.at(i) == '.'){
          throw std::invalid_argument("There is punctuation at the end of tag name");
        }
      }
    }
  }
  // If it meets the requirements, we actually assign tagName
  this->tagName = tagName;
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return this->tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return this->tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if (post == nullptr){
    throw std::invalid_argument("The provided post has nullpointer stored");
  }else{
    this->tagPosts.push_back(post);
  }
}
