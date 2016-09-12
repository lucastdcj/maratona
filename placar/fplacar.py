#Coluna com o nome do time
timecol = 1

#Coluna do primeiro problema (0 based)
firstcol = 4

#Numero de Problemas
numberp = 8

#Arquivo de entrada com o resultado
filein = "tabela.rep"

#Arquivo de entrada com o codigo dos problemas no judge
fileprob = "problist.rep"

#Arquivo de saida com os participantes
filenames = "participantes.rep"

#Arquivo de saida com as submissoes
fileout = "replay"

teams = []
subs = []
probs = []

def comp(a,b):
    return a[0] - b[0]

#carrega a lista de problemas
def carregaprob():
    global probs
    probs = [line.strip() for line in open(fileprob,"r").readlines() if len(line.strip()) > 0]

#filtra a tabela
def filtra():
    nnames = 0
    f = open(filein,"r")
    for line in f:
        l = line.split('\t')
        nome = l[timecol].strip()
        teams.append(nome)
        nnames+=1
        for i in xrange(firstcol,firstcol+numberp):
            pas = map(int,l[i].replace('(',"").replace('/'," ").replace('-',"0").replace(')',"").replace(' +',"").strip().split(' '))
            if pas[0] == 0 or pas[1] == 0:
                continue
            qtd = pas[0]
            try:
                tempo = pas[1]*60
                for j in xrange(qtd-1):
                    subs.append((tempo-1-j,nnames-1,probs[i-firstcol],"wrong answer"))
                subs.append((tempo,nnames-1,probs[i-firstcol],"Accepted"))
            except IndexError:
                for j in xrange(qtd):
                    subs.append((300*60-1-j,nnames-1,probs[i-firstcol],"wrong answer"))
    f.close()

#salva o arquivo de submissoes
def salvasubs():
    f = open(fileout,"w")
    f.write("ver placar em python versao 5 - 2007-08-05 cll\n")
    f.write("ini 2008-10-10 00:00:00\n")
    for ele in subs:
        s = ele[0]%60
        m = (ele[0]/60)%60
        h = ele[0]/3600
        f.write("sub 2008-10-10 %02d:%02d:%02d A%03d %s %s\n" % (h,m,s,ele[1],ele[2],ele[3]))
    f.write("fim 2008-10-10 05:00:00\n")
    f.close()

#salva o arquivo de nomes
def salvanomes():
    f = open(filenames,"w")
    i = 0

    for ele in teams:
        f.write("A%03d %s\n" % (i,ele))
        i += 1
    f.close()

carregaprob()
filtra()
subs.sort(comp)
salvasubs()
salvanomes()






