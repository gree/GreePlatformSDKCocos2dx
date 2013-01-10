#!/bin/sh

URL="http://cocos2d-x.googlecode.com/files/"
TARGET="cocos2d-2.0-x-2.0.4"
TARGETFILE=${TARGET}".zip"
LOCALFILE="cocos2dx.zip"
EXTENSIONDIR="./gree_extension"
EXTENSIONJAVADIR="./gree"
PATCHDIR="./patches"
PROJECT_CREATE_SCRIPT="create-android-gree-project.sh"
INSTALL_GREE_TEMPLATE_SCRIPT="install-gree-templates-xcode.sh"

JAVADIR=${TARGET}"/cocos2dx/platform/android/java/src/org/cocos2dx/lib"


echo ${URL}${TARGETFILE}


if [ ! -e ${LOCALFILE} ]; then
	echo "Download cocos2dx source code"
	curl -o ${LOCALFILE} ${URL}${TARGETFILE} 
	#wget ${URL}${TARGETFILE} -O ${LOCALFILE}
fi
if [ ! -d ${TARGET} ]; then
	echo "Unzip cocos2dx"
	unzip ${LOCALFILE}
fi

rsync -a --delete ${EXTENSIONDIR} ${TARGET}
rsync -a --delete ${EXTENSIONJAVADIR} ${JAVADIR}
rsync -a --delete ${PATCHDIR}/GreeBasicSample ${TARGET}/samples/
rsync -a ${PATCHDIR}/template/xcode4 ${TARGET}/template/

cp ${PATCHDIR}/${PROJECT_CREATE_SCRIPT} ${TARGET}
cp ${PATCHDIR}/${INSTALL_GREE_TEMPLATE_SCRIPT} ${TARGET}

echo "Apply patch for gree_extension"
patch -d ${TARGET} -p0 < ${PATCHDIR}/Cocos2dxHelper.java.patch

echo "Finish Setup"

