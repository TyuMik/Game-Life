#include <iostream>
#include <fstream>
#include <cstdlib>
//#include <unistd.h>
#include <windows.h>

char** create_arr(int rows, int cols) {
    char** arr = new char* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new char[cols];
    }
    return arr;
}

void print_arr(char** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

char** copy_arr(char** arr, int rows, int cols) {
    char** arr_copy = create_arr(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr_copy[i][j] = arr[i][j];
        }
    }
    return arr_copy;
}

int alive_cells(char** arr, int rows, int cols, const char alive_cell) {
    int tmp = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == alive_cell) {
                tmp++;
            }
        }
    }
    return tmp;
}

int stgn_check(char** arr_1, char** arr_2, int rows, int cols) {
    int tmp = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr_1[i][j] == arr_2[i][j]) {
                tmp++;
            }
        }
    }
    return tmp;
}

void delete_arr(char** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}

int aliveCellCount(char** arr, int rows, int cols, int pI, int pJ, char alive_cell) {
    int count = 0;
    for (int i = pI - 1; i <= pI + 1; i++) {
        if (i < 0 || i >= rows) {
            continue;
        }
        for (int j = pJ - 1; j <= pJ + 1; j++) {
            if (j < 0 || j >= cols) {
                continue;
            }
            if (i == pI && j == pJ) {
                continue;
            }
            if (arr[i][j] == alive_cell) {
                count++;
            }
        }
    }
    return count;
}
//////////////////////////////////////////////////////////
int main() {

    const char aliveCell = '*';
    const char deadCell = '-';

    std::ifstream text_arr("in.txt");

    if (text_arr.is_open()) {
        int rows, cols, k, l;
        text_arr >> rows >> cols;

        char** arr2 = create_arr(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr2[i][j] = deadCell;
            }
        }

        for (int i = 0; !(text_arr).eof(); i++) {
            for (int j = 0; j < 2; j++) {
                text_arr >> k >> l;
                arr2[k][l] = aliveCell;
            }
        }
        ///////////////////////////////////////////////////////////
        int Gen = 1;
        char** arr3 = copy_arr(arr2, rows, cols);

        while ((alive_cells(arr2, rows, cols, aliveCell) > 0)) {
            print_arr(arr2, rows, cols);
            std::cout << "Generation: " << Gen << ". " << "Alive cells: ";
            std::cout << alive_cells(arr2, rows, cols, aliveCell);
            std::cout << std::endl;
            ////////////////////////////////////////////////////
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if ((arr2[i][j] == aliveCell) && (aliveCellCount(arr2, rows, cols, i, j, aliveCell) > 3) || (aliveCellCount(arr2, rows, cols, i, j, aliveCell) < 2)) {
                        arr3[i][j] = deadCell;
                    }
                    if ((arr2[i][j] == deadCell) && (aliveCellCount(arr2, rows, cols, i, j, aliveCell) == 3)) {
                        arr3[i][j] = aliveCell;
                    }
                }
            }
            ///////////////////////////////////////////////////////////
            if (stgn_check(arr2, arr3, rows, cols) == (rows * cols)) {
                Sleep(3000);
                std::system("cls");
                print_arr(arr2, rows, cols);
                std::cout << "Generation: " << Gen + 1 << ". " << "Alive cells: " << alive_cells(arr2, rows, cols, aliveCell);
                std::cout << std::endl;
                std::cout << "The world has stagnated. Game over" << std::endl;
                delete_arr(arr2, rows, cols);
                delete_arr(arr3, rows, cols);
                text_arr.close();
                return 0;
            }
            //////////////////////////////////////////////////////////
            delete_arr(arr2, rows, cols);
            arr2 = copy_arr(arr3, rows, cols);
            Gen += 1;
            Sleep(3000);
            std::system("cls");
        };

        print_arr(arr2, rows, cols);
        std::cout << "Generation: " << Gen << ". " << "Alive cells: 0";
        std::cout << std::endl;
        std::cout << "All cells are dead. Game over" << std::endl;
        delete_arr(arr2, rows, cols);
        delete_arr(arr3, rows, cols);
        text_arr.close();
    }
    else {
        std::cout << "Ошибка! Не удалось открыть файл.";
    }
    return 0;
}