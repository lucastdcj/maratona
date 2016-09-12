#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

import datetime
import sys

# obtem hora gmt em datetime
def gmtAgoraNosso ():
    x = datetime.datetime.utcnow()
    return datetime.datetime (x.year, x.month, x.day, x.hour, \
                                  x.minute, x.second)

# faz o parse de cadeia padrao datetime em datetime
def parseDateTime (s, delta = 0):
    s1 = s.split()
    d = s1[0].split('-')
    t = s1[1].split(':')

    timedelta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
    time = datetime.datetime (int(d[0]), int(d[1]), int(d[2]),
                              int(t[0]), int(t[1]), int(t[2]))

    return time + timedelta

# faz o dump de timeDelta em dias, horas, minutos e segundos 
def dumpTimeDelta (d):
    s = ''
    if d.days > 0 or d.days == 0 and d.seconds > 0:
        if (d.days > 0):
            s += '%dd ' % d.days
        s += '%02d:%02d:%02d' % \
            (d.seconds / 3600, d.seconds / 60 % 60, d.seconds % 60)
    return s

# particiona uma cadeia 's'  com padrao 'pat' como s.partition(dat) na
# versao 2.5
def partition (s, pat):
    i = s.find (pat)
    if i == -1:
        return [s, "", ""]
    return  [s[:i], s[i:i + len(pat)], s[i + len(pat):]]

# query com resposta padrao
def query (query, default):
    while True:
        print "%s s/n? [%s]" % (query, default) 
        s = sys.stdin.readline()
        s = s.strip('\n')
        if len(s) == 0:
            if default == "S":
                return "s"
            return "n"
        if s in ["s", "n"]:
            return s

# separa s em lista de tokens separados por palavras da lista 'keywords'
def tokeniza (s, keywords):
    res = {}
    for k in keywords:
        lista = partition (s, k)
        res[k] = lista[0]
        s = lista[2]
    return res
