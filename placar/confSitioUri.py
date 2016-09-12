#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

# configuracao para o sitio URI Online Judge

from placarUtil import gmtAgoraNosso
import datetime
import cookielib
import urllib, urllib2
import re

class sitioUri:
    email = 'placarunicamp@gmail.com'
    password = 'unicamp'
    url_login = "https://www.urionlinejudge.com.br/judge/login"
    url_consulta = "https://www.urionlinejudge.com.br/judge/pt/runs/live"
    
    def __init__ (self):
        cj = cookielib.CookieJar()
        authhandler = urllib2.HTTPSHandler()
        cookiehandler = urllib2.HTTPCookieProcessor(cj)
        opener = urllib2.build_opener(authhandler, cookiehandler)
        urllib2.install_opener(opener)
        
        self.deltaGmt = 3

    def icone (self):
        return "https://urionlinejudge.r.worldssl.net/judge/img/3.1/favicon.030914.icos"

    # FIXME Assumindo que campo 'value' vem em seguida a 'name'
    def getFormField(self, html, name):
        return html.split(name + '\"')[1].split('\"')[1]

    def ensureLogin(self):
        fd = urllib2.urlopen(self.url_login)
        html = fd.read()

        try:
            key = self.getFormField(html, 'data[_Token][key]')
            fields = self.getFormField(html, 'data[_Token][fields]')
            
            postdata = {"data[User][email]":self.email,
                "data[User][password]":self.password,
                "data[_Token][key]":key,
                "data[_Token][fields]":fields,
                "data[_Token][unlocked]":""}

            urllib2.urlopen(self.url_login, urllib.urlencode(postdata))
        except IndexError:
            return

    # url para url_consulta de resultados
    def urlConsulta (self):
        self.ensureLogin()
        return self.url_consulta

    # url de enunciados de problemas
    def urlProblema (self, idProb):
        prefixo = "https://www.urionlinejudge.com.br/judge/pt/problems/view/"
        return prefixo + idProb;

    # hora gmt nao pode ser extraida da cadeia obtida na url_consulta
    def gmtAgora (self, s=None):
        return gmtAgoraNosso()

    # uri retorna apenas a hora, então usamos tambem a data atual
    def parseDateTime (self, s, delta = 0):
        now = self.gmtAgora()
        s_dmy = "%d-%d-%d " % (now.year, now.month, now.day) + s
        delta = datetime.timedelta(0, 0, 0, 0, 0, delta, 0)
        time = delta + datetime.datetime.strptime(s_dmy, "%Y-%m-%d %H:%M:%S")

        if time > now:
            time = time + datetime.timedelta(-1)

        return time

    def translateLang(self, s):
        if 'Java' in s:
            return 'JAVA'
        if 'C++' in s:
            return 'C++'
        return 'Unknown'

    def translateDiag(self, s):
        if 'Accepted' in s:
            return 'accepted'
        if 'Time limit exceeded' in s:
            return 'time limit exceeded'
        if 'Wrong answer' in s:
            return 'wrong answer'
        return 'runtime error'

    def filter_tags(self, s):
        return s.split('>')[1].split('<')[0]

    # filtro  de  linha  de  url_consulta,  dado arquivo  f  determina  um
    # dicionario contendo  dados da url_consulta:  "hora", "part", "prob",
    # "diag" (hora, participante, problema, diagnostico)
    def filtra_linha (self, f):
        headertag = "td class=\"id\""
        while True:
            linha = {}
            line = f.readline()
            if len(line) == 0 or line.strip() == "</table>":
                return None
            if not headertag in line:
                continue

            for i in range(2):
                line = f.readline()
            linha["prob"] = line.split('/problems/view/')[1].split('\"')[0]

            for i in range(2):
                line = f.readline()

            linha["part"] = line.split('/profile/')[1].split('\"')[0]
            
            for i in range(2):
                line = f.readline()

            linha["diag"] = self.translateDiag(self.filter_tags('>' + line))

            line = f.readline()
            linha["lang"] = self.translateLang(self.filter_tags(line))

            for i in range(5):
                line = f.readline()

            linha["hora"] = self.parseDateTime(self.filter_tags(line),
                self.deltaGmt)

            return linha

if __name__ == '__main__':
    import urllib2

    conf = sitioUri()
    f = urllib2.urlopen(conf.urlConsulta())

    while True:
        res = conf.filtra_linha(f)
        if res == None:
            break
        print res
