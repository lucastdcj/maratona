#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio codeforces

from placarUtil import gmtAgoraNosso
from placarUtil import partition
import datetime
import re

class sitioCodeforces:
    def __init__ (self):
        self.deltaGmt = -4

    def icone (self):
        return "http://codeforces.com/favicon.ico"
        
    # url para consulta de resultados
    def urlConsulta (self):
        return "http://www.codeforces.com/problemset/status"

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        prefixo = "http://www.codeforces.com/problemset/problem/"
        return prefixo + idProb[0:-1] + "/" + idProb[-1];

    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso()

    def parseDateTime (self, s, delta = 0):
        delta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
        time = datetime.datetime.strptime(s, "%Y-%m-%d %H:%M:%S")

        return time + delta

    def translateLang(self, s):
        if 'Java' in s:
            return 'JAVA'
        if ' C++' in s:
            return 'C++'
        if ' C' in s:
            return 'C'
        if 'FPC' in s:
            return 'PASCAL'
        return 'Unknown'

    def translateDiag(self, s):
        if 'Accepted' in s:
            return 'accepted'
        if 'Time limit exceeded' in s:
            return 'time limit exceeded'
        if 'Wrong answer' in s:
            return 'wrong answer'
        if 'Runtime Error' in s:
            return 'runtime error'
        if 'Running' in s or 'queue' in s:
            return 'running'
        return 'runtime error'

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        headertag = "data-submission-id="
        while True:
            line = f.readline()
            if len(line) == 0:
                return None
            if not headertag in line:
                continue

            for i in range(5):
                line = f.readline()
            linha = {}
            line = line.strip()
            linha["hora"] = self.parseDateTime(line, self.deltaGmt)

            for i in range(3):
                line = f.readline()
            lista = partition(line, '/profile/')
            lista = partition(lista[2], '"')
            linha["part"] = lista[0]

            for i in range(3):
                line = f.readline()
            lista = partition(line, '/problem/')
            lista = partition(lista[2], '"')
            lista = partition(lista[0], '/')
            linha["prob"] = lista[0]+lista[2]

            for i in range(5):
                line = f.readline()

            linha["lang"] = self.translateLang(line.strip())

            line = f.readline()
            while not 'submissionId' in line:
                line = f.readline()

            line = f.readline()
            linha["diag"] = self.translateDiag(line)
            return linha

if __name__ == '__main__':

    import urllib2

    conf = sitioCodeforces()
    f = urllib2.urlopen(conf.urlConsulta())

    while True:
        res = conf.filtra_linha(f)
        if res == None:
            break
        print res
