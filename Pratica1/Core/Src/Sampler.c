/**
 * @file Sampler.c
 * @brief Implementação do módulo de aquisição e processamento das amostras.
 *
 * Este módulo realiza a aquisição das amostras do ADC através da BSP,
 * calcula a média de 100 amostras e converte o resultado para uma
 * porcentagem entre 0 e 100%.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

#include "Sampler.h"
#include "Bsp.h"

/* ========================================================================== */
/* DEFINES LOCAIS                                                             */
/* ========================================================================== */

#define SAMPLER_MAX_AMOSTRAS  100U
#define SAMPLER_ADC_MAX_VAL   4095.0f

/* ========================================================================== */
/* VARIÁVEIS LOCAIS                                                           */
/* ========================================================================== */

static uint32_t somaAmostras;
static uint16_t quantidadeAmostras;

static uint8_t porcentagemCalculada;
static uint8_t novoValorDisponivel;


/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa o módulo de aquisição.
 *
 * Zera os acumuladores e a flag de novo valor.
 *
 * @retval Nenhum.
 */
void Sampler_Init(void)
{
    somaAmostras = 0U;
    quantidadeAmostras = 0U;

    porcentagemCalculada = 0U;
    novoValorDisponivel = 0U;
}


/**
 * @brief Processa uma nova amostra do ADC.
 *
 * Realiza a leitura através da BSP, acumula 100 amostras,
 * calcula a média e converte o resultado para porcentagem.
 *
 * @retval Nenhum.
 */
void Sampler_Processar(void)
{
    uint32_t valorAdc;
    
    valorAdc = Bsp_LerAdc();

    somaAmostras += valorAdc;
    quantidadeAmostras++;


    /* Verifica se completou a janela de 100 amostras */
    if(quantidadeAmostras >= SAMPLER_MAX_AMOSTRAS)
    {
        uint32_t media;


        media = somaAmostras / SAMPLER_MAX_AMOSTRAS;


        /* Conversão para porcentagem de 0 a 100% */
        porcentagemCalculada =
            (uint8_t)((media * 100U) / SAMPLER_ADC_MAX_VAL);


        /* Proteção contra valores acima de 100% */
        if(porcentagemCalculada > 100U)
        {
            porcentagemCalculada = 100U;
        }


        /* Indica que existe um novo resultado */
        novoValorDisponivel = 1U;


        /* Reinicia a próxima janela de aquisição */
        somaAmostras = 0U;
        quantidadeAmostras = 0U;
    }
}


/**
 * @brief Retorna a porcentagem calculada.
 *
 * @retval Valor entre 0 e 100%.
 */
uint8_t Sampler_ObterPorcentagem(void)
{
    return porcentagemCalculada;
}


/**
 * @brief Verifica se existe uma nova porcentagem disponível.
 *
 * @retval 1 caso exista um novo valor, 0 caso contrário.
 */
uint8_t Sampler_TemNovoValor(void)
{
    return novoValorDisponivel;
}


/**
 * @brief Limpa a flag de novo valor disponível.
 *
 * @retval Nenhum.
 */
void Sampler_LimparFlag(void)
{
    novoValorDisponivel = 0U;
}