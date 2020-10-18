#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int min(int x, int y, int z) {
    vector<int> ffs;
    ffs.push_back(x);
    ffs.push_back(y);
    ffs.push_back(z);
    int min = ffs.front();
    for (int i = 0; i < ffs.size(); i++) {
        if (min > ffs.at(i))
            min = ffs.at(i);
    }
    return min;
}

void copyArray(int array1[], int array2[], int n) {
    for (int i = 0; i < n; i++)
        array1[i] = array2[i];
}

int bottomUp(char *str1, char *str2, int n, int m);

int efficientBottomUp(char *str1, char *str2, int n, int m);

pair<int, int> recursive(char *str1, char *str2, int n, int m);

int main() {
    char str1[] = "TREE";
    char str2[] = "TOR";
    cout << "Bottom Up: " << bottomUp(str1, str2, strlen(str1), strlen(str2)) << endl;
    pair<int, int> recc = recursive(str1, str2, strlen(str1), strlen(str2));
    cout << "Recursive: " << "Edit Distance: " << recc.first << " Solution count: " << recc.second << endl;
    cout << "Efficient Bottom up: " << efficientBottomUp(str1, str2, strlen(str1), strlen(str2));

    return 0;
}

int bottomUp(char *str1, char *str2, int n, int m) {
    int x = n + 1, y = m + 1, value = 0, value1, value2, value3;
    int matrix[x][y];
    int sol_matrix[x][y];

    memset(matrix, -1, sizeof(matrix));
    memset(sol_matrix, 0, sizeof(sol_matrix));

    for (int i = 0; i < y; i++) {
        matrix[0][i] = i;
        sol_matrix[0][i] = 1;
    }

    for (int i = 0; i < x; i++) {
        matrix[i][0] = i;
        sol_matrix[i][0] = 1;
    }

    for (int i = 1; i < x; i++) {
        for (int j = 1; j < y; j++) {
            if (str1[i - 1] == str2[j - 1]) { //if characters are equal, take diagonal value
                matrix[i][j] = matrix[i - 1][j - 1];
                sol_matrix[i][j] = sol_matrix[i - 1][j - 1];
            } else {
                value1 = matrix[i][j - 1]; //insertion
                value2 = matrix[i - 1][j]; //deletion
                value3 = matrix[i - 1][j - 1]; //replace
                value = 1 + min(value1, value2, value3);
                matrix[i][j] = value;
                if (value1 == value - 1)
                    sol_matrix[i][j] += sol_matrix[i][j - 1];
                if (value2 == value - 1)
                    sol_matrix[i][j] += sol_matrix[i - 1][j];
                if (value3 == value - 1)
                    sol_matrix[i][j] += sol_matrix[i - 1][j - 1];
            }
        }
    }

    cout << "Total Solutions: " << sol_matrix[x - 1][y - 1] << endl;
    //tracing back
    int i = x - 1, j = y - 1;
    vector<string> operations;
    while (i and j) {
        if (str1[i - 1] == str2[j - 1])//both are equal, do nothing
        {
            i--;
            j--;
        } else {
            if (matrix[i][j] == matrix[i - 1][j] + 1) //deletion
            {
                operations.push_back("Delete");
                i--;
            } else if (matrix[i][j] == matrix[i][j - 1] + 1) //insertion
            {
                operations.push_back("Insert");
                j--;
            } else {
                operations.push_back("Replace");
                i--;
                j--;
            }
        }
    }

    for (int m = 0; m < operations.size(); m++)
        cout << operations.at(m) << endl;

    return matrix[n][m];
}

int efficientBottomUp(char *str1, char *str2, int n, int m) {
    int array1[m + 1];
    int array2[m + 1];

    memset(array1, -1, sizeof(array1));
    memset(array2, -1, sizeof(array2));

    for (int i = 0; i < m + 1; i++)
        array1[i] = i;

    for (int i = 1; i < n+1; i++) {
        array2[0] = i;
        for (int j = 1; j < m+1; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                array2[j] = array1[j - 1];
            } else {
                array2[j] = 1 + min(array2[j - 1], array1[j - 1], array1[j]);
            }
        }
        copyArray(array1, array2, n + 1);
    }

    return array1[m];
}

pair<int, int> recursive(char *str1, char *str2, int n, int m) {

    if (n == 0) {
        pair<int, int> pairing;
        pairing = make_pair(m, 1);
        return pairing;
    }

    if (m == 0) {
        pair<int, int> pairing;
        pairing = make_pair(n, 1);
        return pairing;
    }

    pair<int, int> value;
    int sol_count = 0;
    if (str1[n - 1] == str2[m - 1]) { //if both are equal, just move backwards
        value = recursive(str1, str2, n - 1, m - 1);
    } else {
        pair<int, int> value1 = recursive(str1, str2, n, m - 1);
        pair<int, int> value2 = recursive(str1, str2, n - 1, m);
        pair<int, int> value3 = recursive(str1, str2, n - 1, m - 1);

        value.first = 1 + min(value1.first, value2.first, value3.first);
        if (value1.first == value.first - 1)
            sol_count += value1.second;
        if (value2.first == value.first - 1)
            sol_count += value2.second;
        if (value3.first == value.first - 1)
            sol_count += value3.second;
        value.second = sol_count;
    }
    return value;
}