#include "pecaL.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

/*             Peca L Estado 0                     Peça L Estado 1
                     []                                     []
                     []           bloco de referencia-> [][][]
bloco de referencia->[][]

               Peca L Estado 2                      Peca L Estado 3
                   [][]                                [][][]
                     []           bloco de referencia->[]
bloco de referencia->[]
 */

void moveLDireita0();
void moveLDireita1();
void moveLDireita2();
void moveLDireita3();
void moveLEsquerda0();
void moveLEsquerda1();
void moveLEsquerda2();
void moveLEsquerda3();
void caiL0();
void caiL1();
void caiL2();
void caiL3();
void rotateL0to1();
void rotateL1to2();
void rotateL2to3();
void rotateL3to0();
void rotateL();
void caiL();
void moveLEsquerda();
void moveLDireita();
static int state = 0;



void rotateL(){
    if((state == 0||state > 3)&&y>1){
        rotateL0to1();
    }
    else if(state == 1&&y>0){
        rotateL1to2();
    }
    else if(state==2&&y>1){
        rotateL2to3();
    }
    else if(state==3&&y>0){
        rotateL3to0();
    }
}

void caiL(){
    if(state==0||state > 3){
        caiL0();
    }
    else if(state==1){
        caiL1();
    }
    else if(state==2){
        caiL2();
    }
    else if(state==3){
        caiL3();
    }
}

void moveLEsquerda(){
    if(state == 0||state > 3){
        moveLEsquerda0();
    }
    else if(state == 1){
        moveLEsquerda1();
    }
    else if(state == 2){
        moveLEsquerda2();
    }
    else if(state == 3){
        moveLEsquerda3();
    }
}

void moveLDireita(){
    if(state == 0||state > 3){
        moveLDireita0();
    }
    else if(state == 1){
        moveLDireita1();
    }
    else if(state == 2){
        moveLDireita2();
    }
    else if(state == 3){
        moveLDireita3();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateL0to1(){
    if(matriz_consulta[y-1][x+2]==0&&
       matriz_consulta[y-2][x+2]==0&&
       x<8){
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+2]=1;
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        gx_system_canvas_refresh();
        state=1;
    }
}

void rotateL1to2(){
    if(matriz_consulta[y-2][x]==0&&
       matriz_consulta[y-3][x]==0&&
       matriz_consulta[y-3][x-1]==0&&
       y>1&&x>0){
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-2][x+2]=0;
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-3][x]);
        pintaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-3][x]=1;
        matriz_consulta[y-3][x-1]=1;
        state=2;
        gx_system_canvas_refresh();
           }
}

void rotateL2to3(){
    if(matriz_consulta[y-2][x+2]==0&&
       matriz_consulta[y-2][x+1]==0&&
       y>1&&x<8){
        limpaBloco(matriz[y-3][x]);
        limpaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-3][x-1]=0;
        matriz_consulta[y-3][x]=0;
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-2][x+2]=1;
        state=3;
        gx_system_canvas_refresh();
           }
}

void rotateL3to0(){
    if(matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-3][x]==0&&
       y>2&&x<9){
        limpaBloco(matriz[y-2][x+2]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-2][x+2]=0;
        matriz_consulta[y-2][x+1]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-3][x]=1;
        state=0;
        gx_system_canvas_refresh();
           }
}

void caiL0(){
    if((y>=0&&y<=2)&&
       (matriz_consulta[y][x]==1||
       matriz_consulta[y][x+1]==1)){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==1||y==2){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||
            matriz_consulta[y][x]==1||
            matriz_consulta[y][x+1]==1)
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
        limpaBloco(matriz[y-3][x]);
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-3][x]=0;
        matriz_consulta[y-1][x+1]=0;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiL1(){
    if((y==0||y==1)&&(matriz_consulta[y][x]==1||
       matriz_consulta[y][x+1]==1||
       matriz_consulta[y][x+2]==1)){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==1){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x]=0;
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1
            ||matriz_consulta[y][x+1]==1
            ||matriz_consulta[y][x+2]==1)
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
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x]=0;
        limpaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-1][x+1]=0;
        limpaBloco(matriz[y-2][x+2]);
        matriz_consulta[y-2][x+2]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiL2(){
    if((y>=0&&y<=2)&&matriz_consulta[y][x]==1){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0||y==1){
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-2][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-2][x-1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y-2][x-1]==1)
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
        pintaBloco(matriz[y-2][x-1]);
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-2][x-1]=1;
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=0;
        limpaBloco(matriz[y-3][x-1]);
        matriz_consulta[y-3][x-1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiL3(){
    if((y==0||y==1)&&matriz_consulta[y][x]==1){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        matriz_consulta[y][x]=1;
        pintaBloco(matriz[y][x]);
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==1){
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x+2]=1;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x+2]);
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y-1][x+1]==1||matriz_consulta[y-1][x+2]==1)
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
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+2]=0;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-2][x+1]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-2][x+2]);
        gx_system_canvas_refresh();
        y++;
    }
}

void moveLEsquerda0(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-3][x-1]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x-1]);
        pintaBloco(matriz[y-3][x-1]);
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x-1]=1;
        matriz_consulta[y-3][x-1]=1;
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        x--;
    }
}

void moveLEsquerda1(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x+1]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-2][x+2]);
        limpaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-2][x+2]=0;
        matriz_consulta[y-1][x+2]=0;
        x--;
    }
}

void moveLEsquerda2(){
    if(x>1&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-3][x-2]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    pintaBloco(matriz[y-3][x-2]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-3][x-2]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x]=0;
    x--;
    }
}
void moveLEsquerda3(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x+2]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x+2]=0;
    x--;
    }
}

void moveLDireita0(){
    if(x<8&&
       matriz_consulta[y-1][x+2]==0&&
       matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-3][x+1]==0){
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-3][x+1]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-3][x+1]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        x++;
    }
}

void moveLDireita1(){
    if(x<7&&
       matriz_consulta[y-1][x+3]==0&&
       matriz_consulta[y-2][x+3]==0){
    pintaBloco(matriz[y-1][x+3]);
    pintaBloco(matriz[y-2][x+3]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x+2]);
    matriz_consulta[y-1][x+3]=1;
    matriz_consulta[y-2][x+3]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x+2]=0;
    x++;
    }
}

void moveLDireita2(){
    if(x<9&&
      matriz_consulta[y-1][x+1]==0&&
      matriz_consulta[y-2][x+1]==0&&
      matriz_consulta[y-3][x+1]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+1]);
    pintaBloco(matriz[y-3][x+1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x-1]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-3][x+1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x-1]=0;
    x++;
    }
}

void moveLDireita3(){
    if(x<7&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+3]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+3]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+3]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    x++;
    }
}
