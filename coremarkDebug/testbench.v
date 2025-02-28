`timescale 1ns/1ps

`define one_nanos 1ns
`define half_period 10ns  //50MHz
`define reset_delay 5us  //accomodate UART reset
`define max_running_time 5s
`define uart_half_period 4.34us  //115200Hz
//`define uart_half_period 8.68us
`define half_mili_sec 500us

module testbench();

  parameter printf_cond = 0;
  
  reg clk;
  reg uart_clk;
  //reg [10:0] divisor_counter;
  reg rst;
  reg gpio_0_ival;
  reg gpio_1_ival;
  wire gpio_0_oe;
  wire gpio_0_ie;
  wire gpio_0_oval;
  wire gpio_1_oe;
  wire gpio_1_ie;
  wire gpio_1_oval;
  wire uart_txd;
  wire uart_end;

// clock generation
  initial begin
    clk = 1'b0;
    forever #(`half_period) clk = ~clk;
  end
  

  initial begin
    uart_clk = 1'b0;
    forever #(`uart_half_period) uart_clk = ~uart_clk;
  end


  initial begin
    rst = 1'b1;
    gpio_0_ival = 1'b0;
    gpio_1_ival = 1'b0;
    #(`reset_delay)
    rst = 1'b0;
    gpio_0_ival = 1'b1;
    gpio_1_ival = 1'b1;
  end

  initial begin
    #(`one_nanos)
    $readmemh("./test.hex", testbench.top.mem.srams.mem.mem_ext.ram);
  end

Platform top(
  .clock                        (clk),
  .reset                        (rst),
  .io_pins_gpio_pins_0_i_ival   (gpio_0_ival),
  .io_pins_gpio_pins_0_o_oval   (gpio_0_oval),
  .io_pins_gpio_pins_0_o_oe     (gpio_0_oe),
  .io_pins_gpio_pins_0_o_ie     (gpio_0_ie),
  .io_pins_gpio_pins_1_i_ival   (gpio_1_ival),
  .io_pins_gpio_pins_1_o_oval   (gpio_1_oval),
  .io_pins_gpio_pins_1_o_oe     (gpio_1_oe),
  .io_pins_gpio_pins_1_o_ie     (gpio_1_ie),
  .io_uartOUT                   (uart_txd),
  .io_success                   ()
);

/*
PlatformJTAG top(
  .clock                        (clk),
  .reset                        (rst),
  .io_success                   ()
);
*/
uart_capture uart_capture(
  .CLK                          (uart_clk),
  .RESET                        (rst),
  .RXD                          (uart_txd),
  .SIMULATIONEND                (uart_end)
);

// time monitor
  reg sim_tim_clk;
  reg [31:0] curr_sim_tim;
  reg [31:0] final_data;

  initial
  begin
    sim_tim_clk = 1'b0;
    curr_sim_tim = 32'h00000000;
  end

  always #(`half_mili_sec) sim_tim_clk = ~sim_tim_clk;

  always @ ( negedge sim_tim_clk )
  begin
    curr_sim_tim = curr_sim_tim + 1'b1;
    $display(">>>>>>>> Curr Sim Time: %16d ms\n", curr_sim_tim );
  end

// output logging
//  integer PAT_RESULT;
//  integer TIME;
  int  data;

/*
  initial begin
    PAT_RESULT = $fopen("./regression_result.dat","at");
    TIME  = $fopen("./timelog","r");
  end

// overtime exit
  initial begin

    //$dumpfile("./wave_dump_log/program.vcd");
    //$dumpvars(0, top);
    #(`max_running_time);
    $system("date +%y%m%d%H%M%S > timelog");
    $fscanf(TIME,"%t",data);
    $fwrite(PAT_RESULT, "%t\n", data );         
    $fwrite(PAT_RESULT, "********************************************\n" );         
    $fwrite(PAT_RESULT, "********************************************\n" );         
    $fwrite(PAT_RESULT, "Program FAILED\n");
    $fwrite(PAT_RESULT, "********************************************\n" );         
    $fwrite(PAT_RESULT, "********************************************\n\n\n" );         
    $fclose(TIME);
    $fclose(PAT_RESULT);
    $display("\n");
    $display("**************************************************");
    $display("**************************************************");
    $display("****** Program FAILED ***********");
    $display("**************************************************");
    $display("**************************************************");
    $finish;
  end*/
  
  
// handles uart overflow error
  /*initial	begin
  // delay period
    //#100ns;
    
    //wait(top.TestHarness.lsys.mmio_axi4_0_aw_ready & top.TestHarness.lsys.mmio_axi4_0_aw_valid);
    wait(top.TestHarness.lsys.mmio_axi4_0_aw_bits_addr[30:0] == 31'h7070_7070);
    //wait(top.TestHarness.lsys.mmio_axi4_0_w_ready & top.TestHarness.lsys.mmio_axi4_0_w_valid);
    wait(top.TestHarness.lsys.mmio_axi4_0_w_bits_data[31:0] == 32'hdead_beef);
    //wait(top.uart_end)
    //wait(top.TestHarness.io_success);
    
    #10us;
    $system("date +%y%m%d%H%M%S > timelog");
    $fscanf(TIME,"%t",data);
    $fwrite(PAT_RESULT, "%t\n", data );    
    $fwrite(PAT_RESULT, "*************************************************\n" );         
    $fwrite(PAT_RESULT, "*************************************************\n" );         
    $fwrite(PAT_RESULT, "Program SUCCESSED\n");
    $fwrite(PAT_RESULT, "*************************************************\n" );         
    $fwrite(PAT_RESULT, "*************************************************\n\n\n" );         
    $fclose(TIME);
    $fclose(PAT_RESULT);
    $display("\n");
    $display("**************************************************");
    $display("**************************************************");
    $display("**************** Program SUCCESSED ***************");
    $display("**************************************************");
    $display("**************************************************");
    $display(" UART is full. \n");
    //$finish;
  end*/
/*
  always @ (posedge top.TestHarness.lsys.mmio_axi4_0_aw_valid) begin
    final_data <= top.TestHarness.lsys.mmio_axi4_0_w_bits_data[31:0];
    $display("data: %h", final_data);
  end
*/
endmodule
