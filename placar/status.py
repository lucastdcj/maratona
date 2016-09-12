#coding=utf-8

from placarUtil import dumpTimeDelta
from placarUtil import parseDateTime
from placarUtil import query
from placarUtil import tokeniza
import confCompeticao
import multiJudge
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
	iteracao = 0

	while True:
		# inicializa a competicao
		competicao = confCompeticao.competicao()

		# adiciona todos os juizes disponiveis
		for sitio in multiJudge.classeSitio.iterkeys():
			competicao.sitio.addSitio(sitio)
		
		if iteracao == 0:
			# verifica se  existe arquivo de log  e se deve  ser usado, se
			# deve entao usa se nao deve entao remove-o
			if os.path.exists(competicao.nomeArqLog):
				s = query ("arquivo '%s' existe; remove" % \
							   competicao.nomeArqLog, "N")
				if s == "s":
					os.remove (competicao.nomeArqLog)

		# reescreve arquivo de log
		tab = tabela.tabela()
		lognew = open (competicao.nomeArqLog + ".new", "w")
		try:
			log = open (competicao.nomeArqLog)

			for line in log:
				token = parseLogLine (line)
				if token["op"] == "sub":
					partId = competicao.partId(token["part"])

					if partId and \
					tab.submissao(1, partId, token["prob"], token["diag"]):
						lognew.write ("sub %s %s %s %s\n" % (token["hora"], \
						token["part"], token["prob"], token["diag"]))
				elif token["op"] not in ("ver", "ini", "fim"):
					print "op invalido %s em log" % token["op"]
					sys.exit()
			log.close()

			os.rename(competicao.nomeArqLog, competicao.nomeArqLog + ".bak")
		except IOError:
			pass # arquivo de log inexistente
		agora = competicao.sitio.gmtAgora(None)

		# filtra a informacao e atualiza tab
		for linha in competicao.sitio.update(iteracao):
			part = linha['part']
			prob = linha['prob']
			hora = linha['hora']
			diag = linha['diag']
			lang = linha['lang']

			partId = competicao.partId(part)
			if partId is None or not competicao.listLang.has_key (lang):
				continue
			print ("sub %s %s %s %s %s\n" % (hora, part, prob, diag,lang)) #debug
			
			##importante
			if tab.submissao(1, partId, prob, diag):
				lognew.write ("sub %s %s %s %s\n" % (hora, part, prob, diag))

		lognew.close()

		os.rename(competicao.nomeArqLog + ".new", competicao.nomeArqLog)

		# armazena o resultado em formato html
		if iteracao == 0:
			f = open (competicao.nomeArqConfStatus)
			s = f.read()
			f.close ()
			keywords = ["-->titulo", "-->cabecalho", \
							"-->linha de participante", "-->epilogo"]
			template = tokeniza (s, keywords)

		f = open (competicao.nomeArqResultadoHtml, 'w')

		# titulo
		f.write(template["-->titulo"] % { "ultimaAtua": agora})

		# cabecalho
		f.write(template["-->cabecalho"])

		log = open (competicao.nomeArqLog)
		lines = reversed(log.readlines())
		for line in lines:
			token = parseLogLine (line)
			if token["op"] == "sub":
				partId = competicao.partId(token['part'])
				part = competicao.listPart[partId]
				sit_prob = token['prob'].split('.')
				hora = token['hora']
				diag = token['diag']
				
				favicon = competicao.sitio.iconeSitio(sit_prob[0])
				target = competicao.sitio.urlProblema(sit_prob[0],sit_prob[1])
				problema = competicao.sitio.traduzId(sit_prob[0],sit_prob[1])
				
				classer = "fundo_accepted" if diag == "accepted" or \
					diag.startswith('rank') else "fundo_wrong"

				f.write(template["-->linha de participante"] % { \
					"classer": classer, "data": hora, \
					"nome": part, "site": sit_prob[0], \
					"problema": problema, "icone": favicon,
					"target": target, "resultado": diag })

		# epilogo
		f.write (template["-->epilogo"])
		f.close()

		if iteracao == 0:
			print "placar iniciado"

		print "Dormindo..."
		time.sleep (competicao.dormida)
		iteracao += 1

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
