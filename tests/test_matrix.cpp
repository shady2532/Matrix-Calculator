#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "E:\matrix calculator\Matrix-Calculator-new\src\matrix.h"

using namespace std;

// Helper function to check if result is close to identity
template<typename T>
bool isIdentity(const Matrix<T>& m, double tolerance = 1e-6) {
    if (m.getRows() != m.getCols()) return false;
    
    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getCols(); j++) {
            double expected = (i == j) ? 1.0 : 0.0;
            if (abs(m(i, j) - expected) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

// Helper to print determinants with smart formatting
void printDet(const string& name, double det, const string& expected) {
    cout << "Det(" << name << ") = ";
    if (det == 0) {
        cout << fixed << setprecision(4) << "0.0000";
    } else if (std::abs(det) < 0.001) {
        cout << scientific << setprecision(4) << det;
    } else {
        cout << fixed << setprecision(4) << det;
    }
    cout << " " << expected << endl;
    cout << fixed << setprecision(4);
}

int main()
{
    cout << fixed << setprecision(4);
    
    // ========== BASIC getInverse TESTS ==========
    cout << "========== BASIC getInverse TESTS ==========" << endl << endl;
    
    // Test 1: Simple 2x2
    cout << "Test 1 - Simple 2x2 getInverse:" << endl;
    Matrix<double> A1 = {
        {4, 7},
        {2, 6}
    };
    cout << "Original A1:" << endl << A1 << endl;
    
    Matrix<double> A1_inv = A1.getInverse();
    cout << "getInverse A1^(-1):" << endl << A1_inv << endl;
    
    Matrix<double> I1 = A1 * A1_inv;
    cout << "A1 * A1^(-1) (should be identity):" << endl << I1 << endl;
    cout << "Is Identity? " << (isIdentity(I1) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 2: 2x2 with negative elements
    cout << "Test 2 - 2x2 with Negatives:" << endl;
    Matrix<double> A2 = {
        {1, -2},
        {-3, 4}
    };
    cout << "Original A2:" << endl << A2 << endl;
    
    Matrix<double> A2_inv = A2.getInverse();
    cout << "getInverse A2^(-1):" << endl << A2_inv << endl;
    cout << "Expected:" << endl;
    cout << "-2.0000  -1.0000" << endl;
    cout << "-1.5000  -0.5000" << endl << endl;
    
    Matrix<double> I2 = A2 * A2_inv;
    cout << "Verification (A2 * A2^(-1)):" << endl << I2 << endl;
    cout << "Is Identity? " << (isIdentity(I2) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 3: Identity matrix (getInverse should be itself)
    cout << "Test 3 - Identity Matrix:" << endl;
    Matrix<double> A3 = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    cout << "Original A3 (Identity):" << endl << A3 << endl;
    
    Matrix<double> A3_inv = A3.getInverse();
    cout << "getInverse A3^(-1):" << endl << A3_inv << endl;
    cout << "Is Identity? " << (isIdentity(A3_inv) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== 3x3 MATRICES ==========
    cout << "========== 3x3 getInverse TESTS ==========" << endl << endl;
    
    // Test 4: 3x3 general matrix
    cout << "Test 4 - General 3x3:" << endl;
    Matrix<double> A4 = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    cout << "Original A4:" << endl << A4 << endl;
    printDet("A4", A4.getDeterminant(), "(Det = 1)");
    
    Matrix<double> A4_inv = A4.getInverse();
    cout << "getInverse A4^(-1):" << endl << A4_inv << endl;
    
    Matrix<double> I4 = A4 * A4_inv;
    cout << "Verification:" << endl << I4 << endl;
    cout << "Is Identity? " << (isIdentity(I4) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 5: 3x3 with larger determinant
    cout << "Test 5 - 3x3 Larger Det:" << endl;
    Matrix<double> A5 = {
        {2, 1, 1},
        {1, 3, 2},
        {1, 0, 0}
    };
    cout << "Original A5:" << endl << A5 << endl;
    printDet("A5", A5.getDeterminant(), "");
    
    Matrix<double> A5_inv = A5.getInverse();
    cout << "getInverse A5^(-1):" << endl << A5_inv << endl;
    
    Matrix<double> I5 = A5 * A5_inv;
    cout << "Verification:" << endl << I5 << endl;
    cout << "Is Identity? " << (isIdentity(I5) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== SPECIAL MATRICES ==========
    cout << "========== SPECIAL MATRICES ==========" << endl << endl;
    
    // Test 6: Diagonal matrix
    cout << "Test 6 - Diagonal Matrix:" << endl;
    Matrix<double> A6 = {
        {2, 0, 0},
        {0, 3, 0},
        {0, 0, 5}
    };
    cout << "Original A6:" << endl << A6 << endl;
    
    Matrix<double> A6_inv = A6.getInverse();
    cout << "getInverse A6^(-1):" << endl << A6_inv << endl;
    cout << "Expected:" << endl;
    cout << "0.5000  0.0000  0.0000" << endl;
    cout << "0.0000  0.3333  0.0000" << endl;
    cout << "0.0000  0.0000  0.2000" << endl << endl;
    
    Matrix<double> I6 = A6 * A6_inv;
    cout << "Verification:" << endl << I6 << endl;
    cout << "Is Identity? " << (isIdentity(I6) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 7: Upper triangular
    cout << "Test 7 - Upper Triangular:" << endl;
    Matrix<double> A7 = {
        {2, 3, 1},
        {0, 4, 2},
        {0, 0, 5}
    };
    cout << "Original A7:" << endl << A7 << endl;
    
    Matrix<double> A7_inv = A7.getInverse();
    cout << "getInverse A7^(-1):" << endl << A7_inv << endl;
    
    Matrix<double> I7 = A7 * A7_inv;
    cout << "Verification:" << endl << I7 << endl;
    cout << "Is Identity? " << (isIdentity(I7) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 8: Permutation matrix
    cout << "Test 8 - Permutation Matrix:" << endl;
    Matrix<double> A8 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };
    cout << "Original A8:" << endl << A8 << endl;
    
    Matrix<double> A8_inv = A8.getInverse();
    cout << "getInverse A8^(-1):" << endl << A8_inv << endl;
    
    Matrix<double> I8 = A8 * A8_inv;
    cout << "Verification:" << endl << I8 << endl;
    cout << "Is Identity? " << (isIdentity(I8) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== 4x4 MATRICES ==========
    cout << "========== 4x4 getInverse TESTS ==========" << endl << endl;
    
    // Test 9: 4x4 general matrix
    cout << "Test 9 - General 4x4:" << endl;
    Matrix<double> A9 = {
        {1, 0, 2, -1},
        {3, 0, 0, 5},
        {2, 1, 4, -3},
        {1, 0, 5, 0}
    };
    cout << "Original A9:" << endl << A9 << endl;
    printDet("A9", A9.getDeterminant(), "");
    
    Matrix<double> A9_inv = A9.getInverse();
    cout << "getInverse A9^(-1):" << endl << A9_inv << endl;
    
    Matrix<double> I9 = A9 * A9_inv;
    cout << "Verification:" << endl << I9 << endl;
    cout << "Is Identity? " << (isIdentity(I9) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 10: 4x4 symmetric matrix
    cout << "Test 10 - 4x4 Symmetric:" << endl;
    Matrix<double> A10 = {
        {4, 2, 2, 1},
        {2, 3, 1, 1},
        {2, 1, 3, 1},
        {1, 1, 1, 2}
    };
    cout << "Original A10:" << endl << A10 << endl;
    printDet("A10", A10.getDeterminant(), "");
    
    Matrix<double> A10_inv = A10.getInverse();
    cout << "getInverse A10^(-1):" << endl << A10_inv << endl;
    
    Matrix<double> I10 = A10 * A10_inv;
    cout << "Verification:" << endl << I10 << endl;
    cout << "Is Identity? " << (isIdentity(I10) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== EDGE CASES ==========
    cout << "========== EDGE CASES ==========" << endl << endl;
    
    // Test 11: 1x1 matrix
    cout << "Test 11 - 1x1 Matrix:" << endl;
    Matrix<double> A11(1, 1, {5.0});
    cout << "Original A11:" << endl << A11 << endl;
    
    Matrix<double> A11_inv = A11.getInverse();
    cout << "getInverse A11^(-1):" << endl << A11_inv << endl;
    cout << "Expected: 0.2000" << endl << endl;
    
    Matrix<double> I11 = A11 * A11_inv;
    cout << "Verification:" << endl << I11 << endl;
    cout << "Is Identity? " << (isIdentity(I11) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // Test 12: Matrix with fractional elements
    cout << "Test 12 - Fractional Elements:" << endl;
    Matrix<double> A12 = {
        {0.5, 0.25},
        {0.75, 0.5}
    };
    cout << "Original A12:" << endl << A12 << endl;
    
    Matrix<double> A12_inv = A12.getInverse();
    cout << "getInverse A12^(-1):" << endl << A12_inv << endl;
    
    Matrix<double> I12 = A12 * A12_inv;
    cout << "Verification:" << endl << I12 << endl;
    cout << "Is Identity? " << (isIdentity(I12) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== SINGULAR MATRIX TESTS (SHOULD THROW) ==========
    cout << "========== SINGULAR MATRIX TESTS ==========" << endl << endl;
    
    // Test 13: Singular matrix (should throw exception)
    cout << "Test 13 - Singular Matrix (should fail):" << endl;
    Matrix<double> A13 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Original A13 (singular):" << endl << A13 << endl;
    printDet("A13", A13.getDeterminant(), "(Should be 0)");
    
    try {
        Matrix<double> A13_inv = A13.getInverse();
        cout << "ERROR: Should have thrown exception! ✗" << endl << endl;
    } catch (const runtime_error& e) {
        cout << "Correctly threw exception: " << e.what() << " ✓" << endl << endl;
    }
    
    // Test 14: Zero row (singular)
    cout << "Test 14 - Matrix with Zero Row (should fail):" << endl;
    Matrix<double> A14 = {
        {1, 2, 3},
        {0, 0, 0},
        {7, 8, 9}
    };
    cout << "Original A14:" << endl << A14 << endl;
    
    try {
        Matrix<double> A14_inv = A14.getInverse();
        cout << "ERROR: Should have thrown exception! ✗" << endl << endl;
    } catch (const runtime_error& e) {
        cout << "Correctly threw exception: " << e.what() << " ✓" << endl << endl;
    }
    
    // ========== CACHED getInverse TEST ==========
    cout << "========== CACHE TEST ==========" << endl << endl;
    
    cout << "Test 15 - Cached getInverse:" << endl;
    Matrix<double> A15 = {
        {3, 1},
        {2, 4}
    };
    cout << "Original A15:" << endl << A15 << endl;
    
    // First call - computes
    auto start1 = chrono::high_resolution_clock::now();
    Matrix<double> A15_inv1 = A15.getInverse();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    
    cout << "First getInverse call (computes): " << duration1.count() << " μs" << endl;
    cout << A15_inv1 << endl;
    
    // Second call - cached
    auto start2 = chrono::high_resolution_clock::now();
    Matrix<double> A15_inv2 = A15.getInverse();
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
    
    cout << "Second getInverse call (cached): " << duration2.count() << " μs" << endl;
    cout << A15_inv2 << endl;
    cout << "Cache speedup: " << (double)duration1.count() / duration2.count() << "x faster" << endl << endl;
    
    // ========== IN-PLACE INVERT TEST ==========
    cout << "========== IN-PLACE INVERT TEST ==========" << endl << endl;
    
    cout << "Test 16 - In-place Invert:" << endl;
    Matrix<double> A16 = {
        {2, 1},
        {1, 3}
    };
    cout << "Original A16:" << endl << A16 << endl;
    
    Matrix<double> A16_copy = A16;  // Keep a copy
    A16.invert();  // Modify in place
    
    cout << "After A16.invert():" << endl << A16 << endl;
    
    Matrix<double> I16 = A16_copy * A16;
    cout << "Verification (original * inverted):" << endl << I16 << endl;
    cout << "Is Identity? " << (isIdentity(I16) ? "YES ✓" : "NO ✗") << endl << endl;
    
    // ========== LARGE MATRIX ==========
    cout << "========== LARGE MATRIX TEST ==========" << endl << endl;
    
    cout << "Test 17 - 5x5 Matrix:" << endl;
    Matrix<double> A17 = {
        {1, 2, 0, 0, 1},
        {0, 1, 2, 0, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 1, 2},
        {1, 0, 0, 0, 1}
    };
    cout << "Original A17:" << endl << A17 << endl;
    printDet("A17", A17.getDeterminant(), "");
    
    Matrix<double> A17_inv = A17.getInverse();
    cout << "getInverse A17^(-1):" << endl << A17_inv << endl;
    
    Matrix<double> I17 = A17 * A17_inv;
    cout << "Verification:" << endl << I17 << endl;
    cout << "Is Identity? " << (isIdentity(I17) ? "YES ✓" : "NO ✗") << endl << endl;
    
    cout << "========== ALL TESTS COMPLETE ==========" << endl;
    
    return 0;
}