var open_btn;
var goback_btn;
var next_page_btn;
var last_page_btn;
var file_items = [];
var file_items_menu = [];
var close_btn;
var open_folder_list = [];
var folder_list_current_index = 0;
var page_count_width = 100;
var show_menu;
var folder_icon;
var folder_icon_white;
var file_icon;
var file_icon_white;
function init() {
    UIInit();
    show_menu = false;
    page_count_width = 100;
    var base_x = 15;
    var bh = 60;
    var x = 15;
    var bottom_button_y = UI.ScreenH - (bh + 10) * 2;
    var y = 60;
    var bw = (UI.ScreenW - 20);
    var padding = 5;
    folder_icon = "/ui/folder-icon.png";
    folder_icon_white = "/ui/folder-icon-white.png";
    file_icon = "/ui/file-icon.png";
    file_icon_white = "/ui/file-icon-white.png";
    var item_size = Math.floor(Math.floor(UI.ScreenH - UI.StatusBarHeight - (bh + padding) * 2 - 40 - padding) / bh);
    for (var i = 0; i < item_size; i++) {
        var btn = IconTextButton(x, y, bw, bh, "", "/ui/folder-icon.png", "/ui/folder-icon-white.png");
        file_items[i] = btn;
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
    y = UI.ScreenH - (bh + padding) * 2;
    var page_button_bw = (UI.ScreenW - page_count_width - 10) / 2;
    var MenuButton_bw = (UI.ScreenW - 5 * 3) / 2;
    last_page_btn = TextButton(5, y + 5, page_button_bw, bh, "<");
    next_page_btn = TextButton(5 + page_button_bw + page_count_width, y + 5, page_button_bw, bh, ">");
    y += bh + 5;
    goback_btn = TextButton(5, y + 5, MenuButton_bw, bh, "Go Back");
    open_btn = TextButton(5 + MenuButton_bw + 5, y + 5, MenuButton_bw, bh, "Open", function () {
        cause_error();
    });
    var root = OpenFile("/", "r");
    open_folder_list[0] = root;
}
function drawBG() {

    UI.FillRect(0, 0, UI.GetScreenW(), UI.GetScreenH(), UI.GetWhite());
}
function wakeup() {
    drawBG();
    load_content();
}
var timer = 0;
var count = 0;
function load_content() {
    var len = open_folder_list.length;
    var idx = len - 1;

    var current_dir = open_folder_list[idx];
    UI.DrawCenterStringFont(current_dir.GetName(), UI.ScreenW / 2, 36, UI.GetFont24());
    var max = file_items.length;
    current_dir.SeekDir(folder_list_current_index);
    var reach_end = false;
    var i = 0;
    for (; i < max; i++) {
        var item = current_dir.OpenNextFile();
        if (item == null) {
            reach_end = true;
        }
        file_items[i].Refresh();
        if (reach_end) {
            file_items[i].OnClick = null;
            file_items[i].IsShown = true;
        } else {
            file_items[i].target_path = item.GetPath();
            file_items[i].IsShown = true;
            file_items[i].content = item.GetName();
            if (item.IsDir()) {

                file_items[i].OnClick = function () {
                    var this_folder = OpenFile_Handle(this.target_path);
                    open_folder_list[open_folder_list.length] = this_folder;
                };
                item.IconBlack = folder_icon;
                item.IconWhite = folder_icon_white;
            } else {
                item.IconBlack = file_icon;
                item.IconWhite = file_icon_white;
            }
            item.Close();
        }
    }
}
function loop() {
    // test_button.Draw();
    var len = file_items.length;
    close_btn.Draw();
    if (show_menu) {

    } else {

        last_page_btn.Draw();
        next_page_btn.Draw();
        goback_btn.Draw();
        open_btn.Draw();
        for (var i = 0; i < len; i++) {
            file_items[i].Draw();
        }
    }
}