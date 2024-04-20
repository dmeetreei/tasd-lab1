#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace std;


/*
void graphicFunction(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Window");
    //sf::CircleShape shape(50);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
        window.display();
    }
}
*/

void inputMatrix(vector<vector<int>> &matrix, int a, int b) {
    //matrix.resize(a, vector<int>(b));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            cout << "[" << i << "][" << j << "]\n";
            cin >> matrix[i][j];
        }
    }
}

void generateRandomMatrixElements(vector<vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0 + rand() % 90;
        }
    }
}

void displayMatrix(vector<vector<int>> &matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}

void
standardMatrixMultiplication(int rowsOne, int colsOne, int rowsTwo, int colsTwo, vector<vector<int>> &matrixOne,
                             vector<vector<int>> &matrixTwo,
                             vector<vector<int>> &matrixResult) {
    for (int i = 0; i < rowsOne; i++) {
        for (int j = 0; j < colsTwo; j++) {
            for (int k = 0; k < colsOne; k++) {
                matrixResult[i][j] = matrixResult[i][j] + matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
    cout << "Результат умножения двух матриц стандартным способом: " << endl;
}

void
winogradMatrixMultiplication(int rowsOne, int colsOne, int rowsTwo, int colsTwo, vector<vector<int>> &matrixOne,
                             vector<vector<int>> &matrixTwo,
                             vector<vector<int>> &matrixResult) {
    vector<int> MH(rowsOne, 0);
    vector<int> MV(colsTwo, 0);

    for (int i = 0; i < rowsOne; i++) {
        for (int k = 0; k < colsOne / 2; ++k) {
            MH[i] -= matrixOne[i][2 * k] * matrixOne[i][2 * k + 1];
        }
    }

    for (int i = 0; i < colsTwo; i++) {
        for (int k = 0; k < rowsTwo / 2; ++k) {
            MV[i] -= matrixTwo[2 * k][i] * matrixTwo[2 * k + 1][i];
        }
    }

    for (int i = 0; i < rowsOne; ++i) {
        for (int j = 0; j < colsTwo; ++j) {
            matrixResult[i][j] = MH[i] + MV[j];
            for (int k = 0; k < colsOne / 2; ++k) {
                matrixResult[i][j] += (matrixOne[i][2 * k] + matrixTwo[2 * k + 1][j]) *
                                      (matrixOne[i][2 * k + 1] + matrixTwo[2 * k][j]);
            }
        }
    }


    if (colsOne % 2 == 1) {
        for (int i = 0; i < rowsOne; ++i) {
            for (int j = 0; j < colsTwo; ++j) {
                matrixResult[i][j] += matrixOne[i][colsOne - 1] * matrixTwo[colsOne - 1][j];
            }
        }
    }

    cout << "Результат умножения двух матриц методом Винограда:" << endl;
}

double
measureStandardMatrixMultiplication(int rowsOne, int colsOne, int rowsTwo, int colsTwo,
                                    vector<vector<int>> &matrixOne,
                                    vector<vector<int>> &matrixTwo, vector<vector<int>> &matrixResult) {
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    standardMatrixMultiplication(rowsOne, colsOne, rowsTwo, colsTwo, matrixOne, matrixTwo, matrixResult);

    QueryPerformanceCounter(&end);
    double timeTaken = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Время выполнения стандартного умножения матриц: " << timeTaken << " секунд." << endl;
    return timeTaken;
}

double
measureWinogradMatrixMultiplication(int rowsOne, int colsOne, int rowsTwo, int colsTwo,
                                    vector<vector<int>> &matrixOne,
                                    vector<vector<int>> &matrixTwo, vector<vector<int>> &matrixResult) {
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    winogradMatrixMultiplication(rowsOne, colsOne, rowsTwo, colsTwo, matrixOne, matrixTwo, matrixResult);

    QueryPerformanceCounter(&end);
    double timeTaken = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Время выполнения умножения матриц методом Винограда: " << timeTaken << " секунд." << endl;
    return timeTaken;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int m, n, p, q;
    //A
    cout << "Введите размеры матрицы A[m*n]" << endl;
    cout << "m: \n";
    cin >> m;
    cout << "n: \n";
    cin >> n;

    vector<vector<int>> matrixA(m, vector<int>(n));

    int randomFlag = 0;
    string checkRandom;
    if (m * n > 9) {
        cout << "Элементов матрицы слишком много для ручного ввода. Сгенерировать их значения случайным образом?\ny/n:"
             << endl;
        cin >> checkRandom;
        if (checkRandom == "y") {
            randomFlag = 1;
            generateRandomMatrixElements(matrixA, m, n);
        } else {
            inputMatrix(matrixA, m, n);
        }
    }else {
        inputMatrix(matrixA, m, n);
    }


    cout << "Матрица A:" << endl;
    displayMatrix(matrixA, m, n);


    //B
    cout << "Введите размеры матрицы B[p*q]" << endl;
    cout << "p: \n";
    cin >> p;
    cout << "q: \n";
    cin >> q;

    vector<vector<int>> matrixB(p, vector<int>(q));
    if (randomFlag == 1) {
        generateRandomMatrixElements(matrixB, p, q);
    } else { inputMatrix(matrixB, p, q); }

    cout << "Матрица B:" << endl;
    displayMatrix(matrixB, p, q);

    vector<vector<int>> matrixC(m, vector<int>(q));
    standardMatrixMultiplication(m, n, p, q, matrixA, matrixB, matrixC);
    displayMatrix(matrixC, m, q);
    matrixC.assign(matrixC.size(), vector<int>(matrixC[0].size(), 0)); // Очистка matrixC перед следующим умножением
    winogradMatrixMultiplication(m, n, p, q, matrixA, matrixB, matrixC);
    displayMatrix(matrixC, m, q);

    matrixC.assign(matrixC.size(), vector<int>(matrixC[0].size(), 0));
    measureStandardMatrixMultiplication(m, n, p, q, matrixA, matrixB, matrixC);
    displayMatrix(matrixC, m, q);
    matrixC.assign(matrixC.size(), vector<int>(matrixC[0].size(), 0));
    measureWinogradMatrixMultiplication(m, n, p, q, matrixA, matrixB, matrixC);
    displayMatrix(matrixC, m, q);

    //graphicFunction();

    return 0;
}
