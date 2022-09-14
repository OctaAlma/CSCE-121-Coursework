/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"
#include "Tag.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  // This constructs a Post object. It has a given post ID, a userName, and the text
  : postId(postId), userName(userName), postText(postText) { 
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

string optimizeTag(string tag){
  string optimizedTag = tag;
  // We gotta remove any punctuation from the tag
  bool punctuation = true;
  while (punctuation){
    char lastChar = optimizedTag.at(optimizedTag.length()-1);
    if(lastChar == '?' || lastChar == '!'|| lastChar == '.' || lastChar == ','){
      //Erase the last character in the string
      optimizedTag.pop_back();
    }else{
      punctuation = false;
    }
  }

  // Now we gotta make any uppercase into lower case:
  for (int i = 0; i < optimizedTag.length(); i++){
    if (optimizedTag.at(i) >= 'A' && optimizedTag.at(i) <= 'Z'){
      optimizedTag.at(i) = optimizedTag.at(i) + 32; // Will convert to lowercase
    }
  }
  return optimizedTag;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post

  // This method returns a string vector that has tag names in a post. Create the vector:
  vector<string> tagsFound;

  // Go through the text in a postText, check for any # and get the word in it
  string text = this->postText;
  string optimizedTag;

  for (int i = 0; i < text.length(); i++){
    if (text.at(i) == '#'){
      // We found a # on string.at(i). We have to make a substring from i -> j
      
      for (int j = i; j < text.length(); j++){
        string tagName;
        
        // If j is the last character in the string, add tag text.substr(i,j-i)
        if (j == text.length() - 1){
          tagName = text.substr(i,j-i+1);
          //cout << "The tagName is " << tagName << endl;
          optimizedTag = optimizeTag(tagName); // Method removes any '?' '!' '.' or ',' at the end and makes string lowercase 
          //cout << "The optimized tagName is " << tagName << endl;
          
          // Now we need to check if the tag is already in the vector.
          bool inVector = false;
          for (int x = 0; x < tagsFound.size(); x++){
            if (optimizeTag(tagsFound.at(x)) == optimizedTag){
              inVector = true;
            }
          }
          if (!inVector){ // If it is NOT in the vector, we pushback the tag to the vector
            tagsFound.push_back(tagName);
            break; 
          }else{break;}
        }else if (text.at(j) == ' '){
          tagName = text.substr(i,j-i);
          //cout << "The tagName is " << tagName << endl;
          optimizedTag = optimizeTag(tagName);
          //cout << "The optimized tagName is " << tagName << endl;
          bool inVector = false;
          for (int x = 0; x < tagsFound.size(); x++){
            if (optimizeTag(tagsFound.at(x)) == optimizedTag){
              inVector = true;
            }
          }
          if (!inVector){
            tagsFound.push_back(tagName);
            break;
          }else{break;}
        }
      }
    }
  }
  // Now that we have put in all the vectors in the array, we can optimize each one
  for (int y = 0; y < tagsFound.size(); y++){
    tagsFound.at(y) = optimizeTag(tagsFound.at(y));
  }
  return tagsFound;
}
