/* PROYECTO CHS 2022/2023
 * IP de vídeo
 * Fichero TOP
*/

module video_ip (
    
    input reset,  // reset
    input clk,  // reloj
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON-MM-SLAVE INTERFACE
    
    input chipselect,  // chip select
    input [2:0] address,  // dirección de acceso a registros
    
    input write,  // bit indicación de escritura
    input [31:0] writedata,  // datos de escritura: 32 bits
    
    input read,  // bit indicación de lectura
    output [31:0] readdata,  // datos de lectura: 32 bits
    
    output reg [31:0] reg3, reg2, reg1, reg0,  // registros de escritura y lectura, control, de 32 bits.
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SINK
    
    input valid_in,  // valid in
    // output valid_reg,  // valid reg
    
    // input ready_reg,
    output ready_out,  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    input [15:0] data_sink,  // datos, colores RGB de 16 bits, serie.
    // output [15:0] data_reg, // datos, registro en la IP
    
    input startofpacket_in,  // indicador inicio frame
    input endofpacket_in,  // indicador fin frame
    
    // output startofpacket_reg,  // indicador inicio frame, registro en la IP
    // output endofpacket_reg,  // indicador fin frame, registro en la IP
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SOURCE
    
    // input valid_reg,  // salida de datos válidos
    output valid_out,  // salida de datos válidos
    
    input ready_in,  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior. Se pasa al registro, y del registro al sink, y del sink al anterior.
    // output ready_reg,
    
    input [15:0] data_reg,  // datos, registro de la IP
    output [15:0] data_source, // datos, salida
    
    // input startofpacket_reg,  // indicador inicio frame, de la IP
    // input endofpacket_reg,  // indicador fin frame, de la IP
    
    output startofpacket_out,  // indicador inicio frame, salida
    output endofpacket_out  // indicador fin frame, salida
    
);


// las señales tienen un flujo: 

// "_in" ---> "_reg" ---> "_out"
//  sink --->   ip   ---> source

// in: procedente del avalon_source anterior (leídos por el avalon sink)
// reg: datos almacenados en esta IP
// out: datos de salida de esta IP, con latencia con respecto a "in" (enviados por avalon_source)


// ///////////////////////////////////////////////////////////////////

// INSTANCIACIÓN DEL AVALON_MM_SLAVE INTERFACE

avalon_mm_slave_interface U1_AVALON_MM_SLAVE_1 (
    .reset(reset),
    .clk(clk),
    .chipselect(chipselect),
    .address(address),
    .write(write),
    .writedata(writedata),
    .read(read),
    .readdata(readdata),
    .reg3(reg3),
    .reg2(reg2),
    .reg1(reg1),
    .reg0(reg0)
);



// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE

avalon_st_sink_interface U2_AVALON_ST_SINK_1 (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_in(valid_in),  // valid in
    .valid_reg(valid_reg),  // valid reg
    
    .ready_reg(ready_reg),
    .ready_out(ready_out),  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    .data_sink(data_sink),  // datos, colores RGB de 16 bits, serie.
    .data_reg(data_reg), // datos, registro en la IP
    
    .startofpacket_in(startofpacket_in),  // indicador inicio frame
    .endofpacket_in(endofpacket_in),  // indicador fin frame
    
    .startofpacket_reg(startofpacket_reg),  // indicador inicio frame, registro en la IP
    .endofpacket_reg(endofpacket_reg)  // indicador fin frame, registro en la IP
);



// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE

avalon_st_source_interface U3_AVALON_ST_SOURCE_1 (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_reg(valid_reg),  // salida de datos válidos
    .valid_out(valid_out),  // salida de datos válidos
    
    .ready_in(ready_in),  // ready, 
    .ready_reg(ready_reg),
    
    .data_reg(data_reg),  // datos, registro de la IP
    .data_source(data_source), // datos, salida
    
    .startofpacket_reg(startofpacket_reg),  // indicador inicio frame, de la IP
    .endofpacket_reg(endofpacket_reg),  // indicador fin frame, de la IP
    
    .startofpacket_out(startofpacket_out),  // indicador inicio frame, salida
    .endofpacket_out(endofpacket_out)  // indicador fin frame, salida
);


endmodule
