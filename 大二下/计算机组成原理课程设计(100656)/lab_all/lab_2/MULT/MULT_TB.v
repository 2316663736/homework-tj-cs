module MULT_tb();

    reg clk;
    reg reset;
    reg [31:0] a, b;
    wire [63:0] z;
    

    MULT mult_inst(
        .clk(clk),
        .reset(reset),
        .a(a),
        .b(b),
        .z(z)
    );
    
 
    initial begin
        clk = 0;
        forever #5 clk = ~clk; 
    end
    

    initial begin

        reset = 1;
        a = 0;
        b = 0;
        #20;
        reset = 0;
        #10;
        

        a = 32'd5;
        b = 32'd7;
        #20;
        

        a = 32'd123;
        b = 32'hFFFFFF85; 
        #20;  
        
      
        a = 32'hFFFFFFB1; 
        b = 32'hFFFFFFD8; 
        #20;  
        

        a = 32'hFFFFFF9C; 
        b = 32'd50;
        #20;  
        
 
        a = 32'h7FFFFFFF; 
        b = 32'h80000000; 
        #20;  

        a = 32'h80000000; 
        b = 32'h80000000; 
        #20; 
        

        a = 32'h7FFFFFFF; 
        b = 32'h7FFFFFFF;
        #20; 
        
    
        a = 32'hFFFFFF00; 
        b = 32'd0;
        #20;  
        
 
        a = 32'd1;
        b = 32'hFFFFF000; 
        #20;  

        a = 32'hFFFFFFFF; 
        b = 32'd12345;
        #20;  
         
    end
endmodule