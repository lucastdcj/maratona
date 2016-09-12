#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio de valladolid

from placarUtil import gmtAgoraNosso
from placarUtil import partition
from placarUtil import parseDateTime
import re

import urllib2

class sitioUva:
    def __init__ (self):
        self.deltaGmt = 0
        self.users = {}

    def icone (self):
        return "http://uva.onlinejudge.org/images/favicon.ico"
        
    # url para consulta de resultados
    def urlConsulta (self):
        return "http://uva.onlinejudge.org/index.php?" \
            "option=com_onlinejudge&Itemid=19"

    def urlUsuario (self, idUser):
        return "http://uva.onlinejudge.org/index.php?" \
            "option=com_onlinejudge&page=show_authorstats&userid=%s" % idUser

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        prefixo = "http://uva.onlinejudge.org/external/"
        return "%s%d/%d.html" % (prefixo, int(idProb)/100, int(idProb))

    # hora gmt extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso ()

        #pref = 'Creation UTC date is '
        #suff = '<br/>Next'
        #lista = partition (s, pref)
        #lista = partition (lista[2], suff)
        #return parseDateTime(lista[0])


    # filtro de dados de ussuario, dado um arquivo f determina os
    # dados do usuario: "username", "nome"
    def filtra_usuario (self, f):
        pref = "(<tr class=\"sectiontableentry(1|2)\">|<tr style=\"background-color:#ccffcc;\">)"
        suff = ""
        patt = pref + ".*" + suff
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
        #pref = "<tr class=\"sectiontableentry"
        pref = "(<tr class=\"sectiontableentry(1|2)\">|<tr style=\"background-color:#ccffcc;\">)"
        suff = ""
        #pref = "\t\t<td><font size=2>"
        #suff = "</tr>"
        #suff = "</font>"
        patt = pref + ".*" + suff
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
                #self.users[linha["part"]] = self.filtra_usuario(fOut)["username"]
                fOut.close()

            # precisa autenticar
            #linha["part"] = self.users[linha["part"]]

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

            #linha["hora"] = parseDateTime(m.group(0)[len(pref):-len(suff)])
            #line = f.readline()
            #lista = partition(line, ">")
            #lista = partition(lista[2], "<")
            #linha["diag"] = lista[0].lower()
            #lista = partition(lista[2], "user=")
            #lista = partition(lista[2],">")
            #linha["part"] = lista[0]
 	    #lista = partition(lista[2], "<td>")
 	    #lista = partition(lista[2],"<td>")
 	    #linha["lang"] = lista[0].upper()
            #lista = partition(lista[2], "?p")
            #lista = partition(lista[2], "=")
            #lista = partition(lista[2], '">')
            #linha["prob"] = lista[0]
