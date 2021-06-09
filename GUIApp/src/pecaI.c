#include "pecaI.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>
/* Peca I Estado 0              Peça I Estado 1
     [][][][]                          []
     ^                                 []
     |                                 []
bloco de referencia                    []-> bloco de referencia
*/

void moveIDireita0();
void moveIDireita1();
void moveIEsquerda0();
void moveIEsquerda1();
void caiI0();
void caiI1();
void rotateI1to0();
void rotateI0to1();
void rotateI();
void caiI();
void moveIEsquerda();
void moveIDireita();

static bool state = 0;

void rotateI(){
    if(state == 0){
        rotateI0to1();
    }
    else if(state == 1&&y>2){
        rotateI1to0();
    }
}

void caiI(){
    if(state==0){
        caiI0();
    }
    else if(state==1){
        caiI1();
    }
}

void moveIEsquerda(){
    if(state == 0){
        moveIEsquerda0();
    }
    else if(state == 1){
        moveIEsquerda1();
    }
}

void moveIDireita(){
    if(state == 0){
        moveIDireita0();
    }
    else if(state == 1){
        moveIDireita1();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateI0to1(){
    if(matriz_consulta[y-3][x]==0&&
       matriz_consulta[y-2][x]==0&&
       matriz_consulta[y][x]==0&&
       y>0&&y<18){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-3][x]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y][x]=1;
        matriz_consulta[y-3][x]=1;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-1][x-1]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-1][x-1]=0;
        gx_system_canvas_refresh();
        state=1;
        y++;
    }
}

void rotateI1to0(){
    if(matriz_consulta[y-1][x+3]==0&&
       matriz_consulta[y-1][x+2]==0&&
       matriz_consulta[y-1][x+1]==0&&
       x>0&&x<8){
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-4][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=0;
        matriz_consulta[y-4][x]=0;
        matriz_consulta[y-2][x]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-1][x+3]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-1][x+3]=0;
        state=0;
        gx_system_canvas_refresh();
        x++;
           }
}

void caiI0(){
    if(y==0&&
       matriz_consulta[y][x]==1&&
       matriz_consulta[y][x+1]==1&&
       matriz_consulta[y][x+2]==1&&
       matriz_consulta[y][x-1]==1){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        pintaBloco(matriz[y][x-1]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        matriz_consulta[y][x-1]=1;
        gx_system_canvas_refresh();
        y++;
            }
    else if(y==20||(
            matriz_consulta[y][x]==1||
            matriz_consulta[y][x+1]==1||
            matriz_consulta[y][x+2]==1||
            matriz_consulta[y][x-1]==1))
    {
        y=0;
        x=4;
        peca1 = peca2;
        peca2 = rand()%7;
        for(int c=19;c>=0;c--){
            for (int d=0; d<10;d++){
                linha=linha+matriz_consulta[c][d];
            }
            if(linha==10){
                limpaLinha(c);
                gx_system_canvas_refresh();
                c++;
                mult++;
                pontuacao+=10*mult;
                update_score(ID_PONTUACAO, pontuacao);
            }
            linha=0;
        }

    }
    else{
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x-1]);
        limpaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-1][x-1]=0;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x-1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x-1]=1;
        matriz_consulta[y][x+2]=1;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiI1(){
    if((y>=0&&y<=3)&&matriz_consulta[y][x]){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==1){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==3){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1)
    {
        y=0;
        x=4;
        peca1 = peca2;
        peca2 = rand()%7;
        for(int c=19;c>=0;c--){
            for (int d=0; d<10;d++){
                linha=linha+matriz_consulta[c][d];
            }
            if(linha==10){
                limpaLinha(c);
                gx_system_canvas_refresh();
                c++;
                mult++;
                pontuacao+=10*mult;
                update_score(ID_PONTUACAO, pontuacao);
            }
            linha=0;
        }

    }
    else {
        limpaBloco(matriz[y-4][x]);
        matriz_consulta[y-4][x]=0;
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
}

void moveIEsquerda0(){
    if(x>1){
        pintaBloco(matriz[y-1][x-2]);
        limpaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x-2]=1;
        matriz_consulta[y-1][x+2]=0;
        x--;
    }
}

void moveIEsquerda1(){
    if(x>0){
    pintaBloco(matriz[y-4][x-1]);
    pintaBloco(matriz[y-3][x-1]);
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    limpaBloco(matriz[y-3][x]);
    limpaBloco(matriz[y-4][x]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    matriz_consulta[y-3][x-1]=1;
    matriz_consulta[y-4][x-1]=1;
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-3][x]=0;
    matriz_consulta[y-4][x]=0;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    x--;
    }
}

void moveIDireita0(){
    if(x<7&&
        matriz_consulta[y-1][x+3]==0){
        pintaBloco(matriz[y-1][x+3]);
        limpaBloco(matriz[y-1][x-1]);
        matriz_consulta[y-1][x+3]=1;
        matriz_consulta[y-1][x-1]=0;
        x++;
    }
}

void moveIDireita1(){
    if(x<9&&
       matriz_consulta[y-4][x+1]==0&&
       matriz_consulta[y-3][x+1]==0&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+1]==0){
    pintaBloco(matriz[y-4][x+1]);
    pintaBloco(matriz[y-3][x+1]);
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+1]);
    limpaBloco(matriz[y-4][x]);
    limpaBloco(matriz[y-3][x]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    matriz_consulta[y-4][x+1]=1;
    matriz_consulta[y-3][x+1]=1;
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-4][x]=0;
    matriz_consulta[y-3][x]=0;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    x++;
    }
}
