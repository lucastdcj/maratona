#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio spoj br

from placarUtil import gmtAgoraNosso
from placarUtil import parseDateTime
from placarUtil import partition
import re

class sitioSpojBR:
    def __init__ (self):
        self.deltaGmt = -3

    def icone (self):
        return "http://www.spoj.com/favicon.ico"

    # url para consulta de resultados
    def urlConsulta (self):
        return "http://br.spoj.pl/status"

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        prefixo = "http://br.spoj.pl/problems/"
        return prefixo + idProb

    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso ()

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        pref = ""
        suff = "</td>"
        patt = pref + ".*" + suff
        while True:
            line = f.readline()
            if len(line) == 0:
                return None
            if not line.startswith('<td class="status_sm">'):
                continue
            line = f.readline()
            line = f.readline()
            linha = {}
            #m = re.search (patt, line)
            linha["hora"] = parseDateTime(line, self.deltaGmt)
            #linha["hora"] = parseDateTime( \
            #    line[len(pref):-len(suff)], self.deltaGmt)
            #print "HORA:", linha["hora"]
            line = f.readline()
            line = f.readline()
            line = f.readline()
            lista = partition(line, 'title="')
            lista = partition(lista[2], '"')
            linha["part"] = lista[0]
            lista = partition(lista[2], 'title="')
            lista = partition(lista[2], '"')
            linha["prob"] = lista[0]
            line = f.readline().strip(' \t\r\n')
            while line == "":
                line = f.readline().strip(' \t\r\n')
            linha["diag"] = self.translate(line)
	    line = f.readline()
	    while not line.startswith('<td class="slang'):
	        line = f.readline()
	    line = f.readline()
            lista = partition(line, '<p>')
            lista = partition(lista[2], '</p>')
            linha["lang"] = lista[0].strip()
            return linha

    def translate (self, s):
        if "aceito" in s:
            return "accepted"
        if "resposta errada" in s:
            return "wrong answer"
        if "tempo limite excedido" in s:
            return "time limit exceeded"
        if "erro em tempo de execução" in s:
            return "runtime error"
        return "running"

if __name__ == '__main__':
    import urllib2

    conf = sitioSpojBR()
    f = urllib2.urlopen(conf.urlConsulta())

    while True:
        res = conf.filtra_linha(f)
        if res == None:
            break
        print res
