/* PROYECTO CHS 2022/2023
 * Módulo de implementación de efectos de vídeo.
*/


module video_effects (
    input wire clk,  // reloj
    input wire reset,  // reset
    
    input wire [4:0] effect,  // indica el efecto de vídeo a aplicar. 5 bits -> 5 efectos diferentes, por sencillez.
    
    // effect[4] : Eliminación de uno o varios colores RGB
    // effect[3] : Sustitución de uno o varios colores por un valor constante
    // effect[2] : Cuantificación
    // effect[1] : Escala de grises
    // effect[0] : Negativo
    
    input wire [15:0] effect_delete_color,  // indica el valor RGB a eliminar para los efectos que lo necesiten.
    input wire [15:0] effect_substitute_color,  // indica el valor RGB a aplicar para los efectos que lo necesiten.
    
    input wire [15:0] video_data_in,  // entrada de datos de vídeo, del avalon sink
    output reg [15:0] video_data_out  // salida de datos de vídeo, procesados, al avalon source
    
);



always @(posedge clk)
begin

    case (effect)  // Si hay un efecto que aplicar
    
        // Eliminación de uno o varios colores RGB
        5'b00001: video_data_out <= video_data_in;
        
        // Sustitución de uno o varios colores por un valor constante
        5'b00010: video_data_out <= video_data_in;
        
        // Cuantificación: reducción de la precisión del color
        5'b00100: video_data_out <= video_data_in;
        
        // Escala de grises: Conversión de RGB a escala de grises
        5'b01000: video_data_out <= video_data_in;
        
        // Negativo: invertir bits
        5'b10000: video_data_out <= ~video_data_in;
        
        // En cualquier otro caso
        default: video_data_out <= video_data_in;
        
    endcase
end


endmodule 


