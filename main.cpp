//Jakub Mazur
#define B(x,y) *(*(plansza + x) + y)
#include <iostream>
#define get(a, x, y) *(*((plansza) + (x)) + (y))
#define set(a, x, y, val) *(*((plansza) + (x)) + (y)) = (val)

#define getR(a, x, y) *(*((plansza) + (x)) + (M) - 1 - (y))
#define setR(a, x, y, val) *(*((plansza) + (x)) + (M) - 1 - (y)) = (val)

#define getL(a, x, y) *(*((plansza) + (x)) + (y))
#define setL(a, x, y, val) *(*((plansza) + (x)) + (y)) = (val)

#define getG(a, x, y) *(*((plansza) + (y)) + (x))
#define setG(a, x, y, val) *(*((plansza) + (y)) + (x)) = (val)

#define getD(a, x, y) *(*((plansza) + (M) - 1 - (y)) + (M) - 1 - (x))
#define setD(a, x, y, val) *(*((plansza) + (M) - 1 - (y)) + (M) - 1 - (x)) = (val)

//#define getR(a, x, y) *(*((plansza) + (M) - 1 - (x)) + (y))
//#define setR(a, x, y, val) *(*((plansza) + (M) - 1 - (x)) + (y)) = (val)

using namespace std;

int** GenerateBoard(int M){
    int** plansza = (int**) calloc(M, sizeof(int*));
    for (int i = 0; i < M; ++i) {
        *(plansza + i) = (int *) calloc(M, sizeof(int));
    }
    return plansza;
}

void printBoard(int **plansza, int M) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << get(plansza, i, j) << " ";
        }
        cout << endl;
    }
}

void printCol(int **plansza, int M, int j) {
    for (int i = 0; i < M; ++i) {
        cout << get(plansza, i, j) << " ";
    }
    cout << endl;
}

void printRow(int **plansza, int M, int i) {
    for (int j = 0; j < M; ++j) {
        cout << get(plansza, i, j) << " ";
    }
    cout << endl;
}

int main() {
    bool ifintuitive = true;

    int M;
    cin >> M;
    int** plansza = GenerateBoard(M);

    char command;
    while (true) {
        cin >> command;
//        cout << command << endl;
        if (command == 'K') {
            int s = 0;
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    s += get(plansza, i, j);
                }
            }
            cout << s << endl;
            return 0;
        }
        if (command == 'N') {
            int x, y, val;
            cin >> x >> y >> val;
            set(plansza, x, y, val);
        }
        if (command == 'C') {
            int val;
            cin >> M;
            plansza = GenerateBoard(M);
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    cin >> val;
                    set(plansza, i, j, val);
                }
            }
        }
        if (command == 'W') {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    cout << get(plansza, i, j) << " ";
                }
                cout << endl;
            }
        }
        if (command == 'S') {
            int s = 0;
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < M; ++j) {
                    s += get(plansza, i, j);
                }
            }
            cout << s << endl;
        }
        if (command == 'L') {
            int g, gprev; bool changed = true;
            for (int i = 0; i < M; ++i) {
                changed = true; int j = 0;
                while (changed) {
                    int k = j + 1; changed = false;
                    cout << "! ";
                    printRow(plansza, M, i);
                    for (; j < M - 1; ++j) {
                        g = getL(plansza, i, j);
                        if (g != 0) continue;
                        for (k = k == 0 ? j + 1 : k; k < M; ++k) {
                            g = getL(plansza, i, k);
                            if (g == 0) continue;
                            setL(plansza, i, j, g);
                            setL(plansza, i, k, 0);
                            cout << "@ ";
                            printRow(plansza, M, i);
                            changed = true;
                            break;
                        }
                    }

                    cout << "# ";
                    printRow(plansza, M, i);
                    g = getL(plansza, i, 0);
                    for (j = 1; j < M; ++j) {
                        gprev = g;
                        g = getL(plansza, i, j);
                        if (gprev == 0) continue;
                        if (g == 0) continue;
                        if (g != gprev) continue;
                        setL(plansza, i, j - 1, g * 2);
                        setL(plansza, i, j, 0);
                        changed = true;
                        g = 0;
                        cout << "$ ";
                        printRow(plansza, M, i);
                        if (ifintuitive) break;
                    }
                }
            }
        }
        if (command == 'G') {
            int g, gprev; bool changed = true;
            for (int i = 0; i < M; ++i) {
                changed = true;
                while (changed) {
                    int k = 0; changed = false;
                    for (int j = 0; j < M - 1; ++j) {
                        g = getG(plansza, i, j);
                        if (g != 0) continue;
                        for (k = k == 0 ? j + 1 : k; k < M; ++k) {
                            g = getG(plansza, i, k);
                            if (g == 0) continue;
                            setG(plansza, i, j, g);
                            setG(plansza, i, k, 0);
//                            cout << "# ";
//                            printRow(plansza, M, 0);
                            changed = true;
                            break;
                        }
                    }

                    g = getG(plansza, i, 0);
                    for (int j = 1; j < M; ++j) {
                        gprev = g;
                        g = getG(plansza, i, j);
                        if (gprev == 0) continue;
                        if (g == 0) continue;
                        if (g != gprev) continue;
                        setG(plansza, i, j - 1, g * 2);
                        setG(plansza, i, j, 0);
                        changed = true;
                        g = 0;
                        if (ifintuitive) break;
//                        cout << "# ";
//                        printRow(plansza, M, 0);
                    }
                }
            }
        }
        if (command == 'D') {
            int g, gprev; bool changed = true;
            for (int i = 0; i < M; ++i) {
                changed = true;
                while (changed) {
                    int k = 0; changed = false;
                    for (int j = 0; j < M - 1; ++j) {
                        g = getD(plansza, i, j);
                        if (g != 0) continue;
                        for (k = k == 0 ? j + 1 : k; k < M; ++k) {
                            g = getD(plansza, i, k);
                            if (g == 0) continue;
                            setD(plansza, i, j, g);
                            setD(plansza, i, k, 0);
//                            cout << "# ";
//                            printRow(plansza, M, 0);
                            changed = true;
                            break;
                        }
                    }

                    g = getD(plansza, i, 0);
                    for (int j = 1; j < M; ++j) {
                        gprev = g;
                        g = getD(plansza, i, j);
                        if (gprev == 0) continue;
                        if (g == 0) continue;
                        if (g != gprev) continue;
                        setD(plansza, i, j - 1, g * 2);
                        setD(plansza, i, j, 0);
                        changed = true;
                        g = 0;
                        if (ifintuitive) break;
//                        cout << "# ";
//                        printRow(plansza, M, 0);
                    }
                }
            }
        }
        if (command == 'P' or command == 'R') {
            int g, gprev; bool changed = true;
            for (int i = 0; i < M; ++i) {
                changed = true;
                while (changed) {
                    int k = 0; changed = false;
                    for (int j = 0; j < M - 1; ++j) {
                        g = getR(plansza, i, j);
                        if (g != 0) continue;
                        for (k = k == 0 ? j + 1 : k; k < M; ++k) {
                            g = getR(plansza, i, k);
                            if (g == 0) continue;
                            setR(plansza, i, j, g);
                            setR(plansza, i, k, 0);
//                            cout << "# ";
//                            printRow(plansza, M, 0);
                            changed = true;
                            break;
                        }
                    }

                    g = getR(plansza, i, 0);
                    for (int j = 1; j < M; ++j) {
                        gprev = g;
                        g = getR(plansza, i, j);
                        if (gprev == 0) continue;
                        if (g == 0) continue;
                        if (g != gprev) continue;
                        setR(plansza, i, j - 1, g * 2);
                        setR(plansza, i, j, 0);
                        changed = true;
                        g = 0;
                        if (ifintuitive) break;
//                        cout << "# ";
//                        printRow(plansza, M, 0);
                    }
                }
            }
        }




//        if (command == 'G') {
//            int g, gprev; bool changed = true;
//            for (int i = 0; i < M; ++i) {
//                changed = true;
//                while (changed) {
//                    int k = 0; changed = false;
//                    for (int j = 0; j < M - 1; ++j) {
//                        g = get(plansza, j, i);
//                        if (g != 0) continue;
//                        for (k = k == 0 ? j + 1 : k; k < M; ++k) {
//                            g = get(plansza, k, i);
//                            if (g == 0) continue;
//                            set(plansza, j, i, g);
//                            set(plansza, k, i, 0);
////                            cout << "# ";
////                            printRow(plansza, M, 0);
//                            changed = true;
//                            break;
//                        }
//                    }
////                    cout << endl;
//
//                    g = get(plansza, 0, i);
////                    cout << "# ";
////                    printRow(plansza, M, 0);
//                    for (int j = 1; j < M; ++j) {
//                        gprev = g;
//                        g = get(plansza, j, i);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, j - 1, i, g * 2);
//                        set(plansza, j, i, 0);
//                        changed = true;
//                        g = 0;
////                        cout << "# ";
////                        printRow(plansza, M, 0);
//                    }
////                    cout << endl;
//                }
//            }
//        }
//        if (command == 'D') {
//            int g, gprev; bool changed = true;
//            for (int i = 0; i < M; ++i) {
//                changed = true;
//                while (changed) {
//                    cout << "@ ";
//                    printCol(plansza, M, i);
//                    int k = M - 1; changed = false;
//                    for (int j = M - 1; j > 0; --j) {
//                        g = get(plansza, j, i);
//                        if (g != 0) continue;
//                        for (k = k == M - 1 ? j - 1 : k; k > -1; --k) {
//                            g = get(plansza, k, i);
//                            if (g == 0) continue;
//                            set(plansza, j, i, g);
//                            set(plansza, k, i, 0);
//                            cout << "# ";
//                            printCol(plansza, M, i);
//                            changed = true;
//                            break;
//                        }
//                    }
//                    cout << endl;
//
//                    g = get(plansza, 0, i);
//                    cout << "@ ";
//                    printCol(plansza, M, i);
//                    for (int j = 1; j < M; ++j) {
//                        gprev = g;
//                        g = get(plansza, j, i);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, j - 1, i, g * 2);
//                        set(plansza, j, i, 0);
//                        changed = true;
//                        g = 0;
//                        cout << "# ";
//                        printCol(plansza, M, i);
//                    }
//                    cout << endl;
//                }
//            }
//        }
//        if (command == 'P') {
//            int g, gprev; bool changed = true;
//            for (int i = 0; i < M; ++i) {
//                changed = true;
//                while (changed) {
//                    cout << "@ ";
//                    printRow(plansza, M, i);
//                    int k = M - 1; changed = false;
//                    for (int j = M - 1; j > 0; --j) {
//                        g = get(plansza, i, j);
//                        if (g != 0) continue;
//                        for (k = k == M - 1 ? j - 1 : k; k > -1; --k) {
//                            g = get(plansza, i, k);
//                            if (g == 0) continue;
//                            set(plansza, i, j, g);
//                            set(plansza, i, k, 0);
//                            cout << "# ";
//                            printRow(plansza, M, i);
//                            changed = true;
//                            break;
//                        }
//                    }
//                    cout << endl;
//
//                    g = get(plansza, i, 0);
//                    cout << "@ ";
//                    printRow(plansza, M, i);
//                    for (int j = 1; j < M; ++j) {
//                        gprev = g;
//                        g = get(plansza, i, j);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, i, j - 1, g * 2);
//                        set(plansza, i, j, 0);
//                        changed = true;
//                        g = 0;
//                        cout << "# ";
//                        printRow(plansza, M, i);
//                    }
//                    cout << endl;
//                }
//            }
//        }




//        if (command == 'G') {
//            int g, gprev;
//            bool changed = true;
//            while (changed) {
//                changed = false;
//                for (int i = 0; i < M; ++i) {
//                    for (int j = 0; j < M - 1; ++j) {
//                        g = get(plansza, j, i);
//                        if (g != 0) continue;
//                        for (int k = j + 1; k < M; ++k) {
//                            g = get(plansza, k, i);
//                            if (g == 0) continue;
//                            set(plansza, j, i, g);
//                            set(plansza, k, i, 0);
//                            changed = true;
//                            break;
//                        }
//                    }
//
//                    g = get(plansza, 0, i);
//                    for (int j = 1; j < M; ++j) {
//                        gprev = g; g = get(plansza, j, i);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, j-1, i, g * 2);
//                        set(plansza, j, i, 0);
//                        changed = true;
//                        break;
//                    }
//                }
//            }
//        }
//        if (command == 'D') {
//            int g, gprev;
//            bool changed = true;
//            while (changed) {
//                changed = false;
//                for (int i = 0; i < M; ++i) {
//                    for (int j = M - 1; j >= 1; --j) {
//                        g = get(plansza, j, i);
//                        if (g != 0) continue;
//                        for (int k = j - 1; k >= 0; --k) {
//                            g = get(plansza, k, i);
//                            if (g == 0) continue;
//                            set(plansza, j, i, g);
//                            set(plansza, k, i, 0);
//                            changed = true;
//                            break;
//                        }
//                    }
//
//                    g = get(plansza, M - 1, i);
//                    for (int j = M - 2; j >= 0; --j) {
//                        gprev = g; g = get(plansza, j, i);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, j + 1, i, g * 2);
//                        set(plansza, j, i, 0);
//                        changed = true;
//                        break;
//                    }
//                }
//            }
//        }
//        if (command == 'P') {
//            int g, gprev;
//            bool changed = true;
//            while (changed) {
//                changed = false;
//                for (int i = 0; i < M; ++i) {
//                    for (int j = M - 1; j >= 1; --j) {
//                        g = get(plansza, i, j);
//                        if (g != 0) continue;
//                        for (int k = j - 1; k >= 0; --k) {
//                            g = get(plansza, i, k);
//                            if (g == 0) continue;
//                            set(plansza, i, j, g);
//                            set(plansza, i, k, 0);
//                            changed = true;
//                            break;
//                        }
//                    }
//
//                    g = get(plansza, i, M - 1);
//                    for (int j = M - 2; j >= 0; --j) {
//                        gprev = g; g = get(plansza, i, j);
//                        if (gprev == 0) continue;
//                        if (g == 0) continue;
//                        if (g != gprev) continue;
//                        set(plansza, i, j, 2 * g);
//                        set(plansza, i, j + 1, 0);
//                        changed = true;
//                        break;
//                    }
//                }
//            }
//        }
    }
}
