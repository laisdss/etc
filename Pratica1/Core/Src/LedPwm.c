/**
 * @file LedPwm.c
 * @brief Implementação do módulo de controle dos LEDs PWM.
 *
 * Este módulo mantém o valor de duty cycle de cada LED
 * e atualiza o LED selecionado através da BSP.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include "LedPwm.h"
#include "Bsp.h"

/* ========================================================================== */
/* VARIÁVEIS LOCAIS                                                           */
/* ========================================================================== */

/**
 * @brief Valores atuais de brilho dos LEDs.
 *
 * Valores armazenados em porcentagem (0 a 100%).
 */
static uint8_t dutyLed1;
static uint8_t dutyLed2;
static uint8_t dutyLed3;


/**
 * @brief LED que receberá o valor do potenciômetro.
 */
static uint8_t ledAtivo;


/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo dos LEDs PWM.
 *
 * Inicializa todos os LEDs desligados
 * e seleciona o LED1 como ativo.
 *
 * @retval Nenhum.
 */
void LedPwm_Init(void)
{
    dutyLed1 = 0U;
    dutyLed2 = 0U;
    dutyLed3 = 0U;

    ledAtivo = LED1;


    /* Garante que os LEDs iniciam desligados */
    Bsp_DefinirPwm(BSP_LED1_CHANNEL, dutyLed1);
    Bsp_DefinirPwm(BSP_LED2_CHANNEL, dutyLed2);
    Bsp_DefinirPwm(BSP_LED3_CHANNEL, dutyLed3);
}


/**
 * @brief Define qual LED será atualizado pelo potenciômetro.
 *
 * @param led LED selecionado.
 *
 * @retval Nenhum.
 */
void LedPwm_DefinirLedAtivo(uint8_t led)
{
    if((led == LED1) ||
       (led == LED2) ||
       (led == LED3))
    {
        ledAtivo = led;
    }
}


/**
 * @brief Atualiza o brilho do LED ativo.
 *
 * O valor recebido do potenciômetro é aplicado
 * somente ao LED selecionado.
 *
 * @param porcentagem Valor entre 0 e 100%.
 *
 * @retval Nenhum.
 */
void LedPwm_Atualizar(uint8_t porcentagem)
{
    switch(ledAtivo)
    {
        case LED1:

            dutyLed1 = porcentagem;
            Bsp_DefinirPwm(BSP_LED1_CHANNEL, dutyLed1);

            break;


        case LED2:

            dutyLed2 = porcentagem;
            Bsp_DefinirPwm(BSP_LED2_CHANNEL, dutyLed2);

            break;


        case LED3:

            dutyLed3 = porcentagem;
            Bsp_DefinirPwm(BSP_LED3_CHANNEL, dutyLed3);

            break;


        default:

            break;
    }
}


/**
 * @brief Retorna o valor atual do duty cycle de um LED.
 *
 * @param led LED desejado.
 *
 * @retval Duty cycle entre 0 e 100%.
 */
uint8_t LedPwm_ObterDuty(uint8_t led)
{
    switch(led)
    {
        case LED1:
            return dutyLed1;


        case LED2:
            return dutyLed2;


        case LED3:
            return dutyLed3;


        default:
            return 0U;
    }
}