/************************************************************************
 *  File: OV9712.h
 *  Group: OV9712 Firmware
 ***********************************************************************/

#ifndef OV9712_h
#define OV9712_h

/************************************************************************
 *                             Includes                      *
 ***********************************************************************/
#include "main.h"
#include "OV9712_calc.h"
#include "OV9712_regs.h"
#include "printers.h"

/************************************************************************
 *                             Local Types                              *
 ***********************************************************************/
typedef struct
{
	/* Pins */
	GPIO_t RESET, LOW_VOLTAGE, POWER_DOWN, MASTER_CLOCK;
} OV9712_pins_t;

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint8_t depth;
	uint32_t *buffer;
	uint16_t buffer_size;
} camera_params_t;

typedef struct
{
	uint8_t address;
	I2C_Handle_t *i2c;
	DCMI_Handle_t *dcmi;
	OV9712_pins_t *pins;
	camera_params_t params;
} OV9712_t;

/************************************************************************
 *                             Local Functions                              *
 ***********************************************************************/
void OV9712_Init( OV9712_t *, camera_params_t *, I2C_Handle_t *, DCMI_Handle_t *, OV9712_pins_t * );
void OV9712_Write( OV9712_t *, uint8_t, uint8_t );
void OV9712_Enable( OV9712_t * );
void OV9712_Disable( OV9712_t * );
void OV9712_Reset( OV9712_t * );

typedef struct
{
	void (*Init)(OV9712_t*, camera_params_t *, I2C_Handle_t*, DCMI_Handle_t*, OV9712_pins_t*);
	void (*Write)(OV9712_t*, uint8_t, uint8_t);
	void (*Enable)(OV9712_t*);
	void (*Disable)(OV9712_t*);
	void (*Reset)(OV9712_t*);
} OV9712_functions;

static OV9712_functions OV9712_Functions =
{
		.Init = OV9712_Init,
		.Write = OV9712_Write,
		.Enable = OV9712_Enable,
		.Disable = OV9712_Disable,
		.Reset = OV9712_Reset
};

/************************************************************************
 *                       Local Instances                                *
 ***********************************************************************/
static OV9712_pins_t Default_OV9712_Pins =
{
		{ CAM_RESET_GPIO_Port, 	CAM_RESET_Pin }, // RESET
		{ EN_1V5_GPIO_Port, 	EN_1V5_Pin }, // LOW_VOLTAGE
		{ PWDN_GPIO_Port,	 	PWDN_Pin }, // POWER_DOWN
		{ MCLK_GPIO_Port, 		MCLK_Pin }  // MASTER_CLOCK
};

static OV9712_t OV9712 = { OV9712_ADDR };

#define FRAME_DEPTH 1
static uint32_t camera_buffer[FRAME_WIDTH_BASE * FRAME_HEIGHT * FRAME_DEPTH / 2 ];
static camera_params_t camera_params = { FRAME_WIDTH_BASE, FRAME_HEIGHT, FRAME_DEPTH, camera_buffer };

#endif
