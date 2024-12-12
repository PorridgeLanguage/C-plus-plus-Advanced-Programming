#include <bits/stdc++.h>

typedef struct evaluate {
    int customer_id;
    double food_rating;
    double service_rating;
    double environment_rating;
    std::string timestamp;
    int version;
    struct evaluate* next;
} evaluate;

std::vector<evaluate*> evaluate_list;

bool compareByTimestampDesc(const evaluate* a, const evaluate* b) {
    return a->timestamp > b->timestamp;
}

bool compareByCustomerIdDesc(const evaluate* a, const evaluate* b) {
    return a->customer_id > b->customer_id;
}

void insert(int customer_id, double food_rating, double service_rating, double environment_rating, std::string timestamp) {
    evaluate* new_evaluate = new evaluate;
    new_evaluate->customer_id = customer_id;
    new_evaluate->food_rating = food_rating;
    new_evaluate->service_rating = service_rating;
    new_evaluate->environment_rating = environment_rating;
    new_evaluate->timestamp = timestamp;
    new_evaluate->version = 1;
    new_evaluate->next = nullptr;
    evaluate_list.push_back(new_evaluate);
    std::cout << "Review inserted successfully\n";
}

void modify(int customer_id, std::string dimonsion, double new_rating, std::string timestamp) {
    evaluate* new_evaluate = new evaluate;
    new_evaluate->customer_id = customer_id;
    new_evaluate->timestamp = timestamp;
    bool is_found = false;
    for (int i = 0; i < evaluate_list.size(); i++) {
        if (evaluate_list[i]->customer_id == customer_id) {
            is_found = true;
            new_evaluate->food_rating = evaluate_list[i]->food_rating;
            new_evaluate->service_rating = evaluate_list[i]->service_rating;
            new_evaluate->environment_rating = evaluate_list[i]->environment_rating;
            new_evaluate->version = evaluate_list[i]->version + 1;
            if (dimonsion == "food") {
                new_evaluate->food_rating = new_rating;
            } else if (dimonsion == "service") {
                new_evaluate->service_rating = new_rating;
            } else if (dimonsion == "environment") {
                new_evaluate->environment_rating = new_rating;
            }
            new_evaluate->next = evaluate_list[i];
            evaluate_list[i] = new_evaluate;
            break;
        }
    }
    if (is_found) {
        std::cout << "Modification successful\n";
    } else {
        std::cout << "Customer ID not found, modification failed\n";
    }
}

void delete_evaluate(int customer_id) {
    bool is_found = false;
    for (int i = 0; i < evaluate_list.size(); i++) {
        if (evaluate_list[i]->customer_id == customer_id) {
            is_found = true;
            evaluate_list.erase(evaluate_list.begin() + i);
            break;
        }
    }
    if (is_found) {
        std::cout << "Deletion successful\n";
    } else {
        std::cout << "Customer ID not found, deletion failed\n";
    }
}

void history(int customer_id, std::string dimension) {
    std::cout << "History:\n";
    evaluate* cur_evaluate;
    for (int i = 0; i < evaluate_list.size(); i++) {
        if (evaluate_list[i]->customer_id == customer_id) {
            cur_evaluate = evaluate_list[i];
            break;
        }
    }
    if (dimension == "food") {
        while (cur_evaluate != nullptr) {
            std::cout << "Version " << cur_evaluate->version << ": " << "Food Rating " << cur_evaluate->food_rating << " Timestamp " << cur_evaluate->timestamp << "\n";
            cur_evaluate = cur_evaluate->next;
        }
    } else if (dimension == "service") {
        while (cur_evaluate != nullptr) {
            std::cout << "Version " << cur_evaluate->version << ": " << "Service Rating " << cur_evaluate->service_rating << " Timestamp " << cur_evaluate->timestamp << "\n";
            cur_evaluate = cur_evaluate->next;
        }
    } else if (dimension == "environment") {
        while (cur_evaluate != nullptr) {
            std::cout << "Version " << cur_evaluate->version << ": " << "Environment Rating " << cur_evaluate->environment_rating << " Timestamp " << cur_evaluate->timestamp << "\n";
            cur_evaluate = cur_evaluate->next;
        }
    } else {
        while (cur_evaluate != nullptr) {
            std::cout << "Version " << cur_evaluate->version << ": " << "Food Rating " << cur_evaluate->food_rating << " Service Rating " << cur_evaluate->service_rating << " Environment Rating " << cur_evaluate->environment_rating << " Timestamp " << cur_evaluate->timestamp << "\n";
            cur_evaluate = cur_evaluate->next;
        }
    }
}

void display(std::string dimension) {
    std::sort(evaluate_list.begin(), evaluate_list.end(), compareByTimestampDesc);
    if (dimension == "food") {
        for (auto evaluate : evaluate_list) {
            std::cout << "Customer ID " << evaluate->customer_id << " Food Rating " << evaluate->food_rating << " Timestamp " << evaluate->timestamp << "\n";
        }
    } else if (dimension == "service") {
        for (auto evaluate : evaluate_list) {
            std::cout << "Customer ID " << evaluate->customer_id << " Service Rating " << evaluate->service_rating << " Timestamp " << evaluate->timestamp << "\n";
        }
    } else if (dimension == "environment") {
        for (auto evaluate : evaluate_list) {
            std::cout << "Customer ID " << evaluate->customer_id << " Environment Rating " << evaluate->environment_rating << " Timestamp " << evaluate->timestamp << "\n";
        }
    } else {
        for (auto evaluate : evaluate_list) {
            std::cout << "Customer ID " << evaluate->customer_id << " Food Rating " << evaluate->food_rating << " Service Rating " << evaluate->service_rating << " Environment Rating " << evaluate->environment_rating << " Timestamp " << evaluate->timestamp << "\n";
        }
    }
}

void range_query(double food_rating_lower, double food_rating_upper, double service_rating_lower, double service_rating_upper, double environment_rating_lower, double environment_rating_upper) {
    std::sort(evaluate_list.begin(), evaluate_list.end(), compareByCustomerIdDesc);
    for (auto evaluate : evaluate_list) {
        bool food_rangting_valid = evaluate->food_rating >= food_rating_lower && evaluate->food_rating <= food_rating_upper;
        bool service_rangting_valid = evaluate->service_rating >= service_rating_lower && evaluate->service_rating <= service_rating_upper;
        bool environment_rangting_valid = evaluate->environment_rating >= environment_rating_lower && evaluate->environment_rating <= environment_rating_upper;
        bool is_valid = food_rangting_valid && service_rangting_valid && environment_rangting_valid;
        if (is_valid) {
            std::cout << "Customer ID " << evaluate->customer_id << " Food Rating " << evaluate->food_rating << " Service Rating " << evaluate->service_rating << " Environment Rating " << evaluate->environment_rating << " Timestamp " << evaluate->timestamp << "\n";
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    for (int i = 0; i < n; i++) {
        std::string command;
        std::getline(std::cin, command);
        std::stringstream ss(command);
        std::string operate;
        ss >> operate;
        if (operate == "insert") {
            int customer_id;
            double food_rating, service_rating, environment_rating;
            std::string timestamp;
            ss >> customer_id >> food_rating >> service_rating >> environment_rating;
            std::string temp;
            ss >> timestamp >> temp;
            timestamp += " " + temp;
            insert(customer_id, food_rating, service_rating, environment_rating, timestamp);
        } else if (operate == "modify") {
            int customer_id;
            std::string dimonsion, timestamp;
            double new_rating;
            ss >> customer_id >> dimonsion >> new_rating;
            std::string temp;
            ss >> timestamp >> temp;
            timestamp += " " + temp;
            modify(customer_id, dimonsion, new_rating, timestamp);
        } else if (operate == "delete") {
            int customer_id;
            ss >> customer_id;
            delete_evaluate(customer_id);
        } else if (operate == "history") {
            int customer_id;
            std::string dimension;
            ss >> customer_id;
            if (ss >> dimension) {
                history(customer_id, dimension);
            } else {
                history(customer_id, "");
            }
        } else if (operate == "display") {
            std::string dimension;
            if (ss >> dimension) {
                display(dimension);
            } else {
                display("");
            }
        } else if (operate == "range_query") {
            double food_rating_lower, food_rating_upper;
            double service_rating_lower, service_rating_upper;
            double environment_rating_lower, environment_rating_upper;
            ss >> food_rating_lower >> food_rating_upper;
            ss >> service_rating_lower >> service_rating_upper;
            ss >> environment_rating_lower >> environment_rating_upper;
            range_query(food_rating_lower, food_rating_upper, service_rating_lower, service_rating_upper, environment_rating_lower, environment_rating_upper);
        }
    }
}
