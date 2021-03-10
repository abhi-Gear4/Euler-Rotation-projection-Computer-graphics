---------------------------------------------------
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"
#include "pipeline.h"
#include "transforms.h"

//----------------------------------------------------------------
void eulerRotate( Parameters *paramsP )
{
  FLOAT64 phiDeg   = RAD2DEG( paramsP->phi );
  FLOAT64 thetaDeg = RAD2DEG( paramsP->theta );
  FLOAT64 psiDeg   = RAD2DEG( paramsP->psi );

  //----------------------------------------
  // Announce ourselves
  printf(
    "//----------------------------------------\n"
    "// Euler rotation by ϕ %g°, θ %g°, ψ %g° ...\n",
    phiDeg, thetaDeg, psiDeg );

  //----------------------------------------
  // Construct the three rotation matrices.

  //    (HINT:  Use the proper routine from transforms.c.)
      Matrix x,y,z;
       

        rotateZMatrix( DEG2RAD(psiDeg), z);
        rotateYMatrix( DEG2RAD(thetaDeg), y);
        rotateXMatrix( DEG2RAD(phiDeg), x);

  //----------------------------------------
  // Compute the object's center.


  //    (HINT:  You can initialize your mins and maxes using
  //        DBL_MAX and -DBL_MAX.)
       FLOAT64 xmin,ymin,zmin,xmax,ymax,zmax;

        xmin = ymin = zmin = DBL_MAX;
        xmax = ymax = zmax = -DBL_MAX;
     for(int i = 0;i<paramsP->numPoints ; i++)
         {
               
              if((paramsP->points[i][0])<xmin)
               {
                  xmin = (paramsP->points[i][0]) ;
               }
             if((paramsP->points[i][1])<ymin)
               {
                  ymin = (paramsP->points[i][1]) ;
               }
              if((paramsP->points[i][2])<zmin)
               {
                  zmin = (paramsP->points[i][2]) ;
               }
              if((paramsP->points[i][0])>xmax)
               {
                  xmax = (paramsP->points[i][0]) ;
               }

              if((paramsP->points[i][1])>ymax)
               {
                  ymax = (paramsP->points[i][1]);
               }

              if((paramsP->points[i][2])>zmax)
               {
                  zmax = (paramsP->points[i][2]) ;
               }
         }

         FLOAT64 tx = (xmin + xmax)/2;
         FLOAT64 ty = (ymin + ymax)/2;
         FLOAT64 tz = (zmin + zmax)/2;

    
  //----------------------------------------
  // Construct the two translation matrices.

  //     
  //    (HINT:  Use the proper routine from transforms.c.)
        Matrix xorigin ;
        Matrix xbcenter ;
        translateMatrix(-tx,-ty,-tz,xorigin);
        translateMatrix(tx,ty,tz,xbcenter);
     

  //----------------------------------------
  // Construct the combined transformation.

  //
  //    (HINT:  Use the proper routine from transforms.c.)
        Matrix combined,rotzy,rotzyx,xlateorigin;
        
         multMatrix(x,y,rotzy);
         multMatrix(rotzy, z,rotzyx);
         multMatrix(xbcenter,rotzyx,xlateorigin);
         multMatrix(xlateorigin,xorigin,combined);
   
     
         
        
    

  //----------------------------------------
  // Display the r and e values.
  printf( "//   r00 = %11.6f, r01 = %11.6f, r02 = %11.6f\n",
    combined[0][0], combined[0][1], combined[0][2] );
  printf( "//   r10 = %11.6f, r11 = %11.6f, r12 = %11.6f\n",
    combined[1][0], combined[1][1], combined[1][2] );
  printf( "//   r20 = %11.6f, r21 = %11.6f, r22 = %11.6f\n",
    combined[2][0], combined[2][1], combined[2][2] );

  printf( "//   ex  = %11.6f, ey  = %11.6f, ez  = %11.6f\n",
    combined[0][3], combined[1][3], combined[2][3] );

  //----------------------------------------
  // Transform all of the points!


        for ( int i=0; i<paramsP->numPoints; i++ )
      {
         double x = paramsP->points[i][0];
         double y = paramsP->points[i][1];
         double z = paramsP->points[i][2];
         Point p = {x,y,z,1};
         multMatrixPoint(combined,p,paramsP->points[i]);

      }
   }

//----------------------------------------------------------------
