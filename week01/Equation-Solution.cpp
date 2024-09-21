# include <iostream>
# include <iomanip>
# include <cmath>

double a, b;

double func(double x);

double solve_equation(double a, double b);

int main () {
    std::cin >> a;
    std::cin >> b;
    double res = solve_equation(a, b);
    std::cout << std::fixed << std::setprecision(6) << res << std::endl;
}

double func(double x) {
    return exp(x) - a * x - b;
}

double solve_equation(double a, double b) {
    double e = exp(1.0);
    double l, r;
    double min_x = log(a);
    double min = func(min_x);

    if (min == 0.) return min_x;
    
    double func_0 = func(0);
    double func_10 = func(10);

    int type = 0; // type = 0 --> 单调增
                  // type = 1 --> 单调减
    if (func_0 <= 0) {
        l = min_x, r = 10, type = 0; // 单调增函数
    } else {
        l = 0, r = min_x, type = 1; // 单调减函数
    }
    double mid = (l + r) / 2.0;
    
    while (1) {
        double temp = func(mid);
        if (temp < 0) {
            if (type) {
                r = mid;
                mid = (l + r) / 2.0;
            } else {
                l = mid;
                mid = (l + r) / 2.0;
            }
        } else if (temp == 0) {
            return mid;
        } else {
            if (type) {
                l = mid;
                mid = (l + r) / 2.0;
            } else {
                r = mid;
                mid = (l + r) / 2.0;
            }
        }    
    }
    return 0.;
}