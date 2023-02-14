//
// Created by leoni on 14.02.2023.
//

#ifndef V_MATH1_GAUSSJORDAN_H
#define V_MATH1_GAUSSJORDAN_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix {

public:
    Matrix(int nRows, int nColumns);                                                        //конструктор матрицы
    Matrix();                                                                               //конструктор матрицы

    void input();                                                                           //ввод матрицы
    int getRows() const;                                                                    //возвращает количество строк
    int getColumns() const;                                                                 //возвращает количество столбцов
    static vector<double> getColumnForDirectStep(Matrix matrix, int                         //получает столбцы для обратного хода
                                        indexRow, const int index_Column);
    static Matrix EMatrix(Matrix &matrix);                                                  //создание единичной матрицы
    static void output(Matrix matrix);                                                      //вывод матрицы
    static Matrix transposition(Matrix m1);                                                 //транспонирование матрицы
    static Matrix summary(Matrix m1, Matrix m2);                                            //сложение матриц
    static Matrix subtraction(Matrix m1, Matrix m2);                                        //вычитание матриц
    static Matrix multiplyOnValue(double value, Matrix m1);                                 //умножение матрицы на число
    static Matrix directStep(Matrix matrix, int indexRow, int indexColumn);                 //прямой ход
    static Matrix unionMatrices(Matrix matrix1, Matrix matrix2);

    friend Matrix operator*(Matrix m1, Matrix m2);                                          //умножение матриц

    vector<double> &operator[](size_t v1);
private:
    size_t _nRows;
    size_t _nColumns;
    vector<vector<double>> _matrix;

    static Matrix p_step(Matrix matrix, int index_row, int index_coloumn, int begin, int end, int step = 1);
};

#endif //V_MATH1_GAUSSJORDAN_H
