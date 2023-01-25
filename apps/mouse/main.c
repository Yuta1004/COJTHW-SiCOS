#include <uart.h>
#include <mouse.h>
#include <draw.h>

void draw_background() {
    DRAW_FRAME({
        draw_set_stmode(0);
        draw_set_color(0, 128, 128, 128);
        draw_box(0, 0, 1280, 1024);
    });

    DRAW_FRAME({
        draw_set_stmode(0);
        draw_set_color(0, 128, 128, 128);
        draw_box(0, 0, 1280, 1024);
    });
}

void draw_pointer(int ox, int oy, int x, int y, int btn) {
    int color[3] = {
        MOUSE_CLICKED(btn, MOUSE_LBTN) ? 255 : 0,
        MOUSE_CLICKED(btn, MOUSE_CBTN) ? 255 : 0,
        MOUSE_CLICKED(btn, MOUSE_RBTN) ? 255 : 0
    };

    DRAW_FRAME({
        draw_set_stmode(0);

        draw_set_color(0, 128, 128, 128);
        draw_box(ox, oy, 30, 30);

        draw_set_color(0, color[0], color[1], color[2]);
        draw_box(x, y, 30, 30);
    });
}

int main(int argc, char **argv) {
    // マウス関連変数
    int m_xpos, m_ypos, m_zpos, m_btn;
    int x = 0, y = 0;
    int ox1 = 0, oy1 = 0;
    int ox2 = 0, oy2 = 0;

    // 初期化処理
    mouse_init(MOUSE_SXGA, MOUSE_SPEED_0);
    draw_background();

    // 描画処理
    while (1) {
        if (mouse_read(&m_xpos, &m_ypos, &m_zpos, &m_btn)) {
            ox2 = ox1; oy2 = oy1;
            ox1 = x; oy1 = y;
            x = m_xpos; y = m_ypos;
            draw_pointer(ox2, oy2, x, y, m_btn);
        }
        else if (uart_inputc(0) != 0) {
            break;
        }
    }

    return 0;
}
