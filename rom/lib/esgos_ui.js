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
            // var color = UI.Black;
            if (__isHitAABB(this.x, this.y, this.w, this.h, Touch.PosX(), Touch.PosY()) && Touch.IsPress()) {
                if (this.__state__ == 1)
                    return this.__state__;
                UI.SetTextColor(UI.White);
                this.__state__ = 1;
                // color = UI.White;
                UI.FillRect(this.x, this.y, this.w, this.h, UI.Black);
            } else {
                if (this.__state__ == 0)
                    return this.__state__;
                this.__state__ = 0;
                UI.SetTextColor(UI.Black);
                UI.FillRect(this.x + 1, this.y + 1, this.w - 2, this.h - 2, UI.White);
                UI.DrawBox(this.x, this.y, this.w, this.h, UI.Black);
            }
            for (var i = 0; i < 5; i++) {
                UI.DrawCenterString(this.content, this.x + this.w / 2, this.y + this.h / 2 - 16 / 2);
            }
        },
        Refresh: function () {
            this.__state__ = -1;
        }
    }
    return btn;
}