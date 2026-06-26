function UIInit() {
    UI.Black = UI.GetBlack();
    UI.White = UI.GetWhite();
    UI.ScreenH = UI.GetScreenH();
    UI.ScreenW = UI.GetScreenW();
    UI.StatusBarHeight = UI.GetStatusBarHeight();
}
function __isHitAABB(x, y, w, h, px, py) {
    return px > x && px < (x + w) && py > y && py < (y + h);
}
function TextButton() {
    var btn = {
        x: 0,
        y: 0,
        w: 0,
        h: 0,
        __state__: -1,
        __state__last: -1,
        content: "",
        Draw: function () {
            var draw = false;
            var is_ptr_inside = __isHitAABB(this.x, this.y, this.w, this.h, Touch.PosX(), Touch.PosY());
            if (is_ptr_inside && Touch.IsPress()) {
                if (this.__state__ != 1) {
                    draw = true;
                    UI.SetTextColor(UI.White);
                    this.__state__ = 1;
                    UI.FillRect(this.x, this.y, this.w, this.h, UI.Black);
                }
            } else {
                if (this.__state__ != 0) {
                    draw = true;
                    this.__state__ = 0;
                    UI.SetTextColor(UI.Black);
                    UI.FillRect(this.x + 1, this.y + 1, this.w - 2, this.h - 2, UI.White);
                    UI.DrawBox(this.x, this.y, this.w, this.h, UI.Black);
                }
            }
            if (draw)
                for (var i = 0; i < 5; i++) {
                    UI.DrawCenterString(this.content, this.x + this.w / 2, this.y + this.h / 2 - 16 / 2);
                }
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
        Refresh: function () {
            this.__state__ = -1;
        }
    }
    return btn;
}
function IconButton() {
    var btn = {
        x: 0,
        y: 0,
        w: 0,
        h: 0,
        IconW: 16,
        IconH: 16,
        IconScale: 1,
        __state__: -1,
        __state__last: -1,
        IconWhite: "/ui/default_icon_16_w.png",
        IconBlack: "/ui/default_icon_16_b.png",
        Draw: function () {
            var draw = false;
            var is_ptr_inside = __isHitAABB(this.x, this.y, this.w, this.h, Touch.PosX(), Touch.PosY());

            var image_x = this.x;
            var image_y = this.y;
            if (this.IconW > 0) {
                image_x += (this.w - this.IconW * this.IconScale) / 2;
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
        Refresh: function () {
            this.__state__ = -1;
        }
    }
    return btn;
}
