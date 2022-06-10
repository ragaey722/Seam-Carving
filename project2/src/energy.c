#include "energy.h"

#include <stdlib.h>
#include <string.h>

#include "indexing.h"
#include "util.h"
#include <limits.h>

uint32_t max(uint32_t a, uint32_t b) { return a > b ? a : b; }

uint32_t min(uint32_t a, uint32_t b) { return a < b ? a : b; }

/**
 * Calculate the difference of two color values @p a and @p b.
 * The result is the sum of the squares of the differences of the three (red,
 * green and blue) color components.
 * */
inline uint32_t diff_color(struct pixel const a, struct pixel const b) {
    // TODO implement (assignment 3.2)
    uint32_t x = ((a.r - b.r) * (a.r - b.r)) + ((a.g - b.g)*(a.g - b.g)) + ((a.b - b.b) * (a.b - b.b)) ;                                                                   
    return x;
    //NOT_IMPLEMENTED;
    //UNUSED(a);
    //UNUSED(b);
}

/**
 * Calculate the total energy at every pixel of the image @p `img`,
 * but only considering columns with index less than @p `w`.
 * To this end, first calculate the local energy and use it to calculate the
 * total energy.
 * @p `energy` is expected to have allocated enough space
 * to represent the energy for every pixel of the whole image @p `img.
 * @p `w` is the width up to (excluding) which column in the image the energy
 * should be calculated. The energy is expected to be stored exactly analogous
 * to the image, i.e. you should be able to access the energy of a pixel with
 * the same array index.
 */
void calculate_energy(uint32_t* const energy, struct image* const img,
                      int const w) {
    // TODO implement (assignment 3.2)
    int32_t hi = img->h;

    for (int y=0;y<hi;y++)
    { for (int x =0;x<w;x++)
        { uint32_t left = 0 , top =0; 
            
             if (y-1>=0){
            top = diff_color( *( img->pixels+yx_index(y,x,img->w) ), *(img->pixels+yx_index(y-1,x,img->w)));
        }
            if (x-1>=0)
            {left = diff_color(  *(img->pixels+yx_index(y,x,img->w)) , *(img->pixels+yx_index(y,x-1,img->w)) );}
            *(energy+yx_index(y,x,img->w)) = top + left;

        }

    }

    for (int y=1;y<hi;y++)
    { for (int x =0;x<w;x++)
        { uint32_t left = UINT_MAX , right = UINT_MAX , above = UINT_MAX  , mn = UINT_MAX; 
            
           if(x-1>=0)
           {left = *(energy+yx_index(y-1,x-1,img->w));}
           if(x+1<w)
           {right = *(energy+yx_index(y-1,x+1,img->w));}
           above = *(energy+yx_index(y-1,x,img->w));
            mn = min(above , min(left,right));
            *(energy+yx_index(y,x,img->w))+= mn;

    }
    }

   // NOT_IMPLEMENTED;
    //UNUSED(energy);
   // UNUSED(img);
   // UNUSED(w);
}

/**
 * Calculate the index of the column with the least energy in bottom row.
 * Expects that @p `energy` holds the energy of every pixel of @p `img` up to
 * column (excluding) @p `w`. Columns with index `>= w` are not considered as
 * part of the image.
 * @p `w0` states the width of the energy matrix @p `energy`
 * @p `h` states the height of the energy matrix @p `energy`
 */
int calculate_min_energy_column(uint32_t const* const energy, int const w0,
                                int const w, int const h) {
    // TODO implement (assignment 3.2)
    uint32_t mn = *(energy+yx_index(h-1,0,w0));
    int mncol=0;
    uint32_t tmp=0;
for (int x=1;x<w;x++ )
{ tmp = *(energy+yx_index(h-1,x,w0));
    if(tmp<mn)
    {mn= tmp; mncol=x;}

}
    return mncol;

   // NOT_IMPLEMENTED;
   // UNUSED(energy);
  //  UNUSED(w0);
 //   UNUSED(w);
  //  UNUSED(h);
}

/**
 * Calculate the optimal path (i.e. least energy), according to the energy
 * entries in @p `energy` up to (excluding) column @p `w`. The path is stored in
 * @p `seam`. Columns with index `>= w` are not considered as part of the image.
 * @p `x` is the index in the bottom row where the seam starts.
 * @p `w0` states the width of the energy matrix @p `energy`
 * @p `h` states the height of the energy matrix @p `energy`
 */
void calculate_optimal_path(uint32_t const* const energy, int const w0,
                            int const w, int const h, int x,
                            uint32_t* const seam) {
    // TODO implement (assignment 3.2)

        int prev=x ;
        *(seam+(h-1))=x;
    for (int y = h-2; y>=0;y--)
    {   uint32_t left = UINT_MAX , right = UINT_MAX , above = UINT_MAX  , mn = UINT_MAX , mncol=0 ;
          above=*(energy+yx_index(y,prev,w0));
        if(prev-1>=0){ left = *(energy+yx_index(y,prev-1,w0)) ;}
        if(prev+1<w){ right= *(energy+yx_index(y,prev+1,w0)) ;}
        mn = above; mncol=prev;
        if(left<mn && prev-1>=0){mn= left; mncol=prev-1;}
        if(right<mn && prev+1<w){mn=right;mncol=prev+1;}
        *(seam+y)=mncol;
        prev=mncol;

    }





    //NOT_IMPLEMENTED;
   // UNUSED(energy);
  //  UNUSED(w0);
   // UNUSED(w);
  //  UNUSED(h);
  //  UNUSED(x);
  //  UNUSED(seam);
}
