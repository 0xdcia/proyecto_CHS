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
    
    input reset,  // reset
    input clk,  // reloj
    
    input valid_in,  // valid in
    output valid_reg,  // valid reg
    
    input ready_reg,
    output ready_out,  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior.
    
    input [15:0] data_sink,  // datos, colores RGB de 16 bits, serie.
    output [15:0] data_reg, // datos, registro en la IP
    
    input startofpacket_in,  // indicador inicio frame
    input endofpacket_in,  // indicador fin frame
    
    output startofpacket_reg,  // indicador inicio frame, registro en la IP
    output endofpacket_reg  // indicador fin frame, registro en la IP
);



// listo para recibir datos inmediatamente cuando el bloque inferior lo esté
ready_out <= ready_reg;



always @(posedge clk)
begin
    if (reset)  // Si hay un reset: borrar todos los registros
    begin
        data_sink <= 16'd0;
    end
    
    else
    begin
        if (valid)  // Si hay datos válidos
        begin
            // pasamos el válido con misma latencia que los datos
            valid_reg <= valid_in;
            
            // transferencias para que sea accesible por la IP
            data_sink <= data;
            startofpacket_reg <= startofpacket_in;
            endofpacket_reg <= endofpacket_in;
        end
    end
end

endmodule
