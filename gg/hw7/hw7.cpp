#include <cmath>
#include <cstdio>
#include <iostream>

using std::min;
using std::max;

typedef unsigned char uchar;

const double CONST_255 = 255.0;
const long long INF = static_cast<long long>(1e8);

struct RGB {
    uchar r, g, b;
};

RGB *my_data;
RGB *temp_data;
FILE *my_file;
uchar *my_bytes;
uchar *temp_bytes;

int cnt = 0;
int width, height;

void reader(int ind, int cur_type) {
    if (cur_type == 5) {
        cnt += fread(&my_bytes[ind], sizeof(uchar), 1, my_file);
    } else {
        cnt += fread(&my_data[ind], sizeof(RGB), 1, my_file);
    }
}

void writer(int ind, int cur_type) {
    if (cur_type == 5) {
        fwrite(&temp_bytes[ind], sizeof(uchar), 1, my_file);
    } else {
        fwrite(&temp_data[ind], sizeof(RGB), 1, my_file);
    }
}

uchar index(uchar *d, int i, int j) {
    return d[i * width + j];
}

RGB indexRGB(RGB *d, int i, int j) {
    return d[i * width + j];
}

void type5_converter(double sh) {
    for (int j = 0; j < height - 1; j++) {
        for (int k = 0; k < width - 1; k++) {
            const double a = index(my_bytes, j - 1, k - 1) / CONST_255;
            const double b = index(my_bytes, j, k - 1) / CONST_255;
            const double c = index(my_bytes, j + 1, k - 1) / CONST_255;
            const double d = index(my_bytes, j - 1, k) / CONST_255;
            const double e = index(my_bytes, j, k) / CONST_255;
            const double f = index(my_bytes, j + 1, k) / CONST_255;
            const double g = index(my_bytes, j - 1, k + 1) / CONST_255;
            const double h = index(my_bytes, j, k + 1) / CONST_255;
            const double i = index(my_bytes, j + 1, k + 1) / CONST_255;

            const double mn = min(min(b, d), min(min(e, f), h)) +
                              min(min(b, min(min(d, e), min(f, h))), min(min(a, c), min(g, i)));
            const double mx = max(max(b, d), max(max(e, f), h)) +
                              max(max(b, max(max(d, e), max(f, h))), max(max(a, c), max(g, i)));

            const double A = sqrt((min(mn, (2 - mx))) / mx);

            const double W = A * (-1) / (8 - 3 * sh);

            const double brightness = ((b * W + d * W + e + f * W + h * W) / (1 + 4 * W)) * CONST_255;
            temp_bytes[j * width + k] = brightness;
        }
    }
}

void type6_converter(double sh) {
    for (int j = 1; j < height - 1; j++) {
        for (int k = 1; k < width - 1; k++) {
            const double aR = indexRGB(my_data, j - 1, k - 1).r / CONST_255;
            const double bR = indexRGB(my_data, j, k - 1).r / CONST_255;
            const double cR = indexRGB(my_data, j + 1, k - 1).r / CONST_255;
            const double dR = indexRGB(my_data, j - 1, k).r / CONST_255;
            const double eR = indexRGB(my_data, j, k).r / CONST_255;
            const double fR = indexRGB(my_data, j + 1, k).r / CONST_255;
            const double gR = indexRGB(my_data, j - 1, k + 1).r / CONST_255;
            const double hR = indexRGB(my_data, j, k + 1).r / CONST_255;
            const double iR = indexRGB(my_data, j + 1, k + 1).r / CONST_255;

            const double aG = indexRGB(my_data, j - 1, k - 1).g / CONST_255;
            const double bG = indexRGB(my_data, j, k - 1).g / CONST_255;
            const double cG = indexRGB(my_data, j + 1, k - 1).g / CONST_255;
            const double dG = indexRGB(my_data, j - 1, k).g / CONST_255;
            const double eG = indexRGB(my_data, j, k).g / CONST_255;
            const double fG = indexRGB(my_data, j + 1, k).g / CONST_255;
            const double gG = indexRGB(my_data, j - 1, k + 1).g / CONST_255;
            const double hG = indexRGB(my_data, j, k + 1).g / CONST_255;
            const double iG = indexRGB(my_data, j + 1, k + 1).g / CONST_255;

            const double aB = indexRGB(my_data, j - 1, k - 1).b / CONST_255;
            const double bB = indexRGB(my_data, j, k - 1).b / CONST_255;
            const double cB = indexRGB(my_data, j + 1, k - 1).b / CONST_255;
            const double dB = indexRGB(my_data, j - 1, k).b / CONST_255;
            const double eB = indexRGB(my_data, j, k).b / CONST_255;
            const double fB = indexRGB(my_data, j + 1, k).b / CONST_255;
            const double gB = indexRGB(my_data, j - 1, k + 1).b / CONST_255;
            const double hB = indexRGB(my_data, j, k + 1).b / CONST_255;
            const double iB = indexRGB(my_data, j + 1, k + 1).b / CONST_255;

            const double mnR = min(min(bR, dR), min(min(eR, fR), hR)) +
                               min(min(bR, min(min(dR, eR), min(fR, hR))), min(min(aR, cR), min(gR, iR)));
            const double mxR = max(max(bR, dR), max(max(eR, fR), hR)) +
                               max(max(bR, max(max(dR, eR), max(fR, hR))), max(max(aR, cR), max(gR, iR)));

            const double mnG = min(min(bG, dG), min(min(eG, fG), hG)) +
                               min(min(bG, min(min(dG, eG), min(fG, hG))), min(min(aG, cG), min(gG, iG)));
            const double mxG = max(max(bG, dG), max(max(eG, fG), hG)) +
                               max(max(bG, max(max(dG, eG), max(fG, hG))), max(max(aG, cG), max(gG, iG)));

            const double mnB = min(min(bB, dB), min(min(eB, fB), hB)) +
                               min(min(bB, min(min(dB, eB), min(fB, hB))), min(min(aB, cB), min(gB, iB)));
            const double mxB = max(max(bB, dB), max(max(eB, fB), hB)) +
                               max(max(bB, max(max(dB, eB), max(fB, hB))), max(max(aB, cB), max(gB, iB)));


            const double AR = sqrt((min(mnR, (2 - mxR))) / mxR);
            const double AG = sqrt((min(mnG, (2 - mxG))) / mxG);
            const double AB = sqrt((min(mnB, (2 - mxB))) / mxB);

            const double WR = AR * (-1) / (8 - 3 * sh);
            const double WG = AG * (-1) / (8 - 3 * sh);
            const double WB = AB * (-1) / (8 - 3 * sh);

            const double brightnessR = ((bR * WR + dR * WR + eR + fR * WR + hR * WR) / (1 + 4 * WR)) * CONST_255;
            const double brightnessG = ((bG * WG + dG * WG + eG + fG * WG + hG * WG) / (1 + 4 * WG)) * CONST_255;
            const double brightnessB = ((bB * WB + dB * WB + eB + fB * WB + hB * WB) / (1 + 4 * WB)) * CONST_255;

            temp_data[j * width + k].r = brightnessR;
            temp_data[j * width + k].g = brightnessG;
            temp_data[j * width + k].b = brightnessB;
        }
    }
}

void convert(double sh, int cur_type) {
    if (cur_type == 5) {
        type5_converter(sh);
    } else if (cur_type == 6) {
        type6_converter(sh);
    }
}

void clear_data(int cur_type) {
    if (cur_type == 6) {
        delete[] my_data;
    } else {
        delete[] my_bytes;
    }
}

int show_error_and_exit(const std::string &message) {
    std::cerr << message << std::endl;
    return 1;
}

int main(int argc, char *argv[]) {

    int type, flag;

    if (argc != 4) {
        show_error_and_exit("Wrong number of arguments");
    }

    my_file = fopen(argv[1], "rb");
    if (my_file == nullptr) {
        show_error_and_exit("Input file can't be opened");
    }

    fscanf(my_file, "P%d%d%d%d\n", &type, &width, &height, &flag);

    if (type < 5 || type > 6) {
        fclose(my_file);
        show_error_and_exit("Input file has a wrong format");
    }
    if (width <= 0 || height <= 0 || (width * 1ll * height > INF)) {
        fclose(my_file);
        show_error_and_exit("Not acceptable amount of data");
    }

    if (type == 5) {
        my_bytes = new uchar[height * width + 1];
        temp_bytes = new uchar[height * width + 1];
    } else {
        my_data = new RGB[height * width + 1];
        temp_data = new RGB[height * width + 1];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            reader(i * width + j, type);
        }
    }
    reader(height * width, type);

    if (cnt != height * width) {
        clear_data(type);
        fclose(my_file);
        show_error_and_exit("Not acceptable amount of data");
    }

    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            if (type == 6) {
                temp_data[j * width + k].r = my_data[j * width + k].r;
                temp_data[j * width + k].g = my_data[j * width + k].g;
                temp_data[j * width + k].b = my_data[j * width + k].b;
            }
            if (type == 5) {
                temp_bytes[j * width + k] = my_bytes[j * width + k];
            }
        }
    }

    double sh = atof(argv[3]);
    convert(sh, type);
    fclose(my_file);

    my_file = fopen(argv[2], "wb");

    if (my_file == nullptr) {
        clear_data(type);
        show_error_and_exit("Output file can't be opened");
    }

    fprintf(my_file, "P%d\n%d %d\n%d\n", type, width, height, flag);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            writer(i * width + j, type);
        }
    }

    clear_data(type);
    fclose(my_file);

    return 0;
}