/**
 * @file Bsp.h
 * @brief Interface da camada BSP.
 *
 * Esta camada disponibiliza funções para acesso aos periféricos da placa,
 * encapsulando o acesso direto à HAL.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include <stdint.h>
#include "main.h"

/* ========================================================================== */
/* DEFINIÇÕES                                                                 */
/* ========================================================================== */

/* PWM */
#define BSP_PWM_MAX_DUTY      (100U)

/* Canais PWM dos LEDs */
#define BSP_LED1_CHANNEL      TIM_CHANNEL_1
#define BSP_LED2_CHANNEL      TIM_CHANNEL_2
#define BSP_LED3_CHANNEL      TIM_CHANNEL_3

/* Botão */
#define BSP_BUTTON_PORT       GPIOC
#define BSP_BUTTON_PIN        GPIO_PIN_13
#define BSP_BUTTON_PRESSED    GPIO_PIN_RESET

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa os periféricos utilizados pela BSP.
 *
 * @retval Nenhum.
 */
void Bsp_Init(void);

/**
 * @brief Realiza uma leitura do ADC.
 *
 * @retval Valor convertido pelo ADC.
 */
uint32_t Bsp_LerAdc(void);

/**
 * @brief Define a intensidade do PWM.
 *
 * @param canal Canal do timer.
 * @param intensidade Intensidade entre 0 e 100%.
 *
 * @retval Nenhum.
 */
void Bsp_DefinirPwm(uint32_t canal, uint8_t intensidade);

/**
 * @brief Envia dados pela USART3.
 *
 * @param dados Ponteiro para os dados.
 * @param tamanho Quantidade de bytes.
 *
 * @retval Nenhum.
 */
void Bsp_EnviarUsart(uint8_t *dados, uint16_t tamanho);

/**
 * @brief Retorna o último caractere recebido pela USART.
 *
 * @retval Caractere recebido.
 */
uint8_t Bsp_Usart_GetChar(void);

/**
 * @brief Verifica se há um novo dado recebido pela USART.
 *
 * @retval 1 caso exista dado recebido, 0 caso contrário.
 */
uint8_t Bsp_Usart_Dado(void);

/**
 * @brief Limpa a flag de recepção da USART.
 *
 * @retval Nenhum.
 */
void Bsp_Usart_LimparFlag(void);

/**
 * @brief Verifica a flag de amostragem.
 *
 * @retval 1 caso exista uma nova amostragem, 0 caso contrário.
 */
uint8_t Bsp_VerificarFlagAmostragem(void);

/**
 * @brief Limpa a flag de amostragem.
 *
 * @retval Nenhum.
 */
void Bsp_LimparFlagAmostragem(void);

/**
 * @brief Verifica a flag de acionamento do botão.
 *
 * @retval 1 caso o botão tenha sido acionado, 0 caso contrário.
 */
uint8_t Bsp_VerificarFlagBotao(void);

/**
 * @brief Limpa a flag de acionamento do botão.
 *
 * @retval Nenhum.
 */
void Bsp_LimparFlagBotao(void);

#endif /* INC_BSP_H_ */