
template<typename T>
class AVLTree{
private:
  struct Node{
    T value;
    int height;
    int sub_size;
    Node* parent;
    Node* left_child;
    Node* right_child;

    Node(T value) : value(value), height(0), sub_size(1), parent(nullptr), left_child(nullptr), right_child(nullptr){}
  };

  Node* base;

  int sz;

  Node* createNode(T d, Node* parent){
    Node* ret = new Node(d);
    ret->parent = parent; ret->left_child = base; ret->right_child = base;
    return ret;
  }

  int getHeight(Node* v){return (v->left_child->height < v->right_child->height ? v->right_child->height : v->left_child->height) + 1;}
  int bias(Node* v){return v->left_child->height - v->right_child->height;}

  void reviseNode(Node* v){
    v->height = getHeight(v);
    v->sub_size = v->left_child->sub_size + v->right_child->sub_size + 1;
  }

  Node* minNode(Node* v){
    while(v->left_child != base) v = v->left_child;
    return v;
  }

  Node* maxNode(Node* v){
    while(v->right_child != base) v = v->right_child;
    return v;
  }

  Node* findNode(T d){
    Node* current = base->right_child;
    for(; current != base; current = (d < current->value ? current->left_child : current->right_child)) if(d == current->value) return current;
    return base;
  }

  Node* findNodeByOrder(int ord){
    if(ord < 0 || ord >= (int)sz) return base;

    Node* current = base->right_child;
    while(current != base){
      if(current->left_child->sub_size == ord) return current;
      else if(current->left_child->sub_size > ord) current = current->left_child;
      else{
        ord -= current->left_child->sub_size + 1;
        current = current->right_child;
      }
    }

    return base;
  }

  Node* rotateLeft(Node* v){
    Node *right = v->right_child;

    v->right_child = right->left_child; right->left_child->parent = v;
    (v->parent->right_child == v ? v->parent->right_child : v->parent->left_child) = right; right->parent = v->parent;
    right->left_child = v; v->parent = right;

    reviseNode(v);
    reviseNode(right);
    return right;
  }

  Node* rotateRight(Node* v){
    Node* left = v->left_child;

    v->left_child = left->right_child; left->right_child->parent = v;
    (v->parent->right_child == v ? v->parent->right_child : v->parent->left_child) = left; left->parent = v->parent;
    left->right_child = v; v->parent = left;

    reviseNode(v);
    reviseNode(left);
    return left;
  }

  void balance(Node* v){
    while(v != base){
      if(bias(v) == 2){
        if(bias(v->left_child) == -1) rotateLeft(v->left_child);
        v = rotateRight(v);
      }else if(bias(v) == -2){
        if(bias(v->left_child) == 1) rotateRight(v->right_child);
        v = rotateLeft(v);
      }else reviseNode(v);

      v = v->parent;
    }
  }

public:
  AVLTree() : sz(0){
    base = new Node(0);
    base->height = -1; base->sub_size = 0; base->parent = base; base->left_child = base; base->right_child = base;
  }

  bool insert(T d){
    Node *current = base->right_child, *parent = base;

    for(; current != base; parent = current, current = (d < current->value ? current->left_child : current->right_child)) if(d == current->value) return false;

    if(size() && d < parent->value) parent->left_child = createNode(d, parent);
    else parent->right_child = createNode(d, parent);

    balance(parent);
    ++sz;
    return true;
  }

  bool erase(T d){
    Node* current = base->right_child;

    for(; current != base; current = (d < current->value ? current->left_child : current->right_child)){
      if(d == current->value){
        Node* changedNode;
        if(current->right_child == base){
          (current->parent->right_child == current ? current->parent->right_child : current->parent->left_child) = current->left_child;
          current->left_child->parent = current->parent;
          changedNode = current->parent;
          delete current;
        }else{
          Node* right_min = minNode(current->right_child);
          current->value = right_min->value;
          (right_min->parent == current ? current->right_child : right_min->parent->left_child) = right_min->right_child; right_min->right_child->parent = right_min->parent;
          changedNode = right_min->parent;
          delete right_min;
        }

        balance(changedNode);
        --sz;
        return true;
      }
    }
    return false;
  }

  bool empty(){return base->right_child == base;}
  int size(){return sz;}

  T getMin(){return minNode(base->right_child)->value;}
  T getMax(){return maxNode(base->right_child)->value;}
  bool contains(T d){return findNode(d) != base;}

  T order(int ord){return findNodeByOrder(ord)->value;}

  void clear(){
    Node* current = base->right_child;
    while(current != base){
      if(current->left_child != base) current = current->left_child;
      else if(current->right_child != base) current = current->right_child;
      else{
        current = current->parent;
        if(current->left_child != base){
          delete current->left_child;
          current->left_child = base;
        }else{
          delete current->right_child;
          current->right_child = base;
        }
      }
    }

    sz = 0;
  }

  ~AVLTree(){
    clear();
    delete base;
  }
};


#include<iostream>

using namespace std;

int main(){
  AVLTree<int> tree;

/*
  int n = 10000;
  for(int i = 0; i < n; i++){
    if(i & 1) tree.insert(i);
    else tree.insert(-i);
  }
*/

  cout << "input" << endl;
  while(true){
    cout << "min: " << tree.getMin() << ", max: " << tree.getMax() << ", size: " << tree.size() << endl;
    int q;
    cin >> q;

    if(q == 0) break;
    else if(q == 1){
      int d;
      cin >> d;
      tree.insert(d);
    }else if(q == 2){
      int d;
      cin >> d;
      tree.erase(d);
    }else if(q == 3){
      int ord;
      cin >> ord;
      cout << tree.order(ord) << endl; 
    }else if(q == 4){
      tree.clear();
    }
  }

  return 0;
}
