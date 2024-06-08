/* * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *              XTEA testbench
 *
 *      author: Antônio dos Santos
 *      version: 5/6/2024
 *      github: @santosantonio1
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

`timescale 1ns/1ps

module tb;

localparam PERIOD = 10, N_TESTS = 10;

reg clock, reset, cfg, start;
reg [127:0] data_i, key;
wire ready, busy;
wire [127:0] data_o;

integer i;

// Test, keys and mode vectors
reg[127:0] tests_vector[0:N_TESTS-1];
reg[127:0] keys_vector[0:N_TESTS-1];
reg cfg_vector[0:N_TESTS-1];

//-----------------------------------------------------
//  Main test process
//-----------------------------------------------------
initial
begin
    $readmemh("./tests/numbers.txt", tests_vector);
    $readmemh("./tests/keys.txt", keys_vector);
    $readmemb("./tests/cfg.txt", cfg_vector);

    start = 0;
    reset = 1;

    data_i = 0;
    key = 0;
    cfg = 0;

    #(2*PERIOD)
    reset = 0;

    i = 0;
    while(i<N_TESTS)
    begin
        data_i = tests_vector[i];
        key = keys_vector[i];
        cfg = cfg_vector[i];
        start = 1;

        #(2*PERIOD)
        start = 0;

        // Wait for the operation to finish before starting a new one
        wait(ready == 1);
        wait(busy == 0);
        #(10*PERIOD)

        i = i+1;
    end
end

//----------------------------------------------
//  Clock signal
//----------------------------------------------
initial
begin
    clock = 0;
    forever #(PERIOD/2) clock = ~clock;   
end

//-----------------------------
//  XTEA device 
//-----------------------------
xtea_top XTEA(
    .clock(clock),
    .reset(reset),
    .start(start),
    .cfg(cfg),
    .data_i(data_i),
    .key(key),
    .ready(ready),
    .busy(busy),
    .data_o
);

endmodule