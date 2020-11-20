/*Project Checklist
  Acquire File Input[x]
  Store File Input[x]
  Develop way to recursively build tree[x] 99% certain
  Decoder[x]
  */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

class Node {
public:
    int value;
    Node *leftchild;
    Node *rightchild;
};

void Parsing(vector<int> &inor, vector<int> &postor, vector<string> &message, char const *argv[]){
  string holder;
  ifstream in;
  ifstream post;
  ifstream encode;

  in.open(argv[1]);
  while (in >> holder){
    inor.push_back(stoi(holder));
  }
in.close();

post.open(argv[2]);
while (post >> holder){
  postor.push_back(stoi(holder));
}
post.close();

encode.open(argv[3]);
while (encode >> holder){
  message.push_back(holder);
}
encode.close();
}//end of Parsing

Node* Build(vector<int> &Side, vector<int> &inorder, vector<int> &postorder)
{
  //this function only works on the creation of the LEFT side of the root
  //this is technically inefficient since they could be one reursive function
  //cout << "Entering the Function" << endl;
  Node* item = new Node;
  item->leftchild = NULL;
  item->rightchild = NULL;

//this chunk interates end of pos and compares with nums in left side to see if it matters
if (Side.size() > 0){
  bool flag = false;
  for (unsigned int i = postorder.size() - 1; i >= 0 && !flag; i--){
    //cout << endl;
    int postValue = postorder.at(i);
    //cout << postValue << endl;
      for (unsigned int j = 0; j < Side.size() && !flag; j++){
        int leftValue = Side.at(j);
        //cout << leftValue << "and" << postValue << endl;

        if (postValue == leftValue){
          item->value = leftValue;
          Side.erase(Side.begin() + (j)); //remove it from the left side list, shit doesn't work
          //cout << "Disovered Value: " << item->value << endl;
          flag = true;
        }
      }
    } //end of first for loop
  }

  //cout << item->value << " is the value of the node" << endl;
  //we have found the item's value!
  //check if it has kids
  if (item->value >= 128){
  //cout << "Entering rightchild" << endl;
  item->rightchild = Build(Side, inorder, postorder);
  //cout << "Entering leftchild" << endl;
  item->leftchild = Build(Side, inorder, postorder);
}
  return item;
}


int main(int argc, char const *argv[]) {
  vector<int> inorder;
  vector<int> postorder;
  vector<string> encoded;

  Parsing(inorder, postorder, encoded, argv);

int rootValue = postorder.at(postorder.size() - 1); //getting int of root
int rootLocation = 0; //root location in inorder

for (unsigned int i = 0; i < inorder.size(); i++){ //finding root in inorder
  int target = inorder.at(i);
    if (target == rootValue){
      rootLocation = i;
    }
  }
  //cout << postorder.at(postorder.size() - 1);

  vector<int> leftSide; //adds the items left of root to one list
  for (int i = 0; i < rootLocation; i++){
    leftSide.push_back(inorder.at(i));
    }

  vector<int> rightSide; //add items right of the root to the list
  for (unsigned int i = rootLocation + 1; i < inorder.size(); i++){
    rightSide.push_back(inorder.at(i));
  }
  //cout << leftSide.size() << endl;
  //cout << postorder.size() << endl;

Node* Root = new Node;
Root->leftchild = NULL;
Root->rightchild = NULL;
Root->value = rootValue;
Root->leftchild = Build(leftSide, inorder, postorder); //root or root->leftchild
Root->rightchild = Build(rightSide, inorder, postorder);
//Root = TreeBuilder(Root, rootValue,inorder, postorder, inorder.size(), postorder.size());
//this is put into main to act as an anchor
/*cout << "Root: " << Root->value << endl;
cout << "Root LC: " << Root->leftchild->value << endl;
cout << "LC LC: " << Root->leftchild->leftchild->value << endl;
cout << "LC RC: " << Root->leftchild->rightchild->value << endl;
cout << "LC RC LC: " << Root->leftchild->rightchild->leftchild->value << endl;
cout << "LC RC RC: " << Root->leftchild->rightchild->rightchild->value << endl;
cout << "Root RC: " << Root->rightchild->value << endl;
*/
//Can safely assume it is making trees properly, now just make a way to decode

unsigned int index = 0;
Node* cur = new Node;
cur = Root;

while (index != encoded.size()){
  string message = encoded.at(index);
  unsigned int i = 0;
    while (i < message.length()){
    //cout << message.at(i) << " ";
    if (!(cur->leftchild && cur->rightchild)){ //leaf detection
      cout << char(cur->value);
      cur = Root;
  }
    else{ //branch detection
      if(message[i] == '1'){
        cur = cur->rightchild;
      }
      else{
        cur = cur->leftchild;
      }
    }
    if (cur != Root)
      i++;
  }
index++;
}
cout << char(cur->value);


  return 0;
}

/*for (unsigned int i = postorder.size(); i >= 0; i--){ //as we cull down members of left leftSide
  while (flag != true){
    for (unsigned int j = 0; j < leftSide.size(); j++){
      if (leftSide.at(j) == postorder.at(i)) flag = true;
    }
  }//end of while loop
cout << postorder.at(i) << endl;
flag = false;
}//end of outside for loop
*/
