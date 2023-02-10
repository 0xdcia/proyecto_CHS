/* PROYECTO CHS 2022/2023
 * IP de vídeo
 * Fichero TOP
*/



module video_ip (
    
    input wire reset,  // reset
    input wire clk,  // reloj
    
    // ///////////////////////////////////////////////////////////////
    // INTERRUPCIONES
    
    output wire irq_sender,
    
    // ///////////////////////////////////////////////////////////////
    // AVALON-MM-SLAVE INTERFACE
    
    input wire chipselect,  // chip select
    input wire [2:0] address,  // dirección de acceso a registros
    input wire write,  // bit indicación de escritura
    input wire [31:0] writedata,  // datos de escritura: 32 bits
    input wire read,  // bit indicación de lectura
    output wire [31:0] readdata,  // datos de lectura: 32 bits
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SINK_CAMERA
    
    input wire camera_valid_in,  // valid in
    output wire camera_ready_out,  // ready, señal del sink al source.
    input wire [15:0] camera_data_in,  // datos, colores RGB de 16 bits, serie.
    input wire camera_startofpacket_in,  // indicador inicio frame
    input wire camera_endofpacket_in,  // indicador fin frame
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SINK_CAMERA
    
    input wire sdcard_valid_in,  // valid in
    output wire sdcard_ready_out,  // ready, señal del sink al source.
    input wire [15:0] sdcard_data_in,  // datos, colores RGB de 16 bits, serie.
    input wire sdcard_startofpacket_in,  // indicador inicio frame
    input wire sdcard_endofpacket_in,  // indicador fin frame
    
    // ///////////////////////////////////////////////////////////////
    // AVALON_STREAMING_SOURCE
    
    output wire source_valid_out,  // salida de datos válidos
    input wire source_ready_in,  // ready, señal del source al sink.
    output wire [15:0] source_data_out, // datos, salida
    output wire source_startofpacket_out,  // indicador inicio frame, salida
    output wire source_endofpacket_out  // indicador fin frame, salida
);



// las señales tienen un flujo: 

// "_in" ---> "in_reg" ---> "out_reg" ---> "_out"
//  sink --->    ip    --->    ip     ---> source

// in: procedente del avalon_source anterior (leídos por el avalon sink)
// reg: datos almacenados en esta IP
// out: datos de salida de esta IP, con latencia con respecto a "in" (enviados por avalon_source)

// Esto se debe a que debemos igualar la latencia de las señales de control con la de datos



// ///////////////////////////////////////////////////////////////////////////////
// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE DE LA CÁMARA

wire camera_ready_reg;  // Esta asignación es inmediata, no se registra

wire camera_startofpacket_in_reg;
wire camera_endofpacket_in_reg;
wire camera_valid_in_reg;

wire [15:0] camera_data_in_reg;

avalon_st_sink_interface U1_AVALON_ST_SINK_CAMERA (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_in(camera_valid_in),  // valid in
    .valid_reg(camera_valid_in_reg),  // valid reg
    
    .ready_reg(camera_ready_reg),
    .ready_out(camera_ready_out),  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    .data_in(camera_data_in),  // datos, colores RGB de 16 bits, serie.
    .data_reg(camera_data_in_reg), // datos de entrada, registro en la IP
    
    .startofpacket_in(camera_startofpacket_in),  // indicador inicio frame
    .startofpacket_reg(camera_startofpacket_in_reg),  // indicador inicio frame, registro en la IP
    
    .endofpacket_in(camera_endofpacket_in),  // indicador fin frame
    .endofpacket_reg(camera_endofpacket_in_reg)  // indicador fin frame, registro en la IP
);



// ///////////////////////////////////////////////////////////////////////////////
// INSTANCIACIÓN DEL AVALON_STREAMING_SINK INTERFACE DE LA SD CARD

wire sdcard_ready_reg;  // Esta asignación es inmediata, no se registra

wire sdcard_startofpacket_in_reg;
wire sdcard_endofpacket_in_reg;
wire sdcard_valid_in_reg;

wire [15:0] sdcard_data_in_reg;

avalon_st_sink_interface U2_AVALON_ST_SINK_SDCARD (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_in(sdcard_valid_in),  // valid in
    .valid_reg(sdcard_valid_in_reg),  // valid reg
    
    .ready_reg(sdcard_ready_reg),
    .ready_out(sdcard_ready_out),  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    .data_in(sdcard_data_in),  // datos, colores RGB de 16 bits, serie.
    .data_reg(sdcard_data_in_reg), // datos de entrada, registro en la IP
    
    .startofpacket_in(sdcard_startofpacket_in),  // indicador inicio frame
    .startofpacket_reg(sdcard_startofpacket_in_reg),  // indicador inicio frame, registro en la IP
    
    .endofpacket_in(sdcard_endofpacket_in),  // indicador fin frame
    .endofpacket_reg(sdcard_endofpacket_in_reg)  // indicador fin frame, registro en la IP
);



// ///////////////////////////////////////////////////////////////////////////////
// INSTANCIACIÓN DEL AVALON_STREAMING_SOURCE INTERFACE

wire source_ready_reg;

reg source_startofpacket_out_reg;
reg source_endofpacket_out_reg;
reg source_valid_out_reg;

wire [15:0] source_data_out_reg;

avalon_st_source_interface U3_AVALON_ST_SOURCE (
    .reset(reset),  // reset
    .clk(clk),  // reloj
    
    .valid_reg(source_valid_out_reg),  // salida de datos válidos
    .valid_out(source_valid_out),  // salida de datos válidos
    
    .ready_in(source_ready_in),  // ready, 
    .ready_reg(source_ready_reg),
    
    .data_reg(source_data_out_reg), // datos de salida, registro en la IP
    .data_out(source_data_out), // datos, salida
    
    .startofpacket_reg(source_startofpacket_out_reg),  // indicador inicio frame, de la IP
    .startofpacket_out(source_startofpacket_out),  // indicador inicio frame, salida
    
    .endofpacket_reg(source_endofpacket_out_reg),  // indicador fin frame, de la IP
    .endofpacket_out(source_endofpacket_out)  // indicador fin frame, salida
);



// ///////////////////////////////////////////////////////////////////////////////
// INSTANCIACIÓN DEL AVALON_MM_SLAVE INTERFACE

wire [31:0] reg3, reg2, reg1, reg0;  // registros del avalon-mm

avalon_mm_slave_interface U4_AVALON_MM_SLAVE (
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
    .reg0(reg0)   // registro 0
);



// ///////////////////////////////////////////////////////////////////////////////
// MAPA DE REGISTROS DE AVALON-MM

/*
+------+-----------------------------------------------+---------------+--------------+
| reg0 | [31:2]                                        | irq_enable[1] | pause_req[0] |
+------+---------+----------------------+---------+----+------------+--+--------------+
| reg1 | [31:18] | quantif_level[17:16] | [15:10] | delete_rgb[9:8] | effect_sel[7:0] |
+------+---------+----------------------+---------+-----------------+-----------------+
| reg2 | color_key[31:16]               | color_mask[15:0]                            |
+------+--------------------------------+---------------------------------------------+
| reg3 | [31:16]                        | color_substitute[15:0]                      |
+------+--------------------------------+---------------------------------------------+

Leyenda:
- nombre[A:B] = valor, bits útiles leídos desde el X al Y.
- [A:B] = región vacía (no se lee)
*/



// ///////////////////////////////////////////////////////////////////////////////
// INSTANCIACIÓN DEL MÓDULO DE EFECTOS DE VÍDEO
// Consultar el mapa de registros para entender las asignaciones

video_effects U5_VIDEO_EFFECTS (
    .clk(clk),  // reloj
    .reset(reset),  // reset
    
    .effect(reg1[7:0]),  // indica el efecto de vídeo a aplicar
    
    // effect[0] : Sustitución de uno o varios colores por un valor constante (Chroma Key)
    //      Usar la variable effect_color_key para especificarlo
    //      Usar la variable effect_color_key_mask para especificar el rango (bits considerados y bits ignorados)
    //      Usar la variable effect_color_substitute para especificar el color de sustitución
    
    // effect[1] : Eliminación de uno o varios colores RGB
    //      Usar la variable effect_delete_rgb para especificar la componente a borrar
    
    // effect[2] : Escala de grises. Se usa la técnica de luminosidad
    
    // effect[3] : Cuantificación
    //      Usar la variable effect_quantif_level para especificar la precisión
    
    // effect[4] : Negativo
    
    .effect_delete_rgb(reg1[9:8]),  // indica el valor RGB a eliminar
    
    // effect_delete_rgb = 00 : No se elimina nada
    // effect_delete_rgb = 01 : Eliminar R
    // effect_delete_rgb = 10 : Eliminar G
    // effect_delete_rgb = 11 : Eliminar B
    
    .effect_quantif_level(reg1[17:16]),  // indica el número de componentes a borrar (cuantificar) de cada color
    
    // effect_quantif_level = 00 : No se elimina nada
    // effect_quantif_level = 01 : Se elimina el último bit (LSB)
    // effect_quantif_level = 10 : Se eliminan los dos últimos bits
    // effect_quantif_level = 11 : Se eliminan los tres últimos bits
    
    .effect_color_key(reg2[31:16]),  // indica el valor RGB a eliminar para los efectos que lo necesiten
    .effect_color_key_threshold(reg2[15:0]),  // indica la tolerancia de colores (+-rango por componente)
    .effect_color_substitute(reg3[15:0]),  // indica el valor RGB por el que sustituir el color eliminado
    
    .video_data_in_camera(camera_data_in_reg),  // entrada de datos de vídeo de la cámara
    .video_data_in_sdcard(sdcard_data_in_reg),  // entrada de datos de vídeo de la SD Card
    
    .video_data_out(source_data_out_reg)  // salida de datos de vídeo, procesados, al avalon source
);



// ///////////////////////////////////////////////////////////////////////////////
// INTERRUPCIONES DE PAUSA DE VÍDEO

reg pause;
wire pause_req;

reg interrupt;
wire interrupt_req;

assign pause_req = reg0[0];
assign interrupt_req = reg0[1];
assign irq_sender = interrupt;


always @(posedge clk)
begin

    if(pause_req & source_endofpacket_out_reg)
    begin
        pause <= 1'b1;
    end
    
    if(~pause_req)
    begin
        pause <= 1'b0;
    end
    
end


// Si el efecto seleccionado es cambiar a la SD card hay que redirigir señales de control.
//wire change_to_sdcard = reg1[0];

/* if (change_to_sdcard)
begin
    sdcard_ready_reg = source_ready_reg;
    camera_ready_reg = 1'b0;
end
    
else
begin
    camera_ready_reg = source_ready_reg;
    sdcard_ready_reg = 1'b0;
end */


assign camera_ready_reg = source_ready_reg;

/*
assign sdcard_ready_reg = (source_ready_in & source_valid_out_reg) | sdcard_sync;
assign camera_ready_reg = (source_ready_in & source_valid_out_reg) | camera_sync;

assign output_startofpacket = foreground_startofpacket;
assign output_endofpacket = foreground_endofpacket;
assign output_valid = valid;

wire camera_sync, sdcard_sync;


assign camera_sync = (camera_valid_in_reg & sdcard_valid_in_reg &
              ((sdcard_startofpacket_in_reg & ~camera_startofpacket_in_reg) |
               (sdcard_endofpacket_in_reg & ~camera_endofpacket_in_reg)));
                    
assign sdcard_sync = (camera_valid_in_reg & sdcard_valid_in_reg &
              ((camera_startofpacket_in_reg & ~sdcard_startofpacket_in_reg) |
               (camera_endofpacket_in_reg & ~sdcard_endofpacket_in_reg)));
*/

always @(posedge clk)
begin
    
    // ///////////////////////////////////////////////////////////////////////////////
    // CONTROL DE LATENCIA
    // Ciclo adicional para igualar la latencia de las señales de control con la de datos
    // Si no está ready, congelamos las transferencias
    

    //source_valid_out_reg <= camera_valid_in_reg & sdcard_valid_in_reg & ~camera_sync & ~sdcard_sync;


    if (camera_valid_in_reg & ~pause)
    begin
    
        source_valid_out_reg <= camera_valid_in_reg;
        source_startofpacket_out_reg <= camera_startofpacket_in_reg;
        source_endofpacket_out_reg <= camera_endofpacket_in_reg;

        /*if (change_to_sdcard)
        begin
            source_valid_out_reg <= sdcard_valid_in_reg;
            source_startofpacket_out_reg <= sdcard_startofpacket_in_reg;
            source_endofpacket_out_reg <= sdcard_endofpacket_in_reg;
        end
        
        else
        begin
            source_valid_out_reg <= camera_valid_in_reg;
            source_startofpacket_out_reg <= camera_startofpacket_in_reg;
            source_endofpacket_out_reg <= camera_endofpacket_in_reg;
        end*/
        
    end
    
    
    // ///////////////////////////////////////////////////////////////////////////////
    // PAUSA E INTERRUPCION
    
    if (pause)
    begin
    
        source_valid_out_reg <= 1'b0;
        
        if (interrupt_req)
        begin
            interrupt = 1'b1;
        end
        
        else
        begin
            interrupt = 1'b0;
        end
        
    end
    
end



endmodule


