/*
 * @file Button.c
 * @brief Implementação do módulo de controle do botão.
 *
 * Este módulo gerencia o estado de congelamento da aplicação.
 * O botão é tratado pela BSP, que apenas sinaliza o evento através
 * de uma flag. Este módulo verifica essa flag e alterna o estado
 * de congelamento.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include "Button.h"
#include "Bsp.h"

/* ========================================================================== */
/* VARIÁVEIS LOCAIS                                                           */
/* ========================================================================== */

/*
 * @brief Estado de congelamento da aplicação.
 *
 * 0 -> Funcionamento normal.
 * 1 -> Aplicação congelada.
 */
static uint8_t congelado;

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/*
 * @brief Inicializa o módulo do botão.
 *
 * @retval Nenhum.
 */
void Button_Init(void)
{
    congelado = 0U;
}

/*
 * @brief Processa os eventos do botão.
 *
 * Verifica se a BSP sinalizou um novo acionamento do botão.
 * Caso positivo, alterna o estado de congelamento e limpa
 * a flag do botão.
 *
 * @retval Nenhum.
 */
void Button_Processar(void)
{
    if (Bsp_VerificarFlagBotao())
    {
        congelado = !congelado;

        Bsp_LimparFlagBotao();
    }
}

/*
 * @brief Informa se a aplicação está congelada.
 *
 * @retval 1 caso a aplicação esteja congelada.
 * @retval 0 caso a aplicação esteja em funcionamento.
 */
uint8_t Button_EstaCongelado(void)
{
    return congelado;
}