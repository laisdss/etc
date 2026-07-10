/**
 * @file Bsp.c
 * @brief Implementação da camada BSP corrigida.
 *
 * Esta camada é responsável pelo acesso direto aos periféricos através da HAL.
 * Nenhum outro módulo da aplicação deve acessar funções da HAL diretamente.
 *
 * @author Lais Duarte Sousa
 * @date 10/julho/2026
 */

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */
#include "Bsp.h"

#include "adc.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"

/* ========================================================================== */
/* VARIÁVEIS LOCAIS                                                           */
/* ========================================================================== */
static uint8_t rxChar;

volatile uint8_t sampleFlag;
volatile uint8_t buttonFlag;
volatile uint8_t uartFlag;

/* ========================================================================== */
/* FUNÇÕES PÚBLICAS                                                           */
/* ========================================================================== */

/**
 * @brief Inicializa os periféricos que serão utilizados.
 *
 * @retval Nenhum.
 */
void Bsp_Init(void)
{
    /*-------------PWM-------------*/
    HAL_TIM_PWM_Start(&htim3, BSP_LED1_CHANNEL);
    HAL_TIM_PWM_Start(&htim3, BSP_LED2_CHANNEL);
    HAL_TIM_PWM_Start(&htim3, BSP_LED3_CHANNEL);
    
    /*-------------Timers-------------*/
    HAL_TIM_Base_Start_IT(&htim2); // Timer de Amostragem (5ms)
    // O Timer de Debounce (htim4) será iniciado apenas sob demanda na interrupção EXTI
    
    /*-------------USART-------------*/
    HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxChar, 1);

    /*-------------Flags-------------*/
    sampleFlag = 0U;
    buttonFlag = 0U;
    uartFlag   = 0U;
}

/**
 * @brief Realiza uma leitura do ADC utilizando polling.
 *
 * @retval Valor lido pelo ADC.
 */
uint32_t Bsp_LerAdc(void)
{
    uint32_t valorAdc = 0;
    HAL_ADC_Start(&hadc1); 
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); 
    valorAdc = HAL_ADC_GetValue(&hadc1); 
    HAL_ADC_Stop(&hadc1); 
    return valorAdc;
}

/**
 * @brief Define a intensidade do PWM.
 *
 * @param canal Canal do timer.
 * @param intensidade Valor entre 0 e 100%.
 */
void Bsp_DefinirPwm(uint32_t canal, uint8_t intensidade)
{
    uint32_t periodo;
    uint32_t pulso;

    if (intensidade > BSP_PWM_MAX_DUTY) 
    {
        intensidade = BSP_PWM_MAX_DUTY;
    }
    periodo = __HAL_TIM_GET_AUTORELOAD(&htim3); 
    pulso = (periodo * intensidade) / BSP_PWM_MAX_DUTY; 
    __HAL_TIM_SET_COMPARE(&htim3, canal, pulso); 
}

/* ========================================================================== */
/* USART                                                                      */
/* ========================================================================== */

/**
 * @brief Envia dados pela USART3.
 *
 * @param dados Ponteiro para os dados.
 * @param tamanho Quantidade de bytes.
 *
 * @retval Nenhum.
 */
void Bsp_EnviarUsart(uint8_t *dados, uint16_t tamanho)
{
    HAL_UART_Transmit(&huart3, dados, tamanho, HAL_MAX_DELAY);
}

/**
 * @brief Retorna o último caractere recebido pela USART3.
 *
 * @retval Caractere recebido.
 */
uint8_t Bsp_Usart_GetChar(void)
{
    return rxChar;
}

/**
 * @brief Verifica se um novo dado foi recebido pela USART3.
 *
 * @retval 1 caso exista um novo dado recebido, 0 caso contrário.
 */
uint8_t Bsp_Usart_Dado(void)
{
    return uartFlag;
}

/**
 * @brief Limpa a flag de recepção da USART3.
 *
 * @retval Nenhum.
 */
void Bsp_Usart_LimparFlag(void)
{
    uartFlag = 0U;
}

/* ========================================================================== */
/* FLAGS                                                                      */
/* ========================================================================== */

/**
 * @brief Verifica se ocorreu uma amostragem pelo timer.
 *
 * @retval 1 caso a flag esteja ativa, 0 caso contrário.
 */
uint8_t Bsp_VerificarFlagAmostragem(void)
{
    return sampleFlag;
}

/**
 * @brief Limpa a flag de amostragem do timer.
 *
 * @retval Nenhum.
 */
void Bsp_LimparFlagAmostragem(void)
{
    sampleFlag = 0U;
}

/**
 * @brief Verifica se ocorreu um evento de botão.
 *
 * @retval 1 caso o botão tenha sido acionado, 0 caso contrário.
 */
uint8_t Bsp_VerificarFlagBotao(void)
{
    return buttonFlag;
}

/**
 * @brief Limpa a flag de acionamento do botão.
 *
 * @retval Nenhum.
 */
void Bsp_LimparFlagBotao(void)
{
    buttonFlag = 0U;
}

/* ========================================================================== */
/* CALLBACKS HAL                                                              */
/* ========================================================================== */

/**
 * @brief Callback executado quando ocorre uma interrupção externa (botão).
 *
 * @param GPIO_Pin Pino que gerou a interrupção.
 *
 * @retval Nenhum.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BSP_BUTTON_PIN)
    {
        /* Interrupção curta: apenas reinicia e dispara o timer de debounce dedicado */
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        HAL_TIM_Base_Start_IT(&htim4);
    }
}

/**
 * @brief Callback executado quando um dado é recebido pela USART.
 *
 * @param huart Ponteiro para a estrutura da UART que gerou a interrupção.
 *
 * @retval Nenhum.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        uartFlag = 1U;
        HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxChar, 1);
    }
}

/**
 * @brief Callback executado quando um timer finaliza sua contagem.
 *
 * @param htim Ponteiro para a estrutura do timer que gerou a interrupção.
 *
 * @retval Nenhum.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* Timer de Amostragem do ADC */
    if (htim->Instance == TIM2)
    {
        sampleFlag = 1U;
    }
    
    /* Timer Dedicado de Debounce do Botão */
    if (htim->Instance == TIM4)
    {
        /* Para o timer para que ele execute a validação apenas uma vez por clique */
        HAL_TIM_Base_Stop_IT(&htim4);
        
        /* Valida se o botão ainda está pressionado após o tempo de debounce */
        if (HAL_GPIO_ReadPin(BSP_BUTTON_PORT, BSP_BUTTON_PIN) == BSP_BUTTON_PRESSED)
        {
            buttonFlag = 1U; // Sinaliza para o laço principal tratar
        }
    }
}