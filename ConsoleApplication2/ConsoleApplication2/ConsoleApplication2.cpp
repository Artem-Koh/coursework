#include <iostream>
using namespace std;

//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
void getMatrixWithoutRowAndCol(double** matrix, int N, int row, int col, double** newMatrix) {
    int offsetRow = 0;
    int offsetCol = 0;

    for (int i = 0; i < N - 1; i++) {
        if (i == row) {
            offsetRow = 1;
        }

        offsetCol = 0;

        for (int j = 0; j < N - 1; j++) {
            if (j == col) {
                offsetCol = 1;
            }
            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}
//Поиск определителя
int matrixDet(double** matrix, int N) {
    int det = 0;
    int degree = 1;

    if (N == 1) {
        return matrix[0][0];
    }
    else if (N == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else {
        double** newMatrix = new double* [N - 1];
        for (int i = 0; i < N - 1; i++) {
            newMatrix[i] = new double[N - 1];
        }

        for (int j = 0; j < N; j++) {
            getMatrixWithoutRowAndCol(matrix, N, 0, j, newMatrix);

            det = det + (degree * matrix[0][j] * matrixDet(newMatrix, N - 1));
            degree = -degree;
        }

        for (int i = 0; i < N - 1; i++) {
            delete[] newMatrix[i];
        }
        delete[] newMatrix;
    }

    return det;
}

//Транспонирование матрицы
void trans(double** matrix, int N) {
    int i, j;
    double s;

    for (i = 0; i < N; i++) {

        for (j = i + 1; j < N; j++) {
            s = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = s;
        }
    }
    cout << endl << "Траспонированная матрица с большим определителем" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}
//Умножение матриц
void multiplication(double** A, double** B, int N) {
    int i, j, k;
    double** C;
    C = new double* [N];

    for (i = 0; i < N; i++)
    {
        C[i] = new double[N];

        for (j = 0; j < N; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < N; k++) {

                C[i][j] += A[i][k] * B[k][j];

            }
                
        }
    }
    // Вывод матрицы произведения
    cout << endl << "Матрица произведения" << endl;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << C[i][j] << " ";
        }

        cout << endl;
        delete[] C[i];
    }
    delete[] C;
}

int main()
{
    srand(time(0));
    double** A, ** B;
    int min, max, i, j, k, detA, detB, N;
    //Использование кириллицы
    system("chcp 1251");
    system("cls");

    cout << "Введите размерность матриц" << endl;
    cin >> N;
    cout << "Введите минимальное значение элементов матрицы" << endl;
    cin >> min;
    cout << "Введите максимальное значение элементов матрицы" << endl;
    cin >> max;

    // Заполнение матриц случайными числами:
    A = new double* [N];
    B = new double* [N];

    for (i = 0; i < N; i++) {
        A[i] = new double[N];
        B[i] = new double[N];

        for (j = 0; j < N; j++) {

            A[i][j] = min + rand() % (max - min + 1);
            B[i][j] = min + rand() % (max - min + 1);

        }

    }
        
    // Вывод первой матрицы
    cout << endl << "Первая матрица" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << " ";
        }

        cout << endl;
    }
    
    // Вывод второй матрицы
    cout << endl << "Вторая матрица" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << B[i][j] << " ";
        }

        cout << endl;
    }
    
    multiplication(A, B, N);

    detA = matrixDet(A, N);
    detB = matrixDet(B, N);

    cout << endl << "Определитель первой матрицы" << endl << detA << endl;
    cout << endl << "Определитель второй матрицы" << endl << detB << endl;

    if (detA > detB) {
        trans(A, N);
    }
    else {
        trans(B, N);
    }
    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
    }

    delete[] A;
    delete[] B;
    return 0;
}