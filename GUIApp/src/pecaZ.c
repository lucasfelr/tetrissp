#include "pecaI.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

/*               Peca S Estado 0                  Peça S Estado 1
                     [][]                               []
  bloco de referencia->[][]                           [][]
                                 bloco de referencia->[]
*/

void moveZDireita0();
void moveZDireita1();
void moveZEsquerda0();
void moveZEsquerda1();
void caiZ0();
void caiZ1();
void rotateZ1to0();
void rotateZ0to1();
void rotateZ();
void caiZ();
void moveZEsquerda();
void moveZDireita();

static bool state = 0;

void rotateZ(){
    if(state == 1&&y>1){
        rotateZ1to0();
    }
    else if(y>1){
        rotateZ0to1();
    }
}

void caiZ(){
    if(state==0){
        caiZ0();
    }
    else if(state==1){
        caiZ1();
    }
}

void moveZEsquerda(){
    if(state == 0){
        moveZEsquerda0();
    }
    else if(state == 1){
        moveZEsquerda1();
    }
}

void moveZDireita(){
    if(state == 0){
        moveZDireita0();
    }
    else if(state == 1){
        moveZDireita1();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateZ0to1(){
    if(matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-3][x+1]==0&&
       y>1){
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-3][x+1]=1;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x-1]=0;
        gx_system_canvas_refresh();
        state=1;
    }
}

void rotateZ1to0(){
    if(matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x-1]==0&&
       x>1){
        limpaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-2][x+1]=0;
        matriz_consulta[y-3][x+1]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-2][x-1]=1;
        state=0;
        gx_system_canvas_refresh();
           }
}

void caiZ0(){
    if(y==0&&
       matriz_consulta[y][x]==1&&
       matriz_consulta[y][x+1]==1){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        gx_system_canvas_refresh();
        y++;
            }
    else if(y==1){
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y][x+1]=1;
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||(
            matriz_consulta[y][x]==1||
            matriz_consulta[y][x+1]==1||
            matriz_consulta[y-1][x-1]==1))
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
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y][x+1]=1;
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=0;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiZ1(){
    if((y==0)&&matriz_consulta[y][x]){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    if((y==1)&&matriz_consulta[y][x]&&
        matriz_consulta[y-1][x+1]){
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
        pintaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        pintaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=1;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||
            matriz_consulta[y-1][x+1]==1)
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
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        pintaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=1;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-3][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void moveZEsquerda0(){
    if(x>1&&matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-2]==0){
        pintaBloco(matriz[y-1][x-1]);
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-1][x+1]=0;
        pintaBloco(matriz[y-2][x-2]);
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x-2]=1;
        matriz_consulta[y-2][x]=0;
        x--;
    }
}

void moveZEsquerda1(){
    if(x>0&& matriz_consulta[y-1][x-1]==0&&
    matriz_consulta[y-2][x-1]==0&&
    matriz_consulta[y-3][x]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    pintaBloco(matriz[y-3][x]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x+1]);
    limpaBloco(matriz[y-3][x+1]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-3][x]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x+1]=0;
    matriz_consulta[y-3][x+1]=0;
    x--;
    }
}

void moveZDireita0(){
    if(x<8&&
        matriz_consulta[y-1][x+2]==0&&
        matriz_consulta[y-2][x+1]==0){
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x-1]=0;
        x++;
    }
}

void moveZDireita1(){
    if(x<8&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+2]==0&&
       matriz_consulta[y-3][x+2]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+2]);
    pintaBloco(matriz[y-3][x+2]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x+1]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+2]=1;
    matriz_consulta[y-3][x+2]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x+1]=0;
    x++;
    }
}
