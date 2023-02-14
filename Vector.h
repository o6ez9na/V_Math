//
// Created by leoni on 14.02.2023.
//

#ifndef V_MATH1_VECTOR_H
#define V_MATH1_VECTOR_H
#include <iostream>
#include <vector>
using namespace std;

class Vector{
public:
    static vector<double> divisionVectors(vector<double> vector1, double a);                //деление вектора на число
    static vector<double> summaryVectors(vector<double> &v1, vector<double>& v2);           //сумма векторов
    static vector<double> multiplyVectors(vector<double> &v1, double v2);                   //умножение векторов
};
#endif //V_MATH1_VECTOR_H
