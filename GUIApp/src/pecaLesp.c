#include "pecaLesp.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

/*        Peca L Espelhada Estado 0              Peça L Espelhada Estado 1
                       []                                 [][][]
                       []                bloco de referencia->[]
bloco de referencia->[][]

          Peca L Espelhada Estado 2              Peca L Espelhada Estado 3
                     [][]                              []
                     []           bloco de referencia->[][][]
bloco de referencia->[]
 */

void moveLespDireita0();
void moveLespDireita1();
void moveLespDireita2();
void moveLespDireita3();
void moveLespEsquerda0();
void moveLespEsquerda1();
void moveLespEsquerda2();
void moveLespEsquerda3();
void caiLesp0();
void caiLesp1();
void caiLesp2();
void caiLesp3();
void rotateLesp0to1();
void rotateLesp1to2();
void rotateLesp2to3();
void rotateLesp3to0();
void rotateLesp();
void caiLesp();
void moveLespEsquerda();
void moveLespDireita();
static int state = 0;


void rotateLesp(){
    if((state == 0||state > 3)&&y<1){
        rotateLesp0to1();
    }
    else if(state == 1&&y>0){
        rotateLesp1to2();
    }
    else if(state==2&&y>1){
        rotateLesp2to3();
    }
    else if(state==3&&y>0){
        rotateLesp3to0();
    }
}

void caiLesp(){
    if(state==0||state > 3){
        caiLesp0();
    }
    else if(state==1){
        caiLesp1();
    }
    else if(state==2){
        caiLesp2();
    }
    else if(state==3){
        caiLesp3();
    }
}

void moveLespEsquerda(){
    if(state == 0||state > 3){
        moveLespEsquerda0();
    }
    else if(state == 1){
        moveLespEsquerda1();
    }
    else if(state == 2){
        moveLespEsquerda2();
    }
    else if(state == 3){
        moveLespEsquerda3();
    }
}

void moveLespDireita(){
    if(state == 0||state > 3){
        moveLespDireita0();
    }
    else if(state == 1){
        moveLespDireita1();
    }
    else if(state == 2){
        moveLespDireita2();
    }
    else if(state == 3){
        moveLespDireita3();
    }
}

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void rotateLesp0to1(){
    if(matriz_consulta[y-2][x]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-2][x-2]==0&&
       x>1){
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-2][x-1]);
        pintaBloco(matriz[y-2][x-2]);
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-2][x-1]=1;
        matriz_consulta[y-2][x-2]=1;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x+1]=0;
        matriz_consulta[y-3][x+1]=0;
        gx_system_canvas_refresh();
        state=1;
    }
}

void rotateLesp1to2(){
    if(matriz_consulta[y-3][x]==0&&
       matriz_consulta[y-3][x+1]==0&&
       y>1&&x<8){
        limpaBloco(matriz[y-2][x-1]);
        limpaBloco(matriz[y-2][x-2]);
        matriz_consulta[y-2][x-1]=0;
        matriz_consulta[y-2][x-2]=0;
        pintaBloco(matriz[y-3][x]);
        pintaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-3][x]=1;
        matriz_consulta[y-3][x+1]=1;
        state=2;
        gx_system_canvas_refresh();
           }
}

void rotateLesp2to3(){
    if(matriz_consulta[y-1][x+2]==0&&
       matriz_consulta[y-1][x+1]==0&&
       x<7){
        limpaBloco(matriz[y-3][x]);
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-3][x+1]=0;
        matriz_consulta[y-3][x]=0;
        pintaBloco(matriz[y-1][x+1]);
        pintaBloco(matriz[y-1][x+2]);
        matriz_consulta[y-1][x+1]=1;
        matriz_consulta[y-1][x+2]=1;
        state=3;
        gx_system_canvas_refresh();
           }
}

void rotateLesp3to0(){
    if(matriz_consulta[y-2][x+1]==0&&
       matriz_consulta[y-3][x+1]==0&&
       y>3){
        limpaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-2][x]=0;
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-2][x+1]=1;
        matriz_consulta[y-3][x+1]=1;
        state=0;
        gx_system_canvas_refresh();
           }
}

void caiLesp0(){
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
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x]=0;
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
        limpaBloco(matriz[y-3][x+1]);
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-3][x+1]=0;
        matriz_consulta[y-1][x]=0;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiLesp1(){
    if(y==0&&matriz_consulta[y][x]==1){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==1&&(matriz_consulta[y][x]==1||
           matriz_consulta[y-1][x-1]==1||
           matriz_consulta[y-1][x-2]==1)){
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
        pintaBloco(matriz[y-1][x-2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-1][x-2]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1
            ||matriz_consulta[y-1][x-1]==1
            ||matriz_consulta[y-1][x-2]==1)
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
        pintaBloco(matriz[y-1][x-2]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-1][x-2]=1;
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x]=0;
        limpaBloco(matriz[y-2][x-1]);
        matriz_consulta[y-2][x-1]=0;
        limpaBloco(matriz[y-2][x-2]);
        matriz_consulta[y-2][x-2]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiLesp2(){
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
        pintaBloco(matriz[y-2][x+1]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-2][x+1]=1;
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y-2][x+1]==1)
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
        pintaBloco(matriz[y-2][x+1]);
        pintaBloco(matriz[y][x]);
        matriz_consulta[y][x]=1;
        matriz_consulta[y-2][x+1]=1;
        limpaBloco(matriz[y-3][x]);
        matriz_consulta[y-3][x]=0;
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-3][x+1]=0;
        gx_system_canvas_refresh();
        y++;
    }
}

void caiLesp3(){
    if((y==0||y==1)&&matriz_consulta[y][x]==1
        &&matriz_consulta[y][x+1]&&
        matriz_consulta[y][x+2]){
        limpaTela();
        gx_system_canvas_refresh();
        t=true;
        i=0;
    }
    else if(y==0){
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==1){
        matriz_consulta[y][x]=1;
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x+2]);
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-1][x+2]=0;
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x+2]);
        gx_system_canvas_refresh();
        y++;
    }
    else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y][x+1]==1||matriz_consulta[y][x+2]==1)
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
        matriz_consulta[y][x+1]=1;
        matriz_consulta[y][x+2]=1;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-1][x+2]=0;
        matriz_consulta[y-1][x+1]=0;
        pintaBloco(matriz[y][x+1]);
        pintaBloco(matriz[y][x]);
        pintaBloco(matriz[y][x+2]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-1][x+2]);
        gx_system_canvas_refresh();
        y++;
    }
}

void moveLespEsquerda0(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x]==0&&
       matriz_consulta[y-3][x]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x]);
        pintaBloco(matriz[y-3][x]);
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x]=1;
        matriz_consulta[y-3][x]=1;
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x+1]=0;
        matriz_consulta[y-3][x+1]=0;
        x--;
    }
}

void moveLespEsquerda1(){
    if(x>2&&
       matriz_consulta[y-2][x-3]==0&&
       matriz_consulta[y-1][x-1]==0){
        pintaBloco(matriz[y-1][x-1]);
        pintaBloco(matriz[y-2][x-3]);
        limpaBloco(matriz[y-2][x]);
        limpaBloco(matriz[y-1][x]);
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-2][x-3]=1;
        matriz_consulta[y-2][x]=0;
        matriz_consulta[y-1][x]=0;
        x--;
    }
}

void moveLespEsquerda2(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0&&
       matriz_consulta[y-3][x-1]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    pintaBloco(matriz[y-3][x-1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x+1]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-3][x-1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x+1]=0;
    x--;
    }
}
void moveLespEsquerda3(){
    if(x>0&&
       matriz_consulta[y-1][x-1]==0&&
       matriz_consulta[y-2][x-1]==0){
    pintaBloco(matriz[y-1][x-1]);
    pintaBloco(matriz[y-2][x-1]);
    limpaBloco(matriz[y-1][x+2]);
    limpaBloco(matriz[y-2][x]);
    matriz_consulta[y-1][x-1]=1;
    matriz_consulta[y-2][x-1]=1;
    matriz_consulta[y-1][x+2]=0;
    matriz_consulta[y-2][x]=0;
    x--;
    }
}

void moveLespDireita0(){
    if(x<8&&
       matriz_consulta[y-1][x+2]==0&&
       matriz_consulta[y-2][x+2]==0&&
       matriz_consulta[y-3][x+2]==0){
        pintaBloco(matriz[y-1][x+2]);
        pintaBloco(matriz[y-2][x+2]);
        pintaBloco(matriz[y-3][x+2]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x+1]);
        limpaBloco(matriz[y-3][x+1]);
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-2][x+2]=1;
        matriz_consulta[y-3][x+2]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x+1]=0;
        matriz_consulta[y-3][x+1]=0;
        x++;
    }
}

void moveLespDireita1(){
    if(x<9&&
       matriz_consulta[y-1][x+1]==0&&
       matriz_consulta[y-2][x+1]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x-2]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x-2]=0;
    x++;
    }
}

void moveLespDireita2(){
    if(x<8&&
      matriz_consulta[y-1][x+1]==0&&
      matriz_consulta[y-2][x+1]==0&&
      matriz_consulta[y-3][x+2]==0){
    pintaBloco(matriz[y-1][x+1]);
    pintaBloco(matriz[y-2][x+1]);
    pintaBloco(matriz[y-3][x+2]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    limpaBloco(matriz[y-3][x]);
    matriz_consulta[y-1][x+1]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-3][x+2]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    matriz_consulta[y-3][x]=0;
    x++;
    }
}

void moveLespDireita3(){
    if(x<7&&
       matriz_consulta[y-1][x+3]==0&&
       matriz_consulta[y-2][x+1]==0){
    pintaBloco(matriz[y-1][x+3]);
    pintaBloco(matriz[y-2][x+1]);
    limpaBloco(matriz[y-1][x]);
    limpaBloco(matriz[y-2][x]);
    matriz_consulta[y-1][x+3]=1;
    matriz_consulta[y-2][x+1]=1;
    matriz_consulta[y-1][x]=0;
    matriz_consulta[y-2][x]=0;
    x++;
    }
}
