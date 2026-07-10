/**
 * @file LedPwm.h
 * @brief Interface do módulo de controle dos LEDs PWM.
 *
 * Este módulo controla o duty cycle dos LEDs através da BSP.
 * Mantém o valor individual de cada LED e permite selecionar
 * qual LED será atualizado pelo valor do potenciômetro.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

#ifndef INC_LEDPWM_H_
#define INC_LEDPWM_H_

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/* DEFINES                                                                    */
/* ========================================================================== */

#define LED1  1U
#define LED2  2U
#define LED3  3U

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo dos LEDs PWM.
 *
 * Inicializa os valores de duty cycle dos LEDs
 * e define o LED ativo inicial.
 *
 * @retval Nenhum.
 */
void LedPwm_Init(void);


/**
 * @brief Define qual LED receberá o valor do potenciômetro.
 *
 * @param led LED selecionado.
 *
 * @retval Nenhum.
 */
void LedPwm_DefinirLedAtivo(uint8_t led);


/**
 * @brief Atualiza o duty cycle do LED ativo.
 *
 * Recebe o valor calculado pelo módulo Sampler
 * e aplica somente no LED selecionado.
 *
 * @param porcentagem Valor entre 0 e 100%.
 *
 * @retval Nenhum.
 */
void LedPwm_Atualizar(uint8_t porcentagem);


/**
 * @brief Retorna o duty cycle atual de um LED.
 *
 * @param led LED desejado.
 *
 * @retval Valor entre 0 e 100%.
 */
uint8_t LedPwm_ObterDuty(uint8_t led);


#endif /* INC_LEDPWM_H_ */