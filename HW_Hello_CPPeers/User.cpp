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
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
  // Throw invalid argument if the userName string is empty
  if (userName.empty()){
    throw std::invalid_argument("UserName is empty");
  }

  // Check if username starts with lower case letter. If not, throw invalid arg
  if (userName.at(0) < 'a' || userName.at(0) > 'z'){
    throw std::invalid_argument("UserName does not start with lowercase letter");
  }

  // Check if user name has ANY uppercase letters
  for (int i = 0; i < userName.length(); i++){
    if (userName.at(i) >= 'A' && userName.at(i) <= 'Z'){
      throw std::invalid_argument("Username contains uppercase letter");
    }
  }
  this->userName = userName;
}

string User::getUserName() {
  // TODO(student): implement getter
  return userName;
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
  return userPosts;
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts
  if (post == nullptr){
    throw std::invalid_argument("Argument is nullptr");
  }else{
    this->userPosts.push_back(post);
  }
}
