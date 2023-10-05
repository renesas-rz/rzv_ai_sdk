#!/bin/sh
VERSION=$1
if [ $VERSION = "" ]; then
  echo "ERROR: please type version. e.g. ./replace_to_latest_sitemap.sh 1.00"
  exit 1
fi

target_path=docs/_site/sitemap.xml
cat ${target_path} | sed -e "s/\/${VERSION}\//\/latest\//" > ${target_path}
