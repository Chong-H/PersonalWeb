module KCSJ1_vlg_tst();
reg buy_button, clk, coin_1, coin_2, reset;
wire change_dispensed;
wire [3:0] change_display;
wire drink_dispensed;
wire [3:0] total_coins_display;
KCSJ1 i1 (
    .buy_button(buy_button),
    .change_dispensed(change_dispensed),
    .change_display(change_display),
    .clk(clk),
    .coin_1(coin_1),
    .coin_2(coin_2),
    .drink_dispensed(drink_dispensed),
    .reset(reset),
    .total_coins_display(total_coins_display)
);
initial begin
    clk = 0;
    #10 reset = 1;
    #10 reset = 0;
    buy_button = 0;
    coin_1 = 0;
    coin_2 = 0;
    #1 coin_2 = 1; #1 coin_2 = 0;
    #1 coin_2 = 1; #1 coin_2 = 0;
    #1 coin_2 = 1; #1 coin_2 = 0;
    #10 buy_button = 1; #10 buy_button = 0;
    $display("Running testbench");
end
always begin
    #1 clk = ~clk;
end
endmodule