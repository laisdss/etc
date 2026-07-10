/**
 * @file Sampler.h
 * @brief Interface do módulo de aquisição e processamento das amostras.
 *
 * Este módulo realiza a aquisição das amostras do ADC através da BSP,
 * calcula a média de 100 amostras e converte o resultado para uma
 * porcentagem entre 0 e 100%.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

#ifndef INC_SAMPLER_H_
#define INC_SAMPLER_H_

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include <stdint.h>

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo de aquisição.
 *
 * @retval Nenhum.
 */
void Sampler_Init(void);

/**
 * @brief Processa uma nova amostra do ADC.
 *
 * Esta função deve ser chamada sempre que a BSP sinalizar
 * uma nova amostragem.
 *
 * @retval Nenhum.
 */
void Sampler_Processar(void);

/**
 * @brief Retorna a porcentagem calculada.
 *
 * @retval Valor entre 0 e 100%.
 */
uint8_t Sampler_ObterPorcentagem(void);

/**
 * @brief Verifica se existe uma nova porcentagem disponível.
 *
 * @retval 1 caso exista um novo valor, 0 caso contrário.
 */
uint8_t Sampler_TemNovoValor(void);

/**
 * @brief Limpa a flag de novo valor disponível.
 *
 * @retval Nenhum.
 */
void Sampler_LimparFlag(void);

#endif /* INC_SAMPLER_H_ */