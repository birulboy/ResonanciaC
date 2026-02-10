#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DESAROLLADO EN ONLINE GDB
void RandomBrain ( int brain[100][100][100] ) { // funcion que le da valores aleatorios al arrayd
    for ( int z = 0 ; z < 100 ; z ++) {
        for ( int y = 0; y < 100 ; y ++ ) {
            for ( int x = 0; x < 100 ; x ++ ){
                //(rand() % 11) + 25 ("LLENO DE PUNTOS")
                //rand() % 256 ("PROBABILIDAD ESTANDAR")
                //(rand() % 15) + 28 ("MUCHA PROBABILIDAD")
                //(rand() % 23) + 19 ("ALGUNA PROBABILIDAD")
                brain[z][y][x] = (rand() % 11) + 25 ; // en la posicion z ( hoja )  y ( fila ) x ( columna ) se genera un numero random del 0 al 255
            } 
            
        }
    }
}
    
int ComNum ( int x ) { // funcion que analiza el valor de un punto
    if ( x >= 20 && x <= 40) { // si esta entre 20 y 40
        return 1;
    } else return 0; // fin if ( x >= 20 && x <= 40)
}

int AnalyzePoint(int x, int y, int z , int brain[100][100][100]) { // analiza si un punto es sospechoso 
    // Verifica límites para (x, y, z)
    if (x > 0 && x < 99 && y > 0 && y < 99 && z > 0 && z < 99 ) {
        if (
            // Verificaciones
            ComNum(brain[z][y][x - 1]) && // Verifica el punto a la izquierda (x-1, y)
            ComNum(brain[z][y][x + 1]) && // Verifica el punto a la derecha (x+1, y)
            ComNum(brain[z][y - 1][x - 1]) && // Arriba izquierda (x-1, y-1)
            ComNum(brain[z][y - 1][x + 1]) && // Arriba derecha (x+1, y-1)
            ComNum(brain[z][y - 1][x]) && // Arriba (x, y-1)
            ComNum(brain[z][y + 1][x - 1]) && // Abajo izquierda (x-1, y+1)
            ComNum(brain[z][y + 1][x + 1]) && // Abajo derecha (x+1, y+1)
            ComNum(brain[z][y + 1][x]) && // Abajo (x, y+1)
            // Plano superior (z+1)
            ComNum(brain[z + 1][y][x - 1]) && // Superior izquierda (x-1, y)
            ComNum(brain[z + 1][y][x + 1]) && // Superior derecha (x+1, y)
            ComNum(brain[z + 1][y - 1][x - 1]) && // Superior arriba izquierda (x-1, y-1)
            ComNum(brain[z + 1][y - 1][x + 1]) && // Superior arriba derecha (x+1, y-1)
            ComNum(brain[z + 1][y - 1][x]) && // Superior arriba (x, y-1)
            ComNum(brain[z + 1][y + 1][x - 1]) && // Superior abajo izquierda (x-1, y+1)
            ComNum(brain[z + 1][y + 1][x + 1]) && // Superior abajo derecha (x+1, y+1)
            ComNum(brain[z + 1][y + 1][x]) && // Superior abajo (x, y+1)
            ComNum(brain[z + 1][y][x]) && // Centro en el plano superior (x, y)
            // Plano inferior (z-1)
            ComNum(brain[z - 1][y][x - 1]) && // Inferior izquierda (x-1, y)
            ComNum(brain[z - 1][y][x + 1]) && // Inferior derecha (x+1, y)
            ComNum(brain[z - 1][y - 1][x - 1]) && // Inferior arriba izquierda (x-1, y-1)
            ComNum(brain[z - 1][y - 1][x + 1]) && // Inferior arriba derecha (x+1, y-1)
            ComNum(brain[z - 1][y - 1][x]) && // Inferior arriba (x, y-1)
            ComNum(brain[z - 1][y + 1][x - 1]) && // Inferior abajo izquierda (x-1, y+1)
            ComNum(brain[z - 1][y + 1][x + 1]) && // Inferior abajo derecha (x+1, y+1)
            ComNum(brain[z - 1][y + 1][x]) && // Inferior abajo (x, y+1)
            ComNum(brain[z - 1][y][x]) // Centro en el plano inferior (x, y)
        ) {
            return 1;
        }
    } // fin  if (x > 0 && x < 99 && y > 0 && y < 99 && z > 0 && z < 99 )
    return 0;
}


void GraphicPage ( int z , int brain[100][100][100]) { // funcion que grafica una pagina
    printf ("    ");// espacios para acomodar la apariencia
    for ( int k = 0 ; k < 100 ; k ++) { k   % 10 == 0? printf ("%i",  k  / 10  ) : printf (" "); } // ciclo que imprime la guia superior ( decenas )
    printf ("\n");
    printf ("    ");
    for ( int i = 0 ; i < 100 ; i ++) { printf ("%i" , i % 10 ); } // ciclo que imprime la guia superior 
    printf ("\n\n");
     for ( int y = 0 ; y < 100 ; y ++ ){ // ciclo que imprime las filas
        y < 10 ? printf (" %i  " , y ) : printf ("%i  " , y ); // condicion para imprimir las guias de las filas
        for ( int x = 0 ; x < 100 ; x ++ ) { // imprime un caracter o otro dependiendo si el punto cumple las condiciones
        if ( ( AnalyzePoint ( z , y , x , brain ) &&  AnalyzePoint ( z , y , x + 1 , brain ) && AnalyzePoint ( z , y , x + 2 , brain ) )
          ||  ( AnalyzePoint ( z , y , x , brain ) &&  AnalyzePoint ( z , y , x - 1 , brain ) && AnalyzePoint ( z , y , x + 1 , brain ) )
           ||  ( AnalyzePoint ( z , y , x , brain ) &&  AnalyzePoint ( z , y , x - 1 , brain ) && AnalyzePoint ( z , y , x - 2 , brain ) )
        ) {
            printf ("%c" , 49 ); // imprime si el punto esta en una linea sospechosa
        }else printf ("%c", 48); // imprime si no esta en una linea sospechosa
        } // fin for ( int x = 0 ; x < 100 ; x ++ ) 
         printf ("\n");
    } // rin for ( int y = 0 ; y < 100 ; y ++ )
}




int PointConter ( int z , int brain[100][100][100]){ // funcion que cuenta los puntos sospechoso
    int counter = 0; // contador de puntos
    for ( int y = 0 ; y < 100 ; y ++ ){
        for ( int x = 0 ; x < 100 ; x ++ ) // ciclos anidados que pasan por toda la pagina
        if ( AnalyzePoint ( z , y , x , brain )) counter ++; // si el punto actual es sospechoso suma al contador
    }
    return counter; // devuelve el contador
}

int LineCounter ( int z , int brain [100][100][100]) { // funcion que cuenta las lineas
    int counter = 0; // contador de lineas
    for ( int y = 0 ; y < 100  ; y ++ ) { // ciclo que recorre todas las filas
        int contarPuntos = 0; // contador de puntos por fila
        for ( int x = 0 ; x < 100 ; x ++ ){ // ciclo que recorre cada columna de una fila
            if ( contarPuntos == 3 ) counter ++; // si hay 3 puntos consecutivos se forma una linea
            if ( AnalyzePoint ( z , y , x , brain ) ) { contarPuntos ++; } else contarPuntos = 0; // si hay un punto se le soma uno al contador de puntos y si no se hace 0 ( rompe linea)
        }
    } return counter; // retorna el contador de lineas
}

void PrintPoint ( int z , int y , int x , int brain [100][100][100] , int mid ) { // funcion que imprime la informacion de un punto en una pagina
    int punto [9] = { brain [z][ y - 1 ][ x - 1 ] , brain [z][ y - 1 ][ x ] , brain [z][ y - 1 ][ x + 1 ] ,
    brain [z][ y ][ x - 1 ] , brain [z][ y ][ x ] , brain [z][ y ][ x + 1 ] ,
    brain [z][ y + 1 ][ x - 1 ] , brain [z][ y + 1 ][ x ] , brain [z][ y + 1 ][ x + 1 ] 
    }; // se asignacion de los valores a un array diferente
    printf ("\n");
    for ( int i = 0 ; i < 9 ; i ++ ) { // ciclo que pasa por todas las posiciones del arrayd
        mid == 1 && i == 4 ? printf ("| XX |" ): printf ("| %i |" , punto [i] ); // condicion para saber si se esta imprimiendo el punto
        if ( i == 2 || i == 5 ) printf ("\n"); // salto de lineas
        
    }
}

int getNumber (  char l  ) { // obtener un valor ingresado por el usuario 
    int x = 0;
    printf ("Ingrese un valor de %c " , l );
    scanf ("%i" , &x);
    if ( x < 1 || x > 98 ) { // condiciones 
        printf ("Valor Incorrecto \n");
        getNumber ( l ); // llamado recursivo
    } else return x; // retorna x cuando el valor sea correcto
}
int main()
{   srand ( time(NULL)); // se plantea la semilla 
    int brain [100][100][100]; // se define el arrayd
    RandomBrain ( brain ); // funcion que le da un valor aleatorio a cada posicion
    int menu = 1; // variable para establecer la permanencia del switch
    
    
    /* printf ("%i     %i\n" , AnalyzePoint ( 9 , 9 , 93 , brain) , PointConter ( 4 , brain ));
    GraphicPage ( 5 , brain);
    printf ("%i" , LineCounter ( 5 , brain));
    PrintPoint ( 4 , 4 , 3 , brain , 0  );
    printf ("\n       Z-1");
    PrintPoint ( 5 , 4 , 3 , brain , 1  );
    printf ("\n        Z");
    PrintPoint ( 6 , 4 , 3 , brain , 0  );
    printf ("\n       Z+1"); */
    
    while ( menu ) { // menu re utilizable
        int opcion = 0; // variable para guardar la opcion
        printf (" Menu De Opciones \n");
        printf (" 0 - Finalizar el Programa \n");
        printf (" 1 - Analizar punto ( x , y , z ) \n");
        printf (" 2 - Analizar Plano ( z )  \n");
        printf (" 3 - Mostrar informe de todos los planos con puntos y líneas sospechosas \n");
        scanf ( "%i" , &opcion);
        switch(opcion){ // caso para cada opcion
            case 0: menu = 0; // se acaba el programa
            break;
            case 1: int z = 0 , y = 0 , x = 0;
            z = getNumber ('z');
            y = getNumber ('y');
            x = getNumber ('x'); // se definen y asignan los valores necesarios
            AnalyzePoint ( z , y , x , brain) ? printf ("punto sospechoso") : printf ("Punto no sospechoso"); // funcion que analiza si un punto es sospechoso
            PrintPoint ( z - 1 , y , x , brain , 0 );
            printf ("\n      Z-1");
            PrintPoint ( z , y , x , brain , 1 );
            printf ("\n       Z");
            PrintPoint ( z + 1 , y , x , brain , 0 );
            printf ("\n      Z+1\n"); // se imprimen los 3 planos z-1 , z , z+1
            break;
            case 2: int ñ = 0;
            ñ = getNumber ('z'); // se recibe el valor deseado
            GraphicPage( ñ , brain); // funcion que grafica la pagina
            break;
            case 3: 
            for ( int m = 0 ; m < 100 ; m ++){ // ciclo que muestra la informacion de todas las paginas
                printf ("Pagina %i      Puntos:%i      Lineas:%i     \n" , m , PointConter ( m , brain) , LineCounter ( m , brain ));
            }
            break;
            default: printf ("Opcion No Valida \n"); // opcion incorrecta en el menu 
            break;
        }
        
        
    };
    

    return 0;
    
}
