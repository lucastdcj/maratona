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
import urllib2
import xml.etree.ElementTree as ET

contestNameById = {}

class sitioTopcoderContests:
    def __init__ (self):
        self.deltaGmt = 4

    def icone (self):
        return "http://www.topcoder.com/favicon.ico"

    # url para consulta de resultados (último contest)
    def urlConsulta (self):
        response = urllib2.urlopen('http://www.topcoder.com/tc?module=BasicData&c=dd_round_list')
        self.clist = ET.parse(response).getroot()
        self.cid = self.clist[-1][0].text
        self.date = self.clist[-1][-1].text

        for contest in self.clist:
            contestNameById[contest[0].text] = contest[2].text
        
        return 'http://www.topcoder.com/tc?module=BasicData&c=dd_round_results' + \
        '&rd=' + str(self.cid)

    # url de enunciados de problemas (nesse caso, contest)
    def urlProblema (self, idProb):
        return "http://community.topcoder.com/stat?c=round_overview&er=5&rd=" + idProb

    def traduzId (self, idProb):
        sp = idProb.split('-')
        try:
            return contestNameById[sp[0]] + ' (Div. ' + sp[1] + ')'
        except IndexError:
            return contestNameById[sp[0]]

    def deveAtualizar (self, iteracao):
        return (iteracao % 15 == 0)
    
    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso()

    def parseDateTime (self, s, delta = 0):
        delta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
        time = datetime.datetime.strptime(s, "%Y-%m-%d %H:%M")

        return time + delta

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        root = ET.parse(f).getroot()

        ans = []
        totalDiv = [0, 0]

        for line in root:
            for prop in line:
                if prop.tag == 'division':
                    totalDiv[int(prop.text)-1] += 1

        for line in root:
            linha = {}
            rank = score = division = 0
            for prop in line:
                if prop.tag == 'handle':
                    linha['part'] = prop.text
                elif prop.tag == 'division_placed':
                    rank = prop.text
                elif prop.tag == 'problems_correct':
                    score = prop.text
                elif prop.tag == 'division':
                    division = int(prop.text)
                    
            linha['hora'] = self.parseDateTime(self.date, self.deltaGmt)
            linha['prob'] = str(self.cid) + '-' + str(division)
            linha['lang'] = 'NONE'
            linha['diag'] = 'rank '+rank+'/'+str(totalDiv[division-1])+\
                            ' (solved '+str(score)+')'
            
            ans.append(linha)

        return ans

if __name__ == '__main__':
    import urllib2

    conf = sitioTopcoderContests()
    print conf.urlConsulta()
    f = urllib2.urlopen(conf.urlConsulta())

    print conf.filtra_linha(f)
