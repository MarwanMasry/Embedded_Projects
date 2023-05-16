module DRAM  
	(
		inout wire [31:0] dataBus,
		input wire [9:0]  addressBus_DRAM,
		input wire MEMR , MEMW , CLK
	);  
	
	/* Module Memory */
	reg [31:0] DRAM_memory[0:1023];
	
	/* Temp Variables */
	integer i;
		
	 /* DRAM is in output mode we put data in data lines*/ 
	assign dataBus = (MEMR)? DRAM_memory[addressBus_DRAM] : 32'bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz; 
	
	
	/* Initializations */
	initial
	begin
		for(i = 0; i<1024 ; i = i+1)
		begin
			DRAM_memory[i] = 0;
		end		
	end


	/* Always Block	 */
	always@(posedge CLK or addressBus_DRAM or dataBus)
	begin
					
		if( MEMW == 1)
		begin
			DRAM_memory[addressBus_DRAM] = dataBus;
		end
			
	end
	
endmodule

