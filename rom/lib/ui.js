function UIInit() {
    UI.Black = UI.GetBlack();
    UI.White = UI.GetWhite();
    UI.ScreenH = UI.GetScreenH();
    UI.ScreenW = UI.GetScreenW();
    UI.StatusBarHeight = UI.GetStatusBarHeight();
    UI.EPDFastest=4;
    UI.EPDFast=3;
    UI.EPDText=2;
    UI.EPDQuality=1;
}
function __isHitAABB(x, y, w, h, px, py) {
    return px > x && px < (x + w) && py > y && py < (y + h);
}
function TextButton(x, y, w, h, content, OnClick) {
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
    if (x != undefined) {
        btn.x = x;
    }
    if (y != undefined) {
        btn.y = y;
    }
    if (w != undefined) {
        btn.w = w;
    }
    if (h != undefined) {
        btn.h = h;
    }
    if (content != undefined) {
        btn.content = content;
    }
    if (OnClick != undefined) {
        btn.OnClick = OnClick;
    }
    return btn;
}
function IconButton(x, y, w, h, icon_black, icon_white, OnClick) {
    var btn = {
        x: 0,
        y: 0,
        w: 0,
        h: 0,
        IconW: 16,
        IconH: 16,
        IsShown: true,
        IconScale: 1,
        __state__: -1,
        __state__last: -1,
        IconWhite: "/ui/default_icon_16_w.png",
        IconBlack: "/ui/default_icon_16_b.png",
        Draw: function () {
            if (!this.IsShown) {
                this.__state__ = -2;
                if (this.__state__ != this.__state__last) {
                    UI.FillRect(this.x, this.y, this.w, this.h, UI.White);
                    this.__state__last = this.__state__;
                }
                return;
            }
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
    if (x != undefined) {
        btn.x = x;
    }
    if (y != undefined) {
        btn.y = y;
    }
    if (w != undefined) {
        btn.w = w;
    }
    if (h != undefined) {
        btn.h = h;
    }
    if (icon_white != undefined) {
        btn.IconWhite = icon_white;
    }
    if (icon_black != undefined) {
        btn.IconBlack = icon_black;
    }
    if (OnClick != undefined) {
        btn.OnClick = OnClick;
    }
    return btn;
}
function QWERTYKeyboard() {
    var kbd_obj = {
        input_key_buttons: [],
        __content__input__: "",
        Draw: function () {
            var len = this.input_key_buttons.length;
            for (var i = 0; i < len; i++) {
                this.input_key_buttons[i].Draw();
            }
            if (this.__content__input__ == "") {
                return null;
            }
            var r = this.__content__input__;
            this.__content__input__ = "";
            return r;
        },
        OnClose: function () {

        }
    };
    var bw = UI.ScreenW / 10 - 5;
    var bh = bw * 1.25;
    var first_line_y = UI.ScreenH - bh * 4 + 5 * 4;
    var first_line_x = (UI.ScreenW - bw * 10 - 5 * 9) / 2;
    var btn_id = 0;
    var x = first_line_x;
    var y = first_line_y;
    {
        {
            var btn = TextButton(x, y, bw, bh, "q", function () {
                kbd_obj.__content__input__ = this.content;
            });
            x += bw + 5;
            kbd_obj.input_key_buttons[btn_id] = btn;
            btn_id++;
        }
        {
            var btn = TextButton(x, y, bw, bh, "w", function () {
                kbd_obj.__content__input__ = this.content;
            });
            x += bw + 5;
            kbd_obj.input_key_buttons[btn_id] = btn;
            btn_id++;
        }
        {
            var btn = TextButton(x, y, bw, bh, "e", function () {
                kbd_obj.__content__input__ = this.content;
            });
            x += bw + 5;
            kbd_obj.input_key_buttons[btn_id] = btn;
            btn_id++;
        }
        {
            var btn = TextButton(x, y, bw, bh, "r", function () {
                kbd_obj.__content__input__ = this.content;
            });
            x += bw + 5;
            kbd_obj.input_key_buttons[btn_id] = btn;
            btn_id++;
        }
    }
    return kbd_obj;
}
function IconTextButton(x, y, w, h, content, icon_black, icon_white, OnClick) {
    var btn = {
        x: 0,
        y: 0,
        w: 0,
        h: 0,
        IsShown: true,
        __state__: -1,
        __state__last: -1,
        content: "",
        IconWhite: "/ui/default_icon_16_w.png",
        IconBlack: "/ui/default_icon_16_b.png",
        IconW: 18,
        IconH: 18,
        IconScale: 1,
        Draw: function () {
            if (!this.IsShown) {
                this.__state__ = -2;
                if (this.__state__ != this.__state__last) {
                    UI.FillRect(this.x, this.y, this.w + 1, this.h + 1, UI.White);
                    this.__state__last = this.__state__;
                }
                return;
            }
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
            if (draw) {
                UI.SetTextCursor(this.x + this.IconW + 10, this.y + this.h / 2 - 16 / 2)
                Core.Write(this.content);
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
        },
    };

    if (x != undefined) {
        btn.x = x;
    }
    if (y != undefined) {
        btn.y = y;
    }
    if (w != undefined) {
        btn.w = w;
    }
    if (h != undefined) {
        btn.h = h;
    }
    if (content != undefined) {
        btn.content = content;
    }
    if (icon_white != undefined) {
        btn.IconWhite = icon_white;
    }
    if (icon_black != undefined) {
        btn.IconBlack = icon_black;
    }
    if (OnClick != undefined) {
        btn.OnClick = OnClick;
    }
    return btn;
}