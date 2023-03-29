/*
* Programadores: Jorge Bussh, Nicolás Miño
* Profesor: Rodrigo Abarzúa Ortiz
* Descripción: El programa genera la descripción instantanea de un string en un DFA, simulando la función de transición, 
*              ya sea este generado de forma aleatoria o mediante un archivo de texto. 
* Curso: Fundamentos de Ciencia de la Computación I
* Fecha: 4 de abril, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

void calc_dimension();
void construir_automata(char* alfabeto, bool* estado_aceptacion, int** func_transicion);
void emular_func_transicion(int estado_actual, char* alfabeto, int** func_transicion, bool* estado_aceptacion);
int buscar_alfabeto(char* alfabeto, char c);
void construir_automata_aleatorio(bool* estado_aceptacion, int** func_transicion);
void emular_func_transicion_aleatoria(int estado_actual, char* alfabeto, int** func_transicion, bool* estado_aceptacion);
char menu();
void imprimir_automata(char* alfabeto, int** func_transicion, bool* estado_aceptacion);

int nCols = -1;
int nFilas = 0;

int main()
{  
    char k = menu();

    if(k == '1'){

        char alfabeto[2] = {'0', '1'};
        char buffer[100];
        int estado_actual = 0;
        nCols = 2;
        printf("Ingrese la cantidad de estados que desea ingresar: ");
        scanf("%s", buffer);
        nFilas = atoi(buffer);
        getc(stdin);
        bool estado_aceptacion[nFilas];
        int** func_transicion = (int**)malloc(sizeof(int*) * nFilas);

        for(int i = 0; i < nFilas; i++) 
            func_transicion[i] = (int*)malloc(sizeof(int) * nCols);

        construir_automata_aleatorio(estado_aceptacion, func_transicion);
        imprimir_automata(alfabeto, func_transicion, estado_aceptacion);
        emular_func_transicion(estado_actual, alfabeto, func_transicion, estado_aceptacion);

        for (int i = 0; i < nFilas; i = i + 1) //limpiar memoria
            free(func_transicion[i]);
        free(func_transicion);


    }else if(k == '2'){

        calc_dimension();
   
        int estado_actual = 0;
        char alfabeto[nCols]; 
        bool estado_aceptacion[nFilas];
        int** func_transicion = (int**)malloc(sizeof(int*) * nFilas);

        for(int i = 0; i < nFilas; i++)

            func_transicion[i] = (int*)malloc(sizeof(int) * nCols);

        construir_automata(alfabeto, estado_aceptacion, func_transicion);

        emular_func_transicion(estado_actual, alfabeto, func_transicion, estado_aceptacion);

        for (int i = 0; i < nFilas; i = i + 1)
            free(func_transicion[i]);

        free(func_transicion);

    }else
        printf("\nNo te he entendido, adios chavalin.\n");
    
    return 0;
}

char menu(){

    char k;

    printf("1. Generar un automata aleatorio con los estados que desee.\n");
    printf("2. Ingresar el automata desde un archivo de texto.\n");
    scanf("%c%*c", &k);

    return k;

}

void calc_dimension(){

    FILE* f;
    f = fopen("1.txt", "r");

    char c; //para recorrer el archivo  

    c = fgetc(f);

    while(c != '\n'){

        if(c == ';')
            nCols++;
        c = fgetc(f);
        
    }

    nFilas++;

    while((c = fgetc(f)) != EOF){
        
        if(c == '\n')
            nFilas++;
             
    }

    fclose(f);
}

void construir_automata(char* alfabeto, bool* estado_aceptacion, int** func_transicion){

    FILE* f;
    int i = 0, j = 0, k = 0, l = 0, d = 0;
    char c, buffer[100]; //para recorrer el archivo

    for(i = 0; i < nFilas; i++)
        estado_aceptacion[i] = false;

    i = 0; 

    f = fopen("1.txt", "r");

    c = fgetc(f);
    
    while(c != ';')
        c = fgetc(f);     

    c = fgetc(f);

    while(c != '\n'){
        
        buffer[i] = c;
        i++;
        c = fgetc(f);

    }

    buffer[i + 1] = '\n';  
    
    i = 0;
    j = 0;
    l = 0;

    while(buffer[l] != '\n'){

        if(buffer[l] != ';'){
            alfabeto[j] = buffer[l];
            j++;
        }

        l++;
    }
        
    i = 0;
    j = -1;
    
    c = fgetc(f);

    int num, aux;

    while(c != EOF){

        if(c == '\n'){ //siguiente fila
            i++;
            j = -1;
        }

        if(c != ';' && j > - 1){ //siguiente columna  //caso leer char de numero ej: 5 

            if(isdigit(c)){

                num = num * 10;
                aux = c - '0'; 
                num = num + aux;
                
            }

        }else if(c == ';' && j > - 1){
            
            func_transicion[i][j] = num;
            num = 0;
            aux = 0;
            j++;
            
        }else if(c == ';'){

            num = 0;
            aux = 0;
            j++;

        }else if(c == '*')
            estado_aceptacion[i] = true;

        c = fgetc(f);

    }

    fclose(f);

    imprimir_automata(alfabeto, func_transicion, estado_aceptacion);

}

void emular_func_transicion(int estado_actual, char* alfabeto, int** func_transicion, bool* estado_aceptacion){   

    int i = 0, j = 0, n, c;
    char string[200], k;

    do{ 
        
        printf("Ingrese el string a evaluar en el automata: ");
        
        fgets(string, 200, stdin);
        n = strlen(string) - 1;

        printf("\n$");

        for(j = 0; j < n; j++){

            if(j == i){
                printf("q_{%d}", estado_actual);
                printf("%c", string[j]);
            }else
                printf("%c", string[j]);

            }

        printf(" \\vdash ");

        for(i = 0; i < n; i++){

            c = buscar_alfabeto(alfabeto, string[i]);
            
            if(c == -1){

                printf("\nEl simbolo ingresado no pertenece al alfabeto, intente nuevamente...\n");
                break;

            }else{

                estado_actual = func_transicion[estado_actual][c];

                for(j = 0; j < n; j++){

                    if(j == i){
                        printf("%c", string[j]);
                        printf("q_{%d}", estado_actual);
                    }else
                        printf("%c", string[j]);

                }

            }

            if(i != n - 1)
                printf(" \\vdash ");
        }

        printf("$\n\n");

        if(estado_aceptacion[estado_actual] == true)
            printf("Estado de aceptación del string %s\ttrue\n\n", string);
        else    
            printf("Estado de aceptación del string %s\tfalse\n\n", string);

        printf("1. Ingresar otro string.\n");
        printf("2. Salir del programa.\n");
        printf("Ingrese opcion: ");
        scanf("%c%*c", &k);

        estado_actual = 0;

    }while(k == '1');

}

int buscar_alfabeto(char* alfabeto, char c){

    for(int i = 0; i < nCols; i++){

        if(alfabeto[i] == c)
            return i;
    }

    return -1;
}

void imprimir_automata(char* alfabeto, int** func_transicion, bool* estado_aceptacion){

    int i, j, max = 0;

    printf("\nAlfabeto: {");
    for(i = 0; i < nCols; i++){
        
        if(i == nCols - 1)
            printf("%c}", alfabeto[i]);
        else
            printf("%c, ", alfabeto[i]);

    }

    printf("\nEstado inicial: {q0}\n");

    for(i = 0; i < nFilas; i++){

        if(estado_aceptacion[i] == true)
            max = i;

    }

    printf("Estado/s de aceptacion: {");

    for(i = 0; i < nFilas; i++){
    
            if(i == max){

                if(estado_aceptacion[i] == true)
                    printf("q%d}", i);

            }else{

                if(estado_aceptacion[i] == true)
                    printf("q%d, ", i);

            }

    }

    printf("\nFuncion de transicion:\n");

    for(i = 0; i < nCols; i++){

        printf("\t%c ", alfabeto[i]);

    }

    for(i = 0; i < nFilas; i++){
    
        printf("\n");
        printf("q%d\t", i);
        for(j = 0; j < nCols; j++)
            printf("q%d\t", func_transicion[i][j]);
    }
    printf("\n\n");

}

void construir_automata_aleatorio(bool* estado_aceptacion, int** func_transicion){

    bool k = false;

    srand(time(NULL));

    for(int i = 0; i < nFilas; i++)
    {
        for(int j = 0; j < nCols; j++)
        {
            func_transicion[i][j] = rand() % nFilas;
        }
    }
    
    estado_aceptacion:;
    for(int i = 0; i < nFilas; i++)
    {
        estado_aceptacion[i] = rand() % 2;
    }

    for(int i = 0; i < nFilas; i++){

        if(estado_aceptacion[i] == true)
            k = true;

    }

    if(k == false) //caso: no hay estados de aceptación
        goto estado_aceptacion;

}
