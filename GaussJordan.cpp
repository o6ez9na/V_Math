//
// Created by leoni on 14.02.2023.
//

#include "GaussJordan.h"
#include "Vector.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//возвращает количество строк
int Matrix::getRows() const {
    return _nRows;
}

//возвращает количество столбцов
int Matrix::getColumns() const {
    return _nColumns;
}

//конструктор матрицы
Matrix::Matrix() {
    _nRows = 0;
    _nColumns = 0;
    _matrix = vector<vector<double>>();
}

//конструктор матрцы
Matrix::Matrix(int nRows, int nColumns) {
    _nRows = nRows;
    _nColumns = nColumns;
    _matrix = vector<vector<double>>(_nRows, vector<double>(_nColumns, 0));
}

Matrix Matrix::EMatrix(Matrix &matrix) {
    Matrix tMatrix = Matrix(matrix.getRows(), matrix.getColumns());
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getColumns(); ++j) {
            if (i == j) {
                tMatrix[i][j] = 1;
            } else {
                tMatrix[i][j] = 0;
            }
        }
    }
}

//ввод матрицы
void Matrix::input() {
    for (size_t i = 0; i < getColumns(); i++) {
        for (size_t j = 0; j < getRows(); j++) {
            cin >> _matrix[i][j];
        }
    }
}

//вывод матрицы
void Matrix::output(Matrix matrix) {
    for (size_t i = 0; i < matrix.getColumns(); i++) {
        for (size_t j = 0; j < matrix.getRows(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}


//траноспонирование матрицы
Matrix Matrix::transposition(Matrix m1) {
    Matrix res;
    if (m1.getRows() == m1.getColumns()) {
        res = Matrix(m1.getRows(), m1.getRows());
        for (int i = 0; i < m1.getRows(); ++i) {
            for (int j = 0; j < m1.getColumns(); ++j) {
                res[j][i] = m1[i][j];
            }
        }
    }
    return res;
}

//сложение матриц
Matrix Matrix::summary(Matrix m1, Matrix m2) {
    if (m1.getColumns() != m2.getColumns() || m1.getRows() != m2.getRows()) {
        throw "Unreal!";
    }

    Matrix result = Matrix(m1.getColumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColumns(); ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

//вычитание матриц
Matrix Matrix::subtraction(Matrix m1, Matrix m2) {
    if (m1.getColumns() != m2.getColumns() || m1.getRows() != m2.getRows()) {
        throw "Unreal!";
    }

    Matrix result = Matrix(m1.getColumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColumns(); ++j) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}

//умножение матрицы на число
Matrix Matrix::multiplyOnValue(double value, Matrix m1) {

    Matrix result = Matrix(m1.getColumns(), m1.getRows());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m1.getColumns(); ++j) {
            result[i][j] = m1[i][j] * value;
        }
    }
    return result;
}

Matrix Matrix::unionMatrices(Matrix matrix1, Matrix matrix2) {
    auto uMatrix = Matrix(matrix1.getRows(),
                          matrix1.getColumns() + matrix2.getColumns());
    for (int i = 0; i < uMatrix.getRows(); ++i) {
        for (int j = 0; j < uMatrix.getColumns(); ++j) {
            uMatrix[i].push_back(j < matrix1.getColumns() ? matrix1[i][j] :
                                 matrix2[i][j - matrix2.getColumns()]);
        }
    }
    return uMatrix;
}

//прямой ход
Matrix Matrix::directStep(Matrix matrix, int indexRow, int indexColumn) {
    if (matrix[indexRow][indexColumn] == 0) {
        auto listColumns = Matrix::getColumnForDirectStep(matrix,
                                                          indexRow, indexColumn);
        double maxElement = *max_element(listColumns.begin(), listColumns.end(),
                                         [](double a, double b) { return abs(a) > abs(b); });
        auto maxIndex = listColumns.end() - max_element(listColumns.begin(), listColumns.end(),
                                                        [](double a, double b) { return abs(a) > abs(b); });
        auto tmp = matrix[indexColumn];
        matrix[indexRow] = matrix[maxIndex];
        matrix[maxIndex] = tmp;
        Vector::divisionVectors(matrix[indexRow], matrix[indexRow][indexColumn]);

        Matrix::p_step(matrix, indexRow, indexColumn, 0, indexRow);
    }
}

void methodOfGauss(Matrix matrix, vector<int> indexVector) {
    int row = 0;
    for (int column = 0; column < indexVector.size(); ++column) {
        Matrix::directStep(matrix, row, column);
        row++;
    }
}

//обратный ход
Matrix reverseStep(Matrix matrix, int indexRow, int indexColumn) {
    for (int i = matrix.getColumns() - 2; i >= 0; --i) {
        Vector::multiplyVectors(matrix[i], 1 / matrix[i][i]);
        auto stepMult = vector<double>();
        for (int j = i - 1; j >= 0; j--) {
            stepMult.push_back(matrix[i][j] != 0 ? -matrix[i][j] : 0);
            Vector::summaryVectors(matrix[j], matrix[i]);
        }
    }
}

//обратная матрица
Matrix inverse(Matrix matrix) {
    auto unionMatrices = Matrix::unionMatrices(matrix, Matrix(Matrix::EMatrix(matrix)));
    for (int i = 0; i < matrix.getRows(); ++i) {
        Vector::multiplyVectors(unionMatrices[i], 1 / unionMatrices[i][i]);
        for (int j = i + 1; j < unionMatrices.getRows(); ++j) {
            auto value= -unionMatrices[i][j]/unionMatrices[j][j];
            Vector::summaryVectors(unionMatrices[j], unionMatrices[i]);
        }
    }
    for (int i = unionMatrices.getRows() - 1; i > -1; i--) {
        Vector::multiplyVectors(unionMatrices[i], 1/unionMatrices[i][i]);
        for (int j = i - 1; j > -1 ; --j) {
            auto value = -unionMatrices[j][i] / unionMatrices[i][i];
            Vector::summaryVectors(unionMatrices[j], unionMatrices[i]);
        }
    }
    auto inverseMatrix = Matrix(matrix.getRows(),matrix.getColumns());
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getColumns(); ++j) {
            inverseMatrix[i][j] = unionMatrices[i][j + inverseMatrix.getRows()];
        }
    }
    return inverseMatrix;
}

vector<double> Matrix::getColumnForDirectStep(Matrix matrix, int indexRow, const int index_Column) {
    vector<double> result;
    for (; indexRow != matrix.getRows(); indexRow++) {
        result.push_back(matrix[indexRow][index_Column]);
    }
    return result;
}


Matrix Matrix::p_step(Matrix matrix, int index_row, int index_coloumn, int begin, int end, int step) {
    auto standard_row = matrix[index_row];
    for (begin; begin < end; begin += step) {
        auto t_time = matrix[begin][index_coloumn];
        if (t_time != 0) {
            Vector::summaryVectors(matrix[begin], standard_row);
        }
    }
}

vector<double> &Matrix::operator[](size_t v1) {
    return _matrix[v1];
}

Matrix operator*(Matrix m1, Matrix m2) {
    if (m1.getColumns() != m2.getRows()) {
        throw "Unreal!";
    }
    Matrix res = Matrix(m2.getRows(), m1.getColumns());
    for (size_t i = 0; i < m1.getRows(); i++) {
        for (size_t j = 0; j < m2.getColumns(); j++) {
            for (size_t k = 0; k < m2.getRows(); k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return res;
}

