#!/bin/bash
#/etc/bash_completion
YELLOW='\033[1;33m'
GREY='\033[1;30m'
RED='\033[0;31m'
NC='\033[0m' # No Color
version='0.6'
function load(){
  echo -ne '[#                             (1%)]\r'
  sleep 1
  echo -ne '[###                           (10%)]\r'
  sleep 2
  printf "$1\n$2\n$3" > .git/value_script.ss
  echo -ne '[#####                         (18%)]\r'
  sleep 1
  echo -ne '[#########                     (29%)]\r'
  sleep 3
  echo -ne '[#################             (55%)]\r'
  sleep 2
  echo -ne '[###################           (62%)]\r'
  sleep 4
  echo -ne '[###########################   (89%)]\r'
  sleep 1
  echo -ne '[###########################   (90%)]\r'
  sleep 1
  echo -ne '[############################  (92%)]\r'
  sleep 1
  echo -ne '[##############################(100%)]\r'
  sleep 1
  exec ./github.ss
}
function init(){
  read -p "$(tput sgr0)Votre pseudo : " pseudo
  read -p "Votre email: " email
  load $pseudo $email $PWD

}
function vhelp(){
  printf "$(tput sgr0)Pour voir letat du projet taper :st\n"
  printf "Pour update un fichier taper :add [fichier]\n"
  printf "Pour commit taper :com [texte]\n"
}
function commande(){
  tput cup 4 0
  tput el
  tput bold; read -e -p "$(tput setaf 1)Commande: " ordre other
  if [ -z $ordre ]
  then
    commande
  else
    tput sgr0; tput ed
    if [ $ordre == "init" ]
    then
      init
    elif [ $ordre == "help" ]
    then
      vhelp
    elif [ $ordre == "st" ]
    then
      git status
    elif [ $ordre == "add" ]; then
      git add $other
      printf "$other ajouter, taper com [texte]"
    elif [ $ordre == "com" ]; then
      git commit -m "$other"
    elif [ $ordre == "open" ]; then
      firefox "$(git config --get remote.origin.url)"
    elif [ $ordre == "log" ]; then
      git log $other
      ./github.ss
    elif [ $ordre == "check" ]; then
      git checkout $other
    elif [ $ordre == "mtp" ]; then
      read -s mtp
    elif [ $ordre == "send" ]; then
      git push
    elif [ $ordre == "ls" ]; then
      ls
    elif [ $ordre == "rm" ]; then
      read -p "Delete $other (y/n)?" verif
      if [ $verif == "y" ]
      then
        rm $other
        ls
      else
        printf "$other no Delete"
      fi
    else
      printf "404 commande\n"
    fi
  fi
  commande
}
clear
echo -e '\033]2;'Github Script'\007'
tput cup 0 10
printf "${YELLOW}Bienvenue dans le script Git by MaxSliw\n"
tput cup 1 23
printf "Version : $version\n${NC}"
tput sgr0
if test -e ".git/value_script.ss"
then
  vdir=$(awk 'NR==3' .git/value_script.ss)
  user=$(awk 'NR==1' .git/value_script.ss)
  email=$(awk 'NR==2' .git/value_script.ss)
  printf "${GREY}Dossier de travail : $vdir\nUtilisateur : $user"
else
  printf "${GREY}Pour commencer l'installation entrer la commande [init]\n"
fi
commande
