#include "pch.h"

#include "C:\J2S4\vakken\ETS\testen\SimpleMatrix\matrix.h"

///*TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPEC*/T_TRUE(true);
//}
// 
// ID 1: Lege matrix en size functie
TEST(MatrixTest, ID1_LegeMatrixSize) {
    Matrix<int> m0;
    int* groote = m0.size();
    EXPECT_EQ(groote[0], 0);
    EXPECT_EQ(groote[1], 0);
}

// -------------------------------------------------
// ID 2: Matrix met eigen parameters, waarden en size
TEST(MatrixTest, ID2_ConstructWaardenEnSize) {
    int waardes[4] = { 1,1,1,1 };
    Matrix<int> m1(2, 2, waardes);
    int* grooteM1 = m1.size();
    EXPECT_EQ(grooteM1[0], 2);
    EXPECT_EQ(grooteM1[1], 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m1.get(i, j), 1);
}

// -------------------------------------------------
// ID 3: Matrix met negatieve parameters
TEST(MatrixTest, ID3_NegatieveWaarden) {
    int waardes[4] = { -1,-1,-1,-1 };
    Matrix<int> m1(2, 2, waardes);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m1.get(i, j), -1);
}

// -------------------------------------------------
// ID 4: Double matrix, niet-vierkant, eigen waarden, size
TEST(MatrixTest, ID4_DoubleMatrixWaardenEnSize) {
    double waardes[6] = { 1.5, 3.99, 4.5, 77.77, 0.0, 2.25 };
    Matrix<double> m1(2, 3, waardes);
    int* grooteM1 = m1.size();
    EXPECT_EQ(grooteM1[0], 2);
    EXPECT_EQ(grooteM1[1], 3);
    int idx = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j, ++idx)
            EXPECT_DOUBLE_EQ(m1.get(i, j), waardes[idx]);
}

// -------------------------------------------------
// ID 5: Zet waarde in matrix, check
TEST(MatrixTest, ID5_SetEnGetWaarde) {
    int waardes[4] = { 1,1,1,1 };
    Matrix<int> m1(2, 2, waardes);
    m1.set(0, 1, 99);
    EXPECT_EQ(m1.get(0, 1), 99);
}

// -------------------------------------------------
// ID 6: Kopiëren matrix object
TEST(MatrixTest, ID6_CopyConstructorEnEquals) {
    int waardes[4] = { 1,1,1,1 };
    Matrix<int> m1(2, 2, waardes);
    Matrix<int> m2(m1);
    EXPECT_TRUE(m1 == m2);
}

// -------------------------------------------------
// ID 7: Veranderen van type
TEST(MatrixTest, ID7_ConvertToDouble) {
    int waardes[4] = { 1,1,1,1 };
    Matrix<int> m6(2, 2, waardes);
    Matrix<double> m7;
    m6.convertTo(m7);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_DOUBLE_EQ(m7.get(i, j), 1.0);
}

// -------------------------------------------------
// ID 8: Optellen tot nieuwe matrix
TEST(MatrixTest, ID8_OptellenTotNieuweMatrix) {
    int waardes1[4] = { 1,2,3,4 };
    int waardes2[4] = { 4,3,2,1 };
    Matrix<int> m3(2, 2, waardes1), m4(2, 2, waardes2);
    Matrix<int> mSOM = Matrix<int>::add(m3, m4);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(mSOM.get(i, j), m3.get(i, j) + m4.get(i, j));
}
// ID 9: Optellen met extreem grote waardes
TEST(MatrixTest, AdditionWithOverflowValues) {
    int int_max = (int)((unsigned int)(~0) >> 1);
    int int_half = int_max / 2;

    int waardes1[4] = { int_half, int_half, int_half, int_half };
    int waardes2[4] = { int_half + 100, int_half + 100, int_half + 100, int_half + 100};

    Matrix<int> m3(2, 2, waardes1);
    Matrix<int> m4(2, 2, waardes2);

    Matrix<int> mSOM = m3 + m4;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int som = mSOM.get(i, j);
            EXPECT_LT(som, 0);
        }
    }
}


// -------------------------------------------------
// ID 10: Optellen van verschillende types (mag niet werken)
// niet te testen doordat het een error oplevert



// -------------------------------------------------
// ID 11: Optellen inplace
TEST(MatrixTest, ID10_AddInPlace) {
    int waardes1[4] = { 1,2,3,4 };
    int waardes2[4] = { 4,3,2,1 };
    Matrix<int> m6(2, 2, waardes1);
    Matrix<int> m7(2, 2, waardes2);
    m6.addInPlace(m7);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m6.get(i, j), waardes1[i * 2 + j] + waardes2[i * 2 + j]);
}

// -------------------------------------------------
// ID 12: Hadamard operatie
TEST(MatrixTest, ID11_Hadamard) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    Matrix<int> m10 =  m8.hadamard(m9);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m10.get(i, j), m8.get(i, j) * m9.get(i, j));
}

// -------------------------------------------------
// ID 13: Hadamard inplace
TEST(MatrixTest, ID12_HadamardInPlace) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    m8.hadamardInPlace(m9);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m8.get(i, j), v8[i * 2 + j] * v9[i * 2 + j]);
}

// -------------------------------------------------
// ID 14: Matrixvermenigvuldiging
TEST(MatrixTest, ID13_MatrixVermenigvuldiging) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    Matrix<int> m10 = Matrix<int>::multiply(m8, m9);
    EXPECT_EQ(m10.get(0, 0), 1 * 4 + 2 * 2);
    EXPECT_EQ(m10.get(0, 1), 1 * 3 + 2 * 1);
    EXPECT_EQ(m10.get(1, 0), 3 * 4 + 4 * 2);
    EXPECT_EQ(m10.get(1, 1), 3 * 3 + 4 * 1);
}

// -------------------------------------------------
// ID 15: In-place multiply met matrix (gebruikt statische multiply, want multiplyInPlace met matrix bestaat niet)
TEST(MatrixTest, ID14_MultiplyInPlaceMatrix) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    m8 = Matrix<int>::multiply(m8, m9);
    EXPECT_EQ(m8.get(0, 0), 1 * 4 + 2 * 2);
    EXPECT_EQ(m8.get(0, 1), 1 * 3 + 2 * 1);
    EXPECT_EQ(m8.get(1, 0), 3 * 4 + 4 * 2);
    EXPECT_EQ(m8.get(1, 1), 3 * 3 + 4 * 1);
}

// -------------------------------------------------
// ID 16: Scalar vermenigvuldiging (functie) // verkeerde functie gebruikt dus uitgecomment
//TEST(MatrixTest, ID15_ScalarMultiplyFunction) {
//    int v8[4] = { 1,2,3,4 };
//    Matrix<int> m8(2, 2, v8);
//    Matrix<int> m10 = Matrix<int>::multiply(m8, 2);
//    for (int i = 0; i < 2; ++i)
//        for (int j = 0; j < 2; ++j)
//            EXPECT_EQ(m10.get(i, j), 2 * v8[i * 2 + j]);
//}

// ID 16: Scalar vermenigvuldiging (functie)
TEST(MatrixTest, MultiplyInPlace) {
    int v8[4] = { 1,2,3,4 };
    Matrix<int> m8(2, 2, v8);
    m8.multiplyInPlace(2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m8.get(i, j), 2 * v8[i * 2 + j]);
}

// -------------------------------------------------
// ID 17: Operator matrixvermenigvuldiging
TEST(MatrixTest, ID16_OperatorMatrixMultiply) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    Matrix<int> m10 = m8 * m9;
    EXPECT_EQ(m10.get(0, 0), 1 * 4 + 2 * 2);
    EXPECT_EQ(m10.get(0, 1), 1 * 3 + 2 * 1);
    EXPECT_EQ(m10.get(1, 0), 3 * 4 + 4 * 2);
    EXPECT_EQ(m10.get(1, 1), 3 * 3 + 4 * 1);
}

// -------------------------------------------------
// ID 18: Operator scalar vermenigvuldiging
TEST(MatrixTest, ID17_OperatorScalarMultiply) {
    int v8[4] = { 1,2,3,4 };
    Matrix<int> m8(2, 2, v8);
    Matrix<int> m10 = m8 * 2;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m10.get(i, j), 2 * v8[i * 2 + j]);
}

// -------------------------------------------------
// ID 19: Operator optellen
TEST(MatrixTest, ID18_OperatorOptellen) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 2,1,0,-1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    Matrix<int> m10 = m8 + m9;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(m10.get(i, j), v8[i * 2 + j] + v9[i * 2 + j]);
}

// -------------------------------------------------
// ID 20: Matrices vergelijken op gelijkheid (na assignment)
TEST(MatrixTest, ID19_OperatorAssignmentEquals) {
    int v8[4] = { 1,2,3,4 }, v9[4] = { 4,3,2,1 };
    Matrix<int> m8(2, 2, v8), m9(2, 2, v9);
    m8 = m9;
    EXPECT_TRUE(m8 == m9);
}

// -------------------------------------------------
// ID 21: Operator copy en vergelijking
TEST(MatrixTest, ID20_OperatorCopyVergelijking) {
    int v8[4] = { 1,2,3,4 };
    Matrix<int> m8(2, 2, v8);
    Matrix<int> m9(2, 2);
    m9 = m8;
    bool testVergelijking = m8 == m9;
    EXPECT_TRUE(testVergelijking);
}

// -------------------------------------------------
// ID 22: Rij opvragen operator[]
TEST(MatrixTest, ID21_OperatorIndexRij) {
    int v8[4] = { 1,2,3,4 };
    Matrix<int> m8(2, 2, v8);
    int* rij = m8[0];
    EXPECT_EQ(rij[0], 1);
    EXPECT_EQ(rij[1], 2);
    rij = m8[1];
    EXPECT_EQ(rij[0], 3);
    EXPECT_EQ(rij[1], 4);
}

// -------------------------------------------------
// ID 23: Transpose
TEST(MatrixTest, ID22_Transpose) {
    int v[4] = { 1,2,3,4 };
    Matrix<int> m34(2, 2, v);
    Matrix<int> m35 = m34.transpose();
    EXPECT_EQ(m35.get(0, 0), 1);
    EXPECT_EQ(m35.get(0, 1), 3);
    EXPECT_EQ(m35.get(1, 0), 2);
    EXPECT_EQ(m35.get(1, 1), 4);
}

// -------------------------------------------------
// ID 24: In-place transpose
TEST(MatrixTest, ID23_TransposeInPlace) {
    int v[4] = { 1,2,3,4 };
    Matrix<int> m36(2, 2, v);
    m36.transposeInPlace();
    EXPECT_EQ(m36.get(0, 0), 1);
    EXPECT_EQ(m36.get(0, 1), 3);
    EXPECT_EQ(m36.get(1, 0), 2);
    EXPECT_EQ(m36.get(1, 1), 4);
}
