//
// Created by 35915 on 24-9-20.
//
#include <iostream>
#include <map>
#include <string>
#include <iomanip>

std::map<std::string, int> Months = {
        {"January",   1},
        {"February",  2},
        {"March",     3},
        {"April",     4},
        {"May",       5},
        {"June",      6},
        {"July",      7},
        {"August",    8},
        {"September", 9},
        {"October",   10},
        {"November",  11},
        {"December",  12}
};

double day_nums[] = {31., 28., 31., 30., 31., 30.,
                     31., 31., 30., 31., 30., 31.};

bool is_leap_year(int year);

int main() {
    int year;
    std::string month;
    int day, hour, minute, second;
    std::cin >> year;
    std::cin >> month;
    std::cin >> day;
    std::cin >> hour;
    std::cin >> minute;
    std::cin >> second;
    // 北京时间 2024-09-16T00:00:00
    // 电子手表 2024-09-01T22:20:00
    double seconds_1 = (31. + 29. + 31. + 30. + 31. + 30. + 31. + 31.) * 24. * 60. * 60. + 22. * 60. * 60. + 20. * 60.;
    // 上面的是电子表时间
    double seconds_2 = (31. + 29. + 31. + 30. + 31. + 30. + 31. + 31. + 15.) * 24. * 60. * 60.;
    // 上面的是北京时间
    seconds_2 -= seconds_1 * 60 / 59;
    double current_seconds = 0;
    for (int i = 2024; i < year; i++) {
        if (is_leap_year(i)) {
            current_seconds += 366. * 24. * 60. * 60.; 
        } else {
            current_seconds += 365. * 24. * 60. * 60.;
        }
    }
    int cur_mon = Months[month];
    // std::cout << current_seconds << '\n';
    for (int i = 0; i < cur_mon - 1; i++) {
        current_seconds += day_nums[i] * 24 * 60 * 60;
    }
    if (is_leap_year(year) && cur_mon > 2) {
        current_seconds += 24 * 60 * 60;
    }
    // std::cout << current_seconds << '\n';
    current_seconds += (day - 1) * 24 * 60 * 60;
    current_seconds += hour * 60 * 60;
    current_seconds += minute * 60;
    current_seconds += second;
    long time = seconds_2 + current_seconds * 60 / 59;
    long cur_year = 2024;
    int year_days = 366;
    // std::cout << "time = " << time << '\n';
    int res_sec = time % 60; // 结果的秒数
    long minutes = time / 60;
    // std::cout << "minutes = " << minutes << '\n';
    int res_min = minutes % 60; // 结果的分钟数
    long hours = minutes / 60;
    // std::cout << "hours = " << hours << '\n';
    int res_hour = hours % 24; // 结果的小时数
    long days = hours / 24;
    // std::cout << "days = " << days << std::endl;
    while (days >= year_days) {
        days -= year_days;
        cur_year++;
        year_days = is_leap_year(cur_year) ? 366 : 365;
    }
    // std::cout << "days = " << days << std::endl;
    // cur_year --> 结果年数
    int res_mon = 1; // 结果月份
    for (int i = 0; i < 12; i++) {
        int cur_month_day = (int)day_nums[i];
        if (i == 1 && is_leap_year(cur_year)) {
            cur_month_day++; // 闰年的二月
        }
        if (days >= cur_month_day) {
            days -= cur_month_day;
            res_mon++;
        } else {
            days++;
            break;
        }
    }
    std::cout << cur_year << '-';
    std::cout << std::setw(2) << std::setfill('0') << res_mon << '-';
    std::cout << std::setw(2) << std::setfill('0') << days << 'T';
    std::cout << std::setw(2) << std::setfill('0') << res_hour << ':';
    std::cout << std::setw(2) << std::setfill('0') << res_min << ':';
    std::cout << std::setw(2) << std::setfill('0') << res_sec << '\n';
    return 0;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0)
           || (year % 400 == 0);
}