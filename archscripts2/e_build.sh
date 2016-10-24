#!/bin/bash
# -*- coding: utf-8 -*-
# Install EFL, Enlightenment and cool stuff on arch

REPO_URL="https://git.enlightenment.org"

REPO_LIST="core/efl core/enlightenment apps/terminology apps/equate apps/ecrire tools/edi"

LOG_FILE=.e_build.out

function get_password {
  echo -n "[SUDO ] Please input password for install scripts: "

  while [ -z "$SUDO_PASS" ]; do
    read -s SUDO_PASS
    echo ""

    echo $SUDO_PASS | sudo -Sk -p "" 1>&2 2>/dev/null true
    if [ $? -eq 0 ]; then
      break;
    fi
    SUDO_PASS=
    echo -n "[SUDO ] Please try again: "
  done
}

function quit {
  IFS='
'
  echo "[FAIL ] Exiting script - last 5 lines of output (see .e_build.out)"
  echo

  if [ -e "$LOG_FILE" ]; then
    for LINE in `tail -5 .e_build.out`; do
      echo "[LOG  ] $LINE";
    done
  fi
  exit 1
}

get_password

for REPO in $REPO_LIST ; do
  NAME=`echo $REPO|cut -d'/' -f2`
  if [ -d "$NAME" ]; then
    echo "[PULL ] ${NAME}"
    cd ${NAME}
    git fetch -q
    if [ $(git rev-parse HEAD) == $(git rev-parse @{u}) ]; then
      echo "[SKIP ] No changes to build"
      cd ..
      continue
    fi

    git pull -q --rebase 1>&2 2>$LOG_FILE || quit
    cd ..
  else
    echo "[CLONE] ${NAME}"
    git clone -q ${REPO_URL}/${REPO}.git ${NAME} 1>&2 2>$LOG_FILE || quit
  fi

  echo "[BUILD] ${NAME}"
  cd ${NAME}
  if [ -e autogen.sh ]; then
    ./autogen.sh > /dev/null 2>$LOG_FILE || quit
  else
    cd ..
    mkdir ${NAME}/build
    cd ${NAME}/build
    cmake .. > /dev/null 2>$LOG_FILE || quit
  fi
  make > /dev/null 2>$LOG_FILE || quit
  echo "[INST ] ${NAME}"
  echo $SUDO_PASS | sudo -kS make install > /dev/null 2>$LOG_FILE || quit
  cd -
done


