#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Agregar esta línea

typedef struct {
    unsigned char red, blue, green;
} Color;

typedef struct {
    Color*** colors;
    unsigned int width, height;
} Image;

int generateRandomNumber(int r1, int r2){
    return r1 + rand() % (r2 - r1 + 1);
}

Color* generateRandomColor(){
    Color* co = (Color*) malloc(sizeof(Color));
    co->red = generateRandomNumber(0, 255);
    co->blue = generateRandomNumber(0, 255);
    co->green = generateRandomNumber(0, 255);
    return co;
}

Image* createImage(int cols, int rows){
    Image* im = (Image*) malloc(sizeof(Image));
    im->width = cols;
    im->height = rows;

    im->colors = (Color***) malloc(rows * sizeof(Color**));

    for (int row = 0; row < rows; row++){
        im->colors[row] = (Color**) malloc(cols * sizeof(Color*));
        for (int col = 0; col < cols; col++){
            im->colors[row][col] = generateRandomColor();
        }
    }

    return im;
}

void printImage(Image* im) {
    for (int row = 0; row < im->height; row++) {
        for (int col = 0; col < im->width; col++) {
            Color* pixelColor = im->colors[row][col];
            printf("R:%d, G:%d, B:%d  ", pixelColor->red, pixelColor->green, pixelColor->blue);
        }
        printf("\n");
    }
}

int main() {
    // para que en cada ejecución realmente haga números aleatorios
    srand(time(NULL)); 

    Image* image1 = createImage(3, 10);
    printImage(image1);

    // liberar la memoria
    for (int row = 0; row < image1->height; row++) {
        for (int col = 0; col < image1->width; col++) {
            free(image1->colors[row][col]);
        }
        free(image1->colors[row]);
    }
    free(image1->colors);
    free(image1);

    return 0;
}
