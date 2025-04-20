/*Дан список точек в пространстве (например, vector<vector<double>> a, где внутренний вектор - это координаты точки в пространстве.). Дана точка  Х в пространстве. Используя библиотеки numeric и functional, найти максимальное расстояние от точки X  до  остальных точек в пространстве.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> //для inner_product
#include <functional> //для plus<>
#include <math.h>
using namespace std;


double distance(const std::vector<double>& p1, const std::vector<double>& p2) {
    return std::sqrt(std::inner_product(p1.begin(), p1.end(), p2.begin(), 0.0,
        std::plus<>(), [](double a, double b) { return (a - b) * (a - b); }));
}

int main(){
    vector<vector<double>> point = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}, 
        {7.0, 8.0, 9.0}
    };

    vector<double> X = {0.0, 0.0, 0.0};

    double max_distance = 0.0;
    for(const vector<double>& p : point){
        double dist = distance(p, X);
        max_distance = max(max_distance, dist);
    }

    cout << "MAX distance от X до ост. точек: " << max_distance << endl;
    return 0;    
}
