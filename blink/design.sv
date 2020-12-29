// Code your design here
module blinking(
input wire clock,
output reg led_state
);
  int count = 0;
  always@ (posedge clock) begin
    if(count == 9999) begin
      count=0;
      led_state =-led_state;
    end
    else begin
      count++;
    end
  end
endmodule
