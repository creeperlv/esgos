var page_index = 0;
var page_home = 0;
var page_msc = 2;
var page_wifi = 1;
var page_rom_upd = 3;
var page_fw_upd = 4;
var page_about = 5;
var settings_home_buttons = [];
var normal_back_btn;
var msc_back_btn;
var close_btn;
var page_index_ = -1;
function refresh_buttons() {
    var len = settings_home_buttons.length;

    for (var i = 0; i < len; i++) {
        settings_home_buttons[i].Refresh();
    }
    normal_back_btn.Refresh();
    msc_back_btn.Refresh();
    close_btn.Refresh();
}
var kbd;
function init() {
    UIInit();
    // kbd = QWERTYKeyboard();
    {
        normal_back_btn = TextButton();
        normal_back_btn.x = 0;
        normal_back_btn.y = 20;
        normal_back_btn.w = 40;
        normal_back_btn.h = 40;
        normal_back_btn.content = "<";
        normal_back_btn.OnClick = function () {
            refresh_buttons();
            UI.ClearScreen();
            page_index = page_home;
        };
    }
    {
        msc_back_btn = TextButton();
        msc_back_btn.x = 0;
        msc_back_btn.y = 20;
        msc_back_btn.w = 40;
        msc_back_btn.h = 40;
        msc_back_btn.content = "<";
        msc_back_btn.OnClick = function () {
            refresh_buttons();
            System.StopMSC();
            UI.ClearScreen();
            page_index = page_home;
        };
    }
    {
        close_btn = TextButton();
        close_btn.x = 0;
        close_btn.y = 20;
        close_btn.w = 40;
        close_btn.h = 40;
        close_btn.content = "<";
        close_btn.OnClick = function () {
            System.LaunchSysApp("/system/home/");
        };
    }
    {

        var bh = 60;
        var x = 10;
        var y = 65;
        var i = 0;
        var bw = (UI.ScreenW - 20);
        {
            var btn = TextButton();
            btn.x = x;
            btn.y = y;
            btn.w = bw;
            btn.h = bh;
            btn.content = "Wi-Fi";
            settings_home_buttons[i] = btn;
            i++;
        }
        y += bh + 5;
        {
            var btn = TextButton();
            btn.x = x;
            btn.y = y;
            btn.w = bw;
            btn.h = bh;
            btn.content = "USB: Mass Storage";
            settings_home_buttons[i] = btn;
            btn.OnClick = function () {
                System.StartMSC();
                refresh_buttons();
                UI.ClearScreen();
                page_index = page_msc;
            };
            i++;
        }
        y += bh + 5;
        {
            var btn = TextButton();
            btn.x = x;
            btn.y = y;
            btn.w = bw;
            btn.h = bh;
            btn.content = "Apply ROM Update";
            settings_home_buttons[i] = btn;
            i++;
        }
        y += bh + 5;
        {
            // var btn = TextButton();
            // btn.x = x;
            // btn.y = y;
            // btn.w = bw;
            // btn.h = bh;
            // btn.content = "Apply Firmware Update";
            var btn = TextButton(x, y, bw, bh, "Apply Firmware Update", function () {
            });
            settings_home_buttons[i] = btn;
            i++;
        }
        y += bh + 5;
        {
            var btn = TextButton(x, y, bw, bh, "About", function () {
                refresh_buttons();
                UI.ClearScreen();
                page_index = page_about;
            });
            // btn.x = x;
            // btn.y = y;
            // btn.w = bw;
            // btn.h = bh;
            // btn.content = "About";
            settings_home_buttons[i] = btn;
            // btn.OnClick = function () {
            //     refresh_buttons();
            //     UI.ClearScreen();
            //     page_index = page_about;
            // };
            i++;
        }
    }
}
function wakeup() {
}
function about_page() {
    var y = 70;
    UI.DrawCenterStringFont('esGOS', UI.GetScreenW() / 2, y, UI.GetFont40());
    y += 45;
    UI.DrawCenterStringFont('Version: ' + Core.GetVersion() + "-" + Core.GetRelease(), UI.GetScreenW() / 2, y, UI.GetFont24());

}
function loop() {
    if (page_index_ != page_index) {
        UI.ClearScreen();
        UI.DrawCenterStringFont('Settings', UI.GetScreenW() / 2, 20 + 12, UI.GetFont24());
        page_index_ = page_index;
        switch (page_index) {
            case 0:
                {
                }
                break;
            case 2:
                {
                    UI.DrawCenterStringFont('Mass Storage Mode', UI.GetScreenW() / 2, UI.GetScreenH() / 2, UI.GetFont40());
                }
                break;
            case 5:
                {
                    about_page();
                }
                break;
        }
    }
    switch (page_index) {
        case 0:
            {
                var len = settings_home_buttons.length;
                for (var i = 0; i < len; i++) {
                    settings_home_buttons[i].Draw();
                }
                close_btn.Draw();
            }
            break;
        case 2:
            {
                msc_back_btn.Draw();
            }
            break;
        case 5:
            {
                normal_back_btn.Draw();
            }
            break;
    }
    // kbd.Draw();
}