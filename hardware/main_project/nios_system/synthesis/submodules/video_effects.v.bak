/* PROYECTO CHS 2022/2023
 * Módulo de implementación de efectos de vídeo.
*/


module video_effects (
    input wire clk,  // reloj
    input wire reset,  // reset
    
    input wire [4:0] effect,  // indica el efecto de vídeo a aplicar. 5 bits
    
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
    
    input wire [1:0] effect_delete_rgb,  // indica el valor RGB a eliminar
    
    // effect_delete_rgb = 00 : No se elimina nada
    // effect_delete_rgb = 01 : Eliminar R
    // effect_delete_rgb = 10 : Eliminar G
    // effect_delete_rgb = 11 : Eliminar B
    
    input wire [1:0] effect_quantif_level,  // indica el número de componentes a borrar (cuantificar) de cada color
    
    // effect_quantif_level = 00 : No se elimina nada
    // effect_quantif_level = 01 : Se elimina el último bit (LSB)
    // effect_quantif_level = 10 : Se eliminan los dos últimos bits
    // effect_quantif_level = 11 : Se eliminan los tres últimos bits
    
    input wire [15:0] effect_color_key,  // indica el valor RGB a eliminar para los efectos que lo necesiten
    input wire [15:0] effect_color_key_mask,  // indica la máscara de colores (rango) de colores a eliminar 
    input wire [15:0] effect_color_substitute,  // indica el valor RGB por el que sustituir el color eliminado
    
    input wire [15:0] video_data_in,  // entrada de datos de vídeo, del avalon sink
    output reg [15:0] video_data_out  // salida de datos de vídeo, procesados, al avalon source
    
);


// Señales internas 

reg [15:0] video_data_mid;  // Net de asignación secuencial de filtros
reg [4:0] video_aux_gs;  // Valores intermedios de cálculos para filtro greyscale


always @(posedge clk)
begin

    video_data_mid = video_data_in;
    
    // Pueden aplicarse varios filtros simultáneamente.
    // Están definidos por prioridad secuencial: los primeros IFs se aplican antes.
    // Por eso se usa esta estructura de ifs encadenados y asignaciones combinacionales.
    
    
    // 1. Sustitución de uno o varios colores por un valor constante (Chroma Key)
    if (effect[0] == 1'b1)
    begin
        // Si (pixel & mask) menos (key & mask) es cero => está en rango => sustituirlo
        if ((video_data_mid & effect_color_key_mask) - (effect_color_key & effect_color_key_mask) == 16'b0)
        begin
            video_data_mid = effect_color_substitute;
        end
    end
    
    
    // 2. Eliminación de uno o varios colores RGB
    if (effect[1] == 1'b1)
    begin
        case (effect_delete_rgb) 
            2'b01: video_data_mid = {5'b0, video_data_mid[10:5], video_data_mid[4:0]};
            2'b10: video_data_mid = {video_data_mid[15:11], 6'b0, video_data_mid[4:0]};
            2'b11: video_data_mid = {video_data_mid[15:11], video_data_mid[10:5], 5'b0};
        endcase
    end
    
    
    // 3. Escala de grises: Conversión de RGB a escala de grises
    if (effect[2] == 1'b1)
    begin
        // Grayscale por luminosidad aproximada: 0.25 * R; 0,5 * G; 0,25* B
        // Para el Green usamos 5 bits, los más significativos (el último es ignorado).
        video_aux_gs = (video_data_mid[15:11] >> 2) + (video_data_mid[10:6] >> 1) + (video_data_mid[4:0] >> 2);
        
        // Concatenación de bits, compensando el bit verde que no hemos considerado antes
        video_data_mid = {video_aux_gs, video_aux_gs, 1'b0, video_aux_gs};
    end
    
    
    // 4. Cuantificación: reducción de la precisión del color
    if (effect[3] == 1'b1)
    begin
        case (effect_quantif_level) 
            2'b01: video_data_mid = {(video_data_mid[15:11] >> 1), (video_data_mid[10:5] >> 1), (video_data_mid[4:0] >> 1)};
            2'b10: video_data_mid = {(video_data_mid[15:11] >> 2), (video_data_mid[10:5] >> 2), (video_data_mid[4:0] >> 2)};
            2'b11: video_data_mid = {(video_data_mid[15:11] >> 3), (video_data_mid[10:5] >> 3), (video_data_mid[4:0] >> 3)};
        endcase
    end
    
    
    // 5. Negativo: invertir bits
    if (effect[4] == 1'b1)
    begin
        video_data_mid = ~video_data_mid;
    end
    
    
    // Si no entra en ningún caso, simplemente se asigna a la salida.
    video_data_out = video_data_mid;
    
end


endmodule 


