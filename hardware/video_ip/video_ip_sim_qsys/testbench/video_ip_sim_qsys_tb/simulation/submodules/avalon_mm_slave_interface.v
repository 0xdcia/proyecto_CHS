/* PROYECTO CHS 2022/2023
 * Avalon MM-slave interface de la IP de vídeo
 * 
 * Implementación a partir de los recursos de Intel/Altera:
 * 
 * "Avalon Interface Specifications. Ch.3: Avalon Memory-Mapped Interfaces", Altera Corp, document ver. 1.2, april 2009
*/


module avalon_mm_slave_interface (
    
    // interfaces básicos de conexión con Avalon
    
    input wire reset,  // reset
    input wire clk,  // reloj
    
    input wire chipselect,  // chip select
    input wire [2:0] address,  // dirección de acceso a registros
    
    input wire write,  // bit indicación de escritura
    input wire [31:0] writedata,  // datos de escritura: 32 bits
    
    input wire read,  // bit indicación de lectura
    output reg [31:0] readdata,  // datos de lectura: 32 bits
    
    // No necesitamos más señales
    
    // interfaces con nuestra lógica
    
    output reg [31:0] reg3, reg2, reg1, reg0  // registros de lectura y escritura, control, de 32 bits
    // Por ahora todos los registros son de lectura y escritura.
);



// Inicializar registros
initial
begin
    reg0 = 32'd0;
    reg1 = 32'd0;
    reg2 = 32'd0;
    reg3 = 32'd0;
    readdata = 32'd0;
end


always @(posedge clk)
begin
    if (reset)  // Si hay un reset: borrar todos los registros
    begin
        reg0 <= 32'd0;
        reg1 <= 32'd0;
        reg2 <= 32'd0;
        reg3 <= 32'd0;
        readdata <= 32'd0;
    end
    
    else
    begin
        if (chipselect)  // Si se selecciona el periférico
        begin
            if (write)  // Si la señal del master es de escritura
            begin
                case (address)  // En qué dirección escribir
                    3'd0: reg0 <= writedata;
                    3'd1: reg1 <= writedata;
                    3'd2: reg2 <= writedata;
                    3'd3: reg3 <= writedata;
                endcase
            end
            
            if (read)  // Si la señal es de lectura
            begin
                case (address)
                    3'd0: readdata <= reg0;
                    3'd1: readdata <= reg1;
                    3'd2: readdata <= reg2;
                    3'd3: readdata <= reg3;
                    default: readdata <= 32'd0;
                endcase
            end
        end
    end
end

endmodule
