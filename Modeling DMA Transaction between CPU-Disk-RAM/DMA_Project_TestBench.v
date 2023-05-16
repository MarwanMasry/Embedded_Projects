module DMA_Project_TestBench;
	reg 	     update;
	wire         HRQ  , DREQ  , IOR_command , IOW_command ,MEMR , MEMW;
	wire         HLDA,  CLK, DACK  ;
	wire         IOR ,IOW , EOP;
	wire  [9:0]  DRAM_startingAddress;
	wire  [9:0]  IO_startingAddress;
	wire  [9:0]  addressCounter ; 
	wire  [9:0]  addressBus_IO;
	wire  [9:0]  addressBus_DRAM;		
	wire  [31:0] dataBus;
	
	
	
	/* Instantiating object */
	CLK_Gen myCLK(.clock(CLK));
	
	MIPS_CPU myCPU
	(
		.CLK(CLK) , .addressCounter(addressCounter) , .HLDA(HLDA) ,.HRQ(HRQ) ,
		.IOR(IOR) , .IOW(IOW) ,.EOP(EOP)  ,.update(update) ,
		.DRAM_startingAddress(DRAM_startingAddress) , .IO_startingAddress(IO_startingAddress)				
	);
	
	DMA myDMA
	(
		.addressCounter(addressCounter) ,.CLK(CLK) , .DACK(DACK)
		,.dataBus(dataBus), .DREQ(DREQ) ,.HLDA(HLDA) ,.HRQ(HRQ) ,
		.IOR(IOR) ,     .IOR_command(IOR_command) ,.IOW(IOW),
		.IOW_command(IOW_command), .MEMR(MEMR) ,.MEMW(MEMW) ,.EOP(EOP) ,
		.addressBus_DRAM(addressBus_DRAM) ,.addressBus_IO(addressBus_IO) ,
		.DRAM_startingAddress(DRAM_startingAddress) , .IO_startingAddress(IO_startingAddress)
	);
	
	IO_device IO
	(
		.CLK(CLK), .addressBus_IO(addressBus_IO) ,.DACK(DACK) ,.dataBus(dataBus) ,
		.DREQ(DREQ) ,.IOR_command(IOR_command) ,.IOW_command(IOW_command) 
	);
	
	DRAM ram
	(
		.CLK(CLK) , .addressBus_DRAM(addressBus_DRAM), .dataBus(dataBus) ,
		.MEMR(MEMR) , .MEMW(MEMW)
	);
	
	
		
	initial 
	begin
		$monitor
		(
		     "Address_IO:%d , Address_DRAM:%d ,Data Transfered:%d        ,MEMR:%b ,MEMW:%b ,IOR:%b ,IOW:%b        ,Time:" 
			,addressBus_IO,addressBus_DRAM,dataBus,MEMR,MEMW,IOR_command,IOW_command,$time
		);			
	end
	
	
	/* Initializations */
	initial 
	begin

	$display("\n\n Moving 50 Words(4B) from IO(starting from address 10) to DRAM(starting from address 0) using DMA:\n");
	
	myCPU.customDRAM_StartingAddress = 0;
	myCPU.customIO_StartingAddress = 10;	
	myCPU.customAddressCounter = 50 ;
	myCPU.customIOR = 1;
	myCPU.customIOW = 0;	
	update = 1;  
	 #2
 	update = 0;
	
	IO.Start_Requisting_DMA = 1;
	#550
	IO.Start_Requisting_DMA = 0;


	$display("\n\nMoving 40 Words(4B) from DRAM(starting from address 70) to IO(starting from address 90) using DMA:\n");

	myCPU.customDRAM_StartingAddress = 70;
	myCPU.customIO_StartingAddress = 90;
	myCPU.customAddressCounter = 40 ;
	myCPU.customIOR = 0;
	myCPU.customIOW = 1;	
	update = 1;  
	 #2
 	update = 0;
	
	IO.Start_Requisting_DMA = 1;
	#525
	IO.Start_Requisting_DMA = 0;
		
	end
		
endmodule


