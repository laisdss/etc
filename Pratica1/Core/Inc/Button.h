/*
 * @file Button.h
 * @brief Interface do módulo de controle do botão.
 *
 * Este módulo gerencia o estado de congelamento da aplicação
 * a partir dos eventos gerados pelo botão.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/*
 * @brief Inicializa o módulo do botão.
 *
 * @retval Nenhum.
 */
void Button_Init(void);

/*
 * @brief Processa os eventos do botão.
 *
 * Verifica se houve um novo acionamento do botão e alterna
 * o estado de congelamento da aplicação.
 *
 * @retval Nenhum.
 */
void Button_Processar(void);

/*
 * @brief Informa se a aplicação está congelada.
 *
 * @retval 1 caso esteja congelada, 0 caso contrário.
 */
uint8_t Button_EstaCongelado(void);

#endif /* INC_BUTTON_H_ */