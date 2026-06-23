var btn_test;
function init() {
    UIInit();
    btn_test = TextButton();
    btn_test.x = 10;
    btn_test.y = 30;
    btn_test.w = UI.ScreenW - 20;
    btn_test.h = 30;
    btn_test.content = "Click Me!";
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
    btn_test.Draw();
    // timer++;
    // if (timer % 50 == 0) {
    //     drawBG();
    //     if (count == 0) {
    //         UI.DrawCenterStringFont('Hello', UI.GetScreenW() / 2, UI.GetScreenH() / 2, UI.GetFont40());
    //     } else if (count == 1) {
    //         UI.DrawCenterStringFont('Welcome', UI.GetScreenW() / 2, UI.GetScreenH() / 2, UI.GetFont40());
    //     } else if (count == 2) {
    //         UI.DrawCenterStringFont('esGOS', UI.GetScreenW() / 2, UI.GetScreenH() / 2, UI.GetFont40());
    //     }
    //     count++;
    //     if (count > 2) {
    //         count = 0;
    //     }
    // }
}