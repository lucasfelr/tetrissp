#include "pecaT.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

/*               Peca T Estado 0                     Peça T Estado 1
                       []                                     []
bloco de referencia->[][][]                                 [][]
                                         bloco de referencia->[]

               Peca L Estado 2                      Peca L Estado 3
                   [][][]                               []
bloco de referencia->[]                                 [][]
                                   bloco de referencia->[]
 */

void moveTDireita0();
void moveTDireita1();
void moveTDireita2();
void moveTDireita3();
void moveTEsquerda0();
void moveTEsquerda1();
void moveTEsquerda2();
void moveTEsquerda3();
void caiT0();
void caiT1();
void caiT2();
void caiT3();
void rotateT0to1();
void rotateT1to2();
void rotateT2to3();
void rotateT3to0();
void rotateT();
void caiT();
void moveTEsquerda();
void moveTDireita();
static int state = 0;


void rotateT(){
    if((state == 0||state > 3)&&y>0){
        rotateT0to1();
    }
    else if(state == 1&&y>1){
        rotateT1to2();
    }
    else if(state==2&&y>0){
        rotateT2to3();
    }
    else if(state==3&&y>1){
        rotateT3to0();
    }
}

void caiT(){
    if(state==0||state > 3){
        caiT0();
    }
    else if(state==1){
        caiT1();
    }
    else if(state==2){
        caiT2();
    }
    else if(state==3){
        caiT3();
    }
}

void moveTEsquerda(){
    if(state == 0||state > 3){
        moveTEsquerda0();
    }
    else if(state == 1){
        moveTEsquerda1();
    }
    else if(state == 2){
        moveTEsquerda2();
    }
    else if(state == 3){
        moveTEsquerda3();
    }
}

void moveTDireita(){
    if(state == 0||state > 3){
        moveTDireita0();
    }
    else if(state == 1){
        moveTDireita1();
    }
    else if(state == 2){
        moveTDireita2();
    }
    else if(state == 3){
        moveTDireita3();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateT0to1(){
    if(matriz_consulta[y-2][x]==0&&
       matriz_consulta[y-3][x]==0&&
       matriz_consulta[y-2][x-1]==0&&
       x>1){
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-3][x]);
        pintaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-3][x]=1;
        matriz_consulta[y-2][x-1]=1;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-2][x+1]=0;
        gx_system_canvas_refresh();
        state=1;
    }
}

void rotateT1to2(){
    if(matriz_consulta[y-2][x+1]==0&&
       x<8){
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=0;
        pintaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-2][x+1]=1;
        state=2;
        gx_system_canvas_refresh();
           }
}

void rotateT2to3(){
    if(matriz_consulta[y-3][x]==0&&
       y>1){
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        pintaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=1;
        state=3;
        gx_system_canvas_refresh();
           }
}

void rotateT3to0(){
    if(matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-1][x+2]==0&&
       x<7){
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x+2]=1;
        state=0;
        gx_system_canvas_refresh();
           }
}

void caiT0(){
    if((y==0)&&
       (matriz_consulta[y][x]==1||
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
        limpaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-1][x+2]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||
            matriz_consulta[y][x]==1||
            matriz_consulta[y][x+1]==1||
            matriz_consulta[y][x+2]==1)
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
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-2][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiT1(){
    if((y==0||y==1||y==2)&&(matriz_consulta[y][x]==1||
       matriz_consulta[y-1][x-1]==1)){
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
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1
            ||matriz_consulta[y-1][x-1]==1)
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
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiT2(){
    if((y==0)&&matriz_consulta[y][x]==1){
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
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x-1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y-1][x-1]==1||
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
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x-1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x-1]=1;
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-2][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiT3(){
    if((y==0)&&matriz_consulta[y][x]==1){
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
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x+1]);
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==2){
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-2][x+1]=0;
        limpaBloco(matriz[y-2][x+1]);
        gx_system_canvas_refresh();
        y++;
        }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y-1][x+1]==1)
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
                pontuacao+=10;
                update_score(ID_PONTUACAO, pontuacao);
            }
            linha=0;
        }

    }
    else {
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x+1]=1;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y-1][x+1]);
        matriz_consulta[y-2][x+1]=0;
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-3][x]=0;
        limpaBloco(matriz[y-3][x]);
        gx_system_canvas_refresh();
        y++;
    }
}

void moveTEsquerda0(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-2][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        x--;
    }
}

void moveTEsquerda1(){
    if(x>1&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-2]==0&&
       matriz_consulta[y-3][x-1]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x-2]);
        pintaBloco(matriz[y-3][x-1]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x-2]=1;
        matriz_consulta[y-3][x-1]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        x--;
    }
}

void moveTEsquerda2(){
    if(x>1&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-2]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-2]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x+1]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-2]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x+1]=0;
    x--;
    }
}
void moveTEsquerda3(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-3][x-1]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    pintaBloco(matriz[y-3][x-1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-3][x]);
    limpaBloco(matriz[y-2][x+1]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-3][x-1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-3][x]=0;
    matriz_consulta[y-2][x+1]=0;
    x--;
    }
}

void moveTDireita0(){
    if(x<7&&
       matriz_consulta[y-1][x+3]==0&&
       matriz_consulta[y-2][x+2]==0){
        pintaBloco(matriz[y-1][x+3]);
        pintaBloco(matriz[y-2][x+2]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-1][x+3]=1;
        matriz_consulta[y-2][x+2]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x+1]=0;
        x++;
    }
}

void moveTDireita1(){
    if(x<9&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-3][x+1]==0){
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-3][x+1]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x-1]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-3][x+1]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x-1]=0;
        matriz_consulta[y-3][x]=0;
        x++;
    }
}

void moveTDireita2(){
    if(x<8&&
      matriz_consulta[y-1][x+1]==0&&
      matriz_consulta[y-2][x+2]==0){
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-2][x+2]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-2][x+2]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x-1]=0;
        x++;
    }
}

void moveTDireita3(){
    if(x<8&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+2]==0&&
       matriz_consulta[y-3][x+1]==0){
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-2][x+2]);
        pintaBloco(matriz[y-3][x+1]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-2][x+2]=1;
        matriz_consulta[y-3][x+1]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-3][x]=0;
        x++;
    }
}
