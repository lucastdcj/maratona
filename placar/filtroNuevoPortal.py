#Programa placar.py para gerenciamento de placar de competições
#Versão original criada por Cláudio Leonardo Lucchesi
#
#Este software é público. É proibido colocar qualquer restrição
#ao uso deste software. Este software não pode ter licença GPL,
#LGPL, nen qualquer outra licença.

f = open("filtro.conf")
versao = f.readline()
inicio = f.readline()
fim = f.readline()
f.close()
f = open("captura.txt")
s = f.read().split('\n')
f.close()
s.pop(0)
n = 0
dic = {}
linha = []

f = open ("Aparticipantes.conf", "w")
while len(s) != 0:
    t = s.pop(0).split('\t')
    nome = t[6].strip(" ")
    if not dic.has_key(nome):
        dic[nome] = "A%03d" % n
        n += 1
        f.write ("%s %s\n" % (dic[nome], nome))
    prob = t[8].split(" - ")                                    
    linha.append([t[2], dic[nome], prob[0], t[3]])
f.close()
f = open("Areplay", "w")    
f.write (versao)
f.write ("ini %s" % inicio)
linha.sort()
while len(linha) != 0:
    t = linha.pop(0)
    f.write("sub %s%s %s %s\n" % (t[0], t[1], t[2], t[3]))
f.write ("fim %s" % fim)
f.close()
