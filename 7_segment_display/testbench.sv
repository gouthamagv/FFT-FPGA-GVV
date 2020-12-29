module testbench;

  reg [3:0] num;
    wire [6:0] seg;
    integer i;
  
    seven_segment uut (
        .num(num), 
        .seg(seg)
    );

    initial begin
      for(i = 0;i < 10000;i = i+1000)
        begin
            num = i/1000; 
            #10; //wait for 10 ns
        end     
    end
      
endmodule
