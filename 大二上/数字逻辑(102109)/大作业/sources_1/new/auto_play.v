module auto_play(
    input wire clk,
    input wire rst,
    input wire sw14,
    input wire sw15,
    output reg [7:0] key_code,
    output reg key_valid,
    output reg key_released
);

    reg [31:0] play_counter;
    reg [6:0] note_index;
    parameter NOTE_DURATION = 25_000_000;
    
    reg [2:0] music_notes_1 [0:127];  // 小星星
    reg [2:0] music_notes_2 [0:127];  
    reg [2:0] music_notes_3 [0:127];   
    reg [2:0] current_note;
    reg [6:0] max_notes;

    // 将1-7转换为对应的键盘码
     reg [7:0] current_keycode;
       always @(*) begin
           case(current_note)
               3'd1: current_keycode = 8'h1A;  //   Z
               3'd2: current_keycode = 8'h22;  //   X
               3'd3: current_keycode = 8'h21;  //   C
               3'd4: current_keycode = 8'h2A;  //   V
               3'd5: current_keycode = 8'h32;  //   B
               3'd6: current_keycode = 8'h31;  //   N
               3'd7: current_keycode = 8'h3A;  //   M
               default: current_keycode = 8'h00;
           endcase
       end

    initial begin
        // 小星星完整版 
        music_notes_1[0] = 1; music_notes_1[1] = 1; 
        music_notes_1[2] = 5; music_notes_1[3] = 5;
        music_notes_1[4] = 6; music_notes_1[5] = 6;
        music_notes_1[6] = 5; music_notes_1[7] = 0;
        music_notes_1[8] = 4; music_notes_1[9] = 4;
        music_notes_1[10] = 3; music_notes_1[11] = 3;
        music_notes_1[12] = 2; music_notes_1[13] = 2;
        music_notes_1[14] = 1; music_notes_1[15] = 0;
        music_notes_1[16] = 5; music_notes_1[17] = 5;
        music_notes_1[18] = 4; music_notes_1[19] = 4;
        music_notes_1[20] = 3; music_notes_1[21] = 3;
        music_notes_1[22] = 2; music_notes_1[23] = 0;
        music_notes_1[24] = 5; music_notes_1[25] = 3; 
        music_notes_1[26] = 1; music_notes_1[27] = 2;
        music_notes_1[28] = 3; music_notes_1[29] = 4;
        music_notes_1[30] = 5; music_notes_1[31] = 0;
        music_notes_1[32] = 5; music_notes_1[33] = 3;
        music_notes_1[34] = 1; music_notes_1[35] = 2;
        music_notes_1[36] = 3; music_notes_1[37] = 4;
        music_notes_1[38] = 5; music_notes_1[39] = 0;
        music_notes_1[40] = 1; music_notes_1[41] = 1;
        music_notes_1[42] = 5; music_notes_1[43] = 5;
        music_notes_1[44] = 6; music_notes_1[45] = 6;
        music_notes_1[46] = 5; music_notes_1[47] = 0;
        music_notes_1[48] = 4; music_notes_1[49] = 4;
        music_notes_1[50] = 3; music_notes_1[51] = 3;
        music_notes_1[52] = 2; music_notes_1[53] = 2;
        music_notes_1[54] = 1; music_notes_1[55] = 0;

        // 神的随波逐流？（不像
        music_notes_2[0] = 1; music_notes_2[1] = 1;
        music_notes_2[2] = 5; music_notes_2[3] = 3;
        music_notes_2[4] = 3; music_notes_2[5] = 2;
        music_notes_2[6] = 2; music_notes_2[7] = 1;
        music_notes_2[8] = 5; music_notes_2[9] = 5;
        music_notes_2[10] = 4; music_notes_2[11] = 2;
        music_notes_2[12] = 2; music_notes_2[13] = 1;
        music_notes_2[14] = 1; music_notes_2[15] = 7;
        music_notes_2[16] = 1; music_notes_2[17] = 1;
        music_notes_2[18] = 5; music_notes_2[19] = 3;
        music_notes_2[20] = 3; music_notes_2[21] = 2;
        music_notes_2[22] = 2; music_notes_2[23] = 1;
        music_notes_2[24] = 5; music_notes_2[25] = 5;
        music_notes_2[26] = 4; music_notes_2[27] = 2;
        music_notes_2[28] = 4; music_notes_2[29] = 3;
        music_notes_2[30] = 2; music_notes_2[31] = 0;
        music_notes_2[32] = 5; music_notes_2[33] = 5;
        music_notes_2[34] = 4; music_notes_2[35] = 2;
        music_notes_2[36] = 2; music_notes_2[37] = 1;
        music_notes_2[38] = 1; music_notes_2[39] = 7;
        music_notes_2[40] = 1; music_notes_2[41] = 1;
        music_notes_2[42] = 2; music_notes_2[43] = 3;
        music_notes_2[44] = 4; music_notes_2[45] = 5;
        music_notes_2[46] = 3; music_notes_2[47] = 0;

        // 使一颗心免于悲伤？（
        music_notes_3[0] = 3; music_notes_3[1] = 3;
        music_notes_3[2] = 3; music_notes_3[3] = 2;
        music_notes_3[4] = 1; music_notes_3[5] = 6;
        music_notes_3[6] = 5; music_notes_3[7] = 0;
        music_notes_3[8] = 3; music_notes_3[9] = 3;
        music_notes_3[10] = 3; music_notes_3[11] = 2;
        music_notes_3[12] = 1; music_notes_3[13] = 2;
        music_notes_3[14] = 1; music_notes_3[15] = 0;
        music_notes_3[16] = 6; music_notes_3[17] = 6;
        music_notes_3[18] = 6; music_notes_3[19] = 5;
        music_notes_3[20] = 3; music_notes_3[21] = 5;
        music_notes_3[22] = 3; music_notes_3[23] = 0;
        music_notes_3[24] = 2; music_notes_3[25] = 2;
        music_notes_3[26] = 2; music_notes_3[27] = 1;
        music_notes_3[28] = 6; music_notes_3[29] = 1;
        music_notes_3[30] = 5; music_notes_3[31] = 0;
        music_notes_3[32] = 3; music_notes_3[33] = 3;
        music_notes_3[34] = 3; music_notes_3[35] = 2;
        music_notes_3[36] = 1; music_notes_3[37] = 6;
        music_notes_3[38] = 5; music_notes_3[39] = 0;
        music_notes_3[40] = 3; music_notes_3[41] = 3;
        music_notes_3[42] = 3; music_notes_3[43] = 2;
        music_notes_3[44] = 1; music_notes_3[45] = 2;
        music_notes_3[46] = 1; music_notes_3[47] = 0;
    end
    
    always @(*) begin
        case ({sw15, sw14})
            2'b10: begin  // 小星星
                current_note = music_notes_1[note_index];
                max_notes = 64;
            end
            2'b01: begin  
                current_note = music_notes_2[note_index];
                max_notes = 48;
            end
            2'b11: begin   
                current_note = music_notes_3[note_index];
                max_notes = 64;
            end
            default: begin
                current_note = 0;
                max_notes = 0;
            end
        endcase
    end
    
    always @(posedge clk) begin
        if (rst) begin
            play_counter <= 0;
            note_index <= 0;
            key_valid <= 0;
            key_released <= 0;
        end
        else if ((sw14 || sw15) && !rst) begin
            if (play_counter >= NOTE_DURATION) begin
                play_counter <= 0;
                note_index <= (note_index < max_notes-1) ? note_index + 1 : 0;
                key_valid <= (current_note != 0);
                key_released <= 0;
            end
            else begin
                play_counter <= play_counter + 1;
                key_valid <= 0;
                key_released <= (play_counter == NOTE_DURATION/2);
            end
            key_code <= current_keycode;
        end
        else begin
            play_counter <= 0;
            note_index <= 0;
            key_valid <= 0;
            key_released <= 0;
        end
    end

endmodule