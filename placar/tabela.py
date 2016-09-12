#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

from datetime import timedelta
from confCompeticao import lastSubs

ignore_msgs = ("received", "sent to judge", "in judge queue",
               "compiling", "linking", "running")

class tabela:
    def __init__ (self):
        self.fim = {False: None, True: None}
        self.tabela = {}
        self.acrescimo = {}
        self.inicio = {}
        self.last = []

    # acerta hora de inicio e desconto, para o caso de interrupcoes
    def inicia (self, hora, replay = False):
        if self.fim[replay] == None:
            self.acrescimo[replay] = timedelta(0)
        else:
            self.acrescimo[replay] += \
                self.fim[replay] - self.inicio[replay]
        self.inicio[replay] = hora

    # anota hora de finalizacao
    def finaliza (self, hora, replay = False):
        self.fim[replay] = hora

    # insere participante na tabela, se ainda lah nao estiver
    def inserePart(self, part):
        if not self.tabela.has_key(part):
            self.tabela[part] = {}

    # insere problema em participante, se ainda lah nao estiver
    def insereProb(self, part, prob):
        self.inserePart(part)
        if not self.tabela[part].has_key(prob):
            self.tabela[part][prob] = [0, []]

    # obtem o tempo decorrido em segundos
    def tempoDecorrido (self, hora, replay = False):
        d = (hora - self.inicio[replay]) + self.acrescimo[replay]
        return d.days * 24 * 60 * 60 + d.seconds

    # anota o aceito, se jah nao ocorreu outro antes
    def insereAceito (self, delta, part, prob, replay):
        self.insereProb(part, prob)
        if self.tabela[part][prob][0] == 0 or \
                self.tabela[part][prob][0] > delta:
            self.tabela[part][prob][0] = delta
            self.last.append((-delta,part,prob))
            return True
        return False

    # anota erro, se jah nao foi anotado
    def insereErro (self, delta, part, prob, replay):
        self.insereProb(part, prob)
        if self.tabela[part][prob][1].count(delta) == 0:
            self.tabela[part][prob][1].append(delta)
            self.last.append((-delta,part,prob))
            return True
        return False

    # anota o resultado de uma submissao
    def submissao (self, delta, part, prob, diag, replay = False):
        if diag in ignore_msgs:
            return False
        if diag == "accepted" or diag.startswith('rank'):
            return self.insereAceito (delta, part, prob, replay)
        else:
            return self.insereErro (delta, part, prob, replay)

    # Mantem K ultimas submissoes de diferentes (usuario,problema)
    def fixLast(self):
        tmp = sorted(self.last)
        vis = set()
        self.last = []
        q = lastSubs
        for delta,part,prob in tmp:
            tempoAceito = self.tabela[part][prob][0]
            if tempoAceito != 0 and tempoAceito != -delta:
                continue
            if not (part,prob) in vis:
                vis.add((part,prob))
                self.last.append((delta,part,prob))        
                q -= 1
                if q == 0:
                    break
        
    # extrai informacao  sobre um  problema de participante:  tempo de
    # aceito se aceitou e numero de erros antes do aceito, se aceitou
    def getInfo (self, part, prob):
        self.insereProb(part, prob)
        tempoAceito = self.tabela[part][prob][0]
        if tempoAceito > 0:
            self.tabela[part][prob][1].sort()
            while len(self.tabela[part][prob][1]) > 0:
                t = self.tabela[part][prob][1].pop()
                if t < tempoAceito:
                    self.tabela[part][prob][1].append(t)
                    break
        st = 0
        for (_,ppart,pprob) in self.last:
            if ppart == part and pprob == prob:
                st = 1
                break

        return {"tempoAceito": tempoAceito,
                "errosProb": len(self.tabela[part][prob][1]),
                "status": st}

    def classifica(self, idPartOrd, idProbOrd):
        self.pontuacao = []
        self.resultado = {}
        self.total = {" ": {"aceitos": 0, "total": 0}}
        for prob in idProbOrd:
            self.total[prob] = {"aceitos": 0, "total": 0}
        for part in idPartOrd:
            self.resultado[part] = []
            aceitos = 0
            pontos = 0
            erros = 0
            for prob in idProbOrd:
                info = self.getInfo(part, prob)
                self.total[prob]["total"] += info["errosProb"]
                erros += info["errosProb"]
                if info["tempoAceito"] != 0:
                    aceitos += 1
                    pontos += info["tempoAceito"] + 20 * 60 * info["errosProb"]
                    for k in ["aceitos", "total"]:
                        self.total[prob][k] += 1
                info["tempoAceito"] /= 60
                self.resultado[part].append(info)
            if aceitos > 0 or erros > 0:
                self.pontuacao.append([-aceitos, pontos, part])
            else:
                del self.resultado[part]
        for prob in idProbOrd:
            if self.total.has_key (prob):
                for k in ["aceitos", "total"]:
                    self.total[" "][k] += self.total[prob][k]
        self.pontuacao.sort()
