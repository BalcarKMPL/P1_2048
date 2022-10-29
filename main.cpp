//Jakub Mazur
#include <iostream>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "UnreachableCode"
#define ifprint false
using namespace std;


int get(char command, int** plansza, int M, int x, int y){
    if (command == 'L')
        return *(*((plansza) + (x)) + (y));
    if (command == 'G')
        return *(*((plansza) + (y)) + (x));
    if (command == 'D')
        return *(*((plansza) + (M) - 1 - (y)) + (x));
    if (command == 'P')
        return *(*((plansza) + (x)) + (M) - 1 - (y));
    return -1;
}
void set(char command, int** plansza, int M, int x, int y, int val){
    if (command == 'L')
        *(*((plansza) + (x)) + (y)) = val;
    if (command == 'G')
        *(*((plansza) + (y)) + (x)) = val;
    if (command == 'D')
        *(*((plansza) + (M) - 1 - (y)) + (x)) = val;
    if (command == 'P')
        *(*((plansza) + (x)) + (M) - 1 - (y)) = val;
}

int** GenerateBoard(int M){
    int** plansza = (int**) calloc(M, sizeof(int*));
    for (int i = 0; i < M; ++i) {
        *(plansza + i) = (int *) calloc(M, sizeof(int));
    }
    return plansza;
}

void printRow(char command, int **plansza, int M, int i) {
    if (not ifprint) return;
    cout << command << i << ": \t\t";
    for (int j = 0; j < M; ++j) {
        cout << get(command, plansza, M, i, j) << " ";
    }
    cout << endl;
}

int main() {
    int M;
    cin >> M;
    int** plansza = GenerateBoard(M);

    char command;
    while (true) {
        cin >> command;
        if (ifprint) cout << command << endl;
        if (command == 'K') {
            int s = 0;
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    s += get('L', plansza, M, i, j);
                }
            }
            cout << s << endl;
            return 0;
        }
        if (command == 'N') {
            int x, y, val;
            cin >> x >> y >> val;
            set('L', plansza, M, x, y, val);
        }
        if (command == 'C') {
            int val;
            cin >> M;
            plansza = GenerateBoard(M);
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    cin >> val;
                    set('L', plansza, M, i, j, val);
                }
            }
        }
        if (command == 'W') {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    cout << get('L', plansza, M, i, j) << " ";
                }
                cout << endl;
            }
        }
        if (command == 'S') {
            int s = 0;
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    s += get('L', plansza, M, i, j);
                }
            }
            cout << s << endl;
        }
        if (command == 'L' or command == 'P' or command == 'G' or command == 'D') {
            int gl, gr; bool changed;
            for (int i = 0; i < M; ++i) {
                int shift = -1;
                printRow(command, plansza, M, i);
                for (int j = 0; j < M; ++j) {
                    gl = get(command, plansza, M, i, j);
                    if (gl != 0 and shift == -1) shift = j;
                    if (shift >= 1) {
                        set(command, plansza, M, i, j - shift, get(command, plansza, M, i, j));
                        set(command, plansza, M, i, j, 0);
                    }
                    if (shift == 0) break;
                }
                changed = true;
                while (changed) {
                    whilebeginL:
                    changed = false;
                    printRow(command, plansza, M, i);
                    for (int j = 0; j < M - 1; ++j) {
                        gl = get(command, plansza, M, i, j);
                        if (gl == 0) continue;
                        for (int k = j + 1; k < M; ++k) {
                            gr = get(command, plansza, M, i, k);
                            if (gr == 0) continue;
                            if (gr == gl){
                                set(command, plansza, M, i, j, 2 * gl);
                                set(command, plansza, M, i, k, 0);
                                changed = true;
                                goto whilebeginL;
                            } else if (j + 1 != k) {
                                set(command, plansza, M, i, k, 0);
                                set(command, plansza, M, i, j + 1, gr);
                                changed = true;
                                goto whilebeginL;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}
#pragma clang diagnostic pop