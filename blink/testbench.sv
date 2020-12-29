`timescale 1ns/1ps

module testbench;
  reg clock=0;
  wire led_state;
  
  blinking A(
    .clock(clock),
    .led_state(led_state)
  );
  always #10 clock=-clock;
endmodule
