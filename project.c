
//----------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "pipeline.h"
#include "transforms.h"

//----------------------------------------------------------------
void project( Parameters *paramsP )
{
  Matrix projection;

  //----------------------------------------
  // Announce ourselves and construct the proper
  //  projection matrix.
  if ( paramsP->viewpoint == 0.0 ) {
    printf(
      "//------------------------- Parallel -----\n"
      "// Projecting\n"
      "//    world range : (%g, %g) .. (%g, %g)\n"
      "//    canvas size : (W %d, H %d)\n",
      paramsP->wXmin, paramsP->wYmin,
      paramsP->wXmax, paramsP->wYmax,
      paramsP->width, paramsP->height );
    //    (HINT:  Use the proper routine from transforms.c.)
      
      FLOAT64 xmin = (paramsP->wXmin);
      FLOAT64 xmax = (paramsP->wXmax);
      FLOAT64 ymin = (paramsP->wYmin);
      FLOAT64 ymax = (paramsP->wYmax);
      projectParallelMatrix(xmin,xmax,ymin,ymax,paramsP->width,paramsP->height,projection);

    ;

  } else {
    printf(
      "//------------------------- Perspective --\n"
      "// Projecting\n"
      "//    world range : (%g, %g) .. (%g, %g)\n"
      "//    canvas size : (W %d, H %d)\n"
      "//    viewpoint   : %g\n",
      paramsP->wXmin, paramsP->wYmin,
      paramsP->wXmax, paramsP->wYmax,
      paramsP->width, paramsP->height,
      paramsP->viewpoint );

    //    (HINT:  Use the proper routine from transforms.c.)

      FLOAT64 d = paramsP->viewpoint;
      FLOAT64 xmin =  paramsP->wXmin;
      FLOAT64 xmax =  paramsP->wXmax;
      FLOAT64 ymin =  paramsP->wYmin;
      FLOAT64 ymax =  paramsP->wYmax;
      projectPerspectiveMatrix(d,xmin,xmax,ymin,ymax,paramsP->width,paramsP->height,projection);
      
  }

  //----------------------------------------
  // Transform all of the points!

  // TODO:  Put something here to transform all of the points
  //          in paramsP->points using the projection matrix you
  //          computed above.  Don't forget to normalize the
  //          point after transforming it!
  //
  //    (HINT:  Use the proper routine from matrix.c to do the
  //        multiply of the transformation matrix and the point
  //        then copy the transformed point back to the proper
  //        spot in paramsP->points.)
   
        for ( int i=0; i<paramsP->numPoints; i++ )
      {
   
         FLOAT64 x = paramsP->points[i][0];
         FLOAT64 y = paramsP->points[i][1];
         FLOAT64 z = paramsP->points[i][2];

         Point p = {x,y,z,1};
         multMatrixPoint(projection,p,paramsP->points[i]);
         normalizePoint( paramsP->points[i], paramsP->points[i]);

      }
   
}

//----------------------------------------------------------------
