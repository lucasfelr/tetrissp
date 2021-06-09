#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "main_thread.h"
#include "peca.h"
#include "peca_entry.h"

extern GX_WINDOW_ROOT * p_window_root;

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);

UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    ULONG esquerda = 1;
    ULONG direita = 2;
    ULONG rotate = 3;
    UINT result = gx_window_event_process(widget, event_ptr);
    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(ID_ESQUERDA, GX_EVENT_CLICKED):
                        //SE BOTÃO ESQUERDO, MOVER CARRO PRA ESQUERDA
                        tx_queue_send(&g_input_queue, &esquerda, TX_WAIT_FOREVER);
                        break;
        case GX_SIGNAL(ID_DIREITA, GX_EVENT_CLICKED):
                        //SE BOTÃO DIREITO, MOVER CARRO PARA A DIREITA
                        tx_queue_send(&g_input_queue, &direita, TX_WAIT_FOREVER);
                        break;
        case GX_SIGNAL(ID_ROTATE, GX_EVENT_CLICKED):
                                //SE BOTÃO DIREITO, MOVER CARRO PARA A DIREITA
            tx_queue_send(&g_input_queue, &rotate, TX_WAIT_FOREVER);
            break;
        default:
            //quando a flag de fim de ogo é ativada, troca a tela
            if(t==true){
                t=false;
                show_window((GX_WINDOW*)&window2, (GX_WIDGET*)widget, true);
            }
            gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

UINT window2_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);
    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(ID_RESET, GX_EVENT_CLICKED):
                show_window((GX_WINDOW*)&window1, (GX_WIDGET*)widget, true);
        break;
        default:
            //mostra a pontuação na tela final e limpa a pontação da primeira tela
            update_score(ID_FIM, pontuacao);
            update_score(ID_PONTUACAO, 0);
            gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET * p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET*)p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}
