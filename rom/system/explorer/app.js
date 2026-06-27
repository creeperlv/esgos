var open_btn;
var goback_btn;
var next_page_btn;
var last_page_btn;
var file_items = [];
var close_btn;
var open_folder_list = [];
var folder_list_current_index = 0;
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
    var bottom_button_y = UI.ScreenH - (bh + 10) * 2;
    var y = 60;
    var bw = (UI.ScreenW - 20);
    var padding = 5;
    var item_size = (UI.ScreenH - UI.StatusBarHeight - (bh + padding) * 2 - 60) / bh;
    for (var i = 0; i < item_size; i++) {
        var btn = IconTextButton(x, y, bw, bh, "", "/ui/folder-icon.png", "/ui/folder-icon-white.png");
        file_items[i] = btn;
        // btn.IsShown = false;
        y += bh;
    }
    {
        close_btn = TextButton(0, 20, 40, 40, "<", function () {
            System.LaunchSysApp("/system/home/");
        });
    }
    var root = OpenFile("/", "r");
    open_folder_list[0] = root;
}
function drawBG() {

    UI.FillRect(0, 0, UI.GetScreenW(), UI.GetScreenH(), UI.GetWhite());
}
function wakeup() {
    drawBG();
}
var timer = 0;
var count = 0;
function loop() {
    // test_button.Draw();
    var len = file_items.length;
    for (var i = 0; i < len; i++) {
        file_items[i].Draw();
    }
    close_btn.Draw();
}