#include "trie.h"
#include <string_view>

template<class T>
auto Trie::Get(std::string_view key) const -> const T * {
  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
  auto node = root_;
  for (char ch: key) {
    if (node == nullptr) {
      return nullptr;
    }
    auto temp = node->children_.find(ch);
    if (temp == node->children_.end()) {
      return nullptr;
    }
    node = node->children_.at(ch);
  }
  // cast it to `const TrieNodeWithValue<T> *
  const auto *value_node = dynamic_cast<const TrieNodeWithValue<T> *>(node.get());
  if (value_node != nullptr) {
    return value_node->value_.get();
  }
  return nullptr;
}

template<class T>
void put_recursively(const std::shared_ptr<TrieNode> &new_root, std::string_view key, T value) {
  for (auto &child: new_root->children_) {
    if (key[0] == child.first) {
      if (key.size() == 1) {
        std::shared_ptr<T> sharedPtr = std::make_shared<T>(std::move(value));
        TrieNodeWithValue node_with_val(child.second->children_, sharedPtr);
        child.second = std::make_shared<const TrieNodeWithValue<T>>(node_with_val);
      } else {
        std::shared_ptr<TrieNode> ptr = child.second->Clone();
        std::string_view sub_key = key.substr(1, key.size() - 1);
        put_recursively<T>(ptr, sub_key, std::move(value));
        child.second = std::shared_ptr<const TrieNode>(ptr);
      }
      return;
    }
  }
  char ch = key.at(0);
  if (key.size() == 1) {
    std::shared_ptr<T> val_p = std::make_shared<T>(std::move(value));
    new_root->children_.insert({ch, std::make_shared<const TrieNodeWithValue<T>>(val_p)});
  } else {
    auto ptr = std::make_shared<TrieNode>();
    std::string_view sub_key = key.substr(1, key.size() - 1);
    put_recursively<T>(ptr, sub_key, std::move(value));
    new_root->children_.insert({ch, std::move(ptr)});
  }
}

template<class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.
  if (key.empty()) {
    std::shared_ptr<T> sharedPtr = std::make_shared<T>(std::move(value));
    std::unique_ptr<TrieNodeWithValue<T>> new_root = nullptr;
    new_root = std::make_unique<TrieNodeWithValue<T>>(root_->children_, std::move(sharedPtr));
    return Trie(std::move(new_root));
  }
  std::shared_ptr<TrieNode> new_root = nullptr;
  new_root = root_ != nullptr ? root_->Clone() : std::make_unique<TrieNode>();
  put_recursively<T>(new_root, key, std::move(value));
  return Trie(std::move(new_root));
}

bool remove_recursively(const std::shared_ptr<TrieNode> &new_root, std::string_view key) {
  for (auto &child: new_root->children_) {
    if (key.at(0) != child.first) {
      continue;
    }
    if (key.size() == 1) {
      if (!child.second->is_value_node_) {
        return false;
      } else if (child.second->children_.empty()) {
        new_root->children_.erase(child.first);
      } else {
        child.second = std::make_shared<const TrieNode>(child.second->children_);
      }
      return true;
    }
    std::shared_ptr<TrieNode> node = child.second->Clone();
    std::string_view sub_key = key.substr(1, key.size() - 1);
    if (!remove_recursively(node, sub_key)) {
      return false;
    }
    if (!node->children_.empty() || node->is_value_node_) {
      child.second = std::shared_ptr<const TrieNode>(node);
    } else {
      new_root->children_.erase(child.first);
    }
    return true;
  }
  return false;
}

auto Trie::Remove(std::string_view key) const -> Trie {
  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
  // throw "Trie::Remove is not implemented.";
  if (key.empty() && root_->is_value_node_) {
    std::shared_ptr<TrieNode> new_root = std::make_shared<TrieNode>(root_->children_);
    return Trie(new_root);
  }
  std::shared_ptr<TrieNode> new_root = root_->Clone();
  if (!remove_recursively(new_root, key)) {
    return *this;
  }
  if (!new_root->children_.empty() || new_root->is_value_node_) {
    return Trie(std::move(new_root));
  }
  return Trie(nullptr);
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;

template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;

template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;

template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;

template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;

template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;
