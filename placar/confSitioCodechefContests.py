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
import random
import json

class sitioCodechefContests:
    def __init__ (self):
        self.deltaGmt = -4

    def icone (self):
        return "http://www.codechef.com/misc/favicon.ico"

    def contestEnded(self, url):
        f = urllib2.urlopen(url)

        for line in f:
            if 'CONTEST ENDED' in line:
                return True

        return False
    
    # retorna uma lista de urls dos últimos contests
    def getContests(self):
        f = urllib2.urlopen("http://www.codechef.com")
        inlist = False
        ans = []
        
        for line in f:
            if inlist and 'href' in line:
                i = line.find('href')
                url = line[i:].split("\"")[1]
                if self.contestEnded(url):
                    ans.append(url)

            if inlist and '</ul>' in line:
                return ans
            
            if "All Contests" in line:
                inlist = True
        
    # url para consulta de resultados
    def urlConsulta (self):
        conts = self.getContests()
        # rand é usado como workaround para capturar vários tipos de contests
        pick = conts[random.randint(0,len(conts)-1)]

        lslash = pick.rfind('/',0,-1)
        ranksUrl = pick[:lslash] + '/api/rankings' + pick[lslash:] + \
        '?itemsPerPage=undefined'
        
        return ranksUrl

    # url de enunciados de problemas (nesse caso, contest)
    def urlProblema (self, idProb):
        return "http://www.codechef.com/" + idProb

    def deveAtualizar (self, iteracao):
        return (iteracao % 15 == 0)

    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso()

    def parseDateTime (self, s, delta = 0):
        delta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
        time = datetime.datetime.strptime(s, "%Y-%m-%d %H:%M:%S")

        return time + delta

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        data = json.load(f)
        cid = data["contest_info"]["contest_code"]

        ans = []

        for line in data['list']:
            linha = {}
            linha['hora'] = gmtAgoraNosso()
            linha['part'] = line['user_handle']
            linha['prob'] = str(cid)
            linha['lang'] = 'NONE'
            linha['diag'] = 'rank '+str(line['rank'])+'/'+\
            str(len(data['list']))+' (score '+str(line['score'])+')'
            
            ans.append(linha)

        return ans

if __name__ == '__main__':
    import urllib2

    conf = sitioCodechefContests()
    print conf.urlConsulta()
    f = urllib2.urlopen(conf.urlConsulta())
    print conf.filtra_linha(f)
