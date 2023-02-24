/************************************************************************
 *  File: master.c
 *  Group: Rho Core
 ***********************************************************************/

/***************************************************************************************/
/*                                    Includes                                         */
/***************************************************************************************/
#include "master.h"
#include "printers.h"

/***************************************************************************************/
/*                                  Core Routines                                      */
/***************************************************************************************/
/* INITIALIZING State Routine */
void InitializePlatform( void )
{
//    dmap_t x[CAPTURE_WIDTH] = { 0 }, y[CAPTURE_HEIGHT] = { 0 };
//    SpoofDensityMap( x, CAPTURE_WIDTH );
//    SpoofDensityMap( y, CAPTURE_HEIGHT );
//    DrawDensityMap( x, CAPTURE_WIDTH );
//    DrawDensityMap( y, CAPTURE_HEIGHT );
//    PrintDensityMaps( x, CAPTURE_WIDTH, y, CAPTURE_HEIGHT );

    PlatformFunctions.Init( &Platform, HOST_COMM_PROTOCOL, (generic_handle_t)Master.IOs->HOST_DEFAULT_CHANNEL );
}

/* CONNECTING_TO_HOST State Routine */
void ConnectToHost( void )
{
#ifdef PERFORM_HOST_PING_FOR_INIT
  while( PlatformFunctions.Host.Command( PING_HOST, NEEDED ) != OK )
  {
    PlatformFunctions.Wait( HOST_COMMAND_WAIT_TIME );
  }
#endif
}

/* CONFIGURING State Routine */
void ConfigureApplication( void )
{
#ifdef __OV9712__
  OV9712_Functions.Init( &OV9712, &camera_params, Master.IOs->CAMERA_COMM_CHANNEL, Master.IOs->CAMERA_DATA_CHANNEL, &Default_OV9712_Pins );
#endif
#ifdef __RHO__
  RhoSystem.Functions.Perform.ConnectToInterface( &PlatformFunctions, &Platform.CameraFlags );
  RhoSystem.Functions.Perform.Initialize( CAMERA_PORT, UART_TX_PORT );
#endif
}

/* READY State Routine */
void ExitInitialization( void )
{
#ifdef __RHO__
  RhoSystem.Functions.Perform.Activate();
#endif
	if( SystemFunctions.State.IsIn( &System, READY ) )
		MasterFunctions.Run();
	else
		PlatformFunctions.Wait(250);
}

/* ACTIVE State Routine */
inline void ApplicationCore( void )
{
#ifdef __RHO__
    RhoSystem.Functions.Perform.CoreProcess();
#else
#warning "No application core."
#endif
}

/* SYS_ERROR State Routine */
void SystemError( void )
{
    LOG( ALWAYS, "System error! Resetting in" );
    for( uint8_t i = 3 ; i > 0; i-- )
    {
        LOG_BARE( ALWAYS, " %d", i );
        PlatformFunctions.Wait(1000);
    }
    PlatformFunctions.Reset();
}

/***************************************************************************************/
/*                                Master Initialize                                    */
/***************************************************************************************/
void Master_Connect( master_ios_t * ios )
{
	Master.IOs = ios;
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	MasterFunctions.Init();
}

void Master_Init( void )
{
	/* Initialize state manager */
	SystemFunctions.Init( &System, &global_states_list );

	/* Initialize core platform */
	SystemFunctions.State.Enter( &System, INITIALIZING );

	/* Connect to host, this is critical for finishing initialization hence endless loop */
	SystemFunctions.State.Enter( &System, CONNECTING_TO_HOST );

	/* Configure application items */
	SystemFunctions.State.Enter( &System, CONFIGURING );

	/* Exit initialization, enter run */
	SystemFunctions.State.Enter( &System, READY );
}


__IO uint32_t frame_captured = 0;
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  frame_captured++;
}
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{
  frame_captured++;
}


/***************************************************************************************/
/*                                   Master Run                                        */
/***************************************************************************************/
void Master_Run( void )
{
	SystemFunctions.State.Set( &System, ACTIVE );
	PlatformFunctions.CAM.Resume( OV9712.dcmi );
	while(1)
	{
		if( frame_captured != 0 )
		{
			frame_captured = 0;
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		}
//		SystemFunctions.State.Perform( &System );
	}
}
