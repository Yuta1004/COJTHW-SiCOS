#ifndef M_WINDOW_H
#define M_WINDOW_H

struct Window {
    /* 基本情報 */
    int x0, y0;             // 左上座標
    int width, height;      // 幅, 高さ
    int layer;              // レイヤ番号(値が大きいほど上位)

    /* コールバック */
    void (*draw_callback)(struct Window *wp, int, int);

    /* 状態保持用 */
    void *statp;

    /* リスト構成情報 */
    struct Window *bef_p;
    struct Window *next_p;
};
typedef struct Window Window;

Window *get_top_window(Window *w_list);
Window *get_clicked_window(Window *w_list, int x, int y);

Window *window_root();
void window_new(
    Window *w_list,
    int x0,
    int y0,
    int width,
    int height,
    void (*draw_callback)(Window *wp, int, int),
    void *statp
);
void window_liftup(Window *w_list, Window *target);
void window_remove(Window *w_list, Window *target);
void window_free(Window *w_list);

#endif
