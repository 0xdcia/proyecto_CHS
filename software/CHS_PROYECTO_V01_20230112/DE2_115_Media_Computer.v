// Plantilla sistema basado en Nios II
// Ricardo Jose Colom Palero
// Version 17.1, 30 de julio de 2018

module DE2_115_Media_Computer (
	// Entradas
	CLOCK_50,
	CLOCK2_50,
	CLOCK3_50,
	
	// /////////////////////////////////////////////////////////////////////////
	TD_CLK27,  // reloj del vídeo TD
	// /////////////////////////////////////////////////////////////////////////
	
	KEY,
	SW,

	//  Comunicacion
	UART_RXD,
	
	// Audio
	AUD_ADCDAT,

	// Memoria Flash 
	FL_RY,

	//Memoria EPCS
	DATA0,
	
	// SD Card
	 SD_WP_N,

/*****************************************************************************/
	// Bidireccionales
	GPIO,

	// Memoria (SRAM)
	SRAM_DQ,
	
	// Memoria (SDRAM)
	DRAM_DQ,

	// Memoria Flash 
	FL_DQ,

	// Puerto PS2
	PS2_KBCLK,
	PS2_KBDAT,
	PS2_MSCLK,
	PS2_MSDAT,
	
	// Audio
	AUD_BCLK,
	AUD_ADCLRCK,
	AUD_DACLRCK,
	
	// LCD  16x2
	LCD_DATA,

	// Configuracion AV
	I2C_SDAT,
	
	// SD Card
	SD_CMD,
	SD_DAT,
	
/*****************************************************************************/
	// Salidas
	 
	// /////////////////////////////////////////////////////////////////////////
	// Vídeo TD
	
	// /////////////////////////////////////////////////////////////////////////
	
	TD_RESET_N,
	TDCLK27,
	
	// /////////////////////////////////////////////////////////////////////////
	
	TD_DATA,  // vector de señales de vídeo 	
	TD_HS,  // horizontal sync
	TD_VS,  // vertical sync
	
	//clk27_reset,  // clk27 del video td, reset
		
	// /////////////////////////////////////////////////////////////////////////
	
	
	
	// 	Simples
	LEDG,
	LEDR,

	HEX0,
	HEX1,
	HEX2,
	HEX3,
	HEX4,
	HEX5,
	HEX6,
	HEX7,
	
	// 	Memoria (SRAM)
	SRAM_ADDR,

	SRAM_CE_N,
	SRAM_WE_N,
	SRAM_OE_N,
	SRAM_UB_N,
	SRAM_LB_N,
	
	//  Comunicación
	UART_TXD,
	
	// Memoria (SDRAM)
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_RAS_N,
	DRAM_CLK,
	DRAM_CKE,
	DRAM_CS_N,
	DRAM_WE_N,
	DRAM_DQM,

	// Memoria Flash 
	FL_ADDR,
	FL_CE_N,
	FL_OE_N,
	FL_RST_N,
	FL_WE_N,
	FL_WP_N,
	
	// Audio
	AUD_XCK,
	AUD_DACDAT,
	
	// VGA
	VGA_CLK,
	VGA_HS,
	VGA_VS,
	VGA_BLANK_N,
	VGA_SYNC_N,
	VGA_R,
	VGA_G,
	VGA_B,

	// LCD 16x2
	LCD_ON,
	LCD_BLON,
	LCD_EN,
	LCD_RS,
	LCD_RW,
	
	// Configuracion AV
	I2C_SCLK,
	
	//Memoria EPCS
    DCLK,
    DATA1,
    FLASH_nCE,
	 
	 // SD Card
	 SD_CLK
	
);

/*****************************************************************************
 *                      Declaraciones de Parametros                          *
 *****************************************************************************/


/*****************************************************************************
 *                       Declaraciones de Puertos                            *
 *****************************************************************************/
// Entradas
input				CLOCK_50;
input				CLOCK2_50;
input				CLOCK3_50;
input				TD_CLK27;
input		[ 3: 0]	KEY;
input		[17: 0]	SW;

//  Comunicacion
input				UART_RXD;

//  Audio
input				AUD_ADCDAT;

// Memoria Flash 
input		      	FL_RY;

//  Memoria EPCS
input				DATA0;

// SD Card
input 			SD_WP_N;

/*****************************************************************************/
// Bidireccionales
inout		[35: 0]	GPIO;

// 	Memoria (SRAM)
inout		[15: 0]	SRAM_DQ;

//  Memoria (SDRAM)
inout		[31: 0]	DRAM_DQ;

// Memoria Flash 
inout		[ 7:0]	FL_DQ;

//  Puerto PS2
inout				PS2_KBCLK;
inout				PS2_KBDAT;
inout				PS2_MSCLK;
inout				PS2_MSDAT;

//  Audio
inout				AUD_BCLK;
inout				AUD_ADCLRCK;
inout				AUD_DACLRCK;

//  Configuracion AV
inout				I2C_SDAT;

//  LCD 16x2
inout		[ 7: 0]	LCD_DATA;

//  SD Card
inout 				SD_CMD;
inout		[ 3: 0]	SD_DAT;



/** ******************************************************************/

// VIDEO
// ////////////////////////////////////////////////////////////////////////////
output				TD_RESET_N;

// ////////////////////////////////////////////////////////////////////////////

/*****************************************************************************/
// Salidas

// 	Simples
output		[ 8: 0]	LEDG;
output		[17: 0]	LEDR;

output		[ 6: 0]	HEX0;
output		[ 6: 0]	HEX1;
output		[ 6: 0]	HEX2;
output		[ 6: 0]	HEX3;
output		[ 6: 0]	HEX4;
output		[ 6: 0]	HEX5;
output		[ 6: 0]	HEX6;
output		[ 6: 0]	HEX7;

// 	Memoria (SRAM)
output		[19: 0]	SRAM_ADDR;
output				SRAM_CE_N;
output				SRAM_WE_N;
output				SRAM_OE_N;
output				SRAM_UB_N;
output				SRAM_LB_N;

//  Comunicacion
output				UART_TXD;

//  Memoria (SDRAM)
output		[12: 0]	DRAM_ADDR;

output		[ 1: 0]	DRAM_BA;
output				DRAM_CAS_N;
output				DRAM_RAS_N;
output				DRAM_CLK;
output				DRAM_CKE;
output				DRAM_CS_N;
output				DRAM_WE_N;
output		[ 3: 0]	DRAM_DQM;

// Memoria Flash 
output		[22:0]	FL_ADDR;
output		        FL_CE_N;
output		        FL_OE_N;
output		        FL_RST_N;
output		        FL_WE_N;
output		        FL_WP_N;

//  Audio
output				AUD_XCK;
output				AUD_DACDAT;

//  VGA
output				VGA_CLK;
output				VGA_HS;
output				VGA_VS;
output				VGA_BLANK_N;
output				VGA_SYNC_N;
output		[ 7: 0]	VGA_R;
output		[ 7: 0]	VGA_G;
output		[ 7: 0]	VGA_B;

//  LCD 16x2
output				LCD_ON;
output				LCD_BLON;
output				LCD_EN;
output				LCD_RS;
output				LCD_RW;

//  Configuracion AV
output				I2C_SCLK;

//  Memoria EPCS
output			    DCLK;
output			    DATA1;
output			    FLASH_nCE;

//  SD Card
output				 SD_CLK;



// /////////////////////////////////////////////////////////////////////////
// Vídeo TD

input [7:0] TD_DATA;  // vector de señales de vídeo 	
input TD_HS;  // horizontal sync
input TD_VS;  // vertical sync
input TDCLK27;  // clk27 del video td, reset
// input clk27_reset,  // clk27 del video td, reset


// /////////////////////////////////////////////////////////////////////////

	
/*****************************************************************************
 *                 Internal Wires and Registers Declarations                 *
 *****************************************************************************/
// Internal Wires

//  MTL
wire						MTL_CLK;
wire						MTL_HS;
wire						MTL_VS;
wire			[ 7: 0]	MTL_R;
wire			[ 7: 0]	MTL_G;
wire			[ 7: 0]	MTL_B;

/*****************************************************************************
 *                            Logica Combinacional                           *
 *****************************************************************************/

// Asignaciones a Salidadas
// assign TD_RESET_N	= 1'b1;

// Configuracion Flash
assign	FL_RST_N = KEY[0];
assign	FL_WP_N = 1'b1;

// Configuracion SD Card
assign	SD_DAT[1] = 1'bZ;
assign	SD_DAT[2] = 1'bZ;

// GPIO MTL
assign 	GPIO[ 0]		= 1'bZ;
assign 	GPIO[ 1]		= MTL_CLK;
assign 	GPIO[ 2]		= 1'bZ;
assign 	GPIO[ 3]		= MTL_R[0];
assign 	GPIO[ 4]		= MTL_R[1];
assign 	GPIO[ 5]		= MTL_R[2];
assign 	GPIO[ 6]		= MTL_R[3];
assign 	GPIO[ 7]		= MTL_R[4];
assign 	GPIO[ 8]		= MTL_R[5];
assign 	GPIO[ 9]		= MTL_R[6];
assign 	GPIO[10]		= MTL_R[7];
assign 	GPIO[11]		= MTL_G[0];
assign 	GPIO[12]		= MTL_G[1];
assign 	GPIO[13]		= MTL_G[2];
assign 	GPIO[14]		= MTL_G[3];
assign 	GPIO[15]		= MTL_G[4];
assign 	GPIO[16]		= 1'bZ;
assign 	GPIO[17]		= 1'bZ;
assign 	GPIO[18]		= MTL_G[5];
assign 	GPIO[19]		= MTL_G[6];
assign 	GPIO[20]		= MTL_B[0];
assign 	GPIO[21]		= MTL_G[7];
assign 	GPIO[22]		= MTL_B[1];
assign 	GPIO[23]		= MTL_B[2];
assign 	GPIO[24]		= MTL_B[3];
assign 	GPIO[25]		= MTL_B[4];
assign 	GPIO[26]		= MTL_B[5];
assign 	GPIO[27]		= MTL_B[6];
assign 	GPIO[28]		= MTL_B[7];
assign 	GPIO[29]		= 1'bZ;
assign 	GPIO[30]		= MTL_HS;
assign 	GPIO[31]		= MTL_VS;
assign 	GPIO[32]		= 1'bZ;
assign 	GPIO[33]		= 1'bZ;
assign 	GPIO[34]		= 1'bZ;
assign 	GPIO[35]		= 1'bZ;


/*****************************************************************************
 *                              Modulos Internos                             *
 *****************************************************************************/
 
nios_system u0 (
        .clk_50_in_clk                             (CLOCK_50),                             //                         clk_50_in.clk
        .clk_50_2_in_clk                           (CLOCK2_50),                           //                       clk_50_2_in.clk
        .clk_50_3_in_clk                           (CLOCK3_50),                           //                       clk_50_3_in.clk
        .reset_bridge_in_reset_n                   (KEY[0]),                   //                   reset_bridge_in.reset_n
        .sys_clk_out_clk                           (),                           //                       sys_clk_out.clk
        .sdram_clk_out_clk                         (DRAM_CLK),                         //                     sdram_clk_out.clk
        .vga_clk_out_clk                           (),                           //                       vga_clk_out.clk
        .mtl_clk_out_clk                           (),                           //                       mtl_clk_out.clk
        .audio_clk_out_clk                         (AUD_XCK),                         //                     audio_clk_out.clk
        .sdram_wire_addr                           (DRAM_ADDR),                           //                        sdram_wire.addr
        .sdram_wire_ba                             (DRAM_BA),                             //                                  .ba
        .sdram_wire_cas_n                          (DRAM_CAS_N),                          //                                  .cas_n
        .sdram_wire_cke                            (DRAM_CKE),                            //                                  .cke
        .sdram_wire_cs_n                           (DRAM_CS_N),                           //                                  .cs_n
        .sdram_wire_dq                             (DRAM_DQ),                             //                                  .dq
        .sdram_wire_dqm                            (DRAM_DQM),                            //                                  .dqm
        .sdram_wire_ras_n                          (DRAM_RAS_N),                          //                                  .ras_n
        .sdram_wire_we_n                           (DRAM_WE_N),                           //                                  .we_n
        .flash_bridge_out_tcm_address_out          (FL_ADDR),          //                  flash_bridge_out.tcm_address_out
        .flash_bridge_out_tcm_read_n_out           (FL_OE_N),           //                                  .tcm_read_n_out
        .flash_bridge_out_tcm_write_n_out          (FL_WE_N),          //                                  .tcm_write_n_out
        .flash_bridge_out_tcm_data_out             (FL_DQ),             //                                  .tcm_data_out
        .flash_bridge_out_tcm_chipselect_n_out     (FL_CE_N),     //                                  .tcm_chipselect_n_out
        .red_leds_external_interface_export        (LEDR),        //       red_leds_external_interface.export
        .green_leds_external_interface_export      (LEDG),      //     green_leds_external_interface.export
        .hex3_hex0_external_interface_HEX0         (HEX0),         //      hex3_hex0_external_interface.HEX0
        .hex3_hex0_external_interface_HEX1         (HEX1),         //                                  .HEX1
        .hex3_hex0_external_interface_HEX2         (HEX2),         //                                  .HEX2
        .hex3_hex0_external_interface_HEX3         (HEX3),         //                                  .HEX3
        .hex7_hex4_external_interface_HEX4         (HEX4),         //      hex7_hex4_external_interface.HEX4
        .hex7_hex4_external_interface_HEX5         (HEX5),         //                                  .HEX5
        .hex7_hex4_external_interface_HEX6         (HEX6),         //                                  .HEX6
        .hex7_hex4_external_interface_HEX7         (HEX7),         //                                  .HEX7
        .switches_external_interface_export        (SW),        //       switches_external_interface.export
        .pushbuttons_external_interface_export     ({KEY[3:1], 1'b1}),     //    pushbuttons_external_interface.export
        .ps2_key_external_interface_CLK            (PS2_KBCLK),            //        ps2_key_external_interface.CLK
        .ps2_key_external_interface_DAT            (PS2_KBDAT),            //                                  .DAT
        .ps2_mouse_external_interface_CLK          (PS2_MSCLK),          //      ps2_mouse_external_interface.CLK
        .ps2_mouse_external_interface_DAT          (PS2_KBDAT),          //                                  .DAT
        .serial_port_external_interface_RXD        (UART_RXD),        //    serial_port_external_interface.RXD
        .serial_port_external_interface_TXD        (UART_TXD),        //                                  .TXD
        .char_lcd_external_interface_DATA          (LCD_DATA),          //       char_lcd_external_interface.DATA
        .char_lcd_external_interface_ON            (LCD_ON),            //                                  .ON
        .char_lcd_external_interface_BLON          (LCD_BLON),          //                                  .BLON
        .char_lcd_external_interface_EN            (LCD_EN),            //                                  .EN
        .char_lcd_external_interface_RS            (LCD_RS),            //                                  .RS
        .char_lcd_external_interface_RW            (LCD_RW),            //                                  .RW
        .audio_config_external_interface_SDAT      (I2C_SDAT),      //   audio_config_external_interface.SDAT
        .audio_config_external_interface_SCLK      (I2C_SCLK),      //                                  .SCLK
        .audio_external_interface_ADCDAT           (AUD_ADCDAT),           //          audio_external_interface.ADCDAT
        .audio_external_interface_ADCLRCK          (AUD_ADCLRCK),          //                                  .ADCLRCK
        .audio_external_interface_BCLK             (AUD_BCLK),             //                                  .BCLK
        .audio_external_interface_DACDAT           (AUD_DACDAT),           //                                  .DACDAT
        .audio_external_interface_DACLRCK          (AUD_DACLRCK),          //                                  .DACLRCK
        .sd_card_conduit_end_b_SD_cmd              (SD_CMD),              //               sd_card_conduit_end.b_SD_cmd
        .sd_card_conduit_end_b_SD_dat              (SD_DAT[0]),              //                                  .b_SD_dat
        .sd_card_conduit_end_b_SD_dat3             (SD_DAT[3]),             //                                  .b_SD_dat3
        .sd_card_conduit_end_o_SD_clock            (SD_CLK),            //                                  .o_SD_clock
        .sram_external_interface_DQ                (SRAM_DQ),                //           sram_external_interface.DQ
        .sram_external_interface_ADDR              (SRAM_ADDR),              //                                  .ADDR
        .sram_external_interface_LB_N              (SRAM_LB_N),              //                                  .LB_N
        .sram_external_interface_UB_N              (SRAM_UB_N),              //                                  .UB_N
        .sram_external_interface_CE_N              (SRAM_CE_N),              //                                  .CE_N
        .sram_external_interface_OE_N              (SRAM_OE_N),              //                                  .OE_N
        .sram_external_interface_WE_N              (SRAM_WE_N),              //                                  .WE_N
        .mtl_controller_external_interface_CLK     (MTL_CLK),     // mtl_controller_external_interface.CLK
        .mtl_controller_external_interface_HS      (MTL_HS),      //                                  .HS
        .mtl_controller_external_interface_VS      (MTL_VS),      //                                  .VS
        .mtl_controller_external_interface_DATA_EN (), //                                  .DATA_EN
        .mtl_controller_external_interface_R       (MTL_R),       //                                  .R
        .mtl_controller_external_interface_G       (MTL_G),       //                                  .G
        .mtl_controller_external_interface_B       (MTL_B),       //                                  .B
		  .camera_video_decoder_external_interface_TD_CLK27      (TD_CLK27),  // camera_video_decoder_external_interface.TD_CLK27
        .camera_video_decoder_external_interface_TD_DATA       (TD_DATA),  // .TD_DATA
        .camera_video_decoder_external_interface_TD_HS         (TD_HS),  // .TD_HS
        .camera_video_decoder_external_interface_TD_VS         (TD_VS),  // .TD_VS
        .camera_video_decoder_external_interface_clk27_reset   (),  // clk27_reset
        .camera_video_decoder_external_interface_TD_RESET      (TD_RESET_N),  // .TD_RESET
        .camera_video_decoder_external_interface_overflow_flag ()  // overflow_flag
    ); 


	 
endmodule

