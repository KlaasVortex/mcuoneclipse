/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (number 62), U7[4]/UART0_RX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                                /* @} */

/*! @name PORTB17 (number 63), U10[1]/UART0_TX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                                /* @} */

/*! @name PORTB22 (number 68), D12[1]/LEDRGB_RED
  @{ */
#define BOARD_INITPINS_LED_RED_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_RED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_RED_PIN 22U    /*!<@brief PORTB pin index: 22 */
                                          /* @} */

/*! @name PORTE26 (number 33), J2[1]/D12[4]/LEDRGB_GREEN
  @{ */
#define BOARD_INITPINS_LED_GREEN_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_LED_GREEN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_LED_GREEN_PIN 26U    /*!<@brief PORTE pin index: 26 */
                                            /* @} */

/*! @name PORTB21 (number 67), D12[3]/LEDRGB_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_BLUE_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_BLUE_PIN 21U    /*!<@brief PORTB pin index: 21 */
                                           /* @} */

/*! @name PORTA4 (number 38), SW3
  @{ */
#define BOARD_INITPINS_SW3_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_SW3_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_SW3_PIN 4U     /*!<@brief PORTA pin index: 4 */
                                      /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
