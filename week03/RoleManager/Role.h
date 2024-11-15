#include <bits/stdc++.h>

#ifndef ROLE_H
#define ROLE_H

#define Warrior 1  // 战士
#define Mage 2     // 法师
#define Rogue 3    // 盗贼

class Role {
 private:
  int character_id;         // 角色编号
  int role;                 // 角色种类
  int grade;                // 角色等级
  double unique_attribute;  // 特殊属性
  double base_strength;
  double base_mana;
  double base_agility;
  double equipment_attribute;  // 装备
  double power;

  void update_unique_attribute() {
    if (role == Warrior) {
      this->unique_attribute = base_strength + equipment_attribute;
    } else if (role == Mage) {
      this->unique_attribute = base_mana + 2 * equipment_attribute;
    } else if (role == Rogue) {
      this->unique_attribute = base_agility + equipment_attribute;
    }
  }
  void update_power() {
    if (role == Warrior) {
      this->power = unique_attribute * 1.5 + base_mana * 0.5 + base_agility * 0.8;
    } else if (role == Mage) {
      this->power = unique_attribute * 2.0 + base_strength * 0.6 + base_agility * 0.7;
    } else if (role == Rogue) {
      this->power = unique_attribute * 1.8 + base_strength * 0.6 + base_mana * 0.4;
    }
  }

 public:
  Role(int character_id, int role) {
    this->character_id = character_id;
    this->role = role;
    this->grade = 0;
    this->unique_attribute = 0;
    this->base_strength = 0;
    this->base_mana = 0;
    this->base_agility = 0;
    this->equipment_attribute = 0;
  }

  Role() {
    this->character_id == 0;
  }
  void set_base_strength(double base_strength) {
    this->base_strength = base_strength;
    update_unique_attribute();
    update_power();
  }

  void set_base_mana(double base_mana) {
    this->base_mana = base_mana;
    update_unique_attribute();
    update_power();
  }

  void set_base_agility(double base_agility) {
    this->base_agility = base_agility;
    update_unique_attribute();
    update_power();
  }

  void equip_role(double value) {
    if (equipment_attribute > 0) {
      std::cout << "Character C" << character_id << " already has equipment\n";
    } else {
      this->equipment_attribute = value;
      update_unique_attribute();
      update_power();
    }
  }

  void upgrade() {
    if (grade < 5) {
      grade++;
      if (role == Warrior) {
        base_strength *= 1.1;
      } else if (role == Mage) {
        base_mana *= 1.2;
      } else if (role == Rogue) {
        base_agility *= 1.15;
      }
      update_unique_attribute();
      update_power();
    } else {
      std::cout << "Character C" << this->character_id << " is already at max level\n";
    }
  }

  double get_base_strength() {
    return this->base_strength;
  }

  double get_base_mana() {
    return this->base_mana;
  }

  double get_base_agility() {
    return this->base_agility;
  }

  double get_power() {
    return this->power;
  }

  double get_unique_attribute() {
    return this->unique_attribute;
  }

  double get_equipment_attribute() {
    return this->equipment_attribute;
  }

  int get_character_id() {
    return this->character_id;
  }

  int get_role() {
    return this->role;
  }
};

#endif  // ROLE_H