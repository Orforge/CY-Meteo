#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Pas le bon nombre d'arguments :("
	echo "		${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
	exit 1
fi

#Initialisation des variables

nbF=0
Fich=0
t1=0
t2=0
t3=0
argt=0
p1=0
p2=0
p3=0
argp=0
w=0
h=0
m=0
nmbL=0
lieux=0
tri=0
liste=0
abr=0
avl=0
type=avl
long_min=0
long_max=0
lat_min=0
lat_max=0
RED='\033[0;31m'
NC='\033[0m'

for i in `seq 1 $#`		#Comptage de nombre de fichier
do
	if [ -f ${!i} ] ; then
		nomF=${!i}
		nbF=$(($nbF+1))
		Fich=$i
	fi
done


while getopts "h:t:p:w:m:f:l:a:F:G:S:A:O:Q" opt

do
	case $opt in
			t) if [ "$OPTARG" = "1" ]
			then
				if [ "$argt" = "0" ]
				then
					t1=1
					argt=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la température"
					exit 2
				fi
			elif [ "$OPTARG" = "2" ]
			then
				if [ "$argt" = "0" ]
				then
					t2=1
					argt=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la température"
					exit 2
				fi
			elif [ "$OPTARG" = "3" ]
			then
				if [ "$argt" = "0" ]
				then
					t3=1
					argt=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la température"
					exit 2
				fi
			else
				echo -e "Veuillez preciser le mode de cette option\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
				exit 2
			fi
			
			;;
			p) if [ "$OPTARG" = "1" ]
			then
				if [ "$argp" = "0" ]
				then
					p1=1
					argp=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la pression"
					exit 2
				fi
			elif [ "$OPTARG" = "2" ]
			then
				if [ "$argp" = "0" ]
				then
					p2=1
					argp=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la pression"
					exit 2
				fi
			elif [ "$OPTARG" = "3" ]
			then
				if [ "$argp" = "0" ]
				then
					p3=1
					argp=1
				else
					echo "Il ne peut y avoir qu'une seule option pour la pression"
					exit 2
				fi
			else
				echo -e "Veuillez preciser le mode de cette option\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
				exit 2
			fi		
			;;
			w) w=1
			;;
			m) m=1
			;;
			h) if [ "$OPTARG" = "elp" ]
			then
				more -d help.txt
			else
				h=1
			fi
			;;
			f) if [ "$OPTARG" = "" ]
			then
				if [ "${!OPTIND}" != "$nomF" ]
				then
					echo -e "Un nom de fichier existant est attendu après la commande -f\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
				fi
			fi
			;;
			l) if [ "$OPTARG" = "iste" ] && [ "$tri" = "0" ]
			then
				tri=1
				liste=1
				type=liste
			else
				echo -e "Un seul type de tri peut être activé en même temps\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
				exit 2
			fi
			;;
			a) if [ "$OPTARG" = "br" ] && [ "$tri" = "0" ]
			then
				tri=1
				abr=1
				type=abr
			elif [ "$OPTARG" = "vl" ] && [ "$tri" = "0" ]
			then
				tri=1
				avl=1
				type=avl
			else
				echo -e "Un seul type de tri peut être activé en même temps\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC}"
				exit 2
			fi
			;;
			F) if [ "$lieux" = "0" ]
				then
					long_min=-6
					long_max=9
					lat_min= 41
					lat_max=51.5
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi
			;;
			G) if [ "$lieux" = "0" ]
				then
					long_min=6
					long_max=-56
					lat_min=1
					lat_max=10
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi
			;;
			S) if [ "$lieux" = "0" ]
				then
					long_min=-56.5
					long_max=-56
					lat_min=46
					lat_max=48
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi
			;;
			A) if [ "$lieux" = "0" ]
				then
					long_min=-85
					long_max=-53
					lat_min=8
					lat_max=28
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi			
			;;
			O) if [ "$lieux" = "0" ]
				then
					long_min=-49
					long_max=-42
					lat_min=-69
					lat_max=11
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi
			
			
			;;
			Q) if [ "$lieux" = "0" ]
				then
					long_min=-100
					long_max=100
					lat_min=-57
					lat_max=100
					lieux=1
				else
					echo "Il ne peut y avoir qu'une seule option de restriction de lieux"
					exit 2
				fi
			;;
			\?) echo -e "L'option n'existe pas debilus maximus\n	${RED}Si t'es paumé, n'hesite pas a utilser le -help pour plus d'info !${NC}"
			;;
	esac
done

if [ $nbF -ne 1 ]
then
	echo -e "La commande doit prendre un fichier en compte, et celui-ci doit être écrit comme l'exemple suivant :\n-f <nom_fichier>\n	${RED}N'hesitez pas a utiliser le -help pour plus d'information${NC}"
	exit 2
fi


if [ $argt -eq 0 ] && [ $argp -eq 0 ] && [ $w -eq 0 ] && [ $h -eq 0 ] && [ $m -eq 0 ]
then
	echo -e "Il faut au moins un des arguments suivants pour pouvoir executer ce programme :\n-t1 | -t2 | -t3 | -p1 | -p2 | -p3 | -w | -m | -h\n	${RED}N'hesitez pas a utilser le -help pour plus d'information${NC} "
fi

chmod u+x Meteo_Project.c

#remplacement des ',' par des ';' et des espaces vides par des €
sed 's/,/;/g' $nomF | sed 's/;;/;€;/g' | sed 's/;;/;€;/g'> tmp0.csv

if [ "$lieux" = "1" ]
then
	awk -F ";" -v long_min="$long_min" -v long_min="$long_min" -v long_min="$long_min" -v long_min="$long_min" ' lat_min<$10 && $10<lat_max {print $0}' tmp0.csv
	awk -F ";" -v long_min="$long_min" -v long_min="$long_min" -v long_min="$long_min" -v long_min="$long_min" ' long_min<$11 && $11<long_max {print $0}' tmp0.csv 
fi

if [ "$t1" = "1" ]
then
	#Découpage des colonnes voulues et suppression de l'en-tête, le tout transférer dans un fichier temporaire
	cut tmp0.csv -d';' -f1,12 | tail -n+2 > tmpT1.csv
	#Comptage du nombre de ligne du fichier temporaire
	nmbL=`wc -l tmpT1.csv | cut -d' ' -f1`
	make.mak
	#Appel du programme c
	./main.o tmpT1.csv FmpT1.dat $nmbL t1 $type
	echo -e '
	set grid nopolar
	set grid xtics mxtics ytics noztics nomztics noztics nortics nomrtics nox2tics nomx2tics noy2tics nomy2tics nomcbtics
	set style data line
	set title "Graphique des temperatures par stations"
	set xlabel "Stations"
	set ylabel "Temperature"
	Shadecolor = "#EECF83"

	set autoscale noextend
	set xrange [*;*]
	set xtics rotated by 90
	plot "FtmT1.dat" using 1:2:3 with filledcurves fc rgb Shadecolor notitle, "FmpT1.dat" using 1:4 with lines set linetype 2 lc rgb "sea-green" lw 2pt 7' | gnuplot --persist 2>/dev/null
fi


elif [ "$t2" = "1" ]
then
	cut tmp0.csv -d';' -f2,12 | tail -n+2 > tmpT2.csv
	nmbL=`wc -l tmpT2.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpT2.csv FmpT2.dat $nmbL t2 $type


elif [ "$t3" = "1" ]
then
	cut tmp0.csv -d';' -f1,2,12 | tail -n+2 > tmpT3.csv
	nmbL=`wc -l tmpT3.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpT3.csv FmpT3.dat $nmbL t3 $type



elif [ "$p1" = "1" ]
then
	#la fonction awk supprime toute les lignes contenant des € (anciennement espaces vides)
	cut tmp0.csv -d';' -f1,7 | tail -n+2 | awk -F";" ' $1!="€" && $2!="€" {print $0} ' > tmpP1.csv
	nmbL=`wc -l tmpP1.csv | cut -d' ' -f1`
	make.mak
	echo "$nmbL"
	./main.o tmpP1.csv FmpP1.dat $nmbL p1 $type
	echo -e '
	set grid nopolar
	set grid xtics mxtics ytics noztics nomztics noztics nortics nomrtics nox2tics nomx2tics noy2tics nomy2tics nomcbtics
	set style data line
	set title "Graphique des pressions par stations"
	set xlabel "Stations"
	set ylabel "Pressions"
	Shadecolor = "#EECF83"

	set autoscale noextend
	set xrange [*;*]
	set xtics rotated by 90
	plot "FtmP1.dat" using 1:2:3 with filledcurves fc rgb Shadecolor notitle, "FmpP1.dat" using 1:4 with lines set linetype 2 lc rgb "sea-green" lw 2pt 7' | gnuplot --persist 2>/dev/null


elif [ "$p2" = "1" ]
then
	cut tmp0.csv -d';' -f2,7 | awk -F";" ' $1!="€" && $2!="€" {print $0} '  | tail -n+2 > tmpP2.csv
	nmbL=`wc -l tmpP2.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpP2.csv FmpP2.dat $nmbL p2 $type


elif [ "$p3" = "1" ]
then
	cut tmp0.csv -d';' -f1,2,7 | awk -F";" ' $1!="€" && $2!="€" && $3!="€" {print $0} '  | tail -n+2 > tmpP3.csv
	nmbL=`wc -l tmpP3.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpP3.csv FmpP3.dat $nmbL p3 $type


elif [ "$w" = "1" ]
then
	cut tmp0.csv -d';' -f1,4,5 | awk -F";" ' $1!="€" && $2!="€" && $3!="€" {print $0} '  | tail -n+2 > tmpW.csv
	nmbL=`wc -l tmpW.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpW.csv FmpW.dat $nmbL w $type


elif [ "$m" = "1" ]
then
	cut tmp0.csv -d';' -f1,6 | awk -F";" ' $1!="€" && $2!="€" {print $0} '  | tail -n+2 > tmpM.csv
	nmbL=`wc -l tmpM.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpM.csv FmpM.dat $nmbL m $type


elif [ "$h" = "1" ]
then
	cut tmp0.csv -d';' -f1,15 | awk -F";" ' $1!="€" && $2!="€" {print $0} '  | tail -n+2 > tmpH.csv
	nmbL=`wc -l tmpH.csv | cut -d' ' -f1`
	make.mak
	./main.o tmpH.csv FmpH.dat $nmbL h $type
	echo -e '
	set xlabel "Stations"
	set ylabel "Altitude"
	set title "altitude des stations"
	set view map
	set dgrid3d 100,100,2
	unset key
	unset surface
	set pm3d at b
	splot "FmpH.dat" ' | gnuplot --persist 2>/dev/null
fi
