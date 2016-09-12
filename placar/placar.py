#coding=utf-8
#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

from placarUtil import dumpTimeDelta
from placarUtil import parseDateTime
from placarUtil import query
from placarUtil import tokeniza
import confCompeticao
import tabela
from datetime import timedelta
import os
import sys
import time
import urllib2
import httplib
import traceback

def aglutina(t):
	res = t[0]
	for i in range(1, len(t)):
		res += ' ' + t[i]
	return res

def parseLogLine (s):
	t = s.split()
	res = {}
	res["op"] = t.pop(0)
	if res["op"] == "ver":
		res["ver"] = aglutina(t)
		return res
	data = t.pop(0)
	hora = t.pop(0)
	res["hora"] = parseDateTime(data + ' ' + hora)
	if res["op"] in ["ini", "fim"]:
		return res
	res["part"] = t.pop(0)
	res["prob"] = t.pop(0)
	res["diag"] = (aglutina(t)).lower()
	return res

def run():
	primeira = True

	while True:
		# inicializa a competicao
		competicao = confCompeticao.competicao()
		if primeira:
			print "iniciando a competicao '%s'" % competicao.titulo

			# inicia a tabela
			tab = tabela.tabela()

			# verifica se  existe arquivo de log  e se deve  ser usado, se
			# deve entao usa se nao deve entao remove-o
			carregaLog = False
			if os.path.exists (competicao.nomeArqLog):
				s = query ("arquivo '%s' existe; remove" % \
							   competicao.nomeArqLog, "N")
				if s == "n":
					carregaLog = True
				else:
					os.remove (competicao.nomeArqLog)
			if carregaLog:
				log = open (competicao.nomeArqLog)                
				for line in log:
					token = parseLogLine (line)
					if token["op"] == "sub":
						deltaHora = tab.tempoDecorrido (token["hora"])
						partId = competicao.partId(token["part"])
						if partId:
							tab.submissao(deltaHora, partId, \
											 token["prob"], token["diag"]) 
					elif token["op"] == "ver":
						continue
					elif token["op"] == "ini":
						tab.inicia(token["hora"])
					elif token["op"] == "fim":
						tab.finaliza(token["hora"])
					else:
						print "op invalido %s em log" % token["op"]
						sys.exit()
				log.close()
				

		# abre o log para saida
		log = open (competicao.nomeArqLog, "a")
		if primeira:
			if not carregaLog:
				log.write ("ver %s\n" % competicao.versao)
			log.write ("ini %s\n" % competicao.inicio)
			tab.inicia(competicao.inicio)

		# hora certa - se possivel pega do site
		agora = competicao.sitio.gmtAgora(None)
		delta = tab.tempoDecorrido (agora)
		competicao.iniciada = (agora >= competicao.inicio)

		# filtra a informacao e atualiza tab
		if competicao.iniciada:
			for linha in competicao.sitio.update():
				part = linha['part']
				prob = linha['prob']
				hora = linha['hora']
				diag = linha['diag']
				lang = linha['lang']
				print ("sub %s %s %s %s %s\n" % (hora, part, prob, diag,lang)) #debug

				partId = competicao.partId(part)
				if partId is None or \
						not competicao.listProb.has_key (prob) or \
						not competicao.listLang.has_key (lang) or \
						(hora < competicao.inicio) or (hora > competicao.termino):
					continue
				deltaHora = tab.tempoDecorrido (hora)
				##importante
				if tab.submissao(deltaHora, partId, prob, diag):
					log.write ("sub %s %s %s %s\n" % (hora, part, prob, diag))

		if primeira:
			replay = None
			if os.path.exists (competicao.nomeArqReplay):
				s = query ("arquivo '%s' existe: deseja usar replay" % \
							   competicao.nomeArqReplay, "S")
				if s == "s":
					replay = open (competicao.nomeArqReplay)
					line = replay.readline()
					line = replay.readline()
					if len(line) == 0:
						replay.close()
						replay = None
					else:
						token = parseLogLine(line)

		if not replay == None:
			while True:
				if token["op"] == "ini":
					tab.inicia(token["hora"], replay = True)
				elif token["op"] == "fim":
					tab.finaliza(token["hora"], replay = True)
				elif token["op"] == "sub":
					deltaReplay = tab.tempoDecorrido (token["hora"], \
															 replay = True)
					if (delta < deltaReplay):
						break
					partId = competicao.partId(token["part"])
					tab.submissao( \
						deltaReplay, partId, \
							token["prob"], token["diag"], \
							replay = True)
				else:
					print "op invalido %s em replay" % token["op"]
					sys.exit()
				line = replay.readline()
				if len(line) == 0:
					replay.close()
					replay = None
					break
				token = parseLogLine(line)

		if agora > competicao.termino:
			log.write ("fim %s\n" % competicao.termino)
		log.close()

		# persiste o log
		fIn = open (competicao.nomeArqLog)
		fOut = open (competicao.nomeArqLog + ".bak", "w")
		for line in fIn:
			fOut.write(line);
		fIn.close()
		fOut.close()

		#atualiza lista de ultimas submissoes
		tab.fixLast()

		# faz contagens e classificacao
		tab.classifica (competicao.idPartOrd, competicao.idProbOrd)

		# armazena o resultado em formato html
		if primeira:
			f = open (competicao.nomeArqConfPlacar)
			s = f.read()
			f.close ()
			keywords = ["-->titulo", "-->cabecalho", \
							"-->linha de participante", \
							"-->linha de total", "-->epilogo"]
			template = tokeniza (s, keywords)
			keywords_cab = ["\t-->nome", "\t-->tabela", "\t-->problema", "\t-->classificacao"]
			keywords = ["\t-->nome", "\t-->problema", "\t-->classificacao"]
			template_cab = tokeniza ( \
				template["-->cabecalho"], \
					keywords_cab)
			template_part = tokeniza ( \
				template["-->linha de participante"], \
					keywords)
			template_total = tokeniza ( \
				template["-->linha de total"], \
					keywords)

		f = open (competicao.nomeArqResultadoHtml, 'w')

		# titulo
		s = template["-->titulo"] % { \
			"titulo": competicao.titulo, \
				"inicio": competicao.inicio, \
				"termino": competicao.termino, \
				"duracao": dumpTimeDelta (competicao.termino - competicao.inicio), \
				"ultimaAtua": agora}
		f.write (s)

		# cabecalho
		falta = competicao.termino - agora
		falta_delta = dumpTimeDelta (falta)
		if not competicao.iniciada:
			inicio_delta = dumpTimeDelta (competicao.inicio - agora)
			s = template_cab["\t-->nome"] % { \
				"alternativa": "Inicia em:", \
					"cabecalho": inicio_delta}
		elif falta_delta == '':
			s = template_cab["\t-->nome"] % { \
				"alternativa": "", \
					"cabecalho": "COMPETI&Ccedil;&Atilde;O ENCERRADA"}
		else:
			s = template_cab["\t-->nome"] % { \
				"alternativa": "Tempo Restante: ", \
					"cabecalho": falta_delta}
		f.write(s)
		
		if competicao.iniciada:
			f.write (template_cab["\t-->tabela"])
			
			count = 0
			for prob in competicao.idProbOrd:
				if count < 26:
					probid = chr(count + ord('A'))
				else:
					probid = str(count - 25)

				f.write(template_cab["\t-->problema"] % { \
						"target": competicao.listProb[prob],
						"prob": prob[prob.find('.')+1:],
						"letter": probid})
				count += 1
			f.write (template_cab["\t-->classificacao"])

			# linhas dos participantes 
			colocacao = 1

			for pont in tab.pontuacao:
				part = pont[2]
				f.write (template_part["\t-->nome"] % \
							 {"nome": competicao.listPart[part],
							  "colocacao" : colocacao}) 
				colocacao += 1
				i = -1
				for prob in competicao.idProbOrd:
					i += 1
					st = tab.resultado[part][i]["status"]
					t = tab.resultado[part][i]["tempoAceito"]
					x = tab.resultado[part][i]["errosProb"]

					if st == 0:
						classer = "normal"

					else:
						if t == 0:
							classer = "recentwrong"
						else:
							classer = "recentaccept"

					if t == 0:
						classe = "normal"
					else:
						classe = "accepted"

					f.write (template_part["\t-->problema"] % { \
							"classer": classer, "classe": classe, "tempo": t, "erros": x})
				f.write (template_part["\t-->classificacao"] % { \
						"aceitos": -pont[0], \
							"penalidade": timedelta(0,pont[1]).days*1440 + timedelta(0,pont[1]).seconds/60}) #dumpTimeDelta(timedelta(0, pont[1]))})

			# linha de total
			f.write (template_total["\t-->nome"])
			for prob in competicao.idProbOrd:
				a = tab.total[prob]["aceitos"]
				t = tab.total[prob]["total"]
				f.write (template_total["\t-->problema"] % { \
						"aceitos": a, "total": t})
			a = tab.total[" "]["aceitos"]
			t = tab.total[" "]["total"]
			f.write (template_total["\t-->classificacao"] % { \
					"total_aceitos": a, "total_total": t})

		# epilogo
		f.write (template["-->epilogo"])
		f.close()

		# copia
		f = open (competicao.nomeArqResultadoHtml)
		s = f.read()
		f.close()
		f = open(competicao.nomeArqResultadoHtmlPublico, "w")
		f.write(s)
		f.close()
		os.system ("chmod go+r %s" % competicao.nomeArqResultadoHtmlPublico)
		if primeira:
			print "placar iniciado"
			primeira = False

		if agora > competicao.termino:
			print "placar finalizado"
			sys.exit()
			
		if competicao.iniciada:
			time.sleep (competicao.dormida)
		else:
			time.sleep (10)

if __name__ ==  "__main__":
	try:
		run()
	except:
		print traceback.format_exc()

		#gravar mensagem de erro
		f = open(confCompeticao.nomeArqErrLog,"a")
		f.write(str(time.ctime()) + "\n")
		f.write(traceback.format_exc()+"\n\n")
		f.close()

