module tb_segment7;

    reg [3:0] bcd;
    wire [6:0] seg;
    integer i;

    segment7 uut (
        .bcd(bcd), 
        .seg(seg)
    );

    initial begin
      for(i = 0;i < 16000;i = i+1000) 
        begin
            bcd = i/1000; 
            #10; 
        end     
    end
      
endmodule
