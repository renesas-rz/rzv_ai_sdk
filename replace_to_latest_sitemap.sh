#!/bin/sh
VERSION=$1
if [ $VERSION = "" ]; then
  echo "ERROR: please type version. e.g. ./replace_to_latest_sitemap.sh 1.00"
  exit 1
fi

target_path=sitemap.xml
cd docs/_site
cat ${target_path} | sed -e "s/\/${VERSION}\//\/latest\//" > new_${target_path}
DELETE_ROW=`sed -n '/RZV2L_board_setup_e2studio/=' new_${target_path}`
DELETE_ROWS_start=$((DELETE_ROW - 1))
DELETE_ROWS_end=$((DELETE_ROWS_start+3))
echo $DELETE_ROW,$DELETE_ROWS_start,$DELETE_ROWS_end
sed "${DELETE_ROWS_start},${DELETE_ROWS_end}d" new_${target_path} > new1_${target_path}
DELETE_ROW=`sed -n '/eSD_format_sd/=' new1_${target_path}`
DELETE_ROWS_start=$((DELETE_ROW - 1))
DELETE_ROWS_end=$((DELETE_ROWS_start+3))
echo $DELETE_ROW,$DELETE_ROWS_start,$DELETE_ROWS_end
sed "${DELETE_ROWS_start},${DELETE_ROWS_end}d" new1_${target_path} > new_${target_path}
mv new_${target_path} ${target_path}
rm -rf new1_${target_path}
