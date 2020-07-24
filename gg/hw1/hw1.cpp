#include <cstdio>
#include <iostream>

typedef unsigned char uchar;

struct RGB {
    uchar r, g, b;
};

RGB *my_data1;
FILE *my_file;
uchar *my_data;

int clearData(int cur_type) {
    delete [] my_data;
    delete [] my_data1;
    fclose(my_file);
    return cur_type;
}

void write(int index, int cur_type) {
    if (cur_type == 5) {
        fwrite(&my_data[index], sizeof(uchar), 1, my_file);
    } else {
        fwrite(&my_data1[index], sizeof(RGB), 1, my_file);
    }
}

int main(int argc, char* argv[]) {

    int type;
    int max_color;
    int width, height;
    int count = 0;

    if (argc != 4) {
        std::cerr << "Wrong count of arguments\n";
        return 1;
    }

    char operation = argv[3][0];
    if (operation < '0' || operation > '4') {
        std::cerr << "Operation doesn't exist\n";
        return 1;
    }

    my_file = fopen(argv[1], "rb");
    if (my_file == nullptr) {
        std::cerr << "Can't open input file\n";
        return 1;
    }

    fscanf(my_file, "P%d%d%d%d\n", &type, &width, &height, &max_color);

    my_data = new uchar[height * width + 1];
    my_data1= new RGB[height * width + 1];

    if (width <= 0 || height <= 0 || type < 5 || type > 6) {
        std::cerr << "Wrong format of input file\n";
        return clearData(1);
    }

    if (type == 5) {
        count = fread(my_data, sizeof(uchar), width * height + 1, my_file);
    } else {
        count = fread(my_data1, sizeof(RGB), width * height + 1, my_file);
    }

    if (count != height * width) {
        std::cerr << "Wrong amount of data\n";
        return clearData(1);
    }

    my_file = fopen(argv[2], "wb");

    if (my_file == nullptr) {
        std::cerr << "Can't open output file\n";
        return clearData(1);
    }

    if (operation == '0') {
        fprintf(my_file, "P%d\n%d %d\n%d\n", type, width, height, max_color);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int index = i * width + j;
                if (type == 5) {
                    my_data[index] = ~my_data[index];
                    fwrite(&my_data[index], sizeof(uchar), 1, my_file);
                } else {
                    my_data1[index].r = ~my_data1[index].r;
                    my_data1[index].g = ~my_data1[index].g;
                    my_data1[index].b = ~my_data1[index].b;
                    fwrite(&my_data1[index], sizeof(RGB), 1, my_file);
                }
            }
        }
    }
    if (operation == '1') {
        fprintf(my_file, "P%d\n%d %d\n%d\n", type, width, height, max_color);
        for (int i = 0; i < height; i++) {
            for (int j = width - 1; j >= 0; j--) {
                write(i * width + j, type);
            }
        }
    }
    if (operation == '2') {
        fprintf(my_file, "P%d\n%d %d\n%d\n", type, width, height, max_color);
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                write(i * width + j, type);
            }
        }
    }
    if (operation == '3') {
        fprintf(my_file, "P%d\n%d %d\n%d\n", type, height, width, max_color);
        for (int i = 0; i < width; i++) {
            for (int j = height - 1; j >= 0; j--) {
                write(j * width + i, type);
            }
        }
    }
    if (operation == '4') {
        fprintf(my_file, "P%d\n%d %d\n%d\n", type, height, width, max_color);
        for (int i = width - 1; i >= 0; i--) {
            for (int j = 0; j < height; j++) {
                write(j * width + i, type);
            }
        }
    }

    return clearData(0);
}