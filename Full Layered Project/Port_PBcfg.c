#include "Port.h"

/*******************************************************************************
 *                                Version Definitions                          *
 *******************************************************************************/
/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Software Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)

/*******************************************************************************
 *                                   INCLUDES                                  *
 *******************************************************************************/
/* AUTOSAR Port header file */
#include "Port.h"

/* Checking AUTOSAR Release compitability between Port.h and Port_Cfg.h */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_AR_RELEASE_PATCH_VERSION != PORT_CFG_AR_RELEASE_PATCH_VERSION))
      #error "The AR version of Port.h does not match the expected version"
#endif

/* Checking Software compitability between Port.h and Port_Cfg.h */
#if ((PORT_SW_MAJOR_VERSION != PORT_CFG_SW_MAJOR_VERSION)\
 ||  (PORT_SW_MINOR_VERSION != PORT_CFG_SW_MINOR_VERSION)\
 ||  (PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION))
      #error "The AR version of Port.h does not match the expected version"
#endif

/*******************************************************************************
 *                           Initialization Structure                          *
 *******************************************************************************/
/* 
 * Note:
 *      The name of each pin is specified at first, then the following features
 *      are configured in the following order:
 *        1. Pin number
 *        2. Port number
 *        3. Pin mode
 *        4. Pin direction
 *        5. Pin initial value
 *        6. Internal pull-up/down resistor control                
 *        7. Pin direction changeable
 *        8. Pin mode changeable
 *
 */
const Port_ConfigType Port_Configuration =
{
 /* PORT_A_PIN_0 */
  PIN_0,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_1 */
  PIN_1,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_2 */
  PIN_2,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_3 */
  PIN_3,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_4 */
  PIN_4,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_5 */
  PIN_5,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_6 */
  PIN_6,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_A_PIN_7 */
  PIN_7,
  PORT_A,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_0 */
  PIN_0,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_1 */
  PIN_1,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_2 */
  PIN_2,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_3 */
  PIN_3,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_4 */
  PIN_4,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_5 */
  PIN_5,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_6 */
  PIN_6,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_B_PIN_7 */
  PIN_7,
  PORT_B,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_0 */
  PIN_0,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_1 */
  PIN_1,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_2 */
  PIN_2,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_3 */
  PIN_3,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_4 */
  PIN_4,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_5 */
  PIN_5,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_6 */
  PIN_6,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_C_PIN_7 */
  PIN_7,
  PORT_C,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
 
 /* PORT_D_PIN_0 */
  PIN_0,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_1 */
  PIN_1,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_2 */
  PIN_2,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_3 */
  PIN_3,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_4 */
  PIN_4,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_5 */
  PIN_5,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_6 */
  PIN_6,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_D_PIN_7 */
  PIN_7,
  PORT_D,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_E_PIN_0 */
  PIN_0,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_E_PIN_1 */
  PIN_1,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_E_PIN_2 */
  PIN_2,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_E_PIN_3 */
  PIN_3,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
  /* PORT_E_PIN_4 */
  PIN_4,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_E_PIN_5 */
  PIN_5,
  PORT_E,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_F_PIN_0 */
  PIN_0,
  PORT_F,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_F_PIN_1 */
  PIN_1,
  PORT_F,
  PORT_DIGITAL_IO,
  PORT_PIN_OUT,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_F_PIN_2 */
  PIN_2,
  PORT_F,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_F_PIN_3 */
  PIN_3,
  PORT_F,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_OFF,
  STD_OFF,
  STD_OFF,
  
 /* PORT_F_PIN_4 */
  PIN_4,
  PORT_F,
  PORT_DIGITAL_IO,
  PORT_PIN_IN,
  STD_LOW,
  PORT_PIN_INTERNAL_RESISTOR_DOWN,
  STD_OFF,
  STD_OFF
};


