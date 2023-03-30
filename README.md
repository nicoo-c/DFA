# Simulación de un autómata finito no determinista

El programa cuenta con dos funciones para simular el autómata, la primera de forma aleatoria, para esta solo se debe ingresar el número de estados que desea simular.

La segunda permite simular un autómata específico, este debe ser explicitado previo a la ejecución del programa en **un archivo de texto llamado automata.txt** ,el formato es el siguiente:

- Los estados deben enumerarse desde 0.
- El alfabeto es el único elemento que puede ser no númerico, los demás elementos deben ser númericos, no se aceptan estados del tipo 'q0' o '2a'.  
- Los estados finales deben marcarse con * seguido del estado.  
- El estado inicial es el estado 0.  

Sean 0, 1, 2, 3, 4 los estados, con estados finales {2, 4} y {a, b} el alfabeto. (0 estado inicial)

*Formato de automata.txt:*

        ;a;b;
    0   ;2;3;
    1   ;0;1;
    *2  ;4;1;
    3   ;2;0;
    *4  ;4;3;
