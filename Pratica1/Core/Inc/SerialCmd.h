/**
 * @file SerialCmd.h
 * @brief Interface do módulo de interpretação de comandos USART.
 *
 * Este módulo recebe comandos pela USART através da BSP,
 * interpreta os comandos recebidos e seleciona o LED ativo.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

#ifndef INC_SERIALCMD_H_
#define INC_SERIALCMD_H_

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo de comandos seriais.
 *
 * @retval Nenhum.
 */
void SerialCmd_Init(void);


/**
 * @brief Processa dados recebidos pela USART.
 *
 * Verifica se existe novo caractere recebido,
 * monta o comando e executa a ação correspondente.
 *
 * @retval Nenhum.
 */
void SerialCmd_Processar(void);


#endif /* INC_SERIALCMD_H_ */