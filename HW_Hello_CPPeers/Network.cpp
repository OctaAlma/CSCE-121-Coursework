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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

string optimizeName(string name){
  string optimizedName = name;
  // Now we gotta make any uppercase into lower case:
  for (int i = 0; i < optimizedName.length(); i++){
    if (optimizedName.at(i) >= 'A' && optimizedName.at(i) <= 'Z'){
      optimizedName.at(i) = optimizedName.at(i) + 32; // Will convert to lowercase
    }
  }
  return optimizedName;
}

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file

  std::ifstream inputFile;
  inputFile.open(fileName);
  if (!inputFile.is_open()){
    throw std::invalid_argument("File could not be opened");
  }

  string typeOfLine;
  string userName;
  unsigned int postId;
  string NameInLine;
  string post;
  string sentence;

  try{
  while (!inputFile.eof()){
    getline(inputFile, sentence);
    if (inputFile.fail()){
      if (inputFile.eof()){
        continue;
      }
      throw std::invalid_argument("");
    }

    std::istringstream sentenceStream(sentence);
    sentenceStream >> typeOfLine;

    if (typeOfLine == "User"){
      sentenceStream >> userName;
      if (sentenceStream.fail()){
        throw std::runtime_error("");
      }
      this->addUser(userName);
    }

    else if (typeOfLine == "Post"){
      sentenceStream >> postId;
      if (sentenceStream.fail()){
        throw std::runtime_error("");
      }

      sentenceStream >> userName;
      if (sentenceStream.fail()){
        throw std::runtime_error("");
      }

      getline(sentenceStream, post);
      if (sentenceStream.fail()){
        throw std::runtime_error("");
      }

      this->addPost(postId, userName, post);
    }
    else{
      throw 1;
    }
  }
  }catch(...){
    throw std::runtime_error("");
  }
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network

  // We gotta check if the username already exists
  userName = optimizeName(userName);
  for (int i = 0; i < this->users.size(); i++){
    if (userName == this->users.at(i)->getUserName()){
      throw std::invalid_argument("User with the same name exists already");
    }
  }
  // There is a vector called users containing pointers to user objects
  User* newUser = new User(userName);
  this->users.push_back(newUser);
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network

  // Check if a post with this ID already exists. If there is, throw invalid argument
  for (int i = 0; i < this->posts.size(); i++){
    if (postId == this->posts.at(i)->getPostId()){
      throw std::invalid_argument("A post with the same ID already exists");
    }
  }

  // If there is no user with this name, we throw invalid argument  
  bool userExists = false;
  int userIndex = -1;
  for (int i = 0; i < this->users.size(); i++){
    if (userName == this->users.at(i)->getUserName()){
      userExists = true;
      userIndex = i;
    }
  }
  if (!userExists){
    throw std::invalid_argument("This user does not exist");
  }


  Post* newPost = new Post(postId,userName,postText);
  posts.push_back(newPost);
  this->users.at(userIndex)->addUserPost(newPost);

  // Extraction of candidate #s within the post
  vector<string> candidateTags = newPost->findTags();

  // For each candidate tag, check if the tag is already in the network
  // if not, create a dynamic memory tag and at it to network's tag vector
  for (int i = 0; i < candidateTags.size(); i++){
    bool tagInNetworkTags = false;
    for (int j = 0; j < this->tags.size(); j++){
      if (candidateTags.at(i) == this->tags.at(j)->getTagName()){
        tagInNetworkTags = true;
        this->tags.at(j)->addTagPost(newPost);
      }
    }
    if (!tagInNetworkTags){
      try{
        Tag* newTag = new Tag(candidateTags.at(i)); // Will throw an exception if it is an invalid tag name
        tags.push_back(newTag);
        this->tags.at(this->tags.size()-1)->addTagPost(newPost);
      }catch(...){
        continue;
      }
    }
  }
  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  if (userName.empty()){
    throw std::invalid_argument("The provided username is an empty string");
  }

  bool userNameExists = false;
  int userIndex;
  for (int i = 0; i < this->users.size(); i++){
    if (userName == users.at(i)->getUserName()){
      userNameExists = true;
      userIndex = i;
    }
  }
  if (!userNameExists){
    throw std::invalid_argument("The provided username does not exist");
  }

  return users.at(userIndex)->getUserPosts();
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  if (tagName.empty()){
    throw std::invalid_argument("The provided tag name is empty");
  }
  
  bool tagExists;
  int tagIndex;
  for (int i = 0; i < tags.size(); i++){
    if (tagName == tags.at(i)->getTagName()){
      tagExists = true;
      tagIndex = i;
    }
  }
  if (!tagExists){
    throw std::invalid_argument("The provided tag name does not exist");
  }

  return tags.at(tagIndex)->getTagPosts();
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  int maxPosts;
  int amountOfPostsWithTag;

  for (int i = 0; i < tags.size(); i++){
    amountOfPostsWithTag = tags.at(i)->getTagPosts().size();
    if (i == 0){
      maxPosts = amountOfPostsWithTag;
      continue;
    }
    if (amountOfPostsWithTag > maxPosts){
      maxPosts = amountOfPostsWithTag;
    }
  }
  vector<string> mostPopularTags;
  for (int i = 0; i < tags.size(); i++){
    if (tags.at(i)->getTagPosts().size() == maxPosts){
      mostPopularTags.push_back(tags.at(i)->getTagName());
    }
  }
  return mostPopularTags;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
