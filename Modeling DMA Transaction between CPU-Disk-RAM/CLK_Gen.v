module CLK_Gen(clock); 
	output reg clock;
	 
	initial
	begin
		clock = 0;
	end
	
	/* Clock cycle takes 10 ns. */
	always 
	begin
		#5
		clock = ~clock;
	end
	
endmodule



