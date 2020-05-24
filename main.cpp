/* C++ matrix multiplication */

#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

using std::cout, std::endl, std::ios, std::fstream;
using namespace std::chrono;

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    Timer()
    {
        start = high_resolution_clock::now();
    }

    ~Timer()
    {
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken : " << duration.count() << " microseconds" << endl;
    }
};

// static matrix
#define MAXN 300
typedef struct Matrix_s
{
    size_t R, C;
    int index[MAXN][MAXN];
} MatrixS;

// dynamic matrix
typedef struct Matrix_d
{
    size_t R, C;
    // Indexing - arr[i*sizeY+j] == arr[i][j]
    int* index;

    ~Matrix_d()
    {
        delete index;
    }
} MatrixD;

void staticProduct()
{
    fstream input("matrix.2.in", ios::in);

    // Read matrix
    MatrixS m1;
    input >> m1.R;
    input >> m1.C;
    for (size_t i = 0; i < m1.R * m1.C; i++)
        input >> m1.index[i / m1.C][i % m1.C];

    // Read matrix
    MatrixS m2;
    input >> m2.R;
    input >> m2.C;
    for (size_t i = 0; i < m2.R * m2.C; i++)
        input >> m2.index[i / m2.C][i % m2.C];

    if (m1.C != m2.R) {
        cout << "Error: matrices cannot be multiplied!" << endl;
        return;
    }

    // Product
    MatrixS m3;
    m3.R = m1.R;
    m3.C = m2.C;
    int sum{};
    for (size_t i = 0; i < m3.R * m3.C; i++) {
        sum = 0;
        for (size_t j = 0; j < m1.C; j++) {
            sum += m1.index[i / m3.C][j % m1.C] * m2.index[j][i % m3.C];
        }
        m3.index[i / m3.C][i % m3.C] = sum;
    }

    // Print matrix
    for (size_t i = 1; i <= m3.R * m3.C; i++) {
        cout << m3.index[(i - 1) / m3.C][(i - 1) % m3.C] << '\t';
        if (i % 5 == 0)
            cout << endl;
    }

    input.close();
}

void dynamicProduct()
{
    fstream input("../matrix.2.in", ios::in);

    // Read matrix
    MatrixD m1;
    input >> m1.R;
    input >> m1.C;
    m1.index = new int[m1.C * m1.R];
    for (size_t i = 0; i < m1.R * m1.C; i++)
        input >> m1.index[i];

    // Read matrix
    MatrixD m2;
    input >> m2.R;
    input >> m2.C;
    m2.index = new int[m2.C * m2.R];
    for (size_t i = 0; i < m2.R * m2.C; i++)
        input >> m2.index[i];

    input.close();

    if (m1.C != m2.R) {
        cout << "Error: matrices cannot be multiplied!" << endl;
        return;
    }

    // Product
    MatrixD m3;
    m3.R = m1.R;
    m3.C = m2.C;
    m3.index = new int[m3.C * m3.R];
    int sum{};
    for (size_t r = 0; r < m3.R; ++r) {
        int ri2 = m2.C * r;
        int ri1 = m1.C * r;
        for (size_t c = 0; c < m3.C; ++c) {
            sum = 0;
            for (size_t j = 0; j < m1.C; j++) {
                sum += m1.index[ri1 + j] * m2.index[m2.C * j + c];
            }
            m3.index[ri2 + c] = sum;
        }
    }

    // Print result
    for (int k = 0; k < m3.R * m3.C; ++k) {
        cout << m3.index[k] << " ";
        if ((k + 1) % m2.C == 0) cout << endl;
    }
}

int main()
{
    // Time the program
    Timer t{};

    // TODO: read matrix transpose and change product

    // staticProduct();
    dynamicProduct();

    return 0;
}