/**
 * @file SerialCmd.c
 * @brief Implementação do módulo de comandos USART.
 *
 * Interpreta comandos recebidos pela USART3.
 * Os comandos aceitos são LED1, LED2 e LED3.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include "SerialCmd.h"
#include "Bsp.h"
#include "LedPwm.h"
#include <string.h>

/* ========================================================================== */
/* DEFINES LOCAIS                                                             */
/* ========================================================================== */

#define CMD_TAMANHO_TEXTO   4U  /**< Quantidade de caracteres do comando (ex: L,E,D,1) */
#define CMD_TAMANHO_BUFFER  5U  /**< Tamanho do buffer com espaço para o '\0' */

/* ========================================================================== */
/* VARIÁVEIS LOCAIS                                                           */
/* ========================================================================== */

static char comando[CMD_TAMANHO_BUFFER];
static uint8_t indice;

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo SerialCmd.
 *
 * @retval Nenhum.
 */
void SerialCmd_Init(void)
{
    indice = 0U;

    for(uint8_t i = 0U; i < CMD_TAMANHO_BUFFER; i++)
    {
        comando[i] = '\0';
    }
}

/**
 * @brief Processa comandos recebidos pela USART3.
 *
 * @retval Nenhum.
 */
void SerialCmd_Processar(void)
{
    char caractere;

    if(Bsp_Usart_Dado())
    {
        caractere = (char)Bsp_Usart_GetChar();
        Bsp_Usart_LimparFlag();

        /* Armazena o caractere apenas se passar na validação de alinhamento */
        if ((indice == 0U) && (caractere != 'L'))
        {
            /* Descarta ruídos, espaços ou restos de \r\n do terminal */
        }
        else
        {
            comando[indice] = caractere;
            indice++;
        }

        /* Quando recebeu exatamente os 4 caracteres válidos iniciados por 'L' */
        if(indice == CMD_TAMANHO_TEXTO)
        {
            comando[CMD_TAMANHO_TEXTO] = '\0';

            if(strcmp(comando, "LED1") == 0)
            {
                LedPwm_DefinirLedAtivo(LED1);
            }
            else if(strcmp(comando, "LED2") == 0)
            {
                LedPwm_DefinirLedAtivo(LED2);
            }
            else if(strcmp(comando, "LED3") == 0)
            {
                LedPwm_DefinirLedAtivo(LED3);
            }

            /* Prepara para o próximo comando */
            indice = 0U;
        }
    }
}