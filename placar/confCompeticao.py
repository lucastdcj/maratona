#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

from confSitioUva import sitioUva
from confSitioLiveArchive import sitioLiveArchive
from confSitioSpoj import sitioSpoj
from confSitioSpojBR import sitioSpojBR
from confSitioUral import sitioUral
from confSitioPku import sitioPku
from confSitioCodeforces import sitioCodeforces
from confSitioUri import sitioUri
from placarUtil import parseDateTime
from multiJudge import multiJudge
import sys



## constantes
# versao
versao = "placar em python versao 5 (com modificacoes) - 2007-08-05 cll"
# nome do arquivo de configuracao de competicao
nomeArqConfCompeticao = "competicao.conf"
# nome do arquivo de nomes de participantes
nomeArqConfParticipantes = "../participantes.conf"
# nome do arquivo de nomes de participantes do replay
nomeArqConfParticipantesReplay = "participantes.rep"
# nome do arquivo html obtido no sitio
nomeArqConsultaHtml = "consulta.html"
# nome do arquivo de configuracao do placar
nomeArqConfPlacar = "placar.conf"
# nome do arquivo de configuracao do status
nomeArqConfStatus = "status.conf"
# nome do placar
nomeArqResultadoHtml = "index.html"
# nome do placar publico
nomeArqResultadoHtmlPublico = "placar.html"
# nome do arquivo consolidado de informacoes
nomeArqLog = "competicao.log"
# nome do arquivo de replay
nomeArqReplay = "replay"
# nome do arquivo com log de excecões que encerram o placar
nomeArqErrLog = "error.log"
# comprimento do identificador de problemas
comprIdProb = 5
# comprimento do identificador de participantes
comprIdPart = 6
# tempo de dormida em segundos
dormida = 60
# Quantidade de ultimas submissoes a serem destacadas
lastSubs = 5

class competicao:
    def __init__ (self):
        self.versao = versao
        self.nomeArqConsultaHtml = nomeArqConsultaHtml
        self.nomeArqConfPlacar = nomeArqConfPlacar
        self.nomeArqConfStatus = nomeArqConfStatus
        self.nomeArqResultadoHtml = nomeArqResultadoHtml
        self.nomeArqResultadoHtmlPublico = nomeArqResultadoHtmlPublico
        self.nomeArqLog = nomeArqLog
        self.nomeArqReplay = nomeArqReplay
        self.comprIdProb = comprIdProb
        self.comprIdPart = comprIdPart
        self.dormida = dormida

        f = open (nomeArqConfCompeticao)
        self.titulo = f.readline().strip('\n')
        s = f.read().split('\n')
        f.close()

        self.inicio = parseDateTime (s.pop(0))
        self.termino = parseDateTime (s.pop(0))

        self.sitio = multiJudge()

        self.listProb = {}
        self.idProbOrd = []
        self.ID = {}
        self.multiID = {}

        for n in s:
            if len(n) == 0:
                continue
            (s,p) = n.split(" ")
            sitio = s.strip()
            p = p.strip()
            self.sitio.addSitio(sitio)
            self.listProb[sitio + "." + p] = self.sitio.urlProblema(sitio,p)
            self.idProbOrd.append(sitio + "." + p)
        #self.idProbOrd = self.listProb.keys()
        #self.idProbOrd.sort()

        allNames = []
            
        f = open (nomeArqConfParticipantes)
        allNames += f.readlines()
        f.close()
        try:
            f = open (nomeArqConfParticipantesReplay)
            allNames += f.readlines()
            f.close()
        except:
            pass
         
        self.listPart = {}
        for line in allNames:
            line = line.strip().split(' ')
            id = line[0]

            name = " ".join(line[1:])
            if name in self.multiID.keys():
                self.ID[id] = self.multiID[name]
            else:
                self.listPart[id] = name
                self.ID[id] = id
                self.multiID[name] = id
        
        self.idPartOrd = self.listPart.keys()
        self.idPartOrd.sort()

        #Hardcoded: fix afterwards
        self.listLang = { "C":"C", "C++":"C++", "JAVA":"Java", "PASCAL":"Pascal", "NONE":"None" }
        self.idLangOrd = self.listLang.keys()
        self.idLangOrd.sort()

    def partId(self, part):
        sep = part.split('.', 2)
        if part in self.ID:
            return self.ID[part]
        elif len(sep) == 2 and sep[1] in self.ID:
            return self.ID[sep[1]]
        else:
            return None
