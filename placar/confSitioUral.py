#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio Ural

from placarUtil import gmtAgoraNosso
from placarUtil import parseDateTime
from placarUtil import partition
import re
import datetime

class sitioUral:
    def __init__ (self):
        self.deltaGmt = -6
        self.start = 1
        self.content = ""
        self.months = {"Jan":"1", "Feb":"2", "Mar":"3", "Apr":"4",
                       "May":"5", "Jun":"6", "Jul":"7", "Aug":"8",
                       "Sep":"9", "Oct":"10", "Nov":"11", "Dec":"12"}

        self.entry = 0

        self.beg = ['<TD class="id">',
                    '<TD class="date">',
                    '<TD class="coder">',
                    '<TD class="problem">',
                    '<TD class="language">',
                    '<TD class="verdict_rj">',
                    '<TD class="test">',
                    '<TD class="runtime">',
                    '<TD class="memory">']

        self.end = ['</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',
                    '</TD>',]

        self.exp = [re.compile('(.*)'),
                    re.compile('(.*<BR>.*)'),
                    re.compile('.*id=(.*)">.*'),
                    re.compile('.*num=([0-9]*)">.*'),
                    re.compile('(.*)'),
                    re.compile('(?:(?:<A HREF="ce.*">)|(?:.*>))?([^<>]+)(:?</A>)?'),
                    re.compile('(.*)'),
                    re.compile('(.*)'),
                    re.compile('(.*)')]

        self.ber = zip(self.beg, self.end, self.exp)

    def icone (self):
        return "http://acm.timus.ru/favicon.ico"

    # url para consulta de resultados
    def urlConsulta (self):
        return "http://acm.timus.ru/status.aspx?space=1&count=30"

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        prefixo = "http://acm.timus.ru/print.aspx?space=1&num="
        return prefixo + idProb

    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso()

    def translateLang(self, s):
        if 'Java' in s:
            return 'JAVA'
        if 'G++' in s or 'C++' in s:
            return 'C++'
        if 'C' in s:
            return 'C'
        if 'FPC' in s:
            return 'PASCAL'
        return 'Unknown'

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        if self.start == 1:
            self.content = f.readline()
            self.start = 0

        if self.entry % 2 == 0:
            needle = '<TR class="even">'
        else: needle = '<TR class="odd">'

        ini = self.content.find(needle)
        fim = self.content[ini:].find("</TD></TR>")

        if ini == -1:
            self.start = 1
            self.entry = 0
            self.content = ""
            return None

        entry = self.content[ini:ini+fim+len("</TD></TR>")]
        self.content = self.content[fim+len("</TD></TR>"):]

        res = []
        for b,e,r in self.ber:
            ini = entry.find(b)
            fim = entry.find(e)

            m = r.match(entry[ini+len(b):fim])
            res.append(m.group(1))

            entry = entry[fim+len(e):]

        s = res[1].split("<BR>")
        date = s[1].split()
        date = '-'.join([date[2], self.months[date[1]], date[0]])

        linha = {}
        timestamp = date + " " + s[0]
        timestamp = timestamp.replace("<NOBR>","").replace("</NOBR>","")
        linha["hora"] = parseDateTime(timestamp, self.deltaGmt)
        linha["part"] = res[2]
        linha["prob"] = res[3]
        linha["diag"] = res[5].lower()
        linha["lang"] = self.translateLang(res[4])

        self.entry += 1

        # {"hora", "part", "prob", "diag", "lang"}

        return linha

#
# Teste
##################################################
if __name__ == '__main__':

    import urllib2

    conf = sitioUral()
    f = urllib2.urlopen(conf.urlConsulta())

    while True:
        res = conf.filtra_linha(f)
        if res == None:
            break
        print res
