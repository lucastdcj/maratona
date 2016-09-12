/*%
Algoritmos Básicos para Geométricos
Autor: Alexandre Kunieda (+ PUC-Rio)
Tempo de implementacao: 2 minutos
Descricao: Contem algoritmos simples para geometricos
%*/

/**
Estrutura de ponto e poligono aqui
**/

double polyarea(poly& p){ /* area com sinal */
  int i, n=p.size();
  double area = 0.0;

  for(i=0 ; i<n ; i++)
    area += p[i]%p[(i+1)%n];

  return area/2.0; /* area>0 = ccw ; area<0 = cw */
}

/* ponto p entre segmento [qr] */
int between3(pt p, pt q, pt r){
  if(cmp((q-p)%(r-p)) == 0) /* colinear */
    if(cmp((q-p)*(r-p)) <= 0) /* < para nao contar extremos */
      return 1;

  return 0;
}

/* rotaciona pt p em ang radianos, em torno do ponto q
   se q nao especificado, rotaciona em torno da origem */
pt rotate(pt p, double ang, pt q = pt(0,0)) {
  double s = sin(ang), c = cos(ang);
  p = p-q;
  return q + pt( p.x*c - p.y*s, p.x*s + p.y*c );
}

/**** Exemplo simples de uso ****/
int main() {
  pt v,w;

  while(scanf(" %lf %lf", &v.x,&v.y)==2){
    w = rotate(v,pi/4);
    printf("%lf %lf\n", w.x,w.y);

    w = rotate(v,pi/4, pt(1,1));
    printf("%lf %lf\n", w.x,w.y);
  }

  return 0;
}
