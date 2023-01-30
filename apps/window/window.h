#ifndef M_WINDOW_H
#define M_WINDOW_H

struct Window {
    /* 基本情報 */
    int x0, y0;             // 左上座標
    int width, height;      // 幅, 高さ
    int layer;              // レイヤ番号(値が大きいほど上位)

    /* リスト構成情報 */
    struct Window *bef_p;
    struct Window *next_p;
};
typedef struct Window Window;

Window *window_root();
void window_new(Window *w_list, int x0, int y0, int width, int height);

#endif