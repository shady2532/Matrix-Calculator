#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "E:\matrix calculator\Matrix-Calculator-new\src\matrix.h"

using namespace std;

int main()
{
    cout << fixed << setprecision(4);
    
    // ========== Basic Tests ==========
    cout << "========== BASIC TESTS ==========" << endl;
    
    // Test 1: Simple 2x2
    Matrix<int> A(2, 2, {1, 2, 3, 4});
    cout << "Test 1 - Simple 2x2:" << endl;
    cout << A << endl;
    cout << "Det(A) = " << A.getDeterminant() << " (Expected: -2)" << endl << endl;
    
    // Test 2: 3x3 singular matrix
    Matrix<int> B = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Test 2 - 3x3 Singular:" << endl;
    cout << B << endl;
    cout << "Det(B) = " << B.getDeterminant() << " (Expected: 0)" << endl << endl;
    
    // Test 3: 3x3 non-singular
    Matrix<int> C = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    cout << "Test 3 - 3x3 Non-singular:" << endl;
    cout << C << endl;
    cout << "Det(C) = " << C.getDeterminant() << " (Expected: 1)" << endl << endl;
    
    // Test 4: Identity matrix
    Matrix<int> I = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    cout << "Test 4 - Identity 3x3:" << endl;
    cout << I << endl;
    cout << "Det(I) = " << I.getDeterminant() << " (Expected: 1)" << endl << endl;
    
    // ========== Larger Matrices ==========
    cout << "========== LARGER MATRICES ==========" << endl;
    
    // Test 5: 4x4 matrix
    Matrix<double> D = {
        {4, 3, 2, 2},
        {0, 1, -3, 3},
        {0, -1, 3, 3},
        {0, 3, 1, 1}
    };
    cout << "Test 5 - 4x4 Matrix:" << endl;
    cout << D << endl;
    cout << "Det(D) = " << D.getDeterminant() << " (Expected: -240)" << endl << endl;
    
    // Test 6: 5x5 matrix
    Matrix<double> E = {
        {2, 1, 0, 0, 0},
        {1, 2, 1, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 1, 2, 1},
        {0, 0, 0, 1, 2}
    };
    cout << "Test 6 - 5x5 Tridiagonal:" << endl;
    cout << E << endl;
    cout << "Det(E) = " << E.getDeterminant() << " (Expected: 6)" << endl << endl;
    
    // ========== Special Cases ==========
    cout << "========== SPECIAL CASES ==========" << endl;
    
    // Test 7: Diagonal matrix
    Matrix<int> F = {
        {5, 0, 0, 0},
        {0, 3, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 7}
    };
    cout << "Test 7 - Diagonal Matrix:" << endl;
    cout << F << endl;
    cout << "Det(F) = " << F.getDeterminant() << " (Expected: 210)" << endl << endl;
    
    // Test 8: Upper triangular
    Matrix<int> G = {
        {2, 5, 3, 1},
        {0, 4, 7, 2},
        {0, 0, 3, 5},
        {0, 0, 0, 6}
    };
    cout << "Test 8 - Upper Triangular:" << endl;
    cout << G << endl;
    cout << "Det(G) = " << G.getDeterminant() << " (Expected: 144)" << endl << endl;
    
    // Test 9: Lower triangular
    Matrix<int> H = {
        {3, 0, 0, 0},
        {2, 5, 0, 0},
        {1, 4, 2, 0},
        {6, 3, 7, 4}
    };
    cout << "Test 9 - Lower Triangular:" << endl;
    cout << H << endl;
    cout << "Det(H) = " << H.getDeterminant() << " (Expected: 120)" << endl << endl;
    
    // ========== Negative Determinants ==========
    cout << "========== NEGATIVE DETERMINANTS ==========" << endl;
    
    // Test 10: Negative determinant
    Matrix<int> J = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 2, 9}
    };
    cout << "Test 10 - Negative Determinant:" << endl;
    cout << J << endl;
    cout << "Det(J) = " << J.getDeterminant() << " (Expected: -36)" << endl << endl;
    
    // Test 11: Large negative
    Matrix<int> K = {
        {-2, 5, 3},
        {1, -4, 2},
        {3, 1, -6}
    };
    cout << "Test 11 - Negative Elements:" << endl;
    cout << K << endl;
    cout << "Det(K) = " << K.getDeterminant() << " (Expected: 55)" << endl << endl;
    
    // ========== Floating Point Tests ==========
    cout << "========== FLOATING POINT TESTS ==========" << endl;
    
    // Test 12: Floating point matrix
    Matrix<double> L = {
        {1.5, 2.5, 3.5},
        {4.5, 5.5, 6.5},
        {7.5, 8.5, 9.5}
    };
    cout << "Test 12 - Floating Point (Singular):" << endl;
    cout << L << endl;
    cout << "Det(L) = " << L.getDeterminant() << " (Expected: 0)" << endl << endl;
    
    // Test 13: Non-integer result
    Matrix<double> M = {
        {1.2, 3.4, 5.6},
        {2.1, 4.3, 6.5},
        {3.7, 2.8, 1.9}
    };
    cout << "Test 13 - Floating Point (Non-zero):" << endl;
    cout << M << endl;
    cout << "Det(M) = " << M.getDeterminant() << " (Expected: 0)" << endl << endl;
    
    // ========== Large Matrices ==========
    cout << "========== LARGE MATRICES ==========" << endl;
    
    // Test 14: 6x6 matrix
    Matrix<int> N = {
        {1, 2, 0, 0, 0, 0},
        {0, 1, 2, 0, 0, 0},
        {0, 0, 1, 2, 0, 0},
        {0, 0, 0, 1, 2, 0},
        {0, 0, 0, 0, 1, 2},
        {0, 0, 0, 0, 0, 1}
    };
    cout << "Test 14 - 6x6 Bidiagonal:" << endl;
    cout << N << endl;
    cout << "Det(N) = " << N.getDeterminant() << " (Expected: 1)" << endl << endl;
    
    // Test 15: Hilbert matrix 4x4 (ill-conditioned)
    Matrix<double> O = {
        {1.0, 1.0/2, 1.0/3, 1.0/4},
        {1.0/2, 1.0/3, 1.0/4, 1.0/5},
        {1.0/3, 1.0/4, 1.0/5, 1.0/6},
        {1.0/4, 1.0/5, 1.0/6, 1.0/7}
    };
    cout << "Test 15 - Hilbert Matrix 4x4:" << endl;
    cout << O << endl;
    cout << "Det(O) = " << O.getDeterminant() << " (Expected: ~0.0000016534)" << endl << endl;
    
    // ========== Edge Cases ==========
    cout << "========== EDGE CASES ==========" << endl;
    
    // Test 16: 1x1 matrix
    Matrix<int> P(1, 1, {5});
    cout << "Test 16 - 1x1 Matrix:" << endl;
    cout << P << endl;
    cout << "Det(P) = " << P.getDeterminant() << " (Expected: 5)" << endl << endl;
    
    // Test 17: Matrix with zeros
    Matrix<int> Q = {
        {0, 2, 3},
        {0, 5, 6},
        {1, 8, 9}
    };
    cout << "Test 17 - First Column Mostly Zero:" << endl;
    cout << Q << endl;
    cout << "Det(Q) = " << Q.getDeterminant() << " (Expected: -3)" << endl << endl;
    
    // Test 18: All same row (singular)
    Matrix<int> R = {
        {1, 2, 3},
        {1, 2, 3},
        {4, 5, 6}
    };
    cout << "Test 18 - Duplicate Rows:" << endl;
    cout << R << endl;
    cout << "Det(R) = " << R.getDeterminant() << " (Expected: 0)" << endl << endl;
    
    // ========== Permutation Matrix ==========
    cout << "========== PERMUTATION MATRIX ==========" << endl;
    
    // Test 19: Permutation matrix
    Matrix<int> S = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };
    cout << "Test 19 - Permutation Matrix:" << endl;
    cout << S << endl;
    cout << "Det(S) = " << S.getDeterminant() << " (Expected: 1)" << endl << endl;
    
    // Test 20: Complex 5x5
    Matrix<int> T = {
        {3, 7, 2, 5, 1},
        {1, 4, 9, 2, 6},
        {8, 3, 5, 7, 4},
        {2, 6, 1, 8, 3},
        {5, 1, 4, 3, 9}
    };
    cout << "Test 20 - Complex 5x5:" << endl;
    cout << T << endl;
    cout << "Det(T) = " << T.getDeterminant() << " (Expected: 10340)" << endl << endl;
    
    return 0;
}