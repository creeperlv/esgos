var open_btn;
var goback_btn;
var next_page_btn;
var last_page_btn;
var file_items = [];
var close_btn;
function FileItemButton(x, y, w, h, content, icon_black, icon_white) {
    var btn = {
        x: x,
        y: y,
        w: w,
        h: h,
        __state__: -1,
        __state__last: -1,
        IconWhite: icon_white,
        IconBlack: icon_black,
        IconW: 18,
        IconH: 18,
        IconScale: 1,
        file_handle: null,
        content: content,
        Draw: function () {
            var draw = false;
            var is_ptr_inside = __isHitAABB(this.x, this.y, this.w, this.h, Touch.PosX(), Touch.PosY());

            var image_x = this.x;
            var image_y = this.y;
            if (this.IconW > 0) {
                image_x += 5;
            }
            if (this.IconH > 0) {
                image_y += (this.h - this.IconH * this.IconScale) / 2;
            }
            if (is_ptr_inside && Touch.IsPress()) {
                if (this.__state__ != 1) {
                    draw = true;
                    UI.SetTextColor(UI.White);
                    this.__state__ = 1;
                    UI.FillRect(this.x, this.y, this.w, this.h, UI.Black);
                    if (FS.Exists(this.IconWhite))
                        UI.DrawPngFile(this.IconWhite, image_x, image_y, this.IconW, this.IconH, this.IconScale, this.IconScale);
                }
            } else {
                if (this.__state__ != 0) {
                    draw = true;
                    this.__state__ = 0;
                    UI.SetTextColor(UI.Black);
                    UI.FillRect(this.x + 1, this.y + 1, this.w - 2, this.h - 2, UI.White);
                    UI.DrawBox(this.x, this.y, this.w, this.h, UI.Black);
                    if (FS.Exists(this.IconBlack))
                        UI.DrawPngFile(this.IconBlack, image_x, image_y, this.IconW, this.IconH, this.IconScale, this.IconScale);
                }
            }
            UI.SetTextCursor(this.x + this.IconW + 10, this.y + this.h / 2 - 16 / 2)
            Core.Write(this.content);
            {
                if (this.__state__ != this.__state__last) {
                    if (this.__state__last == 1) {
                        if ("OnClick" in this) {
                            if (typeof this.OnClick === "function") {
                                if (is_ptr_inside) {
                                    this.OnClick();
                                }
                            }
                        }
                    }
                    this.__state__last = this.__state__;
                }
            }
            return this.__state__;
        },
        OnClick: function () { },
    };

    return btn;
}
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
        var btn = FileItemButton(x, y, bw, bh, "", "/ui/default_icon_16_b.png", "/ui/default_icon_16_w.png");
        file_items[i] = btn;
        y += bh;
    }
    {
        close_btn = TextButton(0, 20, 40, 40, "<", function () {
            System.LaunchSysApp("/system/home/");
        });
    }
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