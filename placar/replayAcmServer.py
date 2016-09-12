from urllib import unquote

#Arquivo de entrada com a competicao ACM Server
filein = "data.rep"

#Arquivo de entrada com o codigo dos problemas no judge
fileprob = "problist.rep"

#Arquivo de saida com os participantes
filenames = "participantes.rep"

#Arquivo de saida com as submissoes
fileout = "replay"

subs = []
probs = []

def comp(a,b):
    return a[0] - b[0]

#carrega a lista de problemas
def carregaprob():
    global probs
    probs = [line.strip() for line in open(fileprob,"r").readlines() if len(line.strip()) > 0]

#parse an object named "title" from competition file, storing its data as
# a dictionary by element name of dictionaries by properties
def parseList(title):
    res = {}
    f = open(filein, "r")

    # skip to beginning of the correct object
    while 1:
        line = f.readline()
        if line.startswith(title):
            f.readline() # skip "{"
            break

    while 1:
        sl = f.readline().strip()
        if sl == "}":
            break
        f.readline() # skip "{"

        elid = sl
        eldict = {}
        while 1:
            sl = f.readline().strip()
            if sl == "}":
                break

            # get property in the form: "key = value;"
            ltoks = sl.split("=", 1)
            eldict[ltoks[0].strip()] = ltoks[1].strip(";\" ")
            
        res[elid]=eldict

    f.close()
    return res

#populate submission list subs with relevant data
def subparser():
    subData = parseList("Submits")

    for _,sdata in subData.iteritems():
        pid = probs[sorted(probsData.keys()).index(sdata["Problem"])]
        subs.append((int(sdata["RelativeTime"]), sdata["Contestant"], pid,
        "Accepted" if int(sdata["Result"])==0 else "wrong answer"))

#salva o arquivo de submissoes
def salvasubs():
    f = open(fileout,"w")
    f.write("ver placar em python versao 5 - 2007-08-05 cll\n")
    f.write("ini 2008-10-10 00:00:00\n")
    for ele in subs:
        s = ele[0]%60
        m = (ele[0]/60)%60
        h = ele[0]/3600
        f.write("sub 2008-10-10 %02d:%02d:%02d A%s %s %s\n" % (h,m,s,ele[1],ele[2],ele[3]))
    f.write("fim 2008-10-10 05:00:00\n")
    f.close()

#salva o arquivo de nomes
def salvanomes():
    f = open(filenames,"w")

    for k,n in teamsData.iteritems():
        f.write("A%s %s\n" % (k,unquote(n["Name"])))
    f.close()

carregaprob()
teamsData = parseList("Contestants")
probsData = parseList("Problems")
subparser()
subs.sort(comp)
salvasubs()
salvanomes()
