module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input logic clk,
    input logic rst, 
    input logic en,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk)
    if (en) count <= count + {{WIDTH-1{1'b0}}, {1'b1}};
    else count <= count - {{WIDTH-1{1'b0}}, {1'b1}};
    

endmodule
