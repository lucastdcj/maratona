/*%
  BigInteger em Java
  Autor: Douglas Oliveira Santos
  Complexidade: --
  Testes: uva10176, uva10183, uva10334, uva113
  uva424, uva495, uva763
  Dependencias: Nenhuma
  Descricao: Operações com BigInteger em Java
  %*/

import java.io.*;
import java.math.BigInteger;
import java.util.*;
  
public class BigInt {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BigInteger res;
        res = BigInteger.valueOf(0);
        BigInteger a, b;
        
        a = sc.nextBigInteger();
        b = sc.nextBigInteger();
        
        res = a.add(b); // a + b
        res = a.subtract(b); // a - b
        res = a.multiply(b); // a * b
        res = a.divide(b); // a / b
        res = a.max(b); // a / b
        res = a.abs(); // abs(a)
        res = a.mod(b); // a mod b
    }
    /* OBS: Scanner tambem pode ser usado
     *  para ler int (sc.nextInt) e double (sc.nextDouble), */
}
