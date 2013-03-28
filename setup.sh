#!/bin/sh

URL="http://cocos2d-x.googlecode.com/files/"
TARGET="cocos2d-2.0-x-2.0.4"
TARGETFILE=${TARGET}".zip"
LOCALFILE="cocos2dx.zip"
EXTENSIONDIR="./gree_extension"
EXTENSIONJAVADIR="./gree"
WEBVIEWDIR="./webview_plugin/webview_plugin"
WEBVIEWJAVADIR="./webview_plugin/gree/webview"
PATCHDIR="./patches"
PROJECT_CREATE_SCRIPT="create-android-gree-project.sh"
INSTALL_GREE_TEMPLATE_SCRIPT="install-gree-templates-xcode.sh"
#WEBVIEW_PROJECT_CREATE_SCRIPT="create-android-webview-project.sh"
INSTALL_WEBVIEW_TEMPLATE_SCRIPT="install-webview-templates-xcode.sh"

JAVADIR=${TARGET}"/cocos2dx/platform/android/java/src/org/cocos2dx/lib"



if [ $# -ne 0 -a $# -ne 2 ]; then
    echo "illegal options";
    echo "usege : ./setup.sh [-m]";
    echo "  -m     Mode, you can specify whether you use WebViewPlugin with GreePlatform functions or not.";
    echo "          default : only GreePlatform functions are enabled."
    echo "          webview : only WebView function is enabled."
    echo "          all     : both of GreePlatform and WebView functions are enabled." 
    exit;
fi

Mode="default";

while getopts m: OPT
do
  case $OPT in
    "m" ) Mode=$OPTARG ;;
  esac
done


if [ ! -e ${LOCALFILE} ]; then
	echo "Download cocos2dx source code"
	curl -o ${LOCALFILE} ${URL}${TARGETFILE} 
	#wget ${URL}${TARGETFILE} -O ${LOCALFILE}
fi
if [ ! -d ${TARGET} ]; then
	echo "Unzip cocos2dx"
	unzip ${LOCALFILE}
fi



echo ${URL}${TARGETFILE}

function prepareGreePlatform() {
	echo "Prepare GreePlatformSDK";
	# Prepare src tree for building Apps with GreePlatformSDK
	rsync -a --delete ${EXTENSIONDIR} ${TARGET}
	rsync -a --delete ${EXTENSIONJAVADIR} ${JAVADIR}
	rsync -a --delete ${PATCHDIR}/GreeBasicSample ${TARGET}/samples/
	rsync -a ${PATCHDIR}/template/xcode4/lib_gree_extension.xctemplate ${TARGET}/template/xcode4
	rsync -a ${PATCHDIR}/template/xcode4/cocos2dx_gree_extension.xctemplate ${TARGET}/template/xcode4
	cp ${PATCHDIR}/${PROJECT_CREATE_SCRIPT} ${TARGET}
	cp ${PATCHDIR}/${INSTALL_GREE_TEMPLATE_SCRIPT} ${TARGET}

	echo "Apply patch for gree_extension"
	patch -d ${TARGET} -p0 < ${PATCHDIR}/Cocos2dxHelper.java.patch
}

function prepareWebView() {
	echo "Prepare WebView";
	rsync -a --delete ${WEBVIEWDIR} ${TARGET}
	rsync -a --delete ${WEBVIEWJAVADIR} ${JAVADIR}/gree/
	rsync -a ${PATCHDIR}/template/xcode4/lib_webview_plugin.xctemplate ${TARGET}/template/xcode4
	rsync -a ${PATCHDIR}/template/xcode4/cocos2dx_webview_plugin.xctemplate ${TARGET}/template/xcode4
	#cp ${PATCHDIR}/${WEBVIEW_PROJECT_CREATE_SCRIPT} ${TARGET}
	cp ${PATCHDIR}/${INSTALL_WEBVIEW_TEMPLATE_SCRIPT} ${TARGET}
}

case $Mode in
    "default" ) prepareGreePlatform ;;
    "webview" ) prepareWebView ;;
    "all"     ) prepareGreePlatform; prepareWebView ;;
	*         ) prepareGreePlatform ;;
esac

echo "Finish Setup"

