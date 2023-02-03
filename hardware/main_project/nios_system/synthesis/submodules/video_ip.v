/* PROYECTO CHS 2022/2023
 * IP de vídeo
 * Fichero TOP
*/


module video_ip (
    
    input wire reset,  // reset
    input wire clk,  // reloj
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON-MM-SLAVE INTERFACE
    
    input wire chipselect,  // chip select
    input wire [2:0] address,  // dirección de acceso a registros
    input wire write,  // bit indicación de escritura
    input wire [31:0] writedata,  // datos de escritura: 32 bits
    input wire read,  // bit indicación de lectura
    output wire [31:0] readdata,  // datos de lectura: 32 bits
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SINK
    
    input wire valid_in,  // valid in
    output wire ready_out,  // ready, señal del sink al source.
    input wire [15:0] data_in,  // datos, colores RGB de 16 bits, serie.
    input wire startofpacket_in,  // indicador inicio frame
    input wire endofpacket_in,  // indicador fin frame
    
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SOURCE
    
    output wire valid_out,  // salida de datos válidos
    input wire ready_in,  // ready, señal del source al sink.
    output wire [15:0] data_out, // datos, salida
    output wire startofpacket_out,  // indicador inicio frame, salida
    output wire endofpacket_out  // indicador fin frame, salida
);


// las señales tienen un flujo: 

// "_in" ---> "in_reg" ---> "out_reg" ---> "_out"
//  sink --->    ip    --->    ip     ---> source

// in: procedente del avalon_source anterior (leídos por el avalon sink)
// reg: datos almacenados en esta IP
// out: datos de salida de esta IP, con latencia con respecto a "in" (enviados por avalon_source)

// Esto se debe a que debemos igualar la latencia de las señales de control con la de datos


wire [31:0] reg3, reg2, reg1, reg0;
wire [15:0] data_in_reg, data_out_reg;

wire ready_reg;  // Esta asignación es inmediata, no se registra

wire valid_in_reg;
reg valid_out_reg;

wire startofpacket_in_reg;
reg startofpacket_out_reg;

wire endofpacket_in_reg;
reg endofpacket_out_reg;


// ///////////////////////////////////////////////////////////////////

// INSTANCIACIÓN DEL AVALON_MM_SLAVE INTERFACE

avalon_mm_slave_interface U1_AVALON_MM_SLAVE_1 (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .chipselect(chipselect),  // chipselect
    .address(address),  // dirección acceso registros 
    
    .write(write),  // indicador escritura
    .writedata(writedata),  // datos de escritura
    
    .read(read),  // indicador lectura 
    .readdata(readdata),  // datos lectura
    
    .reg3(reg3),  // registro 3
    .reg2(reg2),  // registro 2
    .reg1(reg1),  // registro 1
    .reg0(reg0)  // registro 0
);



// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE

avalon_st_sink_interface U2_AVALON_ST_SINK_1 (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_in(valid_in),  // valid in
    .valid_reg(valid_in_reg),  // valid reg
    
    .ready_reg(ready_reg),
    .ready_out(ready_out),  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    .data_in(data_in),  // datos, colores RGB de 16 bits, serie.
    .data_reg(data_in_reg), // datos de entrada, registro en la IP
    
    .startofpacket_in(startofpacket_in),  // indicador inicio frame
    .startofpacket_reg(startofpacket_in_reg),  // indicador inicio frame, registro en la IP
    
    .endofpacket_in(endofpacket_in),  // indicador fin frame
    .endofpacket_reg(endofpacket_in_reg)  // indicador fin frame, registro en la IP
);



// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE

avalon_st_source_interface U3_AVALON_ST_SOURCE_1 (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_reg(valid_out_reg),  // salida de datos válidos
    .valid_out(valid_out),  // salida de datos válidos
    
    .ready_in(ready_in),  // ready, 
    .ready_reg(ready_reg),
    
    .data_reg(data_out_reg), // datos de salida, registro en la IP
    .data_out(data_out), // datos, salida
    
    .startofpacket_reg(startofpacket_out_reg),  // indicador inicio frame, de la IP
    .startofpacket_out(startofpacket_out),  // indicador inicio frame, salida
    
    .endofpacket_reg(endofpacket_out_reg),  // indicador fin frame, de la IP
    .endofpacket_out(endofpacket_out)  // indicador fin frame, salida
);



// INSTANCIACIÓN DEL MÓDULO DE EFECTOS DE VÍDEO

video_effects U4_VIDEO_EFFECTS_1 (
    .clk(clk),  // reloj
    .reset(reset),  // reset
    
    .effect(5'b00000),  // indica el efecto de vídeo a aplicar. 5 bits -> 5 efectos diferentes, por sencillez.
    
    // effect[4] : Eliminación de uno o varios colores RGB
    // effect[3] : Sustitución de uno o varios colores por un valor constante
    // effect[2] : Cuantificación
    // effect[1] : Escala de grises
    // effect[0] : Negativo
    
    .effect_delete_color(16'd0),  // indica el valor RGB a eliminar para los efectos que lo necesiten.
    .effect_substitute_color(16'd0),  // indica el valor RGB a aplicar para los efectos que lo necesiten.
    
    .video_data_in(data_in_reg),  // entrada de datos de vídeo, del avalon sink
    .video_data_out(data_out_reg)  // salida de datos de vídeo, procesados, al avalon source
);



// Ciclo adicional para igualar la latencia de las señales de control con la de datos
// Un ciclo adicional

always @(posedge clk)
begin
    
    // Si no está ready, congelamos las transferencias
    if (ready_reg)
    begin
        
        valid_out_reg <= valid_in_reg;
        startofpacket_out_reg <= startofpacket_in_reg;
        endofpacket_out_reg <= endofpacket_in_reg;
        
    end
    
end



endmodule


