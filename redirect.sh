#!/bin/sh

VERSION=$1
if [ $VERSION = "" ]; then
  echo "ERROR: please type version. e.g. ./redirect.sh 1.00"
  exit 1
fi

# git checkout origin/master
git fetch
git merge --allow-unrelated-histories origin/gh-pages
git pull origin origin/gh-pages

rm -rf latest
ln -sf $VERSION latest
# git config user.name "$(git --no-pager log --format=format:'%an' -n 1)"
# git config user.email "$(git --no-pager log --format=format:'%ae' -n 1)"

dir_path="*"
dirs=`find $dir_path -type d -name "*.**"`
for dir in $dirs;
do
if [ $VERSION != $dir ]; then
    cp $VERSION/version.html $dir/version.html
fi
done

git add .
git commit -m "redirect latest to new version $VERSION"
# git pull origin origin/gh-pages
git push origin gh-pages


