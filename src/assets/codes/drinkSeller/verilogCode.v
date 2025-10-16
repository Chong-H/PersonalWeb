module KCSJ1(
    input wire clk,
    input wire reset,
    input wire coin_2,
    input wire coin_1,
    input wire buy_button,
    output reg drink_dispensed,
    output reg change_dispensed,
    output reg [3:0] total_coins_display,
    output reg [3:0] change_display
);
reg [4:0] state;
always @(posedge clk or posedge reset) begin
    if (reset) begin
        state <= 5'b00000;
        total_coins_display <= 4'b0000;
        change_display <= 4'b0000;
        drink_dispensed <= 1'b0;
        change_dispensed <= 1'b0;
    end else begin
        case (state)
            5'b00000: begin
                if (coin_2) total_coins_display <= total_coins_display + 2;
                else if (coin_1) total_coins_display <= total_coins_display + 1;
                else if (buy_button && total_coins_display >= 3) state <= 5'b00001;
            end
            5'b00001: begin
                drink_dispensed <= 1'b1;
                change_display <= total_coins_display - 3;
                state <= 5'b00010;
            end
            5'b00010: begin
                if (coin_2 && total_coins_display > 0) begin
                    change_dispensed <= change_dispensed - 2;
                    total_coins_display <= total_coins_display - 2;
                end else if (coin_1 && total_coins_display > 0) begin
                    change_dispensed <= change_dispensed - 1;
                    total_coins_display <= total_coins_display - 1;
                end else if (change_dispensed == 0) begin
                    state <= 5'b00000;
                    drink_dispensed <= 1'b0;
                    change_dispensed <= !change_dispensed;
                end
            end
            default: state = 'b00000;
        endcase
    end
end
endmodule