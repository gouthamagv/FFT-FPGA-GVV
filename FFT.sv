parameter BIT_INT = 16;
parameter BIT_FRAC = 16;
parameter W = BIT_INT+BIT_FRAC;

`include "butterfly.sv"
`include "computeMatrix.sv"


module FFT #(parameter N = 4, parameter W=1)
            (input logic signed [W:0] x[N][1:0],
             output logic signed [W+N-1:0] X[N][1:0]);
            
  logic signed [W:0] xe[N/2][1:0], xo[N/2][1:0];
  logic signed [W+N/2-1:0] Xe[N/2][1:0], Xo[N/2][1:0];
  
  always_comb 
    for(int k=0; k<N/2; k++)begin
      xe[k][1:0] = x[2*k][1:0];
      xo[k][1:0] = x[2*k+1][1:0];
    end
           
  if(N[0]) begin  
    butterfly #(.N(N), .W(W)) m_butterfly(.Xe(Xe), .Xo(Xo), .X(X));
    
    FFT #(.N(N/2), .W(W)) FFT_e(.x(xe), .X(Xe));
    FFT #(.N(N/2), .W(W)) FFT_o(.x(xo), .X(Xo));   
  end
  
  else computeMatrix #(.N(N), .W(W)) Matrix(.x(x), .X(X));
  
endmodule: FFT


