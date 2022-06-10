#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "argparser.h"
#include "energy.h"
#include "image.h"
#include "util.h"

/**
 * Compute the brightness and print the statistics of @p `img`,
 * i.e. width, height & brightness.
 */


void statistics(struct image* img) {
    // TODO implement (assignment 3.1)
    /* implement and use the function:
     * `image_brightness`
     */
     unsigned width = img->w;
     unsigned height = img->h;
     unsigned brightness = (image_brightness(img));

printf ( "width: %u\n" , width ) ;
printf ( "height: %u\n" , height);
printf ( "brightness: %u\n" , brightness );
    
  //  NOT_IMPLEMENTED;
    //UNUSED(img);
}

/**
 * Find & print the minimal path of @p `img`.
 */
void find_print_min_path(struct image* img) {
    // TODO implement (assignment 3.2)
    /* implement and use the functions:
     * - `calculate_energy`
     * - `calculate_min_energy_column`
     * - `calculate_optimal_path`
     * in `energy.c`
     */
    int h = img->h , w= img->w;

    uint32_t* energy = malloc(4 * h * w );
   // memset(energy, 0, w * h * 4);
    calculate_energy(energy , img , w);

    int col = calculate_min_energy_column (energy , w , w ,h);
    uint32_t* seam = malloc(4*h );
    //memset(seam, 0, h * 4);
    calculate_optimal_path (energy , w, w ,h , col , seam);

for (int q=0;q<h;q++)
{  uint32_t x = *(seam+q);
    printf("%u\n",x);
}

free(seam);
free(energy);





    //NOT_IMPLEMENTED;
    // UNUSED(img);
}

/**
 * Find & carve out @p `n` minimal paths in @p `img`.
 * The image size stays the same, instead for every carved out path there is a
 * column of black pixels appended to the right.
 */
void find_and_carve_path(struct image* const img, int n) {
    // TODO implement (assignment 3.3)
    /* implement and use the functions from assignment 3.2 and:
     * - `carve_path`
     * - `image_write_to_file`
     * in `image.c`.
     */

    
int h = img->h , w0 = (img->w);

uint32_t* energy = malloc(4 * h * w0 );
uint32_t* seam = malloc(4*h );

    for (int q=0;q<n;q++)
    { 
        
        int w= w0-q;

        
        

        calculate_energy(energy , img , w);

        int col = calculate_min_energy_column (energy , w0 , w ,h);
        
        

        calculate_optimal_path (energy , w0 , w ,h , col , seam);

        carve_path(img, w , seam);

        

    }

free(seam);
free(energy);
image_write_to_file(img, "out.ppm" );



    //NOT_IMPLEMENTED;
    //UNUSED(img);
    //UNUSED(n);
}

/**
 * Parse the arguments and call the appropriate functions as specified by the
 * arguments.
 */
int main(int const argc, char** const argv) {
    // DO NOT EDIT
    bool show_min_path = false;
    bool show_statistics = false;
    int n_steps = -1;

    char const* const filename =
        parse_arguments(argc, argv, &show_min_path, &show_statistics, &n_steps);
    if (!filename) return EXIT_FAILURE;

    struct image* img = image_read_from_file(filename);

    if (show_statistics) {
        statistics(img);
        image_destroy(img);
        return EXIT_SUCCESS;
    }

    if (show_min_path) {
        find_print_min_path(img);
    } else {
        if (n_steps < 0 || n_steps > img->w) n_steps = img->w;

        find_and_carve_path(img, n_steps);
    }

    image_destroy(img);
    return EXIT_SUCCESS;
}
