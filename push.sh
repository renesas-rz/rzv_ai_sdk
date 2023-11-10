#!/bin/sh

VERSION=$1
if [ $VERSION = "" ]; then
  echo "ERROR: please type version. e.g. ./push.sh 1.00"
  exit 1
fi

sed -i -e  "s/version: \"[0-9]*\.[0-9][0-9]\"/version: \"${VERSION}\"/g" ./docs/_config.yml 
sed -i -e  "s/baseurl: \"\/rzv_ai_sdk\/[0-9]*\.[0-9][0-9]\"/baseurl: \"\/rzv_ai_sdk\/${VERSION}\"/g" ./docs/_config.yml 

cd docs
bundle exec jekyll build
cd ..

./replace_to_latest_sitemap.sh ${VERSION}

# git checkout origin/
sed -i -e  "s/RELEASE_VERSION=[0-9]*\.[0-9][0-9]/RELEASE_VERSION=${VERSION}/g" ./.github/workflows/deploy-version.yml 
git add .
git commit -m "${VERSION}"
git fetch
git pull origin docs
git push origin docs
