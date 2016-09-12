# coding=utf-8
import sys, os

import locale
try:
	locale.setlocale(locale.LC_ALL, "pt_BR.utf8")
except locale.Error, err:
	locale.setlocale(locale.LC_ALL, "pt_BR.ISO8859-1")

def get_sections(directories):
    sections = []
    for d in directories:
        file = d + "/SECTION"
        try:
            fp = open(file, "r")
            sections.append(fp.next().strip())
            fp.close()
        except IOError, (errno, errstr):
            print >>sys.stderr, errstr
    return sections

def append_file(append, file):
    hf = open(append, 'r')
    for line in hf:
        print >>file, line,
    hf.close()

def write_section(sec, fp):
    print >>fp, "\\section{%s}\n" % sec

def get_title(algo):
    fa = open(algo, "r")
    tags = {}
    count = 3
    
    # le cabecalho
    # FIXME: codigo repetido na funcao write_algo.
    try:
        for line in fa:
            if line.strip().lstrip() == "/*%": break
        tags["title"] = fa.next().strip("* \t\n\r").lstrip("* \t\n\r")
    except StopIteration:
        print >>sys.stderr, "nao foi possivel encontrar o titulo do algoritmo", algo
        return_code = 1
        return "ERROR_TITLE_NOT_FOUND"

    return tags["title"]

def write_algo(algo, fp):
    
    print "PROCESSANDO:", algo

    fa = open(algo, "r")
    tags = {}
    count = 3
    rem_fields = "Tempo", "Autor", "Depen", "Testes"
    stop_at = "/**** Exemplo simples de uso ****/"
    
    # le cabecalho
    try:
        for line in fa:
            if line.strip().lstrip() == "/*%": break
        tags["title"] = fa.next().strip("* \t\n\r").lstrip("* \t\n\r")
        cabeca = ""
        for line in fa:
            count += 1;
            if line.strip().lstrip() == "%*/": break
            if not line.strip().startswith(rem_fields):
                cabeca += line.strip() + '\n';
    except StopIteration:
        print >>sys.stderr, "algoritmo", algo, "nao tem cabecalho"
        fa.close()
        return False

    # fa.seek(0)

    print >>fp, "\\subsection{%s}" % tags["title"],
    print >>fp, "\\begin{verbatim}\n",
    print >>fp, cabeca, #comente esta linha para nao imprimir o cabecalho

    blank = True
    for line in fa:
        if len(line) > 62 + 2:
            print >>sys.stderr, "%d colunas em %s, %d" % (len(line), algo, count)

        if line.startswith(stop_at): break
        
        if len(line.strip()) == 0: blank = True
        else:
            if blank: print >>fp, "\n",
            blank = False
            print >>fp, line,
        count += 1
    print >>fp, "\\end{verbatim}\n",

    fa.close()

    return True

if __name__ == "__main__":

    fout = open("output/logs/note_mundial.tex", "w")
    append_file("output/res/header.tex", fout)

    directories = ["mundial/grafos", "mundial/geometricos", "mundial/numericos", "mundial/miscelanea", "mundial/pd", "mundial/strings"]

    for dir in directories:
        file = dir + "/SECTION"
        try:
            fp = open(file, "r")
            section = fp.next().strip()
            fp.close()
        except IOError, (errno, errstr):
            print >>sys.stderr, errstr, file
            continue

        write_section(section, fout)
        algos = {}
        for file in os.listdir(dir):
            if file[-3:] == "cpp" or file[-1:] == "c":
                algos[file[:-4]] = dir + "/" + file

        titles = []
        for k in algos.keys():
            titles.append((get_title(algos[k]), k))
        titles.sort(cmp=lambda x,y : locale.strcoll(x[0],y[0]))

        for _, k in titles:
            if not write_algo(algos[k], fout):
                print >>sys.stderr, \
                    "ERRO! Nao foi possível processar o algoritmo", algos[k]

    append_file("output/res/math.tex", fout)
    append_file("output/res/math_ufs.tex", fout)
    append_file("output/res/footer.tex", fout)
    fout.close()
