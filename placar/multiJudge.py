from placarUtil import gmtAgoraNosso
from confSitioUva import sitioUva
from confSitioLiveArchive import sitioLiveArchive
from confSitioSpoj import sitioSpoj
from confSitioSpojBR import sitioSpojBR
from confSitioUral import sitioUral
from confSitioPku import sitioPku
from confSitioCodeforces import sitioCodeforces
from confSitioCodeforcesContests import sitioCodeforcesContests
from confSitioTopcoderContests import sitioTopcoderContests
from confSitioCodechefContests import sitioCodechefContests
from confSitioUri import sitioUri
import sys,urllib2,httplib


classeSitio = {"uva": sitioUva, 
               "liveArchive": sitioLiveArchive,
               "spoj": sitioSpoj,
               "spojBR": sitioSpojBR,
               "ural": sitioUral,
               "pku": sitioPku,
               "codeforces": sitioCodeforces,
               "codeforcesContests": sitioCodeforcesContests,
               "topcoderContests": sitioTopcoderContests,
               "codechefContests": sitioCodechefContests,
               "uri": sitioUri}

class multiJudge:
    def __init__(self):
        self.sitios = {}
        self.iteracao = 0
        pass

    def addSitio(self,sitio):
        if not sitio in classeSitio.keys():
            print "id de sitio '%s' invalido" % sitio
            print "validos: %s" % classeSitio.keys()
            sys.exit()
        if not sitio in self.sitios.keys():
            s = classeSitio[sitio] ()
            self.sitios[sitio] = s

    def update(self, iteracao=0):
        for name,s in self.sitios.items():
            try:
                if not s.deveAtualizar(iteracao):
                    continue
            except:
                pass

            print 'Update ' + name #debug
            self.updateSitio(s)
            if s.html == None:
                continue
            while (1):
                try:
                    l = s.filtra_linha(s.html)
                except httplib.IncompleteRead:
                    break
                except: #deve ser tratado com mais cuidado
                    break
                
                if l == None:
                    break
                elif isinstance(l, list):
                    for elem in l:
                        elem["prob"] = name + "." + elem["prob"]
                        elem["part"] = name + "." + elem["part"]
                        yield elem
                    break
                else:
                    l["prob"] = name + "." + l["prob"]
                    l["part"] = name + "." + l["part"]
                    yield l

    def urlProblema(self, sitio, p):
        return self.sitios[sitio].urlProblema(p)

    def iconeSitio(self, sitio):
        try:
            return self.sitios[sitio].icone()
        except:
            return ""

    def traduzId (self, sitio, idProb):
        try:
            return self.sitios[sitio].traduzId(idProb)
        except:
            return idProb

    def gmtAgora(self, s):
        return gmtAgoraNosso()

        # Faz o download da url de submissoes
    def updateSitio (self,s):
        s.html = None
        try:
            s.html = urllib2.urlopen(s.urlConsulta(),timeout=30)
        except (urllib2.HTTPError, urllib2.URLError, httplib.BadStatusLine):
            print "Erro ao baixar pagina"
            pass
        except: #deve ser tratado com mais cuidado
            print "Erro desconhecido"
            pass

        # parece que urlopen pode retornar HTTPError
        if isinstance(s.html, urllib2.HTTPError):
            s.html = None
