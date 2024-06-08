/* * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *    XTEA top driver
 *
 *      author: Antônio dos Santos
 *      version: 5/6/2024
 *      github: @santosantonio1
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

//------------------
//  States
//------------------
`define IDLE 3'b000
`define ENC_OP 3'b001
`define DEC_OP 3'b010
`define ENC_DONE 3'b011
`define DEC_DONE 3'b100

module xtea_top(
    input clock, reset, cfg, start,
    input[127:0] data_i, key,
    output busy, ready,
    output[127:0] data_o
);

reg[2:0] EA, PE;
wire[127:0] enc_out, dec_out;
wire enc_r, dec_r;

//-----------------------------------------------
//  Initialization and change of states
//-----------------------------------------------
always @(posedge clock, posedge reset)
begin
    if(reset) begin
        EA <= `IDLE;
    end
    else begin
        EA <= PE;
    end
end

// -----------------------------
//   Definition of FSM
// -----------------------------
always @*
begin
    case(EA)
        `IDLE:
        begin
            if(start && cfg)   
                PE <= `ENC_OP;
            else if(start && !cfg) 
                    PE <= `DEC_OP;
                 else 
                    PE <= `IDLE;
        end

        `ENC_OP:
            if(enc_r)   PE <= `ENC_DONE;
            else        PE <= `ENC_OP;

        `DEC_OP:
            if(dec_r)   PE <= `DEC_DONE;
            else        PE <= `DEC_OP;
        
        `ENC_DONE:      PE <= `IDLE;
        
        `DEC_DONE:      PE <= `IDLE;

        default:        PE <= `IDLE;
    endcase
end

//------------------------------
//  XTEA Encryption driver
//------------------------------
xtea_enc ENC_DRIVER(
    .clock(clock), .reset(reset), .en(cfg),
    .start(start), .data_i(data_i), .key(key), 
    .ready(enc_r), .data_o(enc_out)
);

//------------------------------
//  XTEA Decryption driver
//------------------------------
xtea_dec DEC_DRIVER(
    .clock(clock), .reset(reset), .en(cfg),
    .start(start), .data_i(data_i), .key(key), 
    .ready(dec_r), .data_o(dec_out)
);

assign data_o = (EA == `ENC_DONE) ? enc_out :
                (EA == `DEC_DONE) ? dec_out : 0;

assign ready = (enc_r || dec_r);

assign busy = (EA != `IDLE) ? 1 : 0; 

endmodule