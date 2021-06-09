#include "peca.h"
#include "peca_entry.h"
#include "quadrado.h"
#include "pecaI.h"
#include "pecaL.h"
#include "pecaT.h"
#include "pecaS.h"
#include "pecaZ.h"
#include "pecaLesp.h"
#include "main_thread.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int mult; //multiplicado para pontuação
bool i=0; //flag para iniciar o jogo
void proxPeca(int pecas); //funcao para desenhar a proxima peça ao lado do tabuleiro
void rotatePeca(int npeca); //funcao que rotaciona peca 90 graus sentido anti horario
void limpaTela(); //função que limpa as duas matrizes que controlam o tabuleiro
void moveEsquerda(int npeca);   //move peca uma unidade para a esquerda
void moveDireita(int npeca);    //move peca uma unidade para a direita
void limpaLinha(int lim);   //limpa uma linha que for completada
void caiPeca(int npeca);    //funcao que controla a caida das pecas
void pintaBloco(GX_RESOURCE_ID id);  //função para pintar o sprite de preto
void limpaBloco(GX_RESOURCE_ID id);    //funcao para pintar sprite de cinza
short linha = 0; //variavel que auxilia na verificação de uma linha estar completa
int pontuacao;
void update_score(GX_RESOURCE_ID id, int string_id); //atualiza a pontuacao na tela
//matriz usada para consultar se o espaço na matriz esta ocupada
bool matriz_consulta[20][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

//matriz com o nome dos sprites para facilitar a chamada por meio de indices
GX_RESOURCE_ID matriz[20][10] = {
    {ID_SPRITE1_1,ID_SPRITE1_2,ID_SPRITE1_3,ID_SPRITE1_4,ID_SPRITE1_5,ID_SPRITE1_6,ID_SPRITE1_7,ID_SPRITE1_8,ID_SPRITE1_9,ID_SPRITE1_10},
    {ID_SPRITE2_1,ID_SPRITE2_2,ID_SPRITE2_3,ID_SPRITE2_4,ID_SPRITE2_5,ID_SPRITE2_6,ID_SPRITE2_7,ID_SPRITE2_8,ID_SPRITE2_9,ID_SPRITE2_10},
    {ID_SPRITE3_1,ID_SPRITE3_2,ID_SPRITE3_3,ID_SPRITE3_4,ID_SPRITE3_5,ID_SPRITE3_6,ID_SPRITE3_7,ID_SPRITE3_8,ID_SPRITE3_9,ID_SPRITE3_10},
    {ID_SPRITE4_1,ID_SPRITE4_2,ID_SPRITE4_3,ID_SPRITE4_4,ID_SPRITE4_5,ID_SPRITE4_6,ID_SPRITE4_7,ID_SPRITE4_8,ID_SPRITE4_9,ID_SPRITE4_10},
    {ID_SPRITE5_1,ID_SPRITE5_2,ID_SPRITE5_3,ID_SPRITE5_4,ID_SPRITE5_5,ID_SPRITE5_6,ID_SPRITE5_7,ID_SPRITE5_8,ID_SPRITE5_9,ID_SPRITE5_10},
    {ID_SPRITE6_1,ID_SPRITE6_2,ID_SPRITE6_3,ID_SPRITE6_4,ID_SPRITE6_5,ID_SPRITE6_6,ID_SPRITE6_7,ID_SPRITE6_8,ID_SPRITE6_9,ID_SPRITE6_10},
    {ID_SPRITE7_1,ID_SPRITE7_2,ID_SPRITE7_3,ID_SPRITE7_4,ID_SPRITE7_5,ID_SPRITE7_6,ID_SPRITE7_7,ID_SPRITE7_8,ID_SPRITE7_9,ID_SPRITE7_10},
    {ID_SPRITE8_1,ID_SPRITE8_2,ID_SPRITE8_3,ID_SPRITE8_4,ID_SPRITE8_5,ID_SPRITE8_6,ID_SPRITE8_7,ID_SPRITE8_8,ID_SPRITE8_9,ID_SPRITE8_10},
    {ID_SPRITE9_1,ID_SPRITE9_2,ID_SPRITE9_3,ID_SPRITE9_4,ID_SPRITE9_5,ID_SPRITE9_6,ID_SPRITE9_7,ID_SPRITE9_8,ID_SPRITE9_9,ID_SPRITE9_10},
    {ID_SPRITE10_1,ID_SPRITE10_2,ID_SPRITE10_3,ID_SPRITE10_4,ID_SPRITE10_5,ID_SPRITE10_6,ID_SPRITE10_7,ID_SPRITE10_8,ID_SPRITE10_9,ID_SPRITE10_10},
    {ID_SPRITE11_1,ID_SPRITE11_2,ID_SPRITE11_3,ID_SPRITE11_4,ID_SPRITE11_5,ID_SPRITE11_6,ID_SPRITE11_7,ID_SPRITE11_8,ID_SPRITE11_9,ID_SPRITE11_10},
    {ID_SPRITE12_1,ID_SPRITE12_2,ID_SPRITE12_3,ID_SPRITE12_4,ID_SPRITE12_5,ID_SPRITE12_6,ID_SPRITE12_7,ID_SPRITE12_8,ID_SPRITE12_9,ID_SPRITE12_10},
    {ID_SPRITE13_1,ID_SPRITE13_2,ID_SPRITE13_3,ID_SPRITE13_4,ID_SPRITE13_5,ID_SPRITE13_6,ID_SPRITE13_7,ID_SPRITE13_8,ID_SPRITE13_9,ID_SPRITE13_10},
    {ID_SPRITE14_1,ID_SPRITE14_2,ID_SPRITE14_3,ID_SPRITE14_4,ID_SPRITE14_5,ID_SPRITE14_6,ID_SPRITE14_7,ID_SPRITE14_8,ID_SPRITE14_9,ID_SPRITE14_10},
    {ID_SPRITE15_1,ID_SPRITE15_2,ID_SPRITE15_3,ID_SPRITE15_4,ID_SPRITE15_5,ID_SPRITE15_6,ID_SPRITE15_7,ID_SPRITE15_8,ID_SPRITE15_9,ID_SPRITE15_10},
    {ID_SPRITE16_1,ID_SPRITE16_2,ID_SPRITE16_3,ID_SPRITE16_4,ID_SPRITE16_5,ID_SPRITE16_6,ID_SPRITE16_7,ID_SPRITE16_8,ID_SPRITE16_9,ID_SPRITE16_10},
    {ID_SPRITE17_1,ID_SPRITE17_2,ID_SPRITE17_3,ID_SPRITE17_4,ID_SPRITE17_5,ID_SPRITE17_6,ID_SPRITE17_7,ID_SPRITE17_8,ID_SPRITE17_9,ID_SPRITE17_10},
    {ID_SPRITE18_1,ID_SPRITE18_2,ID_SPRITE18_3,ID_SPRITE18_4,ID_SPRITE18_5,ID_SPRITE18_6,ID_SPRITE18_7,ID_SPRITE18_8,ID_SPRITE18_9,ID_SPRITE18_10},
    {ID_SPRITE19_1,ID_SPRITE19_2,ID_SPRITE19_3,ID_SPRITE19_4,ID_SPRITE19_5,ID_SPRITE19_6,ID_SPRITE19_7,ID_SPRITE19_8,ID_SPRITE19_9,ID_SPRITE19_10},
    {ID_SPRITE20_1,ID_SPRITE20_2,ID_SPRITE20_3,ID_SPRITE20_4,ID_SPRITE20_5,ID_SPRITE20_6,ID_SPRITE20_7,ID_SPRITE20_8,ID_SPRITE20_9,ID_SPRITE20_10},
};
int y=0; //coordenada y atual
int x=4; //coordenada x atual
bool t=false;   //flag que possibilita a troca de tela no fim de ogo
int peca1;  //peca que é controlada
int peca2; //peca que aparece no canto da tela


/* Peca entry function */
void peca_entry(void)
{
    srand(time(NULL));
    /* TODO: add your own code here */
    ULONG   received_message = 0;
    while (1)
    {
       mult=0;
       if(i==0){
           //espera pressionar um botão para o jogo iniciar
           tx_queue_receive(&g_input_queue, &received_message, TX_WAIT_FOREVER);
           i=1;
           peca1 = rand()%7;
           peca2 = rand()%7;
           pontuacao=0;
       }
       else if (i==1){
           //a fila espera um tempo para pressionar o botao
           //esse é o tempo para a peca andar um especo para baixo
           tx_queue_receive(&g_input_queue, &received_message, 0x00000010);
       }
       //dependendo do botão pressionado, executa uma ação
       if(received_message == 1){
           moveEsquerda(peca1);
           received_message = 0;
        }
        if(received_message == 2){
           moveDireita(peca1);
           received_message = 0;
        }
        if(received_message == 3){
           rotatePeca(peca1);
           received_message=0;
        }
        proxPeca(peca2);
        caiPeca(peca1);
    }
}

//as funcoes a seguir chamam as funções da peça controlada
void rotatePeca(int npeca){
    if(npeca == 1){
        rotateI();
    }
    if(npeca ==2){
        rotateL();
    }
    if(npeca == 3){
        rotateLesp();
    }
    if(npeca == 4){
        rotateT();
    }
    if(npeca == 5){
        rotateS();
    }
    if(npeca == 6){
        rotateZ();
    }
}

void moveEsquerda(int npeca){
    //move quadrado
    if(npeca == 0){
        moveQuadradoEsquerda();
    }
    if(npeca ==1){
        moveIEsquerda();
    }
    if(npeca == 2){
        moveLEsquerda();
    }
    if(npeca == 3){
        moveLespEsquerda();
    }
    if(npeca == 4){
        moveTEsquerda();
    }
    if(npeca == 5){
        moveSEsquerda();
    }
    if(npeca == 6){
        moveZEsquerda();
    }
}

void moveDireita(int npeca){
    //move quadrado
    if(npeca == 0){
        moveQuadradoDireita();
    }
    if(npeca == 1){
        moveIDireita();
    }
    if(npeca == 2){
        moveLDireita();
    }
    if(npeca == 3){
        moveLespDireita();
    }
    if(npeca == 4){
        moveTDireita();
    }
    if(npeca == 5){
        moveSDireita();
    }
    if(npeca == 6){
        moveZDireita();
    }
}

void caiPeca(int npeca){
    //cai quadrado
    if(npeca == 0)
    {
        caiQuadrado();
    }
    if(npeca == 1){
        caiI();
    }
    if(npeca == 2){
        caiL();
    }
    if(npeca == 3){
        caiLesp();
    }
    if(npeca == 4){
        caiT();
    }
    if(npeca == 5){
        caiS();
    }
    if(npeca == 6){
        caiZ();
    }
}
void limpaLinha(int lim){
     for(int c=lim; c!=1; c--){
         for(int d=0; d<10; d++){
             //se c for a linha cheia que chamou a função, ela é apagada
             if(c==lim){
                 limpaBloco(matriz[c][d]);
                 matriz_consulta[c][d]=0;
             }
             //senão ela move as linhas acima uma unidade para baixo
             //assim a linha sera apagada e as outras acima ocuparão seu lugar
             else{
                 if(matriz_consulta[c][d]==1){
                     pintaBloco(matriz[c+1][d]);
                     matriz_consulta[c+1][d]=1;
                 }
                 else if(matriz_consulta[c][d]==0){
                     limpaBloco(matriz[c+1][d]);
                     matriz_consulta[c+1][d]=0;
                 }
             }
         }
     }
}


void pintaBloco(GX_RESOURCE_ID id){
    GX_WIDGET * p_icon = NULL;
    ssp_err_t err = (ssp_err_t)gx_system_widget_find((USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_icon);
        if (TX_SUCCESS == err)
        {
            _gxe_widget_fill_color_set(p_icon, GX_COLOR_ID_BTN_TEXT,GX_COLOR_ID_BTN_TEXT,GX_COLOR_ID_BTN_TEXT);
        }

}

void limpaBloco(GX_RESOURCE_ID id){
    GX_WIDGET * p_icon = NULL;
    ssp_err_t err = (ssp_err_t)gx_system_widget_find((USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_icon);
        if (TX_SUCCESS == err)
        {
            _gxe_widget_fill_color_set(p_icon, GX_COLOR_ID_WIDGET_FILL,GX_COLOR_ID_WIDGET_FILL,GX_COLOR_ID_WIDGET_FILL);
        }

}

//função simples de percorrer matriz
void limpaTela(){
    for(int c=0;c<20;c++){
        for(int d=0; d<10;d++){
            limpaBloco(matriz[c][d]);
            matriz_consulta[c][d]=0;
        }
    }

}

//essa função limpa e depois escreve a proxima peca ao lado do tabuleiro
void proxPeca(int pecas)
{
    limpaBloco(ID_NEXT1_1);
    limpaBloco(ID_NEXT1_2);
    limpaBloco(ID_NEXT1_3);
    limpaBloco(ID_NEXT1_4);
    limpaBloco(ID_NEXT2_1);
    limpaBloco(ID_NEXT2_2);
    limpaBloco(ID_NEXT2_3);
    limpaBloco(ID_NEXT2_4);
    if(pecas==0){
        pintaBloco(ID_NEXT1_2);
        pintaBloco(ID_NEXT1_3);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
    }
    if(pecas==1){
        pintaBloco(ID_NEXT2_1);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
        pintaBloco(ID_NEXT2_4);
    }
    if(pecas==2){
        pintaBloco(ID_NEXT2_1);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
        pintaBloco(ID_NEXT1_3);
    }
    if(pecas==3){
        pintaBloco(ID_NEXT2_1);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
        pintaBloco(ID_NEXT1_1);
    }
    if(pecas==4){
        pintaBloco(ID_NEXT2_1);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
        pintaBloco(ID_NEXT1_2);
    }
    if(pecas==5){
        pintaBloco(ID_NEXT2_1);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT1_2);
        pintaBloco(ID_NEXT1_3);
    }
    if(pecas==6){
        pintaBloco(ID_NEXT1_1);
        pintaBloco(ID_NEXT1_2);
        pintaBloco(ID_NEXT2_2);
        pintaBloco(ID_NEXT2_3);
    }
}

void update_score(GX_RESOURCE_ID id, int string_id)
{
    GX_NUMERIC_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_system_widget_find((USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        _gxe_numeric_prompt_value_set(p_prompt, string_id);
    }
}
