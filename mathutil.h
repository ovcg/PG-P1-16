#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "ponto.h"
#include "math.h"
#include <vector>
#include <iostream>
namespace MathUtil {
  
   inline void bezier(const std::vector<Ponto>& pts, float t, Ponto& psaida){
      const unsigned int vertices = (unsigned int)pts.size();
      std::vector<Ponto> Ctrl;
    
      for(int i=0;i<vertices;i++){
        Ctrl.push_back(Ponto(pts[i].x,pts[i].y));
       }

      for(int k=1;k<vertices;k++){  
           for(int j=0;j<vertices-k;j++){
             Ctrl[j].x = ((1-t)*Ctrl[j].x) +  ((t)*Ctrl[j+1].x);
             Ctrl[j].y = ((1-t)*Ctrl[j].y) +  ((t)*Ctrl[j+1].y);
                   }
        }
          
 psaida.x=Ctrl[0].x; //devolve as coordenadas da curva
 psaida.y=Ctrl[0].y;
     }
 
}




       

#endif
