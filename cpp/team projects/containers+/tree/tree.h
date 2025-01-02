#ifndef S21_CONTAINERS_TREE_H
#define S21_CONTAINERS_TREE_H

#include <iostream>

namespace s21 {

template <typename Key, typename T>
class tree {
  using value_type = std::pair<Key, T>;

 private:
  struct Node {
    Key key;
    T data;
    Node *parent_node;
    Node *left_node;
    Node *right_node;
  };
  size_t tree_size;
  Node *root_node;
  Node *last_node;

 public:
  class TreeIterator {
    friend class tree;

   public:
    Node *curr_node;

   public:
    TreeIterator(){};
    explicit TreeIterator(Node *other) { curr_node = other; };
    TreeIterator(TreeIterator &other) { curr_node = other.curr_node; };
    TreeIterator(TreeIterator &&other) { curr_node = other.curr_node; };

    TreeIterator operator=(TreeIterator other) {
      if (this != &other) {
        curr_node = other.curr_node;
      }
      return *this;
    };
    Key &operator*() { return curr_node->key; };

    TreeIterator operator++() {
      if (curr_node->right_node != nullptr) {
        curr_node = curr_node->right_node;
        while (curr_node->left_node != nullptr) {
          curr_node = curr_node->left_node;
        }
      } else {
        while (curr_node->parent_node->right_node == curr_node) {
          curr_node = curr_node->parent_node;
        };
        curr_node = curr_node->parent_node;
      }
      return *this;
    };
    TreeIterator operator--() {
      if (curr_node->left_node != nullptr) {
        curr_node = curr_node->left_node;
        while (curr_node->right_node != nullptr) {
          curr_node = curr_node->right_node;
        }
      } else {
        while (curr_node->parent_node->left_node == curr_node) {
          curr_node = curr_node->parent_node;
        };
        curr_node = curr_node->parent_node;
      }
      return *this;
    };
    bool operator==(const TreeIterator &other) {
      return (curr_node == other.curr_node);
    };
    bool operator!=(const TreeIterator &other) {
      return (curr_node != other.curr_node);
    };
  };

  class ConstTreeIterator {
    friend class tree;

   private:
    Node *curr_node;

   public:
    ConstTreeIterator(){};
    explicit ConstTreeIterator(Node *other) { curr_node = other; };
    ConstTreeIterator(TreeIterator &other) { curr_node = other.curr_node; };
    ConstTreeIterator(TreeIterator &&other) { curr_node = other.curr_node; };

    ConstTreeIterator operator=(TreeIterator other) {
      if (this != &other) {
        curr_node = other.curr_node;
      }
      return *this;
    };
    Key &operator*() { return curr_node->key; };

    ConstTreeIterator operator++() {
      if (curr_node->right_node != nullptr) {
        curr_node = curr_node->right_node;
        while (curr_node->left_node != nullptr) {
          curr_node = curr_node->left_node;
        }
      } else {
        while (curr_node->parent_node->right_node == curr_node) {
          curr_node = curr_node->parent_node;
        };
        curr_node = curr_node->parent_node;
      }
      return *this;
    };
    ConstTreeIterator operator--() {
      if (curr_node->left_node != nullptr) {
        curr_node = curr_node->left_node;
        while (curr_node->right_node != nullptr) {
          curr_node = curr_node->right_node;
        }
      } else {
        while (curr_node->parent_node->left_node == curr_node) {
          curr_node = curr_node->parent_node;
        };
        curr_node = curr_node->parent_node;
      }
      return *this;
    };
    bool operator==(const TreeIterator &other) {
      return (curr_node == other.curr_node);
    };
    bool operator!=(const TreeIterator &other) {
      return (curr_node != other.curr_node);
    };
    bool operator==(const ConstTreeIterator &other) {
      return (curr_node == other.curr_node);
    };
    bool operator!=(const ConstTreeIterator &other) {
      return (curr_node != other.curr_node);
    };
  };

  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;

 public:
  tree() {
    last_node = new Node{};
    root_node = last_node;
    tree_size = 0;
  };
  tree(value_type value) : tree() { insert(value); };
  tree(std::initializer_list<value_type> const &items) : tree() {
    for (const value_type &value : items) {
      insert(value);
    }
  };
  tree(const tree &tr) : tree() {
    for (auto i = tr.cbegin(); i != tr.cend(); ++i) {
      insert(std::make_pair(i.curr_node->key, i.curr_node->data));
    }
  };
  tree(tree &&tr) : tree(tr) { tr.clear(); };
  ~tree() {
    clear();
    delete last_node;
  };

  void clear() {
    auto i = begin();
    while (root_node != last_node) {
      erase(i);
      i = begin();
    }
  };
  tree operator=(tree &&tr) {
    swap(tr);
    tr.clear();
    return *this;
  };
  size_t size() { return tree_size; };

  iterator begin() {
    Node *temp = root_node;
    while (temp->left_node != nullptr) {
      temp = temp->left_node;
    }
    return iterator(temp);
  };
  iterator end() { return iterator(last_node); };
  const_iterator cbegin() const {
    Node *temp = root_node;
    while (temp->left_node != nullptr) {
      temp = temp->left_node;
    }
    return const_iterator(temp);
  };
  const_iterator cend() const { return const_iterator(last_node); };

  bool empty() { return (tree_size == 0); };
  bool contains(const Key &key) {
    return recursiveSearch(key, root_node).second;
  };
  iterator find(const Key &key) {
    return recursiveSearch(key, root_node).first;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    Node *new_node = new Node{};
    new_node->key = value.first;
    new_node->data = value.second;
    bool ok = !contains(new_node->key);
    iterator i = find(new_node->key);
    if (ok) {
      if (last_node->parent_node) {
        last_node->parent_node->right_node = nullptr;
      }
      insertLeaf(root_node, new_node);
      Node *temp_node = root_node;
      while (temp_node->right_node != nullptr) {
        temp_node = temp_node->right_node;
      }
      temp_node->right_node = last_node;
      last_node->parent_node = temp_node;
      balance(new_node);
      i = iterator(new_node);
      ++tree_size;
    } else {
      delete new_node;
    }
    return std::make_pair(i, ok);
  };
  void erase(iterator pos) {
    if (pos.curr_node != nullptr && pos.curr_node != last_node) {
      if (pos.curr_node->left_node == nullptr &&
          pos.curr_node->right_node == nullptr) {
        if (pos.curr_node == root_node) {
          root_node = last_node;
        } else {
          create_parent_child(pos.curr_node, pos.curr_node->parent_node,
                              nullptr);
        }
      } else if (pos.curr_node->left_node == nullptr) {
        eraseBalanceOneLeaf(pos.curr_node, pos.curr_node->right_node);
      } else if (pos.curr_node->right_node == nullptr) {
        eraseBalanceOneLeaf(pos.curr_node, pos.curr_node->left_node);
      } else {
        eraseBalanceTwoLeaf(pos);
      }
      --tree_size;
      delete pos.curr_node;
    }
  };
  void swap(tree &other) {
    Node *temp = root_node;
    root_node = other.root_node;
    other.root_node = temp;
    temp = last_node;
    last_node = other.last_node;
    other.last_node = temp;
    size_t s = tree_size;
    tree_size = other.tree_size;
    other.tree_size = s;
  };
  void merge(tree &other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      insert(std::make_pair(i.curr_node->key, i.curr_node->data));
    }
    other.clear();
  };

 private:
  void insertLeaf(Node *curr_root, Node *new_node) {
    if (empty()) {
      root_node = new_node;
    } else if (new_node->key < curr_root->key) {
      new_node->parent_node = curr_root;
      if (curr_root->left_node == nullptr) {
        curr_root->left_node = new_node;
      }
      insertLeaf(curr_root->left_node, new_node);
    } else if (new_node->key > curr_root->key) {
      new_node->parent_node = curr_root;
      if (curr_root->right_node == nullptr) {
        curr_root->right_node = new_node;
      }
      insertLeaf(curr_root->right_node, new_node);
    }
  };
  void balance(Node *new_node) {
    if (new_node->parent_node && new_node->parent_node->parent_node) {
      if ((new_node->parent_node->right_node == nullptr &&
           new_node->parent_node->parent_node->right_node == nullptr) ||
          (new_node->parent_node->left_node == nullptr &&
           new_node->parent_node->parent_node->left_node == nullptr)) {
        balanceRotate(new_node);
      } else if ((new_node->parent_node->right_node == nullptr &&
                  new_node->parent_node->parent_node->left_node == nullptr) ||
                 (new_node->parent_node->left_node == nullptr &&
                  new_node->parent_node->parent_node->right_node == nullptr)) {
        balanceRotate(balanceSwap(new_node));
      }
    }
  };
  void balanceRotate(Node *new_node) {
    Node *new_parent = new_node->parent_node;
    Node *new_second = new_parent->parent_node;
    new_parent->parent_node = new_second->parent_node;
    if (new_parent->parent_node == nullptr) {
      root_node = new_parent;
    } else {
      create_parent_child(new_second, new_parent->parent_node, new_parent);
    }
    new_second->parent_node = new_parent;
    if (new_second->right_node == nullptr) {
      new_second->left_node = nullptr;
      new_parent->right_node = new_second;
    } else {
      new_second->right_node = nullptr;
      new_parent->left_node = new_second;
    }
  };
  Node *balanceSwap(Node *new_node) {
    Node *temp = new_node->parent_node;
    new_node->parent_node = temp->parent_node;
    create_parent_child(temp, temp->parent_node, new_node);
    temp->parent_node = new_node;
    if (temp->right_node == new_node) {
      temp->right_node = nullptr;
      new_node->left_node = temp;
    } else {
      temp->left_node = nullptr;
      new_node->right_node = temp;
    }
    return temp;
  };
  void create_parent_child(Node *curr_parent, Node *new_parent,
                           Node *new_child) {
    if (new_parent->right_node == curr_parent) {
      new_parent->right_node = new_child;
    } else {
      new_parent->left_node = new_child;
    }
  };
  std::pair<iterator, bool> recursiveSearch(const Key &key, Node *curr_root) {
    bool equal = false;
    iterator it = end();
    if (curr_root) {
      if (key == curr_root->key) {
        equal = true;
        it.curr_node = curr_root;
      } else if (key < curr_root->key) {
        equal = recursiveSearch(key, curr_root->left_node).second;
      } else {
        equal = recursiveSearch(key, curr_root->right_node).second;
      }
    }
    return std::make_pair(it, equal);
  };
  void eraseBalanceOneLeaf(Node *curr_node, Node *leaf_node) {
    leaf_node->parent_node = curr_node->parent_node;
    if (curr_node == root_node) {
      root_node = leaf_node;
    } else {
      create_parent_child(curr_node, curr_node->parent_node, leaf_node);
    }
  };
  void eraseBalanceTwoLeaf(iterator pos) {
    auto next = pos;
    ++next;
    create_parent_child(next.curr_node, next.curr_node->parent_node,
                        next.curr_node->right_node);
    next.curr_node->parent_node = pos.curr_node->parent_node;
    next.curr_node->left_node = pos.curr_node->left_node;
    next.curr_node->right_node = pos.curr_node->right_node;
    if (pos.curr_node == root_node) {
      root_node = next.curr_node;
    } else {
      create_parent_child(pos.curr_node, pos.curr_node->parent_node,
                          next.curr_node);
    }
    if (pos.curr_node->left_node) {
      pos.curr_node->left_node->parent_node = next.curr_node;
    }
    if (pos.curr_node->right_node) {
      pos.curr_node->right_node->parent_node = next.curr_node;
    }
  }
};

}  // namespace s21

#endif