#include <iostream>
#include <string>
#include <vector>
using namespace std;

void optimizeTag(string& tag){
  string tagBefore = tag;
  // We gotta remove any punctuation from the tag
  bool punctuation = true;
  while (punctuation){
    char lastChar = tag.at(tag.length()-1);
    if(lastChar == '?' || lastChar == '!'|| lastChar == '.' || lastChar == ','){
      //Erase the last character in the string
      tag.pop_back();
    }else{
      punctuation = false;
    }
  }

  // Now we gotta make any uppercase into lower case:
  for (int i = 0; i < tag.length(); i++){
    if (tag.at(i) >= 'A' && tag.at(i) <= 'Z'){
      tag.at(i) = tag.at(i) + 32; // Will convert to lowercase
    }
  }
}


int main(){
  string text = "When #deallocating #dynamic #Arrays, use delete[]";
  vector<string> tagsFound;

  for (int i = 0; i < text.length(); i++){
    if (text.at(i) == '#'){

      // We found a # on string.at(i). We have to make a substring from i -> j
      for (int j = i; j < text.length(); j++){
        string tagName;
        // If j is the last character in the string, add tag text.substr(i,j-i)
        if (j == text.length() - 1){
          tagName = text.substr(i,j-i+1);
          cout << "The tagName is " << tagName << endl;
          optimizeTag(tagName); // Method removes any '?' '!' '.' or ',' at the end and makes string lowercase 
          cout << "The optimized tagName is " << tagName << endl;
          try{
            // Now we need to check if the tag is already in the vector.
            bool inVector = false;
            for (int x = 0; x < tagsFound.size(); x++){
              if (tagsFound.at(x) == tagName){
                inVector = true;
              }
            }
            if (inVector){
              throw std::invalid_argument("");
            }
            tagsFound.push_back(tagName);
            break;
          }catch(std::invalid_argument){
            cout << "The value is already in vector" << endl;
            break;
          }
          
        }else if (text.at(j) == ' '){
          tagName = text.substr(i,j-i);
          cout << "The tagName is " << tagName << endl;
          optimizeTag(tagName);
          cout << "The optimized tagName is " << tagName << endl;
          bool inVector = false;
          for (int x = 0; x < tagsFound.size(); x++){
            if (tagsFound.at(x) == tagName){
              inVector = true;
            }
          }
          if (!inVector){
            tagsFound.push_back(tagName);
            break;
          }else{
              break;
          }
        }
      }
    }
  }
  cout << "First tag: " << tagsFound.at(0) << " Second tag: "<< tagsFound.at(1) << endl;

    return 0;
    //Post post1 (42314, "newuser", "When deallocating #dynamic arrays, use delete[]");
    //std::cout << "Expected #dynamic. Got: "<< post1.findTags().at(0) << std::endl;

    /*
    Post post2(42315, "newuser", "When #deallocating #dynamic arrays, use delete[]");
    Post post3(42316, "newuser", "When #deallocating #dynamic #Arrays, use delete[]");
    Post post4(42317, "newuser", "When deallocating dynamic arrays, use delete[]");
    Post post5(42318, "newuser", "#dynamic");
    Post post6(42319, "newuser", "#");
    Post post7(42320, "newuser", "When # to");
    */
}