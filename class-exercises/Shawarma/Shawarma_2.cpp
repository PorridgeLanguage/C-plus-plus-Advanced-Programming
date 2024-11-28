#include <bits/stdc++.h>

std::unordered_map<std::string, int> foods_map =
    {{"Chicken", 0}, {"Lettuce", 0}, {"Tomato", 0}, {"Cheese", 0}, {"Onion", 0}, {"Sauce", 0}};

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string operate;
    std::cin >> operate;
    if (operate == "Stock") {
      std::string food_type;
      int quality;
      std::cin >> food_type >> quality;
      foods_map[food_type] += quality;
      std::cout << "Stocked " << food_type << " with " << quality << " units\n";
    } else if (operate == "Order") {
      std::string customer_id;
      std::cin >> customer_id;
      std::string food_type;
      int quality;
      std::string command;
      std::getline(std::cin, command);
      command.substr(0, 1);
      std::stringstream ss(command);
      int count = 0;
      while (ss >> food_type >> quality) {
        if (foods_map[food_type] < quality) {
          count++;
          if (count == 1) {
            std::cout << "Order " << customer_id << " failed: missing ";
            std::cout << food_type << " " << quality - foods_map[food_type];
          } else {
            std::cout << ", " << food_type << " " << quality - foods_map[food_type];
          }
        }
      }
      if (count == 0) {
        std::cout << "Order " << customer_id << " completed\n";
        std::stringstream ss(command);
        while (ss >> food_type >> quality) {
          foods_map[food_type] -= quality;
        }
      } else {
        std::cout << "\n";
      }
    } else if (operate == "Inventory") {
      std::cout << "=== Inventory ===\n";
      std::cout << "Chicken: " << foods_map["Chicken"] << "\n";
      std::cout << "Lettuce: " << foods_map["Lettuce"] << "\n";
      std::cout << "Tomato: " << foods_map["Tomato"] << "\n";
      std::cout << "Cheese: " << foods_map["Cheese"] << "\n";
      std::cout << "Onion: " << foods_map["Onion"] << "\n";
      std::cout << "Sauce: " << foods_map["Sauce"] << "\n";
      std::cout << "=================\n";
    }
  }
}