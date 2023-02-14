//
// Created by leoni on 14.02.2023.
//
#include "Vector.h"

//деление векторов
vector<double> Vector::divisionVectors(vector<double> vector1, double a) {
    for (int i = 0; i < vector1.size(); ++i) {
        vector1[i] /= a;
    }
    return vector1;
}

//умножение векторов
vector<double> Vector::multiplyVectors(vector<double> &v1, double v2) {
    for (int i = 0; i < v1.size(); ++i) {
        v1[i] *= v2;
    }
    return v1;
}

//сумма векторов
vector<double> Vector::summaryVectors(vector<double> &v1, vector<double> &v2) {
    for (int i = 0; i < v1.size(); ++i) {
        v1[i] += v2[i];
    }
    return v1;
}