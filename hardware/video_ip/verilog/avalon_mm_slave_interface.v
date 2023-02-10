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
    input wire [6:0] address,  // dirección de acceso a registros
    
    input wire write,  // bit indicación de escritura
    input wire [31:0] writedata,  // datos de escritura: 32 bits
    
    input wire read,  // bit indicación de lectura
    output reg [31:0] readdata,  // datos de lectura: 32 bits
    
    // No necesitamos más señales
    
    // interfaces con nuestra lógica
    
    output reg [31:0] registers [7:0]  // registros de lectura y escritura, control, de 32 bits
    // Por ahora todos los registros son de lectura y escritura.
);

integer ii = 0;

// Inicializar registros
initial
begin

    for (ii = 0; ii < 6; ii = ii+1)
    begin
        registers[ii] = 32'd0;
    end

    readdata = 32'd0;
end



always @(posedge clk)
begin

    if (reset)  // Si hay un reset: borrar todos los registros
    begin
        
        for (ii = 0; ii < 6; ii = ii+1)
        begin
            registers[ii] = 32'd0;
        end
        
        readdata <= 32'd0;
    end
    
    else
    begin
        
        if (chipselect)  // Si se selecciona el periférico
        begin
            if (write)  // Si la señal del master es de escritura
            begin
                registers[address] <= writedata;
            end
            
            if (read)  // Si la señal es de lectura
            begin
                readdata <= registers[address];
            end
        end
        
    end
end

endmodule
