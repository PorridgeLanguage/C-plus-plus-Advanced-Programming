#include "Calculator.h"
#include <bits/stdc++.h>
#include <stack>
using namespace std;

Calculator::Calculator() {
  precedenceTable['+'] = 6;
  precedenceTable['-'] = 6;
  precedenceTable['*'] = 5;
  precedenceTable['/'] = 5;

  functionTable['+'] = [](double a, double b) { return a + b; };
  functionTable['-'] = [](double a, double b) { return a - b; };
  functionTable['*'] = [](double a, double b) { return a * b; };
  functionTable['/'] = [](double a, double b) { return a / b; };
}

void Calculator::registerOperator(const string& expr, int precedence) {
  // TODO: 注册运算符
  stringstream ss(expr);
  string left, op, right, eq, new_expr;
  ss >> left >> op >> right >> eq;
  precedenceTable[op[0]] = precedence;
  getline(ss, new_expr);
  new_expr.erase(0, new_expr.find_first_not_of(" "));
  new_expr.erase(new_expr.find_last_not_of(" ") + 1);
  functionTable[op[0]] = [left, right, new_expr, this](double a, double b) {
    stringstream ss(new_expr);
    string result = "";
    string temp;
    while (ss >> temp) {
      if (temp == left) {
        temp = to_string(a);
      } else if (temp == right) {
        temp = to_string(b);
      }
      temp += " ";
      result += temp;
    }
    return this->calculate(result);
  };
}

void Calculator::registerConstant(const string& symbol, double val) {
  // TODO：注册常数
  constantTable[symbol] = val;
}

double Calculator::calculate(const string& expr) {
  // TODO: 解析并计算表达式
  vector<string> tokens;
  string cur_token = "";
  int size = expr.size();
  for (int i = 0; i < size; i++) {
    if (expr[i] == ' ') {
      if (!cur_token.empty()) {
        tokens.push_back(cur_token);
        cur_token = "";
      }
    } else {
      cur_token += expr[i];
    }
  }
  if (!cur_token.empty()) {
    tokens.push_back(cur_token);
  }
  TreeNode* nodes = buildTree(tokens);
  return getVal(nodes);
  // double res = getVal(nodes);
  // std::cout << res << "\n";
  // return res;
}

bool is_number(const string str, double& value) {
  if (str.empty()) {
    return false;
  }
  std::istringstream iss(str);
  iss >> value;

  if (iss.fail() || !iss.eof()) {
    return false;
  }
  return true;
}

bool is_operater(const string str) {
  return str == "+" || str == "-" || str == "*" || str == "/" || str == "!" || str == "@" || str == "#" || str == "$" || str == "%" || str == "^" || str == "&" || str == "<" || str == ">" || str == "?";
}

TreeNode* Calculator::buildTree(vector<string>& tokens) {
  // TODO: 解析表达式并构造表达式解析树
  vector<string> new_token;  // 后缀表达式
  stack<string> such_stack;
  for (auto element : tokens) {
    // cout << element << "\n";
    if (!is_operater(element) && element != "(" && element != ")") {
      // 不是操作符且不是括号
      new_token.push_back(element);
    }
    if (element == "(") {
      such_stack.push(element);
    }
    if (element == ")") {
      // string cur_op = such_stack.top();
      while (!such_stack.empty()) {
        string cur_op = such_stack.top();
        if (cur_op == "(") {
          such_stack.pop();
          break;
        }
        new_token.push_back(cur_op);
        such_stack.pop();
        // cur_op = such_stack.top();
      }
    }
    if (is_operater(element)) {
      int pre = precedenceTable[element[0]];
      while (!such_stack.empty()) {
        string cur_oper = such_stack.top();
        if (cur_oper == "(") {
          break;
        }
        int cur_pre = precedenceTable[cur_oper[0]];
        if (cur_pre > pre) {
          break;
        }
        new_token.push_back(cur_oper);
        such_stack.pop();
      }
      such_stack.push(element);
    }
  }
  while (!such_stack.empty()) {
    new_token.push_back(such_stack.top());
    such_stack.pop();
  }
  // for (auto token : new_token) {
  //   cout << token << " ";
  // }
  // cout << "\n";
  // 生成树
  stack<TreeNode*> tree_nodes;
  for (auto token : new_token) {
    if (!is_operater(token)) {
      TreeNode* leaf_node = new TreeNode(token);
      tree_nodes.push(leaf_node);
    } else {
      TreeNode* right = NULL;
      TreeNode* left = NULL;

      if (!tree_nodes.empty()) {
        right = tree_nodes.top();
        tree_nodes.pop();
      }
      if (!tree_nodes.empty()) {
        left = tree_nodes.top();
        tree_nodes.pop();
      }

      TreeNode* oper_node = new TreeNode(functionTable[token[0]], token, left, right);
      tree_nodes.push(oper_node);
    }
  }
  return tree_nodes.top();
}

double Calculator::getVal(TreeNode* node) {
  // TODO: 获取树上某一节点的值
  if (node == NULL) {
    return 0.0;
  }
  if (node->operate) {
    // 是非叶节点
    return node->operate(getVal(node->left), getVal(node->right));
  }
  // 是叶节点
  double value = 0.0;
  if (is_number(node->element, value)) {
    return value;
  }
  return constantTable[node->element];
}
