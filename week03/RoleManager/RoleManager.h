#include <bits/stdc++.h>
#include "Role.h"

#ifndef ROLE_MANAGER_H
#define ROLE_MANAGER_H

#define N 1005
typedef struct Team {
  int team_id;
  std::vector<int> character_ids;
} team_t;

Role roles[N];
team_t team_list[N];

class RoleManager {
 private:
  std::vector<int> role_ids;

  static bool compare_by_power(const int& id_1, const int id_2) {
    double power_1 = roles[id_1].get_power();
    double power_2 = roles[id_2].get_power();
    if (power_1 != power_2) {
      return power_1 > power_2;
    }
    return id_1 < id_2;
  }

 public:
  RoleManager() {
  }

  void add_role(Role new_role) {
    int id = new_role.get_character_id();
    roles[id] = new_role;
    role_ids.push_back(id);
  }

  void set_attribute(int character_id, std::string attribute, int value) {
    switch (attribute[5]) {
      case 's':
        roles[character_id].set_base_strength(value);
        break;
      case 'm':
        roles[character_id].set_base_mana(value);
        break;
      case 'a':
        roles[character_id].set_base_agility(value);
        break;
      default:
        break;
    }
  }

  void upgrade(int character_id) {
    roles[character_id].upgrade();
  }

  void equip(int character_id, std::string equip_type, double value) {
    roles[character_id].equip_role(value);
  }

  //   void equip(int character_id, std::string equip_type, double value) {
  //     if (roles[character_id].get_role() == Warrior && equip_type == "weapon"  //
  //         || roles[character_id].get_role() == Mage && equip_type == "staff"   //
  //         || roles[character_id].get_role() == Rogue && equip_type == "stealth") {
  //       roles[character_id].equip_role(value);
  //     }
  //   }

  void list_normal() {
    std::sort(role_ids.begin(), role_ids.end());
    for (int id : role_ids) {
      Role cur_role = roles[id];
      int strength = cur_role.get_role() == Warrior ? cur_role.get_unique_attribute() : cur_role.get_base_strength();
      int mana = cur_role.get_role() == Mage ? cur_role.get_unique_attribute() : cur_role.get_base_mana();
      int agility = cur_role.get_role() == Rogue ? cur_role.get_unique_attribute() : cur_role.get_base_agility();
      std::cout << "C" << id << " strength " << strength << " mana " << mana << " agility " << agility << "\n";
    }
  }

  void list_power() {
    std::sort(role_ids.begin(), role_ids.end(), compare_by_power);
    for (int id : role_ids) {
      Role cur_role = roles[id];
      int strength = cur_role.get_role() == Warrior ? cur_role.get_unique_attribute() : cur_role.get_base_strength();
      int mana = cur_role.get_role() == Mage ? cur_role.get_unique_attribute() : cur_role.get_base_mana();
      int agility = cur_role.get_role() == Rogue ? cur_role.get_unique_attribute() : cur_role.get_base_agility();
      std::cout << "C" << id << " strength " << strength << " mana " << mana << " agility " << agility << "\n";
    }
  }

  void power_list() {
    std::sort(role_ids.begin(), role_ids.end());
    for (int id : role_ids) {
      double power = roles[id].get_power();
      std::cout << "C" << id << " power: " << power << "\n";
    }
  }

  void battle(int id_1, int id_2) {
    double power_1 = roles[id_1].get_power();
    double power_2 = roles[id_2].get_power();
    double min_power = std::min(power_1, power_2);
    if (std::abs(power_1 - power_2) / min_power < 0.1) {
      std::cout << "Draw\n";
    } else {
      int win_id = power_1 > power_2 ? id_1 : id_2;
      std::cout << "C" << win_id << " wins\n";
    }
  }

  void team_characters(team_t new_team) {
    team_list[new_team.team_id] = new_team;
  }

  void modify_team(int team_id, std::string attribute, int value) {
    team_t cur_team = team_list[team_id];
    for (int character_id : cur_team.character_ids) {
      if (attribute == "base_strength") {
        roles[character_id].set_base_strength(value);
      }
      if (attribute == "base_mana") {
        roles[character_id].set_base_mana(value);
      }
      if (attribute == "base_agility") {
        roles[character_id].set_base_agility(value);
      }
    }
  }
};
#endif  // ROLE_MANAGER_H