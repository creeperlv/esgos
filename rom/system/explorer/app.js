var open_btn;
var goback_btn;
var next_page_btn;
var last_page_btn;
var file_items = [];
var close_btn;
var open_folder_list = [];
var folder_list_current_index = 0;
var page_count_width = 100;
var show_menu;
var folder_icon;
var folder_icon_white;
var file_icon;
var file_icon_white;
var last_selection_y;
var selected_path;
var bh;

function unselect_all() {
    if (last_selection_y > 0) {
        UI.FillRect(5, last_selection_y, 50, bh, UI.White);
    }
}
function load_content() {
    var len = open_folder_list.length;
    var idx = len - 1;

    var current_dir = OpenFile(open_folder_list[idx]);
    close_btn.Refresh();
    UI.FillRect(0, 20, UI.GetScreenW(), 40, UI.White);
    UI.DrawCenterStringFont(open_folder_list[idx], UI.GetScreenW() / 2, 36, UI.GetFont24());
    current_dir.SeekDir(folder_list_current_index);
    var max = file_items.length;
    var reach_end = false;
    var i = 0;
    for (; i < max; i++) {
        var item = current_dir.OpenNextFile();
        if (item == null) {
            reach_end = true;
        }
        file_items[i].Refresh();
        if (reach_end) {
            file_items[i].IsShown = false;
        } else {
            file_items[i].target_path = "" + item.GetPath();
            file_items[i].file_name = "" + item.GetName();
            file_items[i].IsShown = true;
            file_items[i].IsDir = item.IsDir();
            file_items[i].content = file_items[i].file_name;
            if (file_items[i].IsDir) {
                file_items[i].IconBlack = folder_icon;
                file_items[i].IconWhite = folder_icon_white;
            } else {
                file_items[i].IconBlack = file_icon;
                file_items[i].IconWhite = file_icon_white;
            }
            item.Close();
        }
    }
    // }
    current_dir.Close();
}
function init() {
    UIInit();
    selected_path = null;
    show_menu = false;
    page_count_width = 150;
    folder_list_current_index = 0;
    last_selection_y = -1;
    var base_x = 15;
    bh = 60;
    var bottom_button_y = UI.ScreenH - (bh + 10) * 2;
    var y = 60;
    var bw = (UI.ScreenW - 60);
    var x = 55;
    var padding = 5;
    folder_icon = "/ui/folder-icon.png";
    folder_icon_white = "/ui/folder-icon-white.png";
    file_icon = "/ui/file-icon.png";
    file_icon_white = "/ui/file-icon-white.png";
    var item_size = Math.floor(Math.floor(UI.ScreenH - UI.StatusBarHeight - (bh + padding) * 2 - 40 - padding) / bh);
    for (var i = 0; i < item_size; i++) {
        var btn = IconTextButton(x, y, bw, bh, "", "/ui/default_icon_16_b.png", "/ui/default_icon_16_w.png");
        btn.file_name = "";
        btn.target_path = "";
        btn.IsDir = false;
        btn.OnClick = function () {
            unselect_all();
            last_selection_y = this.y;
            UI.FillRect(5, last_selection_y, 50, this.h, UI.Black);
            selected_path = this.target_path;
        };
        file_items[i] = btn;
        y += bh;
    }
    {
        close_btn = TextButton(0, 20, 40, 40, "<", function () {
            System.LaunchSysApp("/system/home/");
        });
    }
    y = UI.ScreenH - (bh + padding) * 2;
    var page_button_bw = (UI.ScreenW - page_count_width - 10) / 2;
    var MenuButton_bw = (UI.ScreenW - 5 * 3) / 2;
    last_page_btn = TextButton(5, y + 5, page_button_bw, bh, "<");
    next_page_btn = TextButton(5 + page_button_bw + page_count_width, y + 5, page_button_bw, bh, ">");
    y += bh + 5;
    goback_btn = TextButton(5, y + 5, MenuButton_bw, bh, "Go Back", function () {
        if (open_folder_list.length > 1) {

            open_folder_list.pop();
            folder_list_current_index = 0;
            unselect_all();
            selected_path = null;
            load_content();
        }
    });
    open_btn = TextButton(5 + MenuButton_bw + 5, y + 5, MenuButton_bw, bh, "Open", function () {
        if (selected_path != null) {
            var len = open_folder_list.length;
            folder_list_current_index = 0;
            open_folder_list[len] = selected_path;
            unselect_all();
            selected_path = null;
            load_content();
        }
    });
    open_folder_list[0] = "/";
}
function drawBG() {

    UI.FillRect(0, 0, UI.GetScreenW(), UI.GetScreenH(), UI.GetWhite());
}
function wakeup() {
    drawBG();
    load_content();
}
function loop() {
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