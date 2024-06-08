/* * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *    XTEA encryption driver
 *
 *      author: Antônio dos Santos
 *      version: 5/6/2024
 *      github: @santosantonio1
 *
 * * * * * * * * * * * * * * * * * * * * * * * */

// ------------------
//  States
// ------------------
`define IDLE 3'b000
`define LOOP 3'b001
`define UPDATE_Y 3'b010
`define UPDATE_Z 3'b011
`define DONE 3'b101

module xtea_enc(
    input clock, reset, en, start,
    input[127:0] data_i, key,
    output ready,
    output[127:0] data_o
);

// Auxiliar registers for flipping the original input and final output
reg[127:0] d, k, result;

// 
wire[31:0] y0, z0, y1, z1;
assign y0 = d[127:96], z0 = d[95:64],
       y1 = d[ 63:32], z1 = d[31:0];

reg[31:0] sum, delta;

// keys[] iterator
wire[1:0] idx;

// keys[idx]
wire[31:0] key_at_idx;

// Registers for replicating a for loop
reg[6:0] i;
reg[2:0] EA, PE;

// -----------------------------------------------
//  Initialization and change of states
// -----------------------------------------------
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
            if(start && en) PE <= `LOOP;
            else            PE <= `IDLE;

        `LOOP:
            if(i<32)    PE <= `UPDATE_Y;
            else        PE <= `DONE;

        `UPDATE_Y:      PE <= `UPDATE_Z;
        `UPDATE_Z:      PE <= `LOOP;
        `DONE:          PE <= `IDLE;
        default:        PE <= `IDLE;
    endcase
end

//--------------------------------------
//  Operations inside for loop
//--------------------------------------
always @(posedge clock, posedge reset)
begin
    if(reset) begin
        d <= 0;
        k <= 0;

        result <= 0;

        sum <= 0;
        delta <= 32'h9E3779B9;
        i <= 0;
    end
    else
        case(EA)
            `IDLE:
            begin
            // ----------------------------------------------------------
            //  Flips input[] and key[] 
            // ----------------------------------------------------------
                d <= {data_i[31:0], data_i[63:32], data_i[95:64], data_i[127:96]};
                k <= {key[31:0], key[63:32], key[95:64], key[127:96]};

                sum <= 0;
                delta <= 32'h9E3779B9;
                i <= 0;
            end

            `UPDATE_Z:
            begin
                d[95:64] <= z0 + ((((y0 << 4) ^ (y0 >> 5)) + y0) ^ (sum + key_at_idx));
                d[31:0] <= z1 + ((((y1 << 4) ^ (y1 >> 5)) + y1) ^ (sum + key_at_idx));
                i <= i + 1;
            end

            `UPDATE_Y:
            begin
                d[127:96] <= y0 + ((((z0 << 4) ^ (z0 >> 5)) + z0) ^ (sum + key_at_idx));
                d[63:32] <= y1 + ((((z1 << 4) ^ (z1 >> 5)) + z1) ^ (sum + key_at_idx));
                sum <= sum + delta;
            end

            `DONE:
                result <= d;

            // Do nothing if outside for loop
            default: begin 

            end
        endcase
end

assign ready = (EA == `DONE) ? 1 : 0;

// Flips result[]
assign data_o = {result[31:0], result[63:32], result[95:64], result[127:96]};


// Defines idx as (sum & 3), (sum >> 11 & 3) or 0
assign idx = (EA == `UPDATE_Y) ? sum & 3 :
             (EA == `UPDATE_Z) ? (sum>>11) & 3 : 0;

// ...
assign key_at_idx = (idx == 0) ? k[127:96] :
                    (idx == 1) ? k[ 95:64] : 
                    (idx == 2) ? k[ 63:32] : k[31:0];

endmodule