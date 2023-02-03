/* PROYECTO CHS 2022/2023
 * Avalon streaming source interface de la IP de vídeo
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


module avalon_st_source_interface (
    
    input wire reset,  // reset
    input wire clk,  // reloj
    
    input wire ready_in,  // ready, señal del sink al source. Indica si la IP está lista para recibir datos al source anterior. Se pasa al registro, y del registro al sink, y del sink al anterior.
    output wire ready_reg,
    
    input wire valid_reg,  // salida de datos válidos
    output reg valid_out,  // salida de datos válidos
    
    input wire [15:0] data_reg,  // datos, registro de la IP
    output reg [15:0] data_out, // datos, salida
    
    input wire startofpacket_reg,  // indicador inicio frame, de la IP
    input wire endofpacket_reg,  // indicador fin frame, de la IP
    
    output reg startofpacket_out,  // indicador inicio frame, salida
    output reg endofpacket_out  // indicador fin frame, salida
);


// listo para recibir datos inmediatamente cuando el bloque inferior lo esté
assign ready_reg = ready_in;


always @(posedge clk)
begin
    
    if (reset)  // Si hay un reset: borrar todos los registros
    begin
        data_out <= 16'd0;
    end
    
    else
    begin
        if (ready_reg)
        begin
            // pasamos el válido con misma latencia que los datos
            valid_out <= valid_reg;
            
            // transferencias para que sea accesible por la IP
            data_out <= data_reg;
            startofpacket_out <= startofpacket_reg;
            endofpacket_out <= endofpacket_reg;
        end
    end
end

endmodule
