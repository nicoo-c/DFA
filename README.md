# Simulación de un autómata finito no determinista

El programa cuenta con dos funciones para simular el autómata, la primera de forma aleatoria, para esta solo se debe ingresar el número de estados que desea simular.

Si se desea simular un autómata específico, este se puede ingresar mediante un archivo de texto, el archivo de texto debe llamarse automata.txt y el formato es el siguiente:

Los estados deben empezar desde 0, donde 0 es el estado inicial. 
Sean 0, 1, 2, 3, 4 los estados, con estados finales {2, 4} y {a, b} el alfabeto.

        ;a;b;
    0   ;2;3;
    1   ;0;1;
    *2  ;4;1;
    3   ;2;0;
    *4  ;4;3;

Los estados finales deben marcarse con *
El estado inicial se asume como el estado 0
