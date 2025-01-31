#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "matrix_calculator_lib.h"
#include "calculation_options_lib.h"

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// PROCEDIMIENTOS QUE MANEJAN EL MENU DE OPCIONES
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void mostrarMenu(void) 
{
    printf("\n========== CALCULADORA DE MATRICES ==========\n");
    printf("Por favor, seleccione una opción:\n");
    printf("\n--- Operaciones Básicas ---\n");
    printf("'1': Sumar dos matrices\n");
    printf("'2': Restar dos matrices\n");
    printf("'3': Multiplicar dos matrices\n");
    printf("'4': Multiplicar matriz por escalar\n");
    
    printf("\n--- Operaciones Avanzadas ---\n");
    printf("'5': Calcular determinante\n");
    printf("'6': Calcular matriz transpuesta\n");
    printf("'7': Calcular matriz adjunta\n");
    printf("'8': Calcular matriz inversa\n");

    printf("\n'0': Salir\n");
    printf("\n=============================================\n");
    printf("Su elección:\t");
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

uint8_t obtenerOpcionMenu(void) 
{
    uint8_t opcion;
    do{
        mostrarMenu();
        scanf("%hhu", &opcion);
        if(opcion != 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7 && opcion != 8)
        {
            Beep(900,500);
            printf("\nSr Usuario: Se le explico claramente que opciones validas podia ingresar para realizar la operacion del menu que usted deseara.\nSin lugar a dudas, ¡A usted no le funciona la materia gris!\n");
        }
    }while(opcion != 0 && opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7 && opcion != 8);
    return opcion;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// PROCEDIMIENTOS QUE PREGUNTAN ACERCA DEL CARGADO Y EL GUARDADO DE LA MATRIZ RESULTADO
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

uint8_t preguntaSiCargar(void) // Pregunta si quiere CARGAR la matriz del archivo.
{
    uint8_t askCharging;
    do{
        printf("Ingrese si desea cargar la matriz resultado del archivo\n'1': SI\n'0': NO\nSu eleccion:\t");
        scanf("%hhu", &askCharging);
        if(askCharging != 1 && askCharging != 0)
        {
            Beep(900,500);
            printf("\nSr Usuario, se le explico claramente que debe seleccionar:\n'1' si desea cargar la matriz del archivo y '0' si no desea cargarla.\nSin lugar a dudas, ¡A usted no le funciona la materia gris!\n");
        }
    }while(askCharging != 1 && askCharging != 0);
    return askCharging;
}

char preguntaDondeCargar(void)
{
    char chargingPlace;
    do{
        printf("\nIngrese donde desea cargar la matriz del archivo:\n'A': Matriz A\n'B': Matriz B:\nSu eleccion:\t");
        scanf("%c", &chargingPlace);
        if(chargingPlace != 'A' && chargingPlace != 'B')
        {
            Beep(900,500);
            printf("\nSr Usuario, se le explico claramente que debe seleccionar:\n'A' si desea cargar la matriz del archivo en la Matriz A y 'B' si  desea cargar la matriz del archivo en la Matriz B.\nSin lugar a dudas, ¡A usted no le funciona la materia gris!\n");
        }
    }while(chargingPlace != 'A' && chargingPlace != 'B');
    return chargingPlace;
}

uint8_t preguntaSiGuardar(void)
{
    uint8_t askSaving;
    do{
        printf("Ingrese si desea guardar la matriz resultado en el archivo\n'1': SI\n'0': NO\nSu eleccion:\t");
        scanf("%hhu", &askSaving);
        if(askSaving != 1 && askSaving != 0)
        {
            Beep(900,500);
            printf("\nSr Usuario, se le explico claramente que debe seleccionar:\n'1' si desea guardar la matriz en el archivo y '0' si no desea guardarla.\nSin lugar a dudas, ¡A usted no le funciona la materia gris!\n");
        }
    }while(askSaving != 1 && askSaving != 0);
    return askSaving;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// PROCEDIMIENTOS QUE MANEJAN LAS OPERACIONES MATRICIALES
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void handle_matrix_addition() 
{
    printf("\n--- Suma de Matrices ---\n");

    uint8_t rows, cols;
    uint8_t askCharging, askSaving;
    
    // Pregunta si quiere CARGAR la matriz del archivo.
    askCharging = preguntaSiCargar();

    if(askCharging == 0) // NO desea CARGAR.
    {
        // Ingresa el numero de filas de las matrices.
        do{
            printf("\nIngresa el numero de filas de las matrices:\t");
            scanf("%hhu", &rows);
            if(rows == 0)
            {
                Beep(900,500);
                printf("\nSr Usuario: El numero de filas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
            }
            if(rows > 255)
            {
                Beep(900,500);
                printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
            }
        }while(rows == 0 || rows > 255);
        
        // Ingresa el numero de columnas de las matrices.
        do{
            printf("\nIngresa el numero de columnas de las matrices:\t");
            scanf("%hhu", &cols);
            if(cols == 0)
            {
                Beep(900,500);
                printf("\nSr Usuario: El numero de columnas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
            }
            if(cols > 255)
            {
                Beep(900,500);
                printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
            }
        }while(cols == 0 || cols > 255); 
    }

    if(askCharging == 1) // SI desea CARGAR.
    {
        leerDimensionesMatriz("matrizResultado.txt", &rows, &cols);
    }

    double** matrix_a = crearMatriz(rows, cols);
    double** matrix_b = crearMatriz(rows, cols);

    if(askCharging == 0)
    {
        printf("\nIngresa los elementos de la Matriz A:\n");
        llenarMatriz(matrix_a, rows, cols);
        printf("\nMatriz A:\n");
        mostrarMatriz(rows, cols, matrix_a);
        
        printf("\nIngresa los elementos de la Matriz B:\n");
        llenarMatriz(matrix_b, rows, cols);
        printf("\nMatriz B:\n");
        mostrarMatriz(rows, cols, matrix_b);
    }
    
    if(askCharging == 1)
    {
        cargarMatriz("matrizResultado.txt", &matrix_a, &rows, &cols);
        printf("\nMatriz A:\n");
        mostrarMatriz(rows, cols, matrix_a);

        printf("\nIngresa los elementos de la Matriz B:\n");
        llenarMatriz(matrix_b, rows, cols);
        printf("\nMatriz B:\n");
        mostrarMatriz(rows, cols, matrix_b);
    }

    double** result = crearMatriz(rows, cols);
    
    sumaDeMatrices(rows, cols, matrix_a, matrix_b, result);
    printf("\nResultado de la suma:\n");
    mostrarMatriz(result, rows, cols);

    askSaving = preguntaSiGuardar();
    if(askSaving == 1)
    {
        guardarMatriz(result, rows, cols, "matrizResultado.txt");
    }

    liberarMatriz(matrix_a, rows);
    liberarMatriz(matrix_b, rows);
    liberarMatriz(result, rows);

    matrix_a = NULL;
    matrix_b = NULL;
    result = NULL;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void handle_matrix_subtraction() 
{
    printf("\n--- Resta de Matrices ---\n");

    uint8_t rows, cols;
    printf("Ingresa el número de filas: ");
    scanf("%hhu", &rows);
    printf("Ingresa el número de columnas: ");
    scanf("%hhu", &cols);

    double** matrix_a = crearMatriz(rows, cols);
    double** matrix_b = crearMatriz(rows, cols);

    printf("\nIngresa los elementos de la primera matriz:\n");
    llenarMatriz(matrix_a, rows, cols);
    printf("\nIngresa los elementos de la segunda matriz:\n");
    llenarMatriz(matrix_b, rows, cols);

    double** result = restaDeMatrices(matrix_a, matrix_b, rows, cols);

    printf("\nResultado de la resta:\n");
    mostrarMatriz(result, rows, cols);

    liberarMatriz(matrix_a, rows);
    liberarMatriz(matrix_b, rows);
    liberarMatriz(result, rows);
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void handle_matrix_multiplication() 
{
    printf("\n--- Multiplicación de Matrices ---\n"); // Este printf lo agrego solo por estetica.
    
    // Declaro las variables fuera de las estructuras de control para poder seguir utilizandolas fuera de estas ultimas.
    uint8_t rows_a, N, cols_b;
    uint8_t askCharging, askSaving;
    char chargingPlace;
    
    // Pregunta si quiere CARGAR la matriz del archivo.
    askCharging = preguntaSiCargar();
    
    if(askCharging == 0) // NO desea CARGAR.
    {
        // Ingresa el numero de filas de la Matriz A.
        do{
            printf("\nIngresa el numero de filas de la Matriz A:\t");
            scanf("%hhu", &rows_a);
            if(rows_a == 0)
            {
                Beep(900,500);
                printf("\nSr Usuario: El numero de filas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
            }
            if(rows_a > 255)
            {
                Beep(900,500);
                printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
            }
        }while(rows_a == 0 || rows_a > 255);
        
        // Ingresa el numero de columnas de la Matriz A y el numero de filas de la Matriz B.
        do{
            printf("\nIngresa el numero de columnas de la Matriz A y el numero de columnas de la Matriz B:\t");
            scanf("%hhu", &N);
            if(N == 0)
            {
                Beep(900,500);
                printf("\nSr Usuario: El numero de filas y de columnas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
            }
            if(N > 255)
            {
                Beep(900,500);
                printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
            }
        }while(N == 0 || N > 255);
        
        // Ingresa el numero de columnas de la Matriz B.
        do{
            printf("\nIngresa el numero de columnas de la Matriz B:\t");
            scanf("%hhu", &cols_b);
            if(cols_b == 0)
            {
                Beep(900,500);
                printf("\nSr Usuario: El numero de columnas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
            }
            if(cols_b > 255)
            {
                Beep(900,500);
                printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
            }
        }while(cols_b == 0 || cols_b > 255); 
    }
    
    if(askCharging == 1) // SI desea CARGAR.
    {
        // Pregunta donde quiere CARGAR la matriz.
        chargingPlace = preguntaDondeCargar();
        
        // La matriz proveniente del archivo se carga en la Matriz A.
        if(chargingPlace == 'A')
        {
            // Lee del archivo las dimensiones de la Matriz A.
            leerDimensionesMatriz("matrizResultado.txt", &rows_a, &N);
            // Ingresa el numero de columnas de la Matriz B.
            do{
                printf("\nIngresa el numero de columnas de la Matriz B:\t");
                scanf("%hhu", &cols_b);
                if(cols_b == 0)
                {
                    Beep(900,500);
                    printf("\nSr Usuario: El numero de columnas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
                }
                if(cols_b > 255)
                {
                    Beep(900,500);
                    printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
                }
            }while(cols_b == 0 || cols_b > 255); 
        }
        
        // La matriz proveniente del archivo se carga en la Matriz B.
        if(chargingPlace == 'B')
        {
            // Ingresa el numero de filas de la Matriz A.
            do{
                printf("\nIngresa el numero de filas de la Matriz A:\t");
                scanf("%hhu", &rows_a);
                if(rows_a == 0)
                {
                    Beep(900,500);
                    printf("\nSr Usuario: El numero de filas de una matriz es estrictamente positivo.\nSin lugar a dudas, ¡Usted es retrasado!\n");
                }
                if(rows_a > 255)
                {
                    Beep(900,500);
                    printf("\nSr Usuario: Esta calculadora soporta como mucho matrices de 255x255. Disculpe los inconvenientes.\n");
                }
            }while(rows_a == 0 || rows_a > 255);
            // Lee del archivo las dimensiones de la Matriz B.
            leerDimensionesMatriz("matrizResultado.txt", &N, &cols_b);
        }
    }

    // Declaro las Matrices A y B.
    double** matrix_a = crearMatriz(rows_a, N);
    double** matrix_b = crearMatriz(N, cols_b);

    if(askCharging == 0) // NO desea CARGAR.
    {
        // Llena y Muestra la Matriz A.
        printf("\nIngresa los elementos de la Matriz A:\n");
        llenarMatriz(rows_a, N, matrix_a);
        printf("\nMatriz A:\n");
        mostrarMatriz(rows_a, N, matrix_a);
        // Llena y Muestra la Matriz B.
        printf("\nIngresa los elementos de la Matriz B:\n");
        llenarMatriz(N, cols_b, matrix_b);
        printf("\nMatriz B:\n");
        mostrarMatriz(N, cols_b, matrix_b);
    }
    
    if(askCharging == 1) // SI desea CARGAR.
    {
        // La matriz proveniente del archivo se carga en la Matriz A.
        if(chargingPlace == 'A')
        {
            // Carga y Muestra la Matriz A.
            cargarMatriz("matrizResultado.txt", &matrix_a, &rows_a, &N);
            printf("\nMatriz A:\n");
            mostrarMatriz(rows_a, N, matrix_a);
            // Llena y Muestra la Matriz B.
            printf("\nIngresa los elementos de la Matriz B:\n");
            llenarMatriz(N, cols_b, matrix_b);
            printf("\nMatriz B:\n");
            mostrarMatriz(N, cols_b, matrix_b);
        }
        
        // La matriz proveniente del archivo se carga en la Matriz B.
        if(chargingPlace == 'B')
        {
            // Llena y Muestra la Matriz A.
            printf("\nIngresa los elementos de la Matriz A:\n");
            llenarMatriz(rows_a, N, matrix_a);
            printf("\nMatriz A:\n");
            mostrarMatriz(rows_a, N, matrix_a);
            // Carga y Muestra la Matriz B.
            cargarMatriz("matrizResultado.txt", &matrix_b, &N, &cols_b);
            printf("\nMatriz B:\n");
            mostrarMatriz(N, cols_b, matrix_b);
        }

    }
    
    // Declaro la Matriz Resultado.
    double** result = crearMatriz(rows_a, cols_b);
    
    // Calculo el producto de Matrices.
    productoDeMatrices(rows_a, cols_b, N, matrix_a, matrix_b, result);

    // Muestro la Matriz Resultado.
    printf("\nResultado de la multiplicación:\n");
    mostrarMatriz(rows_a, cols_b, result);

    // Pregunta si quiere GUARDAR la matriz del archivo.
    askSaving = preguntaSiGuardar();

    if(askSaving == 1) // SI desea GUARDAR.
    {
        guardarMatriz(result, rows_a, cols_b, "matrizResultado.txt");
    }

    // Libero la memoria dinamica.
    liberarMatriz(matrix_a, rows_a);
    liberarMatriz(matrix_b, N);
    liberarMatriz(result, rows_a);

    // Quitando punteros residuales.
    matrix_a = NULL;
    matrix_b = NULL;
    result = NULL;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void handle_matrix_transpose() 
{
    printf("\n--- Transponer una Matriz ---\n");

    uint8_t rows, cols;
    printf("Ingresa el número de filas: ");
    scanf("%hhu", &rows);
    printf("Ingresa el número de columnas: ");
    scanf("%hhu", &cols);

    double** matrix = crearMatriz(rows, cols);

    printf("\nIngresa los elementos de la matriz:\n");
    llenarMatriz(matrix, rows, cols);

    double** result = transponerMatriz(matrix, rows, cols);

    printf("\nResultado de la transposición:\n");
    mostrarMatriz(result, cols, rows);

    liberarMatriz(matrix, rows);
    liberarMatriz(result, cols);
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //

void handle_matrix_determinant() 
{
    printf("\n--- Determinante de una Matriz ---\n");

    uint8_t size;
    printf("Ingresa el tamaño de la matriz (cuadrada): ");
    scanf("%hhu", &size);

    double** matrix = crearMatriz(size, size);

    printf("\nIngresa los elementos de la matriz:\n");
    llenarMatriz(matrix, size, size);

    double determinant = calcularDeterminante(matrix, size);

    printf("\nEl determinante de la matriz es: %d\n", determinant);

    liberarMatriz(matrix, size);
}
