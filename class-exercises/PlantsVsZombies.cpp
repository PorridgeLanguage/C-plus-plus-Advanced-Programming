#include <bits/stdc++.h>

#define PEA 1     // 豌豆射手
#define NUT 2     // 坚果
#define POTATO 3  // 土豆地雷

typedef struct Plant {
  int type;
  int hp;
  int atk;
  int x;
  int y;
  bool is_alife = false;
} plant_t;

typedef struct Zombie {
  int hp;
  int atk;
  int speed;
  int x;
  int y;

} zombies_t;

std::vector<plant_t> plants;
std::vector<zombies_t> zombies;

int main() {
  int num_p, num_z;
  std::cin >> num_p >> num_z;
  for (int i = 0; i < num_p; i++) {
    // 输入植物相关信息
    std::string plant_type;
    std::cin >> plant_type;
    plant_t cur_plant;
    cur_plant.is_alife = false;
    if (plant_type == "pea") {
      cur_plant.type = PEA;
      std::cin >> cur_plant.hp >> cur_plant.atk >> cur_plant.x >> cur_plant.y;
    } else if (plant_type == "nut") {
      cur_plant.type = NUT;
      cur_plant.atk = 0;
      std::cin >> cur_plant.hp >> cur_plant.x >> cur_plant.y;
    } else if (plant_type == "potato") {
      cur_plant.type = POTATO;
      cur_plant.hp = 100005;
      std::cin >> cur_plant.atk >> cur_plant.x >> cur_plant.y;
    }
    plants.push_back(cur_plant);
  }
  for (int i = 0; i < num_z; i++) {
    // 输入僵尸相关信息
    zombies_t cur_zombie;
    cur_zombie.y = 9;
    std::cin >> cur_zombie.hp >> cur_zombie.atk >> cur_zombie.speed >> cur_zombie.x;
    zombies.push_back(cur_zombie);
  }
  bool is_end = false;
  int count = 0;
  while (!is_end) {
    count++;
    // Plants attack
    for (plant_t plant : plants) {
      if (plant.type == PEA) {
        int atk_y = 9;
        for (zombies_t& zombie : zombies) {
          if (zombie.x == plant.x && zombie.y < atk_y) {
            atk_y = zombie.y;
          }
        }
        for (zombies_t& zombie : zombies) {
          if (zombie.x == plant.x && zombie.y == atk_y) {
            zombie.hp -= plant.atk;
          }
        }
      }
      if (plant.type == POTATO && plant.is_alife) {
        for (zombies_t& zombie : zombies) {
          if (zombie.x >= plant.x - 1 && zombie.x <= plant.x + 1 && zombie.y >= plant.y - 1 && zombie.y <= plant.y + 1) {
            zombie.hp -= plant.atk;
          }
        }
      }
      for (int i = zombies.size() - 1; i >= 0; i--) {
        if (zombies[i].hp <= 0) {
          zombies.erase(zombies.begin() + i);
        }
      }
      for (int i = plants.size() - 1; i >= 0; i--) {
        if (plants[i].type == POTATO && plants[i].is_alife) {
          plants.erase(plants.begin() + i);
        }
      }
    }
    // Zombies move left
    for (zombies_t& zombie : zombies) {
      int next_pos = zombie.y - zombie.speed;
      for (plant_t plant : plants) {
        if (plant.type == PEA || plant.type == NUT) {
          if (plant.x == zombie.x && plant.y > next_pos) {
            next_pos = plant.y;
          }
        }
      }
      // make potato alive
      for (plant_t& plant : plants) {
        if (plant.type == POTATO && plant.y >= next_pos) {
          plant.is_alife = true;
        }
      }
      zombie.y = next_pos;
    }
    // Zombie attack
    for (zombies_t& zombie : zombies) {
      for (plant_t& plant : plants) {
        if (plant.type != POTATO && zombie.x == plant.x && zombie.y == plant.y) {
          plant.hp -= zombie.atk;
        }
      }
    }
    for (int i = plants.size() - 1; i >= 0; i--) {
      if (plants[i].hp <= 0) {
        plants.erase(plants.begin() + i);
      }
    }

    // Output the result
    std::cout << count << " " << plants.size() << " " << zombies.size() << "\n";
    // Judge wins
    if (zombies.size() == 0 && plants.size() >= 0) {
      std::cout << "plants win\n";
      is_end = true;
    }
    for (zombies_t& zombie : zombies) {
      if (zombie.y < 0) {
        std::cout << "zombies win\n";
        is_end = true;
        break;
      }
    }
  }
  return 0;
}