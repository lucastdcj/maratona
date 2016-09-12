/*%
Distância Esférica
Autor: Guilherme Kunigami
Complexidade: O(1)
Tempo de implementacao: 1min
Testes: Uva 10075, nuevo 4153
Descricao: Calcula a distância entre 2 pontos em uma esfera
%*/

#include <cmath>

double torad;
double r = 6378;

struct geo {
  double lat, lon;
   geo(double lat1 = 0.0, double lon1 = 0.0) {
    lat = lat1 * torad;
    lon = lon1 * torad;
}};

double geoDist(geo a, geo b)
{
  return acos(sin(a.lat) * sin(b.lat) +
         cos(a.lat)*cos(b.lat)*cos(fabs(a.lon - b.lon)))*r;
}

/**** Exemplo simples de uso ****/
int main(void)
{
  torad = acos(-1) / 180.0;
  /* Calcula a distancia entre os pontos a e b, dadas
     sua latitude/longitude no planeta de raio r  */
  geo a(23.8500, 90.4000);
  geo b(22.2500, 91.8333);
  printf("Distancia esferica: %.3lf\n", geoDist(a, b));

  return 0;
}
