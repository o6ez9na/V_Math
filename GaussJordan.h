//
// Created by leoni on 14.02.2023.
//

#ifndef V_MATH1_GAUSSJORDAN_H
#define V_MATH1_GAUSSJORDAN_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix{


public:

    Matrix(int nRows, int nColoumns);                           //конструктор матрицы
    Matrix();                                                   //конструктор матрицы
    void input();                                               //ввод матрицы
    int getRows() const;                                        //возвращает количество строк
    int getColoumns() const;                                    //возвращает количество столбцов

    static void output(Matrix matrix);                          //вывод матрицы
    static Matrix multiply(Matrix m1, Matrix m2, Matrix res);   //умножение матрицы
    static Matrix transposition(Matrix m1);                     //транспонирование матрицы
    static Matrix summary(Matrix m1, Matrix m2);                //сложение матриц
    static Matrix subtraction(Matrix m1, Matrix m2);            //вычитание матриц
    static Matrix multiplyOnValue(double value, Matrix m1);     //умножение матрицы на число
    vector<double>& operator[](size_t v1);
private:
    size_t _nRows;
    size_t _nColomns;
    vector<vector<double>> _matrix;
};
#endif //V_MATH1_GAUSSJORDAN_H
