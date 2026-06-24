var app_button;
var calc_button;
var FM_button;
var settings_button;
var poweroff_button;
var restart_button;
function init() {
    UIInit();
    var base_x = 15;
    var x = 15;
    var y = UI.ScreenH - 80;
    var bw = (UI.ScreenW - 20) / 3 - 10;
    {
        app_button = TextButton();
        app_button.x = x;
        app_button.y = y;
        app_button.w = bw;
        app_button.h = 30;
        app_button.content = "Apps";
    }
    x += bw + 10;
    {
        calc_button = TextButton();
        calc_button.x = x;
        calc_button.y = y;
        calc_button.w = bw;
        calc_button.h = 30;
        calc_button.content = "Calc";
    }
    x += bw + 10;
    {
        FM_button = TextButton();
        FM_button.x = x;
        FM_button.y = y;
        FM_button.w = bw;
        FM_button.h = 30;
        FM_button.content = "Explorer";
    }
    x = base_x;
    y += 40;
    {
        settings_button = TextButton();
        settings_button.x = x;
        settings_button.y = y;
        settings_button.w = bw;
        settings_button.h = 30;
        settings_button.content = "Settings";
    }
    x += bw + 10;
    {
        restart_button = TextButton();
        restart_button.x = x;
        restart_button.y = y;
        restart_button.w = bw;
        restart_button.h = 30;
        restart_button.content = "Restart";
        restart_button.OnClick = function () {
            System.Restart();
        };
    }
    x += bw + 10;
    {
        poweroff_button = TextButton();
        poweroff_button.x = x;
        poweroff_button.y = y;
        poweroff_button.w = bw;
        poweroff_button.h = 30;
        poweroff_button.content = "Power Off";

    }
}
function drawBG() {

    if (FS.Exists("/ui/bg.png")) {
        var w = UI.GetScreenW();
        var h = UI.GetScreenH();
        UI.DrawPngFile("/ui/bg.png", 0, 0, w, h, 1, 1);
    } else {
        UI.FillRect(0, 0, UI.GetScreenW(), UI.GetScreenH(), UI.GetWhite());
    }
}
function wakeup() {
    drawBG();
}
var timer = 0;
var count = 0;
function loop() {
    app_button.Draw();
    calc_button.Draw();
    FM_button.Draw();
    settings_button.Draw();
    poweroff_button.Draw();
    restart_button.Draw();
}