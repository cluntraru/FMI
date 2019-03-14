#include <iostream>
#include <fstream>

std::ifstream fin("pav.in");
std::ofstream fout("pav.out");

const int kMaxN = 515;

int nxt_color = 1;
int r_tree, c_tree;
int mat[kMaxN][kMaxN];

void make_0(int r, int c) {
    mat[r][c] = nxt_color;
    mat[r][c + 1] = nxt_color;
    mat[r + 1][c] = nxt_color;
    ++nxt_color;
}

void make_90(int r, int c) {
    mat[r][c] = nxt_color;
    mat[r - 1][c] = nxt_color;
    mat[r][c + 1] = nxt_color;
    ++nxt_color;
}

void make_180(int r, int c) {
    mat[r][c] = nxt_color;
    mat[r][c - 1] = nxt_color;
    mat[r - 1][c] = nxt_color;
    ++nxt_color;
}

void make_270(int r, int c) {
    mat[r][c] = nxt_color;
    mat[r + 1][c] = nxt_color;
    mat[r][c - 1] = nxt_color;
    ++nxt_color;
}

void color_4x4(int occupied_corner, int r, int c) {
    switch(occupied_corner) {
        case 0: // Top left
            make_180(r + 1, c + 1);
            make_180(r + 2, c + 2);
            make_180(r + 3, c + 3);
            make_270(r, c + 3);
            make_90(r + 3, c);
            break;
        case 1: // Top right
            make_90(r + 1, c + 2);
            make_90(r + 2, c + 1);
            make_90(r + 3, c);
            make_0(r, c);
            make_180(r + 3, c + 3);
            break;
        case 2: // Bottom right
            make_0(r + 2, c + 2);
            make_0(r + 1, c + 1);
            make_0(r, c);
            make_270(r, c + 3);
            make_90(r + 3, c);
            break;
        case 3: // Bottom left
            make_270(r + 2, c + 1);
            make_270(r + 1, c + 2);
            make_270(r, c + 3);
            make_0(r, c);
            make_180(r + 3, c + 3);
    }
}

void color_2x2(int r, int c) {
    if (r_tree == r && c_tree == c) {
        make_180(r + 1, c + 1);
    }
    else if (r_tree == r && c_tree == c + 1) {
        make_90(r + 1, c);
    }
    else if (r_tree == r + 1 && c_tree == c + 1) {
        make_0(r, c);
    }
    else {
        make_270(r, c + 1);
    }
}

void color_mat(int r, int c, int len, int sector_code) {
    if (len == 2 && found) {
        return;
    }
    else if (len == 1 && mat[r][c] == -1) {
        return true;
    }
    else if (len == 1) {
        return;
    }

    int half_len = len / 2;

    bool found_s0 = color_mat(r, c, half_len, 0, found);
    bool found_s1 = color_mat(r, c + half_len, half_len, 1, found);
    bool found_s2 = color_mat(r + half_len, c + half_len, half_len, 2, found);
    bool found_s3 = color_mat(r + half_len, c, half_len, 3, found);

    if (found && len == 2) {
        color_2x2(r, c);
    }
}

int main() {
    int n;
    fin >> n;
    n = (1 << n);
    fin >> r_tree >> c_tree;
    --r_tree;
    --c_tree;

    color_mat(0, 0, n, 0);
    return 0;
}