#include "pecaI.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

/*               Peca S Estado 0              Peça S Estado 1
                       [][]                          []
bloco de referencia->[][]                            [][]
                                  bloco de referencia->[]
*/

void moveSDireita0();
void moveSDireita1();
void moveSEsquerda0();
void moveSEsquerda1();
void caiS0();
void caiS1();
void rotateS1to0();
void rotateS0to1();
void rotateS();
void caiS();
void moveSEsquerda();
void moveSDireita();

static bool state = 0;

void rotateS(){
    if(state == 1&&y>1){
        rotateS1to0();
    }
    else if(y>1){
        rotateS0to1();
    }
}

void caiS(){
    if(state==0){
        caiS0();
    }
    else if(state==1){
        caiS1();
    }
}

void moveSEsquerda(){
    if(state == 0){
        moveSEsquerda0();
    }
    else if(state == 1){
        moveSEsquerda1();
    }
}

void moveSDireita(){
    if(state == 0){
        moveSDireita0();
    }
    else if(state == 1){
        moveSDireita1();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateS0to1(){
    if(matriz_consulta[y-2][x]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-3][x-1]==0&&
       y>0&&x>0){
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-2][x-1]);
        pintaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-2][x-1]=1;
        matriz_consulta[y-3][x-1]=1;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x+2]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x+2]=0;
        matriz_consulta[y-2][x+1]=0;
        gx_system_canvas_refresh();
        state=1;
    }
}

void rotateS1to0(){
    if(matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-2][x+2]==0&&
       x<7){
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-2][x-1]);
        limpaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-2][x-1]=0;
        matriz_consulta[y-3][x-1]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-2][x+2]=1;
        state=0;
        gx_system_canvas_refresh();
           }
}

void caiS0(){
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
        pintaBloco(matriz[y-1][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y][x+1]=1;
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||(
            matriz_consulta[y][x]==1||
            matriz_consulta[y][x+1]==1||
            matriz_consulta[y-1][x+2]==1))
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
        pintaBloco(matriz[y-1][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y][x+1]=1;
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x]=0;
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-2][x+1]=0;
        limpaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-2][x+2]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiS1(){
    if((y==0)&&matriz_consulta[y][x]){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if((y==1)&&(matriz_consulta[y][x]||
            matriz_consulta[y-1][x-1])){
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
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y-1][x-1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y-1][x-1]=1;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||
            matriz_consulta[y-1][x-1]==1)
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
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y-1][x-1]=1;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        limpaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-3][x-1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void moveSEsquerda0(){
    if(x>0&&matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x]==0){
        pintaBloco(matriz[y-1][x-1]);
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-1][x+1]=0;
        pintaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-2][x+2]=0;
        x--;
    }
}

void moveSEsquerda1(){
    if(x>1&& matriz_consulta[y-1][x-1]==0&&
    matriz_consulta[y-2][x-2]==0&&
    matriz_consulta[y-3][x-2]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-2]);
    pintaBloco(matriz[y-3][x-2]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x-1]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-2]=1;
    matriz_consulta[y-3][x-2]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x-1]=0;
    x--;
    }
}

void moveSDireita0(){
    if(x<7&&
        matriz_consulta[y-1][x+2]==0&&
        matriz_consulta[y-2][x+3]==0){
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-2][x+3]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+3]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x+1]=0;
        x++;
    }
}

void moveSDireita1(){
    if(x<9&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-3][x]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+1]);
    pintaBloco(matriz[y-3][x]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x-1]);
    limpaBloco(matriz[y-3][x-1]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-3][x]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x-1]=0;
    matriz_consulta[y-3][x-1]=0;
    x++;
    }
}
