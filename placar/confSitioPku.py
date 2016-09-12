#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio de pku

from placarUtil import gmtAgoraNosso
from placarUtil import partition
from placarUtil import parseDateTime
import re

import urllib2

class sitioPku:
    def __init__ (self):
        self.deltaGmt = -8
        self.users = {}

    def icone (self):
        return "http://poj.org/poj.ico"
        
    # url para consulta de resultados
    def urlConsulta (self):
        return "http://poj.org/status"

    def urlUsuario (self, idUser):
    	return "http://poj.org/userstatus?user_id=%s" % idUser

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        return "http://poj.org/problem?id=%s" % idProb

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
        #pref = "\t\t<td><font size=2>"
        #suff = "</tr>"
        #suff = "</font>"
        #patt = pref + ".*" + suff
        while True:
            line = f.readline()
            if len(line) == 0:
                return None
            if not line.startswith('<tr align=center><td>'):
            	continue
            linha = {}

            celulas = line.split('<td>')

            linha["part"]=celulas[2].split('>')[0].split('=')[2]
        
            lang=celulas[7].split('<')[0]
            if lang == "G++":
                lang = "C++"
            linha["lang"]=lang
            linha["prob"]=celulas[3].split('>')[1].split('<')[0]

            status = celulas[4].split('>')[1].split('<')[0]
            if status == "":
                linha["diag"] = "compile error"
            else:
                linha["diag"] = status.lower()

            linha["hora"]=parseDateTime(celulas[9].split('<')[0], self.deltaGmt)

            return linha
