#!/bin/sh

for iter in */*.c*
do
    expand "${iter}" > filename.notabs && mv filename.notabs "${iter}"
done

python output/res/genoutput.py

if [ $? = 0 ] ; then
    pdflatex output/logs/note.tex 
    pdflatex output/logs/note.tex > /dev/null
    pdflatex output/logs/note.tex > /dev/null

    mv note.pdf output/pdf/
    mv note.aux note.log note.toc output/logs/
    
    caminho=$(pwd)
    caminho="$caminho/output/pdf/note.pdf"
    echo "\n\nPDF gerado em: $caminho"
else
    echo ======================================================================
    echo ERRO na geração do .tex, corrija o erro e execute novamente.
fi
