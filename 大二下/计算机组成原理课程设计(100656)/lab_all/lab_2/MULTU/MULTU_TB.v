module MULTU_tb();

    reg clk;
    reg reset;
    reg [31:0] a, b;
    wire [63:0] z;
    

    MULTU multu_inst(
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
        

        a = 32'd12345;
        b = 32'd6789;
        #20;          

        a = 32'hFFFFFFFF; 
        b = 32'd2;
        #20;  
        
      
        a = 32'hFFFFFFFF; 
        b = 32'hFFFFFFFF; 
        #20;  
        
        
        a = 32'd123456;
        b = 32'd0;
        #20;
        
      
        a = 32'd1;
        b = 32'd987654;
        #20; 
        
       
        a = 32'd1000000;
        b = 32'd9;
        #20;  
        
     
        a = 32'h80000000; 
        b = 32'h00000002; 
        #20; 
         
    end
endmodule
