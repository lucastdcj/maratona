#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.


from placarUtil import gmtAgoraNosso
from placarUtil import partition
from placarUtil import parseDateTime
import re

import urllib2

class sitioLiveArchive:
    def __init__ (self):
        self.deltaGmt = 0
        self.users = {}

    def icone (self):
        return "http://icpc.baylor.edu/img/icon-icpc-small.gif"

    # url para consulta de resultados
    def urlConsulta (self):
        return "http://icpcarchive.ecs.baylor.edu/index.php?" \
            "option=com_onlinejudge&Itemid=19"

    def urlUsuario (self, idUser):
        return "http://icpcarchive.ecs.baylor.edu/index.php?" \
            "option=com_onlinejudge&page=show_authorstats&userid=%s" % idUser

    # url de enunciados de problemas
    def urlProblema (self, idProb):
       prefixo = "http://icpcarchive.ecs.baylor.edu/external/"
       return "%s%d/%d.html" % (prefixo, int(idProb)/100, int(idProb))

    # hora gmt extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso ()

    # filtro de dados de ussuario, dado um arquivo f determina os
    # dados do usuario: "username", "nome"
    def filtra_usuario (self, f):
        pref = "(<tr class=\"sectiontableentry(1|2)\">|<tr style=\"background-color:#ccffcc;\">)"
        patt = pref + ".*"
        while True:
            line = f.readline()
            if len(line) == 0:
                return None
            m = re.search(patt, line)
            if m == None:
                continue
            dados = {}

            f.readline()
            f.readline()

            line = f.readline()[:-6]
            line = line.split("(")
            dados["nome"] = line[0].strip()
            dados["username"] = line[1][:-1]
            return dados


    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        pref = "(<tr class=\"sectiontableentry(1|2)\">|<tr style=\"background-color:#ccffcc;\">)"
        patt = pref + ".*"
        while True:
            line = f.readline()
            if len(line) == 0:
                return None
            m = re.search (patt, line)
            if m == None:
                continue
            linha = {}

            f.readline()
            linha["prob"] = f.readline().split(">")[2].split("<")[0]
            f.readline()

            linha["part"] = f.readline().split("userid=")[1].split(">")[0][:-1]
            if False and linha["part"] not in self.users:
                # Hardcoded:
                # consulta url
                fOut = open ("competidor.html", "w")
                fIn = urllib2.urlopen(self.urlUsuario(linha["part"]))
                fOut.write (fIn.read())
                fIn.close()
                fOut.close()

                fOut = open("competidor.html", "r")
                fOut.close()

            linha["diag"] = f.readline().strip()[4:-5].lower()
            if linha["diag"] == "":
                linha["diag"] = "running"

            linha["lang"] = "C"

            f.readline()
            f.readline()
            f.readline()

            line = f.readline().strip()[4:-5]
            linha["hora"] = parseDateTime(line, self.deltaGmt)

            return linha

if __name__ == '__main__':

    import urllib2

    conf = sitioLiveArchive()
    f = urllib2.urlopen(conf.urlConsulta())

    while True:
        res = conf.filtra_linha(f)
        if res == None:
            break
        print res
    
