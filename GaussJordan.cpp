//
// Created by leoni on 14.02.2023.
//

#include "GaussJordan.h"
#include <iostream>
#include <vector>

using namespace std;

//возвращает количество строк
int Matrix::getRows() const {
    return _nRows;
}

//возвращает количество столбцов
int Matrix::getColoumns() const {
    return _nColomns;
}

//конструктор матрицы
Matrix::Matrix() {
    _nRows = 0;
    _nColomns = 0;
    _matrix = vector<vector<double>>();
}

//конструктор матрцы
Matrix::Matrix(int nRows, int nColoumns) {
    _nRows = nRows;
    _nColomns = nColoumns;
    _matrix = vector<vector<double>>(_nRows, vector<double>(_nColomns, 0));
}

//ввод матрицы
void Matrix::input() {
    for (size_t i = 0; i < getColoumns(); i++) {
        for (size_t j = 0; j < getRows(); j++) {
            cin >> _matrix[i][j];
        }
    }
}

//вывод матрицы
void Matrix::output(Matrix matrix) {
    for (size_t i = 0; i < matrix.getColoumns(); i++) {
        for (size_t j = 0; j < matrix.getRows(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

//умножение матрицы на матрицу и вектор
Matrix Matrix::multiply(Matrix m1, Matrix m2, Matrix res) {

    if (m1.getColoumns() != m2.getRows()) {
        throw "Unreal!";
    }

    for (size_t i = 0; i < m1.getRows(); i++) {
        for (size_t j = 0; j < m2.getColoumns(); j++) {
            for (size_t k = 0; k < m2.getRows(); k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return res;
}

//траноспонирование матрицы
Matrix Matrix::transposition(Matrix m1) {
    Matrix res;
    if (m1.getRows() == m1.getColoumns()) {
        res = Matrix(m1.getRows(), m1.getRows());
        for (int i = 0; i < m1.getRows(); ++i) {
            for (int j = 0; j < m1.getColoumns(); ++j) {
                res[j][i] = m1[i][j];
            }
        }
    }
    return res;
}

//сложение матриц
Matrix Matrix::summary(Matrix m1, Matrix m2) {
    if (m1.getColoumns() != m2.getColoumns() || m1.getRows() != m2.getRows()) {
        throw "Unreal!";
    }

    Matrix result = Matrix(m1.getColoumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColoumns(); ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

//вычитание матриц
Matrix Matrix::subtraction(Matrix m1, Matrix m2) {
    if (m1.getColoumns() != m2.getColoumns() || m1.getRows() != m2.getRows()) {
        throw "Unreal!";
    }

    Matrix result = Matrix(m1.getColoumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColoumns(); ++j) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}

//умножение матрицы на число
Matrix Matrix::multiplyOnValue(double value, Matrix m1) {

    Matrix result = Matrix(m1.getColoumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColoumns(); ++j) {
            result[i][j] = m1[i][j] * value;
        }
    }
    return result;
}

vector<double> &Matrix::operator[](size_t v1) {
    return _matrix[v1];
}

