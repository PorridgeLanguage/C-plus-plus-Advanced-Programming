#include <bits/stdc++.h>

int Chicken = 0;
int Lettuce = 0;
int Tomato = 0;
int Cheese = 0;
int Onion = 0;
int Sauce = 0;

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string operate;
    std::cin >> operate;
    if (operate == "Stock") {
      std::string food_type;
      int num;
      std::cin >> food_type >> num;
      if (food_type == "Chicken") {
        Chicken += num;
      } else if (food_type == "Lettuce") {
        Lettuce += num;
      } else if (food_type == "Tomato") {
        Tomato += num;
      } else if (food_type == "Cheese") {
        Cheese += num;
      } else if (food_type == "Onion") {
        Onion += num;
      } else if (food_type == "Sauce") {
        Sauce += num;
      }
      std::cout << "Stocked " << food_type << " with " << num << " units\n";
    } else if (operate == "Order") {
      std::string customer_id;
      std::cin >> customer_id;
      std::string food_type;
      int num;
      std::string command;
      std::getline(std::cin, command);
      command.erase(0, 1);
      std::stringstream ss(command);
      int count = 0;
      while (ss >> food_type >> num) {
        int cur_num = 0;
        if (food_type == "Chicken") {
          cur_num = Chicken;
        } else if (food_type == "Lettuce") {
          cur_num = Lettuce;
        } else if (food_type == "Tomato") {
          cur_num = Tomato;
        } else if (food_type == "Cheese") {
          cur_num = Cheese;
        } else if (food_type == "Onion") {
          cur_num = Onion;
        } else if (food_type == "Sauce") {
          cur_num = Sauce;
        }
        if (cur_num < num) {
          count++;
          if (count == 1) {
            std::cout << "Order " << customer_id << " failed: missing ";
            std::cout << food_type << " " << num - cur_num;
          } else {
            std::cout << ", " << food_type << " " << num - cur_num;
          }
        }
      }
      if (count == 0) {
        std::cout << "Order " << customer_id << " completed\n";
        std::stringstream tt(command);
        while (tt >> food_type >> num) {
          if (food_type == "Chicken") {
            Chicken -= num;
          } else if (food_type == "Lettuce") {
            Lettuce -= num;
          } else if (food_type == "Tomato") {
            Tomato -= num;
          } else if (food_type == "Cheese") {
            Cheese -= num;
          } else if (food_type == "Onion") {
            Onion -= num;
          } else if (food_type == "Sauce") {
            Sauce -= num;
          }
        }
      } else {
        std::cout << "\n";
      }
    } else if (operate == "Inventory") {
      std::cout << "=== Inventory ===\n";
      std::cout << "Chicken: " << Chicken << "\n";
      std::cout << "Lettuce: " << Lettuce << "\n";
      std::cout << "Tomato: " << Tomato << "\n";
      std::cout << "Cheese: " << Cheese << "\n";
      std::cout << "Onion: " << Onion << "\n";
      std::cout << "Sauce: " << Sauce << "\n";
      std::cout << "=================\n";
    }
  }
}