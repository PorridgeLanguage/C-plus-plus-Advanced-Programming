#include <iostream>
#include "Calculator.h"
#include "TreeNode.h"
int main() {
  Calculator calculator;
  calculator.registerConstant("x", 2);
  calculator.registerOperator("h ^ l = h * l / x", 5);
  calculator.registerConstant("h", 2);
  calculator.registerConstant("l", 2);
  std::cout << calculator.calculate("h ^ l") << std::endl;
  calculator.registerConstant("h", 3);
  calculator.registerConstant("l", 3);
  std::cout << calculator.calculate("h ^ l") << std::endl;
}