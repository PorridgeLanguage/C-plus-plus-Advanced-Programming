#include "MessageQueueManager.h"

// Message 类的实现

Message::Message(const char* d, int p) {
  // TODO: Task 1-1
  priority = p;
  data = new char[strlen(d) + 1];
  strcpy(data, d);
}

Message::Message(Message&& other) noexcept {
  // TODO: Task 1-2
  data = other.data;
  priority = other.priority;
  other.data = nullptr;
}

Message& Message::operator=(Message&& other) noexcept {
  // TODO: Task 1-2
  if (this != &other) {
    delete[] data;
    data = other.data;
    priority = other.priority;
    other.data = nullptr;
  }
  return *this;
}

Message::~Message() {
  delete[] data;
}

// MessageQueueManager 类的实现
MessageQueueManager::MessageQueueManager() {}

void MessageQueueManager::addMessage(Message m) {
  // TODO: Task 2
  auto it = std::lower_bound(messages.begin(), messages.end(), m,
                             [](const Message& a, const Message& b) { return a.priority < b.priority; });
  // 插入消息
  messages.insert(it, std::move(m));
}

MessageQueueManager::MessageQueueManager(MessageQueueManager&& other) noexcept {
  // TODO: Task 3-1
  messages = std::move(other.messages);
}

MessageQueueManager&
MessageQueueManager::operator=(MessageQueueManager&& other) noexcept {
  // TODO: Task 3-2
  if (this != &other) {
    // 移动赋值运算符：释放现有资源，接管其他对象的资源
    messages = std::move(other.messages);
  }
  return *this;
}

void MessageQueueManager::printMessages() const {
  for (const auto& msg : messages) {
    std::cout << "Message: " << msg.data << ", Priority: " << msg.priority
              << std::endl;
  }
}

MessageQueueManager::~MessageQueueManager() {
  std::cout << "Destructing MessageQueueManager" << std::endl;
}