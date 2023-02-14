#include <clocale>
#include "GaussJordan.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    Matrix a = Matrix(2, 2);
    a.input();

    a[1][1] = 5151;
    Matrix::output(a);
    Matrix::multiplyOnValue(2,a);
}
