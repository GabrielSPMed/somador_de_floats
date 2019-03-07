//
//  main.c
//  Lab01
//
//  Created by Gabriel Medeiros on 3/1/19.
//  Copyright © 2019 Gabriel Medeiros. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

void clear_string(char *str){
    int i =0;
    while (str[i]!='\0') {
        str[i] = '\0';
        i++;
    }
}

void clean_answer(char * str) {
    if (!strcmp(str, "0")) return;
    int i = strlen(str) - 1;
    while (1) {
        if (str[i] == '0') {
            str[i] = '\0';
        } else if (str[i] == '.'){
            str[i]='\0';
            break;
        }
        else break;
        i--;
    }
}
void add_char_to_string (char c, char * str){
    char *aux = malloc(1*sizeof(char));
    aux[0]=c;
    strcat(str, aux);
}

int opera_fsm(int atual, char next, char *aux){
    if (atual == 0){
        if (next>=48 && next<=57){
            add_char_to_string(next, aux);
            return 1;
        }
        else return -1;
    }
    else if (atual==-1){
        if (next == ' ') {
            return 0;
        } else return -1;
    }
    else if (atual == 1){
        if (next>=48 && next<=57){
            add_char_to_string(next, aux);
            return 1;
        }
        if (next=='.'){
            add_char_to_string(next, aux);
            return 2;
        }
        if (next == ' ' || next == '\n'){
            return 4;
        }
        else{
            clear_string(aux);
            return -1;
        }
    }
    else if (atual==2){
        if (next>=48 && next<=57){
            add_char_to_string(next, aux);
            return 3;
        }
        else{
            clear_string(aux);
            return -1;
        }
    }
    else{
        if (next>=48 && next<=57){
            add_char_to_string(next, aux);
            return 3;
        }
        if (next == ' ' || next == '\n'){
            return 4;
        } else {
            clear_string(aux);
            return -1;
        }
    }
}

int main() {
    char c;
    float accumulator=0; //soma dos numeros
    int pointer;//posicao na string original
    char *buffer_in= malloc(100*sizeof(char));
    char *aux = malloc(100* sizeof(char));
    
    
    for (int i=0; i<100; i++) buffer_in[i] = '\0';
    
    pointer = 0;
    do {
        c=getchar();
        buffer_in[pointer++] = c;
    } while (c != '\n');
    fsm maquina;
    maquina.estado_atual=0;
    
    pointer =0;
    
    while (buffer_in[pointer]!='\0'){
        maquina.estado_atual= opera_fsm(maquina.estado_atual, buffer_in[pointer], aux);
        if (maquina.estado_atual==4){
            maquina.estado_atual=0;
            accumulator = accumulator + atof(aux);
            clear_string(aux);
        }
        pointer++;
    }
    sprintf(aux, "%f", accumulator);
    clean_answer(aux);
    printf("%s\n", aux);
    
    
    
    return 0;
}
