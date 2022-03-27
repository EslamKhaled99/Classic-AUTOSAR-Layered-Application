 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Dio.h"
#include "Dio_Regs.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Dio_ConfigType * Dio_PortChannels = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID,
		     DIO_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status       = DIO_INITIALIZED;
		Dio_PortChannels = ConfigPtr; /* address of the Structure */
	}
}

/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a value of the port.
************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
        volatile uint32 * Port_Ptr = NULL_PTR;
        boolean error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        /*Check if the driver is initialized*/
        if(DIO_NOT_INITIALIZED == Dio_Status)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_WRITE_PORT_SID, DIO_E_UNINIT);
                error = TRUE;
        }
        else
        {
          /*Do Nothing*/
        }
        /*Check if the port number is valid*/
        if(DIO_CONFIGURED_PORTS <= PortId)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
                error = TRUE;
        }
        else
        {
          /*Do Nothing*/
        }
#endif
        if(FALSE == error)
        {
                switch(Dio_PortChannels->Ports[PortId])
                {
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
                }
                if(STD_HIGH == Level)
                {
                    uint8 iterator;
                    for(iterator = 0; iterator < DIO_CONFIGURED_CHANNLES; iterator++)
                    {
                            SET_BIT(*Port_Ptr,Dio_PortChannels->Channels[iterator].Ch_Num);
                    }
                }
                else if(STD_LOW == Level)
                {
                    uint8 iterator;
                    for(iterator = 0; iterator < DIO_CONFIGURED_CHANNLES; iterator++)
                    {
                            CLEAR_BIT(*Port_Ptr,Dio_PortChannels->Channels[iterator].Ch_Num);
                    }
                }
        }
        else
        {
          /*Do Nothing*/
        }
}

/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType - Level of all channels of that port
* Description: Returns the level of all channels of that port.
************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
        volatile uint32 * Port_Ptr = NULL_PTR;
        Dio_PortLevelType output = 0x00;
        boolean error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        /*Check if the Dio Driver is initialized*/
        if(DIO_INITIALIZED == Dio_Status)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_READ_PORT_SID, DIO_E_UNINIT);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
        /*Check if the port number is valid*/
        if(DIO_CONFIGURED_PORTS <= PortId)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
#endif
        if(FALSE == error)
        {
                switch(Dio_PortChannels->Ports[PortId])
                {
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
                }
                uint8 iterator;
                for(iterator = 0; iterator < DIO_CONFIGURED_CHANNLES; iterator++)
                {
                        if(BIT_IS_SET(*Port_Ptr, Dio_PortChannels->Channels[iterator].Ch_Num))
                        {
                                SET_BIT(output,Dio_PortChannels->Channels[iterator].Ch_Num);
                        }
                        else
                        {
                                CLEAR_BIT(output,Dio_PortChannels->Channels[iterator].Ch_Num);
                        }
                }
                
        }
        else
        {
                /*Do Nothing*/
        }
        return output;
}

/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a subset of the adjoining bits of a port to a specified level.
************************************************************************************/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
        volatile uint32 * Port_Ptr = NULL_PTR;
        boolean error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        /*Check if the driver is initialized*/
        if(DIO_NOT_INITIALIZED == Dio_Status)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_UNINIT);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
        /*Check if the input configuration pointer isn't a Null pointer*/
        if(NULL_PTR == ChannelGroupIdPtr)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_CONFIG);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
        /*Check if the channel group is valid*/
        if(MAX_CHANNELS <= ChannelGroupIdPtr->offset)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
#endif
        if(FALSE == error)
        {
                switch(ChannelGroupIdPtr->PortIndex)
                {
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
                }
                *Port_Ptr = (*Port_Ptr & ~ChannelGroupIdPtr->mask) | (Level << ChannelGroupIdPtr->offset);
        }
        else
        {
                /*Do Nothing*/
        }          
}

/************************************************************************************
* Service Name: Dio_ReadChannelGroup
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
* Description: This Service reads a subset of the adjoining bits of a port.
************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
        volatile uint32 * Port_Ptr = NULL_PTR;
        Dio_PortLevelType output = 0x00;
        boolean error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        /*Check if the driver is initialized*/
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_GROUP_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        /*Check if the input configuration pointer isn't a Null pointer*/
        if(NULL_PTR == ChannelGroupIdPtr)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_CONFIG);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
        /*Check if the channel group is valid*/
        if(MAX_CHANNELS <= ChannelGroupIdPtr->offset)
        {
                Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
                error = TRUE;
        }
        else
        {
                /*Do Nothing*/
        }
#endif
        if(FALSE == error)
        {
                switch(ChannelGroupIdPtr->PortIndex)
                {
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
                }
                output = (*Port_Ptr & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset;
        }
        else
        {
                /*Do Nothing*/
        }   
        return output;
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels->Channels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		if(Level == STD_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*Port_Ptr,Dio_PortChannels->Channels[ChannelId].Ch_Num);
		}
		else if(Level == STD_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*Port_Ptr,Dio_PortChannels->Channels[ChannelId].Ch_Num);
		}
	}
	else
	{
		/* No Action Required */
	}

}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels->Channels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		/* Read the required channel */
		if(BIT_IS_SET(*Port_Ptr, Dio_PortChannels->Channels[ChannelId].Ch_Num))
		{
			output = STD_HIGH;
		}
		else
		{
			output = STD_LOW;
		}
	}
	else
	{
		/* No Action Required */
	}
        return output;
}

/************************************************************************************
* Service Name: Dio_GetVersionInfo
* Service ID[hex]: 0x12
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	Dio_LevelType output = STD_LOW;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_FLIP_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels->Channels[ChannelId].Port_Num)
		{
                    case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
                    case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
                    case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		/* Read the required channel and write the required level */
		if(BIT_IS_SET(*Port_Ptr, Dio_PortChannels->Channels[ChannelId].Ch_Num))
		{
			CLEAR_BIT(*Port_Ptr,Dio_PortChannels->Channels[ChannelId].Ch_Num);
			output = STD_LOW;
		}
		else
		{
			SET_BIT(*Port_Ptr, Dio_PortChannels->Channels[ChannelId].Ch_Num);
			output = STD_HIGH;
		}
	}
	else
	{
		/* No Action Required */
	}
        return output;
}
#endif
