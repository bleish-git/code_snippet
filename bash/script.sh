#!/bin/sh
# Lo script preleva la lista di tutti i file in un determinata directory e ricorsivamente
# in tutte sottodirectory e chiede tramite zenity all'utente dove sistemarlo,
# provvedendo a raccogliere anche informazioni circa l'autore, la materia trattata nel file o un tag di
# catalogazione e memorizzando tali informazioni in un db

directory=/usr/bin

#for file in $( find $directory -type f -name '*' | sort )

for file in $( find . -printf "%p;" | sort --version-sort )
do
	ID=`sha512sum $file`
	
	#nome del file senza percorso
	filename="${file##*/}"
		
	#estensione del file
	extension="${filename##*.}"
	
	#solo il nome, senza estensione
	filename="${filename%.*}"
	
	#nome del file rinominato
	o=`zenity --entry --title="Inserire il nome del file" --entry-text=$s`
	mv $file $filename$extension
	
done

exit 0


