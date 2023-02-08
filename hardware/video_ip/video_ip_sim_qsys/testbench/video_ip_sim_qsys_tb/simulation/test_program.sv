//----------------------------------------------------------------------------------------------
// Modificacion del programa de test del tutorial de Altera
// This test module uses System Verilog syntax.
//----------------------------------------------------------------------------------------------


`timescale 1 ns / 1 ps

// console messaging level
`define VERBOSITY VERBOSITY_INFO



//----------------------------------------------------------------------------------------------
// DEFINICIÓN DE JERARQUÍA DE SEÑALES

`define CLK tb.video_ip_sim_qsys_inst_clk_bfm_clk_clk
`define RST tb.video_ip_sim_qsys_inst_reset_bfm_reset_reset
`define AV_MM_BFM tb.video_ip_sim_qsys_inst.mm_master_bfm_0

`define AV_ST_SINK_1_BFM tb.video_ip_sim_qsys_inst.mm_master_bfm_0
`define AV_ST_SOURCE_1_BFM tb.video_ip_sim_qsys_inst.mm_master_bfm_0

//----------------------------------------------------------------------------------------------


`define AV_ADDRESS_W 3
`define AV_DATA_W 32



module test_program();

import avalon_mm_pkg::*;
import verbosity_pkg::*;


reg [`AV_DATA_W-1:0] datos_out;
int j=0;


initial
begin

    set_verbosity(`VERBOSITY);
    `AV_MM_BFM.init();

    // Espera hasta que el reset esté inactivo
    wait(`RST == 1);
    #100

    // Escribe un dato en el esclavo
    avalon_write (3'h1,32'h00000102);  // Efecto: Eliminación de colores RGB. delete_rgb=1; elimina R

    repeat (20) @(posedge `CLK);

    // avalon_write (3'h1,32'h00005678);

    // $display("Operacion Escritura acabada");

    // repeat (20) @(posedge `CLK);

    // Lee dato del esclavo y comprueba si es correcto
    // avalon_read (3'h2,datos_out);

    // $display("Datos leidos del IP: %h",datos_out);

    j++;

    $display("//////// ITERACION %d /////////",j);
    
    $stop();

end


    // ============================================================
    // Tasks
    // ============================================================
    // Avalon-MM single-transaction read and write procedures.


    // ------------------------------------------------------------
    task avalon_write (
    // ------------------------------------------------------------

    input [`AV_ADDRESS_W-1:0] addr,
        input [`AV_DATA_W-1:0] data
    );
    begin
        // Construct the BFM request
        `AV_MM_BFM.set_command_request(REQ_WRITE);
        `AV_MM_BFM.set_command_idle(0, 0);
        `AV_MM_BFM.set_command_init_latency(0);
        `AV_MM_BFM.set_command_address(addr);
        `AV_MM_BFM.set_command_byte_enable('1,0);
        `AV_MM_BFM.set_command_data(data, 0);
        `AV_MM_BFM.set_command_burst_count(1);
        `AV_MM_BFM.set_command_burst_size(1);
        // Queue the command
        `AV_MM_BFM.push_command();
        // Wait until the transaction has completed
        while (`AV_MM_BFM.get_response_queue_size() != 1)
        @(posedge `CLK);
        // Dequeue the response and discard
        `AV_MM_BFM.pop_response();
    end

    endtask


    // ------------------------------------------------------------
    task avalon_read (
    // ------------------------------------------------------------

    input [`AV_ADDRESS_W-1:0] addr,
        output [`AV_DATA_W-1:0] data
    );
    begin

        // Construct the BFM request
        `AV_MM_BFM.set_command_request(REQ_READ);
        `AV_MM_BFM.set_command_idle(0, 0);
        `AV_MM_BFM.set_command_init_latency(0);
        `AV_MM_BFM.set_command_address(addr);
        `AV_MM_BFM.set_command_byte_enable('1,0);
        `AV_MM_BFM.set_command_data(0, 0);
        `AV_MM_BFM.set_command_burst_count(1);
        `AV_MM_BFM.set_command_burst_size(1);
        // Queue the command
        `AV_MM_BFM.push_command();
        // Wait until the transaction has completed
        while (`AV_MM_BFM.get_response_queue_size() != 1)
        @(posedge `CLK);
        // Dequeue the response and return the data
        `AV_MM_BFM.pop_response();
        data = `AV_MM_BFM.get_response_data(0);
    end

    endtask

endmodule


