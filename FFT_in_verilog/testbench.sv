`timescale 1ns/1ps

`include "FFT.sv"

`define SAMPLES 8
parameter N = `SAMPLES;

module top();
  
  logic signed [W:0] x[N][1:0];
  logic signed [W+N-1:0] X[N][1:0];

  FFT #(.N(N), .W(W)) RFFT(.x(x), .X(X));
  
  initial begin
    for(int k=0; k<N; k++)begin
      x[k][0]=k<<<BIT_FRAC;
      x[k][1]=0;
    end
    
    #1
    testFFTinput(.x(x), .X(X));
    $finish;
  end
  
  localparam K=1<<BIT_FRAC;
  
  task testFFTinput(input logic signed [W:0] x[N][1:0], 
                    input logic signed [W+N-1:0] X[N][1:0]);
    
    for(int k=0; k<N; k++)
      $display("x[%0d]=%0f+i*(%0f), X[%0d]=%f+i*(%f)", 
                k, real'(x[k][0])/K, real'(x[k][1])/K, 
                k, real'(X[k][0])/K, real'(X[k][1])/K);
  endtask: testFFTinput

endmodule: top
