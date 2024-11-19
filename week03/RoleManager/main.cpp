#include <bits/stdc++.h>
#include "Role.h"
#include "RoleManager.h"

int main() {
  RoleManager role_manager;
  std::string operater;
  int num;
  std::cin >> num;
  for (int i = 0; i < num; i++) {
    std::cin >> operater;
    if (operater == "Add") {
      std::string role;
      char ch;
      int character_id;
      std::cin >> role >> ch >> character_id;
      // std::cout << role << " " << character_id << "\n";
      int character;
      switch (role[0]) {
        case 'W':
          character = Warrior;
          break;
        case 'M':
          character = Mage;
          break;
        case 'R':
          character = Rogue;
          break;
        default:
          break;
      }
      Role new_role = Role(character_id, character);
      role_manager.add_role(new_role);
      // role_manager.list_normal();
    }
    if (operater == "Set") {
      int character_id;
      char temp;
      std::string attribute;
      double value;
      std::cin >> temp >> character_id >> attribute >> value;
      role_manager.set_attribute(character_id, attribute, value);
      // role_manager.list_normal();
    }
    if (operater == "Team") {
      team_t new_team;
      char temp;
      std::cin >> temp >> new_team.team_id;

      std::string character_ids_line;
      std::getline(std::cin, character_ids_line);
      std::stringstream ss(character_ids_line);
      std::string character_id_str;

      while (ss >> character_id_str) {
        int character_id = std::stoi(character_id_str.substr(1));
        new_team.character_ids.push_back(character_id);
      }
      role_manager.team_characters(new_team);
      // role_manager.list_normal();
    }
    if (operater == "Modify") {
      char temp;
      int team_id;
      std::string attribute;
      double value;
      std::cin >> temp >> team_id >> attribute >> value;
      role_manager.modify_team(team_id, attribute, value);
      // role_manager.list_normal();
    }
    if (operater == "List") {
      std::string sub_operator;
      std::cin >> sub_operator;
      if (sub_operator[0] == 'N') {
        role_manager.list_normal();
      } else {
        role_manager.list_power();
      }
    }
    if (operater == "Upgrade") {
      int character_id;
      char temp;
      std::cin >> temp >> character_id;
      role_manager.upgrade(character_id);
      // role_manager.list_normal();
    }
    if (operater == "Equip") {
      int character_id;
      char temp;
      std::string equipment_type;
      double value;
      std::cin >> temp >> character_id >> equipment_type >> value;
      role_manager.equip(character_id, equipment_type, value);
    }
    if (operater == "PowerList") {
      role_manager.power_list();
    }
    if (operater == "Battle") {
      int character_id1, character_id2;
      char temp;
      std::cin >> temp >> character_id1 >> temp >> character_id2;
      //   std::cout << character_id1 << "\n";
      //   std::cout << character_id2 << '\n';
      role_manager.battle(character_id1, character_id2);
    }
  }
}