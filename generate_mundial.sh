#!/bin/sh

for iter in mundial/*/*.c*
do
    expand "${iter}" > filename.notabs && mv filename.notabs "${iter}"
done

python output/res/genoutput_mundial.py

pdflatex output/logs/note_mundial.tex  
pdflatex output/logs/note_mundial.tex  > /dev/null
pdflatex output/logs/note_mundial.tex  > /dev/null

mv note_mundial.pdf output/pdf/
mv note_mundial.aux note_mundial.log note_mundial.toc output/logs/
svn revert mundial/*/*

caminho=$(pwd)
caminho="$caminho/output/pdf/note_mundial.pdf"
echo "\n\nPDF gerado em: $caminho"
