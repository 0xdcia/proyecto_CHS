/* PROYECTO CHS 2022/2023
 * Avalon streaming sink interface de la IP de vídeo
 * 
 * Implementación a partir de los recursos de Intel/Altera:
 * 
 * Altera Corp, "Avalon Interface Specifications. 
 * Ch.6: Avalon Streaming Interfaces: 6.2: Avalon-ST Interface
 * Signals" document ver. 1.2, april 2009
*/

// Señales necesarias extraídas de la interfaz del 
// avalon_streaming_source del avalon_pixel_source del 
// video_dma_controller_ip_input, elemento del qsys que nos sirve los
// datos por streaming con un formato determinado.

// Señales necesarias: 
// clk, ready, valid, startofpacket, endofpacket, data[15:0]
// startofpacket y endofpacket indican el principio y fin de un frame?


module avalon_st_sink_interface (
    
    input wire reset,  // reset
    input wire clk,  // reloj
    
    input wire ready_reg,
    output wire ready_out,  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    input wire valid_in,  // valid in
    output wire valid_reg,  // valid reg
    
    input wire [15:0] data_in,  // datos, colores RGB de 16 bits, serie.
    output wire [15:0] data_reg, // datos, registro en la IP
    
    input wire startofpacket_in,  // indicador inicio frame
    input wire endofpacket_in,  // indicador fin frame
    
    output wire startofpacket_reg,  // indicador inicio frame, registro en la IP
    output wire endofpacket_reg  // indicador fin frame, registro en la IP
);



// listo para recibir datos inmediatamente cuando el bloque inferior lo esté
assign ready_out = ready_reg;

// pasamos el válido con misma latencia que los datos
assign valid_reg = valid_in;

// transferencias para que sea accesible por la IP
assign data_reg = data_in;
assign startofpacket_reg = startofpacket_in;
assign endofpacket_reg = endofpacket_in;


/*
always @(posedge clk)
begin
    if (reset)  // Si hay un reset: borrar todos los registros
    begin
        data_reg <= 16'd0;
    end
    
    else
    begin
        if (ready_reg)
        begin
            // pasamos el válido con misma latencia que los datos
            valid_reg <= valid_in;
            
            // transferencias para que sea accesible por la IP
            data_reg <= data_in;
            startofpacket_reg <= startofpacket_in;
            endofpacket_reg <= endofpacket_in;
        end
        // si no está ready: no hacer nada (se mantiene el dato anterior)
    end
end
*/


endmodule


