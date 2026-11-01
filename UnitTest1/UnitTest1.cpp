#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_1Recursive.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab71RecTests
{
	static int** MakeMatrix(const int* data, int rows, int cols) {
		int** m = new int* [rows];
		for (int i = 0; i < rows; i++) {
			m[i] = new int[cols];
			for (int j = 0; j < cols; j++)
				m[i][j] = data[i * cols + j];
		}
		return m;
	}

	static void FreeMatrix(int** m, int rows) {
		for (int i = 0; i < rows; i++)
			delete[] m[i];
		delete[] m;
	}

	static void AssertMatrix(const int* expected, int** m, int rows, int cols) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				Assert::AreEqual(expected[i * cols + j], m[i][j]);
	}

	TEST_CLASS(RecursiveTests)
	{
	public:
		TEST_METHOD(CreateRec_ValuesInRange)
		{
			const int rows = 7, cols = 9;
			int zeros[rows * cols] = {};
			int** R = MakeMatrix(zeros, rows, cols);
			CreateRec(R, rows, cols, -12, 37);
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++) {
					Assert::IsTrue(R[i][j] >= -12);
					Assert::IsTrue(R[i][j] <= 37);
				}
			FreeMatrix(R, rows);
		}

		TEST_METHOD(ChangeRec_SwapsWholeColumns)
		{
			int data[] = { 1, 2, 3,
						   4, 5, 6 };
			int expected[] = { 3, 2, 1,
							   6, 5, 4 };
			int** R = MakeMatrix(data, 2, 3);
			ChangeRec(R, 0, 2, 2);
			AssertMatrix(expected, R, 2, 3);
			FreeMatrix(R, 2);
		}

		TEST_METHOD(ShouldSwap_FirstRowDecides)
		{
			int data[] = { 5, 2,
						   1, 9,
						   1, 9 };
			int** R = MakeMatrix(data, 3, 2);
			Assert::IsTrue(ShouldSwap(R, 0));
			FreeMatrix(R, 3);
		}

		TEST_METHOD(ShouldSwap_AlreadyOrdered)
		{
			int data[] = { 2, 5,
						   9, 1,
						   9, 1 };
			int** R = MakeMatrix(data, 3, 2);
			Assert::IsFalse(ShouldSwap(R, 0));
			FreeMatrix(R, 3);
		}

		TEST_METHOD(SortRec_ByFirstRow)
		{
			int data[] = { 5, 2, 9,
						   1, 8, 3,
						   7, 4, 6 };
			int expected[] = { 2, 5, 9,
							   8, 1, 3,
							   4, 7, 6 };
			int** R = MakeMatrix(data, 3, 3);
			SortRec(R, 3, 3);
			AssertMatrix(expected, R, 3, 3);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(SortRec_SecondKeyWhenFirstRowEqual)
		{
			int data[] = { 5, 2, 5, 2,
						   7, 9, 3, 1,
						   0, 0, 4, 8 };
			int expected[] = { 2, 2, 5, 5,
							   1, 9, 3, 7,
							   8, 0, 4, 0 };
			int** R = MakeMatrix(data, 3, 4);
			SortRec(R, 3, 4);
			AssertMatrix(expected, R, 3, 4);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(SortRec_ThirdKeyWhenTwoRowsEqual)
		{
			int data[] = { 1, 1, 0,
						   2, 2, 5,
						   9, 3, 7 };
			int expected[] = { 0, 1, 1,
							   5, 2, 2,
							   7, 3, 9 };
			int** R = MakeMatrix(data, 3, 3);
			SortRec(R, 3, 3);
			AssertMatrix(expected, R, 3, 3);
			FreeMatrix(R, 3);
		}

		TEST_METHOD(CalcRec_SumCountAndZeroing)
		{
			int data[] = { 3, -3, 0,
						  -2, -6, 4 };
			int expected[] = { 0, -3, 0,
							   0, -6, 0 };
			int** R = MakeMatrix(data, 2, 3);
			int S = -1, k = -1;
			CalcRec(R, 2, 3, S, k);
			Assert::AreEqual(5, S);
			Assert::AreEqual(3, k);
			AssertMatrix(expected, R, 2, 3);
			FreeMatrix(R, 2);
		}

		TEST_METHOD(CalcRec_NothingSelected)
		{
			int data[] = { -3, -6,
							0, -9 };
			int** R = MakeMatrix(data, 2, 2);
			int S = -1, k = -1;
			CalcRec(R, 2, 2, S, k);
			Assert::AreEqual(0, S);
			Assert::AreEqual(0, k);
			AssertMatrix(data, R, 2, 2);
			FreeMatrix(R, 2);
		}
	};
}