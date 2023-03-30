# Simulación de cómputo en un autómata finito no determinista

El programa cuenta con dos funciones para simular el autómata, la primera de forma aleatoria, para esta solo se debe ingresar el número de estados que desea simular.

La segunda permite simular un autómata específico, este debe ser explicitado previo a la ejecución del programa en un archivo de texto llamado automata.txt , el formato es el siguiente:

- Los estados deben enumerarse desde 0.
- El alfabeto es el único elemento que puede ser no númerico, los demás elementos deben ser númericos, no se aceptan estados del tipo 'q0' o '2a'.  
- Los estados finales deben marcarse con * seguido del estado.  
- El estado inicial es el estado 0.  

Sea M un DFA con:
- Estados: {q0, q1, q2, q3, q4}  
- Estado inicial: {q0}  
- Estados finales: {q2, q4}  
- Alfabeto: {a, b}  
- Función de transición: especificada en automata.txt  

*Formato de automata.txt*:

        ;a;b;
    0   ;2;3;
    1   ;0;1;
    *2  ;4;1;
    3   ;2;0;
    *4  ;4;3;
