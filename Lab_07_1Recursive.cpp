#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRec(int** R, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void PrintRec(int** R, const int rowCount, const int colCount, int i = 0, int j = 0);
void SortRec(int** R, const int rowCount, const int colCount, int i0 = 0);
void SortPassRec(int** R, const int rowCount, const int colCount, const int i0, int i1);
bool ShouldSwap(int** R, const int c);
void ChangeRec(int** R, const int col1, const int col2, const int rowCount, int i = 0);
void CalcRec(int** R, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main() {
	srand((unsigned)time(NULL));

	int Low = -12;
	int High = 37;

	int rowCount = 7;
	int colCount = 9;

	int** R = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		R[i] = new int[colCount];

	CreateRec(R, rowCount, colCount, Low, High);
	PrintRec(R, rowCount, colCount);
	SortRec(R, rowCount, colCount);
	PrintRec(R, rowCount, colCount);

	int S = 0;
	int k = 0;
	CalcRec(R, rowCount, colCount, S, k);
	cout << "S = " << S << endl;
	cout << "k = " << k << endl;
	PrintRec(R, rowCount, colCount);

	for (int i = 0; i < rowCount; i++)
		delete[] R[i];
	delete[] R;

	return 0;
}

void CreateRec(int** R, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
	if (i >= rowCount) return;
	if (j >= colCount) {
		CreateRec(R, rowCount, colCount, Low, High, i + 1, 0);
		return;
	}
	R[i][j] = Low + rand() % (High - Low + 1);
	CreateRec(R, rowCount, colCount, Low, High, i, j + 1);
}

void PrintRec(int** R, const int rowCount, const int colCount, int i, int j) {
	if (i == 0 && j == 0) cout << endl;
	if (i >= rowCount) {
		cout << endl;
		return;
	}
	if (j >= colCount) {
		cout << endl;
		PrintRec(R, rowCount, colCount, i + 1, 0);
		return;
	}
	cout << setw(4) << R[i][j];
	PrintRec(R, rowCount, colCount, i, j + 1);
}

bool ShouldSwap(int** R, const int c) {
	return (R[0][c] > R[0][c + 1])
		|| (R[0][c] == R[0][c + 1] && R[1][c] > R[1][c + 1])
		|| (R[0][c] == R[0][c + 1] && R[1][c] == R[1][c + 1] && R[2][c] > R[2][c + 1]);
}

void ChangeRec(int** R, const int col1, const int col2, const int rowCount, int i) {
	if (i >= rowCount) return;
	int tmp = R[i][col1];
	R[i][col1] = R[i][col2];
	R[i][col2] = tmp;
	ChangeRec(R, col1, col2, rowCount, i + 1);
}

void SortPassRec(int** R, const int rowCount, const int colCount, const int i0, int i1) {
	if (i1 >= colCount - i0 - 1) return;
	if (ShouldSwap(R, i1))
		ChangeRec(R, i1, i1 + 1, rowCount);
	SortPassRec(R, rowCount, colCount, i0, i1 + 1);
}

void SortRec(int** R, const int rowCount, const int colCount, int i0) {
	if (i0 >= colCount - 1) return;
	SortPassRec(R, rowCount, colCount, i0, 0);
	SortRec(R, rowCount, colCount, i0 + 1);
}

void CalcRec(int** R, const int rowCount, const int colCount, int& S, int& k, int i, int j) {
	if (i == 0 && j == 0) {
		S = 0;
		k = 0;
	}
	if (i >= rowCount) return;
	if (j >= colCount) {
		CalcRec(R, rowCount, colCount, S, k, i + 1, 0);
		return;
	}
	if (R[i][j] > 0 || !(R[i][j] % 3 == 0)) {
		S += R[i][j];
		k++;
		R[i][j] = 0;
	}
	CalcRec(R, rowCount, colCount, S, k, i, j + 1);
}