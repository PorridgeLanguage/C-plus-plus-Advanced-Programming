#include <iostream>
#include <vector>

struct TreeNode {
  int id;
  int val;
  std::vector<TreeNode*> children;
  TreeNode(int x)
      : id(x) {}
};

int n, p, q, k;

bool strategy_wang(TreeNode* cur_node, TreeNode* parent) {
  return cur_node->val > p;
}

bool strategy_hu(TreeNode* cur_node, TreeNode* parent) {
  if (parent == NULL) {
    return true;
  }
  return cur_node->val > q && cur_node->val + parent->val > k;
}

bool strategy_xie(TreeNode* cur_node, TreeNode* parent) {
  if (parent == NULL) {
    return true;
  }
  return cur_node->val % 2 == 0;
}

int calculate(TreeNode* node, TreeNode* parent, int result, bool (*strategy)(TreeNode*, TreeNode*)) {
  if (strategy(node, parent)) {
    result += node->val;
    for (auto child : node->children) {
      result = calculate(child, node, result, strategy);
    }
  }
  return result;
}

int main() {
  std::cin >> n >> p >> q >> k;
  std::vector<TreeNode*> nodes(n);
  for (int i = 0; i < n; i++) {
    nodes[i] = new TreeNode(i + 1);
  }
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    std::cin >> x >> y;
    nodes[x - 1]->children.push_back(nodes[y - 1]);
  }
  for (int i = 0; i < n; i++) {
    std::cin >> nodes[i]->val;
  }
  int value_wang = calculate(nodes[0], NULL, 0, strategy_wang);
  int value_hu = calculate(nodes[0], NULL, 0, strategy_hu);
  int value_xie = calculate(nodes[0], NULL, 0, strategy_xie);
  std::cout << value_wang << " " << value_hu << " " << value_xie << "\n";

  return 0;
}