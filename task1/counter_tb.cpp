#include "Vcounter.h"   //mandatory header files
#include "verilated.h"
#include "verilated_vcd_c.h"

int main (int argc, char **argv, char **env){
    int i; //counts the number of clock cycles to simulate
    int clk; //the module clock signal 

    Verilated:: commandArgs (argc, argv);
    //init top verilog instance
    Vcounter* top = new Vcounter;  //instantiate the counter module as Vcounter which is the name of all generated files this is the DUT (device under testing)
    //init trace dump
    Verilated::traceEverOn (true); //turn on signal tracing and tell Verilator to dump waveform data to counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC; 
    top->trace (tfp, 99); 
    tfp->open ("counter.vcd");

    //initialize simulation inputs
    top->clk = 1; //only top level signals are visible
    top->rst = 1; 
    top->en = 0; 

    //run simulation for many clock cycles
    for (i=0; i < 300; i++){ //for loop where simulation happens - i counts clock cycles
        //dump vars into VCDfile and toggle clock 
        for (clk = 0; clk < 2; clk++){ //for loop to toggle clock and outputs trace for each half of the clock cycle and forces model to evaluate on both edges of clock 
            tfp->dump (2*i+clk);
            top->clk = !top->clk; 
            top->eval(); 
        }
        top->rst = (i<2); //vertical bar meaning??
        top->en = ((i>4) & (i<=13) | (i >= 16));  
        if (Verilated::gotFinish()) exit (0);
    }
    tfp->close(); 
    exit(0);
}
