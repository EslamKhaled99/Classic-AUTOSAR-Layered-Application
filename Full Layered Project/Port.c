 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

/*******************************************************************************
 *                                   INCLUDES                                  *
 *******************************************************************************/
#include "Port.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h" 

/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/
STATIC const Port_ConfigPin * Port_configurations = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/*******************************************************************************
* Service Name: Port_Init
* Service ID: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initialize the Port Driver module
********************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
  Port_PinType pin_ID = 0;
  volatile uint32 * port_Ptr = NULL_PTR;
  volatile uint32 delay = 0;
  
#if (STD_ON == PORT_DEV_ERROR_DETECT)
  
  /* Check if the passed pointer is valid */
  if(NULL_PTR == ConfigPtr)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                     PORT_E_PARAM_CONFIG );
  }
  else
  {
    /* Do Nothing */
  }
#endif
  /*
   * The Algorithm:
   *    1. Obtain the base address of the current port
   *    2. Activate the clock for the current port
   *    3. Check special pins for unlocking
   *    4. Set pin direction
   *    5. Set the resistor network
   *    6. Set the initial value
   *    7. Set the mode
   */
  Port_configurations = ConfigPtr->Pins;
  for(pin_ID = 0; pin_ID < PORT_PINS_NUM; pin_ID++)
  {
    /* 1. Obtain the base address of the current port */
    switch(Port_configurations[pin_ID].port_num)
    {
      case 0: port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
              break;
      case 1: port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
              break;
      case 2: port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
              break;
      case 3: port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
              break;
      case 4: port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
              break;
      case 5: port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
              break;
    }
    
    /* 2. Activate the clock for the current port */
        /* Check if the port clock is already active */
    if(BIT_IS_CLEAR(SYSCTL_REGCGC2_REG, Port_configurations[pin_ID].port_num))
    {
      SET_BIT(SYSCTL_REGCGC2_REG, Port_configurations[pin_ID].port_num);
      delay = SYSCTL_REGCGC2_REG;
    }
    else
    {
      /* Do Nothing */
    }
    
    /* 3. Check special pins for unlocking PF0,PD7 and PC[0:3] */
    if((Port_configurations[pin_ID].port_num == PORT_D && Port_configurations[pin_ID].pin_num == PIN_7)
        || (Port_configurations[pin_ID].port_num == PORT_F && Port_configurations[pin_ID].pin_num == PIN_0)
        || (Port_configurations[pin_ID].port_num == PORT_C && Port_configurations[pin_ID].pin_num == PIN_0)
        || (Port_configurations[pin_ID].port_num == PORT_C && Port_configurations[pin_ID].pin_num == PIN_1)
        || (Port_configurations[pin_ID].port_num == PORT_C && Port_configurations[pin_ID].pin_num == PIN_2)
        || (Port_configurations[pin_ID].port_num == PORT_C && Port_configurations[pin_ID].pin_num == PIN_3))
    {
      /* Unlocking the lock register */
      *(volatile uint32 *)((volatile uint8 *)port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
      /* Unlocking the commit register */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr + PORT_COMMIT_REG_OFFSET), Port_configurations[pin_ID].pin_num);
    }
    else
    {
      /* Normal Pins Do Nothing */
    }
    
    /* 4. Set pin direction */
    if(PORT_PIN_IN == Port_configurations[pin_ID].pin_direction)
    {
      /* Set pin as input */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[pin_ID].pin_num);
    }
    else
    {
      /* Set pin as output */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[pin_ID].pin_num);
    }
              
    /* 5. Set the resistor network (For input pins Only) */
    if(PORT_PIN_IN == Port_configurations[pin_ID].pin_direction)
    {
      if(PORT_PIN_INTERNAL_RESISTOR_UP == Port_configurations[pin_ID].pin_internalResistor)
      {
        /* Activate the pull-up network, which automatically disables the pull-down for the same pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_PULL_UP_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      else
      {
        /* Activate the pull-down network, which automatically disables the pull-up for the same pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_PULL_DOWN_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }  
    }
    else
    {
      /* Turn off the resistor networks */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_PULL_UP_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_PULL_DOWN_REG_OFFSET), Port_configurations[pin_ID].pin_num);
    }
    
    /* 6. Set the initial value (For Output pins Only)*/
    if(PORT_PIN_OUT == Port_configurations[pin_ID].pin_direction)
    {
      if(STD_HIGH == Port_configurations[pin_ID].pin_initialValue)
      {
        /* Set the initial value of the pin to be high */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DATA_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      else
      {
        /* Set the initial value of the pin to be low */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DATA_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
    }
    else
    {
        /* Do Nothing */
    }
    
    /* 7. Set the mode */
    if(PORT_ANALOG == Port_configurations[pin_ID].pin_mode)
    {
      /* Set the alterantive function bit */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      /* Clear the peripheral function in the control register */
      *(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET) = 
              ((*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET)) & ~(PIN_MODE_MASK << Port_configurations[pin_ID].pin_num * SHIFT_4));
      /* Disable digital functionality */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      /* Activate analog functionality */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      
      /* Configuration is done for this pin, continue to the next pin */
      continue;
    }
    else
    {
      /* Clear the Analog bit */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      
      /* Check whether the mode is DIO or another mode */
      if(PORT_DIGITAL_IO == Port_configurations[pin_ID].pin_mode)
      {
        /* disable the alterantive function bit */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      else
      {
        /* Set the alterantive function bit */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      /* Set the peripheral function in the control register */
      *(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET) = 
              ((*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET)) & ~(PIN_MODE_MASK << Port_configurations[pin_ID].pin_num * SHIFT_4))
            | (Port_configurations[pin_ID].pin_mode << Port_configurations[pin_ID].pin_num * SHIFT_4);
      /* Enable the digital functionality */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_configurations[pin_ID].pin_num);
    }
  
  }
  
}

#if (STD_ON == PORT_SET_DIRECTION_API)
/*******************************************************************************
* Service Name: Port_SetPinDirection
* Service ID: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin       - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
********************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
  volatile uint32 * port_Ptr = NULL_PTR;
#if (STD_ON == PORT_DEV_ERROR_DETECT)
  
  /* Check if the module is initialized */
  if(PORT_NOT_INITIALIZED == Port_Status)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                     PORT_E_UNINIT );
  }
  else
  {
    /* Do Nothing */
  }
  
  /* Check if the passed pin number is valid */
  if(PORT_PINS_NUM <= Pin)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                     PORT_E_PARAM_PIN );
  }
  else
  {
    /* Do Nothing */
  }
  
  /* Check if the pin direction is configured as changeable */
  if(STD_OFF == Port_configurations[Pin]->pin_directionChangeable) 
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                     PORT_E_DIRECTION_UNCHANGEABLE );
  }
  else
  {
    /* Do Nothing */
  }
#endif 
  switch(Port_configurations[Pin].port_num)
    {
      case 0: port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
              break;
      case 1: port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
              break;
      case 2: port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
              break;
      case 3: port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
              break;
      case 4: port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
              break;
      case 5: port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
              break;
    }
  
  if(PORT_PIN_IN == Direction)
    {
      /* Set pin as input */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[Pin]->pin_num);
    }
    else
    {
      /* Set pin as output */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[Pin]->pin_num);
    }
  
}
#endif

/*******************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
********************************************************************************/
void Port_RefreshPortDirection(void)
{
  volatile uint32 * port_Ptr = NULL_PTR;
  Port_PinType pin_ID = 0;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
  
  /* Check if the module is initialized */
  if(PORT_NOT_INITIALIZED == Port_Status)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                     PORT_E_UNINIT );
  }
  else
  {
    /* Do Nothing */
  }
#endif
  
  for(pin_ID = 0; pin_ID < PORT_PINS_NUM; pin_ID++)
  {
    /* Obtain the base address of the current port */
    switch(Port_configurations[pin_ID].port_num)
    {
      case 0: port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
              break;
      case 1: port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
              break;
      case 2: port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
              break;
      case 3: port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
              break;
      case 4: port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
              break;
      case 5: port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
              break;
    }
    
    /* Check if the current pin direction is changeable */
    if(STD_ON == Port_configurations[pin_ID].pin_directionChangeable)
    {
      continue;
    }
    else
    {
      if(PORT_PIN_IN == Port_configurations[pin_ID].pin_direction)
      {
        /* Refresh pin as input */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      else
      {
        /* Refresh pin as output */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIR_REG_OFFSET), Port_configurations[pin_ID].pin_num);
      }
      
    }
    
  }
  
}

#if (STD_ON == PORT_VERSION_INFO_API)
/*******************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version info
* Return value: None
* Description: Returns the version information of this module
********************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
  if(NULL_PTR == versioninfo)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID ,
                     PORT_E_POINTER );
  }
  else
  {
    /* Do Nothing */
  }
#endif
  
  /* Copying the version info into the storage the passed pointer is pointing to */
  versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
  versioninfo->moduleID = (uint16)PORT_MODULE_ID;
  versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
  
}
#endif

#if (STD_ON == PORT_SET_MODE_API)
/*******************************************************************************
* Service Name: Port_SetPinMode
* Service ID: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin  - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode
********************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
volatile uint32 * port_Ptr = NULL_PTR;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
  
  /* Check if the module is initialized */
  if(PORT_NOT_INITIALIZED == Port_Status)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                     PORT_E_UNINIT );
  }
  else
  {
    /* Do Nothing */
  }
  
  /* Check if the passed pin number is valid */
  if(PORT_PINS_NUM <= Pin)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                     PORT_E_PARAM_PIN );
  }
  else
  {
    /* Do Nothing */
  }
  
  /* Check if the mode is valid*/
  if(MAX_MODE_NUMBER < Mode)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                     PORT_E_PARAM_INVALID_MODE );
  }
  else
  {
    /* Do Nothing */
  }
  
  /* Check if the pin direction is configured as changeable */
  if(STD_OFF == Port_configurations[Pin].pin_modeChangeable)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                     PORT_E_MODE_UNCHANGEABLE );
  }
  else
  {
    /* Do Nothing */
  }
#endif

  switch(Port_configurations[Pin].port_num)
  {
    case 0: port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
    case 1: port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
    case 2: port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
    case 3: port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
    case 4: port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
    case 5: port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
    }
  
  if(PORT_ANALOG == Port_configurations[Pin].pin_mode)
  {
    /* Set the alterantive function bit */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[Pin].pin_num);
    /* Clear the peripheral function in the control register */
      *(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET) = 
              ((*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET)) & ~(PIN_MODE_MASK << Port_configurations[Pin].pin_num * SHIFT_4));
    /* Disable digital functionality */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_configurations[Pin].pin_num);
    /* Activate analog functionality */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_configurations[Pin].pin_num);
    /* Configuration is done for this pin, return */
    return;
  }
  else
  {
    /* Clear the Analog bit */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_configurations[Pin].pin_num);
      
    /* Check whether the mode is DIO or another mode */
    if(PORT_DIGITAL_IO == Port_configurations[Pin].pin_mode)
    {
      /* disable the alterantive function bit */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[Pin].pin_num);  
    }
    else
    {
      /* Set the alterantive function bit */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_ALT_FUNC_REG_OFFSET), Port_configurations[Pin].pin_num);
    }
    /* Set the peripheral function in the control register */
    *(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET) = 
            ((*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_CTL_REG_OFFSET)) & ~(PIN_MODE_MASK << Port_configurations[Pin].pin_num * SHIFT_4))
          | (Port_configurations[Pin].pin_mode << Port_configurations[Pin].pin_num * SHIFT_4);
    /* Enable the digital functionality */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)port_Ptr  + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_configurations[Pin].pin_num);
  } 
 
}
#endif