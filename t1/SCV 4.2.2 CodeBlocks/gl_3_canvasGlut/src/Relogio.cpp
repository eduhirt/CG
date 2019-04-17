#include "Relogio.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Relogio::Relogio()
{
   hora = 0;
}
  
void Relogio::anima()
{
   clear(0,0,0);
   color(1,0,0);

   int x = (int)(cos(hora) * 100);
   int y = (int)(sin(hora) * 100);
   clear(0, 1, 0);
   color(0,0,0);
   circle(200, 200, 110, 30);
   line(200, 200, x + 200, y + 200);
   hora -= 0.001;
}
 
