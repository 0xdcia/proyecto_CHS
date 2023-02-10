/* PROYECTO CHS 2022/2023
 * Módulo de implementación de efectos de vídeo.
*/


module video_effects (
    input wire clk,  // reloj
    input wire reset,  // reset
    
    input wire [7:0] effect,  // indica el efecto de vídeo a aplicar. 5 bits
    
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
    input wire [15:0] effect_color_key_threshold,  // indica la tolerancia de colores (+-rango por componente)
    input wire [15:0] effect_color_substitute,  // indica el valor RGB por el que sustituir el color eliminado
    
    input wire [15:0] video_data_in_camera,  // entrada de datos de camara de vídeo
    input wire [15:0] video_data_in_sdcard,  // entrada de datos de imagen de la SD
    output reg [15:0] video_data_out  // salida de datos de vídeo, procesados, al avalon source
    
);


// Señales internas 

// Nets de asignación secuencial de filtros, pipeline
reg [15:0] video_data_proc_0, video_data_proc_1, video_data_proc_2,
           video_data_proc_3, video_data_proc_4;

reg [4:0] video_aux_gs;  // Valores auxiliares de cálculos para filtro greyscale


// /////////////////////////////////////////////////////////////////////////////////
// Pipelining, primer ciclo

always @(posedge clk)
begin
    
    // Pueden aplicarse varios filtros simultáneamente.
    // Están definidos por prioridad secuencial: los primeros IFs se aplican antes.
    // Por eso se usa esta estructura de ifs encadenados y asignaciones combinacionales.
    
    if (reset)
    begin
        video_data_proc_0 <= 16'b0;
        video_data_proc_1 <= 16'b0;
        video_data_proc_2 <= 16'b0;
        video_data_proc_3 <= 16'b0;
        video_data_proc_4 <= 16'b0;
        video_data_out <= 16'b0;
    end
    else
    begin
    
        // 0. Seleccionar entre vídeo de la cámara o de la SD
        if (effect[0] == 1'b1)
        begin
            video_data_proc_0 <= video_data_in_sdcard;
        end
        else
        begin
            video_data_proc_0 <= video_data_in_camera;
        end
        
        
        // 1. Sustitución de uno o varios colores por un valor constante (Chroma Key)
        if (effect[1] == 1'b1)
        begin
            // Si (pixel & mask) menos (key & mask) es cero => está en rango => sustituirlo
            // (video_data_proc[15:11] >> 2) + (video_data_proc[10:6] >> 1) + (video_data_proc[4:0] >> 2);
            
            if ( 
                ((video_data_proc_0[15:11] < (effect_color_key[15:11] + effect_color_key_threshold[15:11])) | 
                ((video_data_proc_0[15:11] > (effect_color_key[15:11] - effect_color_key_threshold[15:11]))))
                &
                ((video_data_proc_0[10:5] < (effect_color_key[10:5] + effect_color_key_threshold[10:5])) | 
                ((video_data_proc_0[10:5] > (effect_color_key[10:5] - effect_color_key_threshold[10:5]))))
                &
                ((video_data_proc_0[4:0] < (effect_color_key[4:0] + effect_color_key_threshold[4:0])) | 
                ((video_data_proc_0[4:0] > (effect_color_key[4:0] - effect_color_key_threshold[4:0]))))
                )
            begin
                video_data_proc_1 <= effect_color_substitute;
            end
        end
        else
        begin
            video_data_proc_1 <= video_data_proc_0;
        end
        
        
        // 2. Eliminación de uno o varios colores RGB
        if (effect[2] == 1'b1)
        begin
            case (effect_delete_rgb) 
                2'b01: video_data_proc_2 <= {5'b0, video_data_proc_1[10:5], video_data_proc_1[4:0]};
                2'b10: video_data_proc_2 <= {video_data_proc_1[15:11], 6'b0, video_data_proc_1[4:0]};
                2'b11: video_data_proc_2 <= {video_data_proc_1[15:11], video_data_proc_1[10:5], 5'b0};
                default: video_data_proc_2 <= video_data_proc_1;
            endcase
        end
        else
        begin
            video_data_proc_2 <= video_data_proc_1;
        end
        
        
        // 3. Escala de grises: Conversión de RGB a escala de grises
        if (effect[3] == 1'b1)
        begin
            // Grayscale por luminosidad aproximada: 0.25 * R; 0,5 * G; 0,25* B
            // Para el Green usamos 5 bits, los más significativos (el último es ignorado).
            video_aux_gs = (video_data_proc_2[15:11] >> 2) + (video_data_proc_2[10:6] >> 1) + (video_data_proc_2[4:0] >> 2);
            
            // Concatenación de bits, compensando el bit verde que no hemos considerado antes
            video_data_proc_3 <= {video_aux_gs, video_aux_gs, 1'b0, video_aux_gs};
        end
        else
        begin
            video_data_proc_3 <= video_data_proc_2;
        end
        
        
        // 4. Cuantificación: reducción de la precisión del color
        if (effect[4] == 1'b1)
        begin
            case (effect_quantif_level) 
                2'b01: video_data_proc_4 <= {video_data_proc_3[15:12], video_data_proc_3[12],
                                            video_data_proc_3[10:7], {2{video_data_proc_3[7]}},
                                            video_data_proc_3[4:1], video_data_proc_3[1]};
                
                2'b10: video_data_proc_4 <= {video_data_proc_3[15:13], {2{video_data_proc_3[13]}},
                                            video_data_proc_3[10:8], {3{video_data_proc_3[8]}},
                                            video_data_proc_3[4:2], {2{video_data_proc_3[2]}}};
                
                2'b11: video_data_proc_4 <= {video_data_proc_3[15:14], {3{video_data_proc_3[14]}},
                                            video_data_proc_3[10:9], {4{video_data_proc_3[9]}},
                                            video_data_proc_3[4:3], {3{video_data_proc_3[3]}}};
                                            
                default: video_data_proc_4 <= video_data_proc_3;
            endcase
        end
        else
        begin
            video_data_proc_4 <= video_data_proc_3;
        end
        
        
        // 5. Negativo: invertir bits
        if (effect[5] == 1'b1)
        begin
            video_data_out <= ~video_data_proc_4;
        end
        else
        begin
            video_data_out <= video_data_proc_4;
        end
        
        // Si no entra en ningún caso, simplemente se asigna a la salida.
        // video_data_out <= video_data_proc_5;
    end
    
end



endmodule 


