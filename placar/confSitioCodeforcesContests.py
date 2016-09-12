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
import json
import random

contestNameById = {}

class sitioCodeforcesContests:
    def __init__ (self):
        self.contestNameById = {}
        self.deltaGmt = 3

    def icone (self):
        return "http://codeforces.com/favicon.ico"

    # url para consulta de resultados
    def urlConsulta (self):
        response = urllib2.urlopen('http://codeforces.com/api/contest.list?gym=false')
        self.clist = json.load(response)['result']
        
        while self.clist[0]['phase'] != "FINISHED":
            self.clist.pop(0)

        # rand é usado como workaround para capturar tanto div 1 quanto div 2
        self.cid = self.clist[random.randint(0,1)]['id']

        for contest in self.clist:
            contestNameById[str(contest['id'])] = contest['name'].replace( \
            'Codeforces Round', 'CF')

        return 'http://codeforces.com/api/contest.standings?' + \
        'contestId=' + str(self.cid) + '&from=1&count=5000&showUnofficial=false'

    # url de enunciados de problemas (nesse caso, contest)
    def urlProblema (self, idProb):
        return "http://www.codeforces.com/contest/" + idProb

    def traduzId (self, idProb):
        return contestNameById[idProb]

    def deveAtualizar (self, iteracao):
        return (iteracao % 15 == 0)
        
    # hora gmt nao pode ser extraida da cadeia obtida na consulta
    def gmtAgora (self, s):
        return gmtAgoraNosso()

    def parseDateTime (self, ts, delta = 0):
        delta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
        time = datetime.datetime.fromtimestamp(ts)

        return time + delta

    # filtro  de  linha  de  consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        data = json.load(f)['result']

        if data['contest']['phase'] != 'FINISHED':
            return []

        ans = []

        for line in data['rows']:
            linha = {}
            linha['hora'] = self.parseDateTime(data['contest']['startTimeSeconds'], \
                self.deltaGmt)
            linha['part'] = line['party']['members'][0]['handle']
            linha['prob'] = str(self.cid)
            linha['lang'] = 'NONE'

            score = len(filter(lambda x: x['points'] > 0, line['problemResults']))
            linha['diag'] = 'rank '+str(line['rank'])+'/'+str(len(data['rows']))+\
            ' (solved '+str(score)+')'
            
            ans.append(linha)

        return ans

if __name__ == '__main__':

    import urllib2

    conf = sitioCodeforcesContests()
    print conf.urlConsulta()
    f = urllib2.urlopen(conf.urlConsulta())

    print conf.filtra_linha(f)
