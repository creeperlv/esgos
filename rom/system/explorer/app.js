var open_btn;
var goback_btn;
var next_page_btn;
var last_page_btn;
var file_items = [];
var close_btn;
var open_folder_list = [];
var folder_list_current_index = 0;
var page_count_width = 100;
function init() {
    UIInit();
    page_count_width = 100;
    var base_x = 15;
    var bh = 60;
    var x = 15;
    var bottom_button_y = UI.ScreenH - (bh + 10) * 2;
    var y = 60;
    var bw = (UI.ScreenW - 20);
    var padding = 5;
    var item_size = Math.floor(Math.floor(UI.ScreenH - UI.StatusBarHeight - (bh + padding) * 2 - 40 - padding) / bh);
    for (var i = 0; i < item_size; i++) {
        var btn = IconTextButton(x, y, bw, bh, "", "/ui/folder-icon.png", "/ui/folder-icon-white.png");
        file_items[i] = btn;
        // btn.IsShown = false;
        y += bh;
    }
    {
        close_btn = TextButton(0, 20, 40, 40, "<", function () {
            {
                var len = open_folder_list.length;
                for (var i = 0; i < len; i++) {
                    open_folder_list[i].Close();
                }
            }
            System.LaunchSysApp("/system/home/");
        });
    }
    var page_button_bw = (UI.ScreenW - page_count_width - 10) / 2;
    var MenuButton_bw = (UI.ScreenW - 5 * 3) / 2;
    last_page_btn = TextButton(5, y + 5, page_button_bw, bh, "<");
    next_page_btn = TextButton(5 + page_button_bw + page_count_width, y + 5, page_button_bw, bh, ">");
    y += bh + 5;
    goback_btn = TextButton(5, y + 5, MenuButton_bw, bh, "Go Back");
    open_btn = TextButton(5 + MenuButton_bw + 5, y + 5, MenuButton_bw, bh, "Open");
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
    close_btn.Draw();
    last_page_btn.Draw();
    next_page_btn.Draw();
    goback_btn.Draw();
    open_btn.Draw();
    for (var i = 0; i < len; i++) {
        file_items[i].Draw();
    }
}