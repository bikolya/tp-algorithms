#include <iostream>

using namespace std;

struct node_t {
  node_t(int _data = 0, node_t *_left = NULL, node_t *_right = NULL) :
          data(_data),
          left(_left),
          right(_right)
  {}

  int data;
  node_t *left;
  node_t *right;
};

void print_node(node_t *node) {
  cout << node->data << " ";
}

struct tree_t {
public:
  node_t *root;

  tree_t() : root(0) {}

  ~tree_t() {
    free(root);
  }

  void insert(int data) {
    node_t *node = new node_t(data);
    insert(&root, node);
  }

  template<class action_t>
  void traverse_pre_order(const action_t &action) {
    traverse_pre_order(root, action);
  }

private:
  static void insert(node_t **root, node_t *node) {
    if (!*root) {
      *root = node;
      return;
    }

    if (node->data < (*root)->data) {
      insert(&(*root)->left, node);
    } else {
      insert(&(*root)->right, node);
    }
  }

  template<class action_t>
  static void traverse_pre_order(node_t *root, const action_t &action) {
    if (!root) return;

    action(root);
    traverse_pre_order(root->left, action);
    traverse_pre_order(root->right, action);
  }
  
  static void free(node_t *node) {
    if (!node) return;

    free(node->left);
    free(node->right);

    delete node;
  }

};


int main()
{
  tree_t tree;

  size_t size = 0;
  cin >> size;

  int value;
  for (size_t i = 0; i < size; ++i) {
    cin >> value;
    tree.insert(value);
  }

  tree.traverse_pre_order(print_node);
  return 0;
}
