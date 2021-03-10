
//----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "pipeline.h"

//----------------------------------------------------------------
#define INSIDE    (0)
#define LEFT      (1 << 0)
#define ABOVE     (1 << 1)
#define RIGHT     (1 << 2)
#define BELOW     (1 << 3)

static int _zone( int x, int y, Parameters *paramsP );

//----------------------------------------------------------------
int clipLine( int *p1x, int *p1y, int *p2x, int *p2y, Parameters *paramsP )
{
       int p1zone = _zone(*p1x,*p1y,paramsP);
       int  p2zone = _zone(*p2x,*p2y,paramsP);
       int clip ;

   while ( 1 )
  {
    
     if((p1zone == INSIDE) && (p2zone == INSIDE))
       { 
         clip = 1;
          break;
       }
     
      if((p1zone & p2zone)!=INSIDE)
       {  
         clip = 0;
         break;
       }
      
       FLOAT64 x, y ;
       int temp ;

        
       if(p1zone == INSIDE)
       {
        temp = p2zone;
       }
       else  
        {
        temp = p1zone;
        }
       if(temp & ABOVE)
        {
           x = *p1x + (*p2x - *p1x)*(paramsP->sYmax - *p1y)/(*p2y - *p1y);
           y = paramsP->sYmax;
        }
         else if(temp & BELOW)
        {
           x = *p1x + (*p2x - *p1x)*(paramsP->sYmin - *p1y)/(*p2y - *p1y) ;
           y = paramsP->sYmin;
        }

         else if(temp & LEFT)
        {
           y = *p1y + (*p2y - *p1y)*(paramsP->sXmin - *p1x)/(*p2x - *p1x) ;
           x = paramsP->sXmin;
        }
         else if(temp & RIGHT)
        {
           y = *p1y + (*p2y - *p1y)*(paramsP->sXmax - *p1x)/(*p2x - *p1x)  ;
           x = paramsP->sXmax;
        }
         else
        {
            fprintf(stderr, "Code didn't  match any regions.");
            exit(1);
        }
        if(temp == p1zone)
        {
         *p1x = ROUND(x);
         *p1y = ROUND(y);
         p1zone = _zone(*p1x,*p1y,paramsP);
        }
        else
        { 
          *p2x = ROUND(x);
          *p2y = ROUND(y);
         p2zone = _zone(*p2x,*p2y,paramsP);
         }
        }
       
 
      return clip ;
  }


//----------------------------------------------------------------
static int _zone( int x, int y, Parameters *paramsP )
{
         
         int code = INSIDE;
         if(x<paramsP->sXmin)
          { 
             code = code | LEFT;
          }
         
         else if(x>paramsP->sXmax)
         { 
          code = code | RIGHT;
         }

        if(y<paramsP->sYmin)
          { 
             code = code | BELOW;
          }

         else if(y>paramsP->sYmax)
         { 
          code = code | ABOVE;
         }
       

    return code;

         
          
}

//----------------------------------------------------------------
