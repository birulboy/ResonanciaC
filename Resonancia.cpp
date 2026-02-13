#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>


using namespace std;

// El cerebro se modela como un cubo de dimensiones iguales
static const int SIZE = 100;

// Rango que define un valor sospechoso
static const int SUSPICIOUS_MIN_VALUE = 20;
static const int SUSPICIOUS_MAX_VALUE = 40;

class Brain {
private:
    int data[SIZE][SIZE][SIZE];

public:
    void generateRandomValuesToFillTheBrain() {
        for (int plano = 0; plano < SIZE; plano++) {
            for (int fila = 0; fila < SIZE; fila++) {
                for (int columna = 0; columna < SIZE; columna++) {
                    data[plano][fila][columna] = (rand() % 11) + 25;
                }                               //(rand() % 11) + 25 ("LLENO DE PUNTOS")
                                                //(rand() % 256) ("PROBABILIDAD ESTANDAR")
                                                //(rand() % 15) + 28 ("MUCHA PROBABILIDAD")
                                                //(rand() % 23) + 19 ("ALGUNA PROBABILIDAD")
            }
        }
    }

    int readValueAt(int plano, int fila, int columna) const {
        return data[plano][fila][columna];
    }
};

class SuspicionAnalyzer {
private:
    bool isPointOutsideSuspiciousBounds(int fila, int columna, int plano) const {
    return fila <= 0 || fila >= SIZE - 1 ||
           columna <= 0 || columna >= SIZE - 1 ||
           plano <= 0 || plano >= SIZE - 1;
    }


    bool isValueSuspicious(int value) const {
        return value >= SUSPICIOUS_MIN_VALUE &&
               value <= SUSPICIOUS_MAX_VALUE;
    }

public:
    bool isPointSuspicious(
    const Brain& brain,
    int fila,
    int columna,
    int plano
    ) const {
    
        if (isPointOutsideSuspiciousBounds(fila, columna, plano)) {
            return false;
        }
    
        bool samePlane =
            isValueSuspicious(brain.readValueAt(plano, fila - 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano, fila - 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano, fila - 1, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano, fila, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano, fila, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano, fila + 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano, fila + 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano, fila + 1, columna + 1));
    
        bool upperPlane =
            isValueSuspicious(brain.readValueAt(plano + 1, fila - 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila - 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila - 1, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila + 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila + 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila, columna)) &&
            isValueSuspicious(brain.readValueAt(plano + 1, fila + 1, columna + 1));
    
        bool lowerPlane =
            isValueSuspicious(brain.readValueAt(plano - 1, fila - 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila - 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila - 1, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila, columna)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila, columna + 1)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila + 1, columna - 1)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila + 1, columna)) &&
            isValueSuspicious(brain.readValueAt(plano - 1, fila + 1, columna + 1));
    
        return samePlane && upperPlane && lowerPlane;
        
        
    }


    bool isPointPartOfSuspiciousLine(
        const Brain& brain,
        int fila,
        int columna,
        int plano
    ) const {
        bool center =
            isPointSuspicious(brain, fila, columna, plano);

        bool rightLine =
            center &&
            isPointSuspicious(brain, fila, columna + 1, plano) &&
            isPointSuspicious(brain, fila, columna + 2, plano);

        bool centeredLine =
            isPointSuspicious(brain, fila, columna - 1, plano) &&
            center &&
            isPointSuspicious(brain, fila, columna + 1, plano);

        bool leftLine =
            isPointSuspicious(brain, fila, columna - 2, plano) &&
            isPointSuspicious(brain, fila, columna - 1, plano) &&
            center;

        return rightLine || centeredLine || leftLine;
    }

    int countSuspiciousLines(const Brain& brain, int plano) const {
        int lineCounter = 0;

        for (int fila = 0; fila < SIZE; fila++) {
            int consecutivePoints = 0;

            for (int columna = 0; columna < SIZE; columna++) {
                if (consecutivePoints == 3) {
                    lineCounter++;
                }

                if (isPointSuspicious(brain, fila, columna, plano)) {
                    consecutivePoints++;
                } else {
                    consecutivePoints = 0;
                }
            }
        }
        return lineCounter;
    }

    int countSuspiciousPoints(const Brain& brain, int plano) const {
        int pointCounter = 0;

        for (int fila = 0; fila < SIZE; fila++) {
            for (int columna = 0; columna < SIZE; columna++) {
                if (isPointSuspicious(brain, fila, columna, plano)) {
                    pointCounter++;
                }
            }
        }
        return pointCounter;
    }
};

class ConsoleUI {
private:
    SuspicionAnalyzer analyzer;
    
    bool isNotAnInteger(const string& text) {
        stringstream ss(text);
        int value;
        char extra;
    
        if (!(ss >> value)) {
            return true;
        }
    
        if (ss >> extra) {
            return true;
        }
    
        return false;
    }


    int requestCoordinate(char label) {
        string input;
        int value;
    
        cout << "Ingrese " << label << ": ";
        cin >> input;
    
        if (isNotAnInteger(input)) {
            cout << "Entrada invalida. Solo numeros enteros.\n";
            return requestCoordinate(label);
        }
    
        stringstream ss(input);
        ss >> value;
    
        if (value < 1 || value >= SIZE - 1) {
            cout << "Valor fuera de rango\n";
            return requestCoordinate(label);
        }
    
        return value;
    }



    void drawSuspiciousLinesInPlane(const Brain& brain, int plano) {
        for (int fila = 0; fila < SIZE; fila++) {
            for (int columna = 0; columna < SIZE; columna++) {
                cout << (analyzer.isPointPartOfSuspiciousLine(brain, fila, columna, plano) ? '1' : '0');
            }
            cout << '\n';
        }
    }
    
    void printPointNeighborhood(
        const Brain& brain,
        int plano,
        int fila,
        int columna,
        bool markCenter
    ) {
        int values[9] = {
            brain.readValueAt(plano, fila - 1, columna - 1),
            brain.readValueAt(plano, fila - 1, columna),
            brain.readValueAt(plano, fila - 1, columna + 1),

            brain.readValueAt(plano, fila, columna - 1),
            brain.readValueAt(plano, fila, columna),
            brain.readValueAt(plano, fila, columna + 1),

            brain.readValueAt(plano, fila + 1, columna - 1),
            brain.readValueAt(plano, fila + 1, columna),
            brain.readValueAt(plano, fila + 1, columna + 1)
        };

        cout << '\n';

        for (int i = 0; i < 9; i++) {
            if (markCenter && i == 4) {
                cout << "| XX |";
            } else {
                cout << "| " << values[i] << " |";
            }

            if (i == 2 || i == 5) {
                cout << '\n';
            }
        }
    }

public:
    void run(Brain& brain) {
        bool running = true;

        while (running) {
            int option;
            cout << "\nMENU\n";
            cout << "0 - Salir\n";
            cout << "1 - Analizar punto\n";
            cout << "2 - Analizar plano\n";
            cout << "3 - Informe general\n";
            cin >> option;

            switch (option) {
            case 0:
                running = false;
                break;

            case 1: {
                int plano = requestCoordinate('Z');
                int fila = requestCoordinate('Y');
                int columna = requestCoordinate('X');
            
                cout << (analyzer.isPointSuspicious(brain, fila, columna, plano)
                         ? "Punto sospechoso\n"
                         : "Punto no sospechoso\n");
            
                // Plano inferior
                printPointNeighborhood(brain, plano - 1, fila, columna, false);
                cout << "\nZ-1";
            
                // Plano actual
                printPointNeighborhood(brain, plano, fila, columna, true);
                cout << "\nZ";
            
                // Plano superior
                printPointNeighborhood(brain, plano + 1, fila, columna, false);
                cout << "\nZ+1\n";
            
                break;
            }


            case 2: {
                int plano = requestCoordinate('Z');
                drawSuspiciousLinesInPlane(brain, plano);
                break;
            }

            case 3:
                for (int plano = 0; plano < SIZE; plano++) {
                    cout << "Plano " << plano
                         << " | Puntos: " << analyzer.countSuspiciousPoints(brain, plano)
                         << " | Lineas: " << analyzer.countSuspiciousLines(brain, plano)
                         << '\n';
                }
                break;

            default:
                cout << "Opcion invalida\n";
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Brain brain;
    brain.generateRandomValuesToFillTheBrain();

    ConsoleUI ui;
    ui.run(brain);

    return 0;
}
