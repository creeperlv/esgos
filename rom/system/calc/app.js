
var num_btns = [];
var input_field_height;
var close_btn;
var backspace_btn;
var input = "";
function DrawInput() {
    UI.FillRect(50, 20, UI.GetScreenW() - 55, input_field_height + 10, UI.GetWhite());
    UI.DrawBox(50, 20, UI.GetScreenW() - 55, input_field_height + 10, UI.GetBlack());
    UI.SetTextFont(UI.GetFont24());
    UI.SetTextCursor(60, 30);
    if (input == "")
        Core.Write("0");
    else
        Core.Write(input);
}
function refresh_buttons() {
    var len = close_btn.length;

    for (var i = 0; i < len; i++) {
        close_btn[i].Refresh();
    }
    close_btn.Refresh();
}
function init() {
    UIInit();

    {
        close_btn = TextButton();
        close_btn.x = 5;
        close_btn.y = 20;
        close_btn.w = 40;
        close_btn.h = 40;
        close_btn.content = "<";
        close_btn.OnClick = function () {
            System.LaunchSysApp("/system/home/");
        };
    }
    input_field_height = 30;
    var button_region_size = UI.ScreenH - 20 - input_field_height - 20;
    var bh = button_region_size / 5 - 10;
    var x = 15;
    var y = UI.ScreenH - (bh + 10) * 2;
    var bw = (UI.ScreenW - 20) / 4 - 10;
    var base_x = UI.ScreenW - (bw + 10) * 4;
    var base_y = 20 + input_field_height + 20;
    {
        var base_x_num_btn = UI.ScreenW - (bw + 10) * 2;
        var base_y_num_btn = 20 + input_field_height + 20 + bh + 10;
        x = base_x_num_btn;
        y = base_y_num_btn;
        for (var i = 9; i >= 0; i--) {
            var btn = TextButton();
            btn.x = x;
            btn.y = y;
            btn.h = bh;
            btn.w = bw;
            btn.content = "" + i;
            var num = i
            btn.OnClick = function () {
                input += this.content;
                DrawInput();
            };
            x -= bw + 10;
            if (x < 0) {
                x = base_x_num_btn;
                y += bh + 10;
            }
            num_btns[i] = btn;
        }
        num_btns[0].x -= bw + 10;
    }
    {
        backspace_btn = IconButton();
        backspace_btn.IconWhite = "/ui/backspace-white.png";
        backspace_btn.IconBlack = "/ui/backspace.png";
        backspace_btn.x = base_x;
        backspace_btn.y = base_y;
        backspace_btn.w = bw;
        backspace_btn.h = bh;
        backspace_btn.IconW = 40;
        backspace_btn.IconH = 40;
        backspace_btn.OnClick = function () {
            if (input.length > 1)
                input = input.slice(0, -1)
            else {
                input = ""
            }
            DrawInput();
        }
    }
}
function wakeup() {
    UI.FillRect(0, 0, UI.GetScreenW(), UI.GetScreenH(), UI.GetWhite());
    UI.DrawBox(50, 20, UI.GetScreenW() - 55, input_field_height + 10, UI.GetBlack());
}
var timer = 0;
var count = 0;
function loop() {
    // test_button.Draw();

    var len = num_btns.length;
    for (var i = 0; i < len; i++) {
        num_btns[i].Draw();
    }
    close_btn.Draw();
    backspace_btn.Draw();
}