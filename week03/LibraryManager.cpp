#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class BorrowStrategy {
 public:
  virtual ~BorrowStrategy() = default;
  virtual double calculate(int days) const = 0;
};

class DailyBorrowStrategy : public BorrowStrategy {
 public:
  DailyBorrowStrategy() {}

  double calculate(int days) const override {
    return days * 1.0;
  }
};

// 完成会员按周收费策略
class MemberBorrowStrategy : public BorrowStrategy {
 public:
  MemberBorrowStrategy(std::string level)
      : memberLevel(level) {}

  double calculate(int days) const override {
    int weeks = (days + 6) / 7;  // 如果天数不足一周，按一周计算
    double base_fee = weeks * 5.0;

    // 根据会员等级，应用不同的折扣
    double discount = 1.0;
    if (memberLevel == "REGULAR") {
      discount = 0.95;
    } else if (memberLevel == "GOLD") {
      discount = 0.85;
    } else if (memberLevel == "PLATINUM") {
      discount = 0.75;
    }

    return base_fee * discount;
  }

 private:
  std::string memberLevel;
};

class Book {
 public:
  Book(int id)
      : id(id) {}

  double calculate_fee() const {
    // 如果书籍没有借阅策略，则不收费
    if (borrow_strategy) {
      double price = borrow_strategy->calculate(days);
      return price;
    }
    return 0.0;
  }

  int get_id() const { return id; }

  void setBorrowStrategy(std::shared_ptr<BorrowStrategy> strategy) {
    borrow_strategy = strategy;
  }

  void setDays(int days) {
    this->days = days;
  }

 private:
  int id;
  int days = 0;  // 默认借阅天数为0

  std::shared_ptr<BorrowStrategy> borrow_strategy;
};

class Library {
 public:
  using BookPtr = std::shared_ptr<Book>;

  void add_book(const BookPtr& book) {
    books[book->get_id()] = book;
  }

  void borrow_book(int id, const std::shared_ptr<BorrowStrategy>& strategy) {
    auto book = books.find(id);
    if (book != books.end()) {
      book->second->setBorrowStrategy(strategy);
    }
  }

  double return_books(int days) {
    double total_fee = 0.0;
    // 为每本书设置借阅天数并计算费用
    for (auto& book : books) {
      book.second->setDays(days);
      total_fee += book.second->calculate_fee();
      book.second->setBorrowStrategy(nullptr);
    }

    return total_fee;
  }

 private:
  std::unordered_map<int, BookPtr> books;
};

// === TEST_CASES ===
void TEST_1();

void TEST_2();

void TEST_3();

void TEST_4();

void TEST_5();

void TEST_6();

void TEST_7();

#define REGISTER_TEST_CASE(name) {#name, name}

int main() {
  std::unordered_map<std::string, std::function<void()> >
      test_functions_by_name = {
          REGISTER_TEST_CASE(TEST_1),
          REGISTER_TEST_CASE(TEST_2),
          REGISTER_TEST_CASE(TEST_3),
          REGISTER_TEST_CASE(TEST_4),
          REGISTER_TEST_CASE(TEST_5),
          REGISTER_TEST_CASE(TEST_6),
          REGISTER_TEST_CASE(TEST_7),
      };

  std::string test_case_name;
  std::cin >> test_case_name;
  auto it = test_functions_by_name.find(test_case_name);
  assert(it != test_functions_by_name.end());
  auto fn = it->second;
  fn();
  return 0;
}

void TEST_1() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());

  assert(library.return_books(5) == 5.0);
}

void TEST_2() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("GOLD"));

  assert(library.return_books(8) == 8.5);
}

void TEST_3() {
  Library library;

  library.add_book(std::make_shared<Book>(1));

  assert(library.return_books(0) == 0.0);
}

void TEST_4() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());
  library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("PLATINUM"));

  assert(library.return_books(10) == 17.5);
}

void TEST_5() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());

  assert(library.return_books(5) == 5.0);

  library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("REGULAR"));

  assert(library.return_books(7) == 4.75);
}

void TEST_6() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("PLATINUM"));

  assert(library.return_books(14) == 7.5);
}

void TEST_7() {
  Library library;

  library.add_book(std::make_shared<Book>(1));
  library.add_book(std::make_shared<Book>(2));

  library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());

  assert(library.return_books(5) == 5.0);

  assert(library.return_books(10000) == 0.0);
}
