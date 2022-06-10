#include "image.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "indexing.h"
#include "util.h"

/**
 * Initialize the image @p `img` with width @p `w` and height @p `h`.
 */
struct image* image_init(int const w, int const h) {
    // DO NOT EDIT
    struct image* img = malloc(sizeof(struct image));
    img->w = w;
    img->h = h;
    img->pixels = malloc(w * h * sizeof(*img->pixels));
    memset(img->pixels, 0, w * h * sizeof(*img->pixels));
    return img;
}

/**
 * Destroy the image @p `img` by freeing its pixels field and by freeing @p
 * `img` itself. Don't use @p img afterwards.
 */
void image_destroy(struct image* img) {
    free(img->pixels);
    free(img);
}

/**
 * Read an image from the file at @p `filename` in the portable pixmap (P3)
 * format. See http://en.wikipedia.org/wiki/Netpbm_format for details on the
 * file format.
 * @returns the image that was read.
 */
struct image* image_read_from_file(const char* filename) {
    // DO NOT EDIT
    FILE* f = fopen(filename, "r");
    if (f == NULL) exit(EXIT_FAILURE);

    if (fscanf(f, "P3") == EOF) {
        fclose(f);
        exit(EXIT_FAILURE);
    }

    int w, h;
    if (fscanf(f, "%d %d 255 ", &w, &h) == EOF) {
        fclose(f);
        exit(EXIT_FAILURE);
    }
    if (w <= 0 || h <= 0) {
        fclose(f);
        exit(EXIT_FAILURE);
    }

    struct image* img = image_init(w, h);
    struct pixel* pixels = img->pixels;

    for (int y = 0; y < img->h; ++y) {
        unsigned int r, g, b;
        for (int x = 0; x < img->w; ++x, ++pixels) {
            if (fscanf(f, "%u %u %u ", &r, &g, &b) == EOF) {
                image_destroy(img);
                fclose(f);
                exit(EXIT_FAILURE);
            }
            pixels->r = r;
            pixels->g = g;
            pixels->b = b;
        }
    }

    if (fgetc(f) != EOF) {
        image_destroy(img);
        fclose(f);
        exit(EXIT_FAILURE);
    }

    fclose(f);
    return img;
}

/**
 * Write the image @p `img` to file at @p `filename` in the portable pixmap (P3)
 * format. See http://en.wikipedia.org/wiki/Netpbm_format for details on the
 * file format.
 */
void image_write_to_file(struct image* img, const char* filename) {
    // TODO implement (assignment 3.3)

FILE* f = fopen(filename, "w");
fprintf(f, "P3\n%d %d\n255\n", img->w ,img->h);

for (int y =0;y<img->h;y++)
{   for (int x =0 ; x<img->w;x++)       
    { uint8_t r , g, b ;
        r= (img->pixels+yx_index(y,x,img->w))->r ;
        b= (img->pixels+yx_index(y,x,img->w))->b ;
        g= (img->pixels+yx_index(y,x,img->w))->g ;
fprintf(f, "%d %d %d ", r, g, b );
//if(x!=(img->w)-1)
//fprintf(f, " ");
    }
//fprintf(f,"\n");

}

fclose(f);

//if (f == NULL) exit(EXIT_FAILURE);



   // NOT_IMPLEMENTED;
    //UNUSED(img);
   // UNUSED(filename);
}

/**
 * Compute the brightness of the image @p `img`.
 */
uint8_t image_brightness(struct image* img) {
    // TODO implement (assignment 3.1)
    unsigned wd = img->w;
    unsigned ht = img->h;
    unsigned sum = 0;
    struct pixel* pixels = img->pixels;
    for (int y = 0; y < img->h; ++y) {
        for (int x = 0; x < img->w; ++x, ++pixels) {
            sum += ((pixels->r) + (pixels->g) + (pixels->b))/3 ;
        }
    }
int x = sum / (wd*ht);
uint8_t result = x;
return (result);

   // NOT_IMPLEMENTED;
    //UNUSED(img);
}

/**
 * Carve out the path @p `seam` from the image @p `img`,
 * where only the @p `w` left columns are considered.
 * Move all pixels right of it one to the left and fill the rightmost row with
 * black (0,0,0). Columns with index >= `w` are not considered as part of the
 * image.
 */
void carve_path(struct image* const img, int const w,
                uint32_t const* const seam) {
    // TODO implement (assignment 3.3)

for(int y =0; y<img->h ; y++)
{ int x = *(seam+y);
for (; x<w-1;x++)
{ *(img->pixels+yx_index(y,x,img->w)) = *(img->pixels+yx_index(y,x+1,img->w));

}
(img->pixels+yx_index(y,x,img->w))->r=0;
(img->pixels+yx_index(y,x,img->w))->g=0;
(img->pixels+yx_index(y,x,img->w))->b=0;



}    





    //NOT_IMPLEMENTED;
    //UNUSED(img);
    //UNUSED(w);
    //UNUSED(seam);
}
