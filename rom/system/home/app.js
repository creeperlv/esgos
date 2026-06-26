var app_button;
var calc_button;
var FM_button;
var settings_button;
var poweroff_button;
var restart_button;
var test_button;
function init() {
    UIInit();
    {
        test_button = IconButton();
        test_button.x = 32;
        test_button.y = 32;
        test_button.w = 128;
        test_button.h = 48;
    }
    var base_x = 15;
    var bh = 60;
    var x = 15;
    var y = UI.ScreenH - (bh + 10) * 2;
    var bw = (UI.ScreenW - 20) / 3 - 10;
    {
        app_button = IconButton();
        app_button.x = x;
        app_button.y = y;
        app_button.w = bw;
        app_button.h = bh;
        app_button.IconW = 42;
        app_button.IconH = 42;
        app_button.IconWhite = "/ui/apps-white.png";
        app_button.IconBlack = "/ui/apps.png";
    }
    x += bw + 10;
    {
        calc_button = IconButton();
        calc_button.x = x;
        calc_button.y = y;
        calc_button.w = bw;
        calc_button.h = bh;
        calc_button.IconW = 42;
        calc_button.IconH = 42;
        calc_button.IconWhite = "/ui/calc-white.png";
        calc_button.IconBlack = "/ui/calc.png";
        calc_button.OnClick = function () {
            System.LaunchSysApp("/system/calc/");
        };
    }
    x += bw + 10;
    {
        FM_button = IconButton();
        FM_button.x = x;
        FM_button.y = y;
        FM_button.w = bw;
        FM_button.h = bh;
        FM_button.IconW = 42;
        FM_button.IconH = 42;
        FM_button.IconWhite = "/ui/file-open-white.png";
        FM_button.IconBlack = "/ui/file-open.png";
    }
    x = base_x;
    y += bh + 10;
    {
        settings_button = IconButton();
        settings_button.x = x;
        settings_button.y = y;
        settings_button.w = bw;
        settings_button.h = bh;
        settings_button.IconW = 42;
        settings_button.IconH = 42;
        settings_button.IconWhite = "/ui/cog-white.png";
        settings_button.IconBlack = "/ui/cog.png";
        settings_button.OnClick = function () {
            System.LaunchSysApp("/system/settings/");
        };
    }
    x += bw + 10;
    {
        restart_button = IconButton();
        restart_button.x = x;
        restart_button.y = y;
        restart_button.w = bw;
        restart_button.h = bh;
        restart_button.IconW = 42;
        restart_button.IconH = 42;
        restart_button.IconWhite = "/ui/restart-white.png";
        restart_button.IconBlack = "/ui/restart.png";
        restart_button.OnClick = function () {
            System.Restart();
        };
    }
    x += bw + 10;
    {
        poweroff_button = IconButton();
        poweroff_button.x = x;
        poweroff_button.y = y;
        poweroff_button.w = bw;
        poweroff_button.h = bh;
        poweroff_button.IconW = 42;
        poweroff_button.IconH = 42;
        poweroff_button.IconWhite = "/ui/poweroff-white.png";
        poweroff_button.IconBlack = "/ui/poweroff.png";
        poweroff_button.OnClick = function () {
            drawBG();
            UI.SetTextColor(UI.Black);
            UI.DrawCenterStringFont('Goodbye!', UI.GetScreenW() / 2, UI.GetScreenH() / 2, UI.GetFont40());
            System.PowerOff();
        };

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
    // test_button.Draw();
    app_button.Draw();
    calc_button.Draw();
    FM_button.Draw();
    settings_button.Draw();
    poweroff_button.Draw();
    restart_button.Draw();
}