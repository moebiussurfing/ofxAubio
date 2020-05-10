# All variables and this file are optional, if they are not present the PG and the
# makefiles will try to parse the correct values from the file system.
#
# Variables that specify exclusions can use % as a wildcard to specify that anything in
# that position will match. A partial path can also be specified to, for example, exclude
# a whole folder from the parsed paths from the file system
#
# Variables can be specified using = or +=
# = will clear the contents of that variable both specified from the file or the ones parsed
# from the file system
# += will add the values to the previous ones in the file or the ones parsed from the file 
# system
# 
# The PG can be used to detect errors in this file, just create a new project with this addon 
# and the PG will write to the console the kind of error and in which line it is

meta:
	ADDON_NAME = ofxAubio
	ADDON_DESCRIPTION = openFrameworks addon to use Aubio: https://aubio.org/ofxAubio/
	ADDON_AUTHOR = Paul Brossier piem@aubio.org
	ADDON_TAGS = "audio" "analyzer"
	ADDON_URL = https://github.com/aubio/ofxAubio

common:
	# dependencies with other addons, a list of them separated by spaces 
	# or use += in several lines
	#ADDON_DEPENDENCIES = ofxOpenCv
	

	# include search paths, this will be usually parsed from the file system
	# but if the addon or addon libraries need special search paths they can be
	# specified here separated by spaces or one per line using +=

	ADDON_INCLUDES
	ADDON_INCLUDES += F:\openFrameworks\addons\ofxAubio\aubio-0.4.6-win64\include
	#ADDON_INCLUDES += ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\include

	#ADDON_INCLUDES += src
	#ADDON_INCLUDES += ..\..\..\addons\ofxAubio\aubio\src
	



	# LIBS

	ADDON_LIBS += F:\openFrameworks\addons\ofxAubio\aubio-0.4.6-win64\lib\aubio.dll.a
	ADDON_LIBS += F:\openFrameworks\addons\ofxAubio\aubio-0.4.6-win64\lib\libaubio.a

	#not working
	#ADDON_LIBS = ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\lib\
	#ADDON_LIBS = ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\lib\aubio.dll.a 
	#ADDON_LIBS += ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\lib\libaubio.a
	#ADDON_LIBS += ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\include





	# any special flag that should be passed to the compiler when using this
	# addon
	# ADDON_CFLAGS = 
	
	# any special flag that should be passed to the linker when using this
	# addon, also used for system libraries with -lname
	# ADDON_LDFLAGS =
	
	# linux only, any library that should be included in the project using
	# pkg-config
	# ADDON_PKG_CONFIG_LIBRARIES = 
	
	# osx/iOS only, any framework that should be included in the project
	#ADDON_FRAMEWORKS = Accelerate
	
	# source files, these will be usually parsed from the file system looking
	# in the src folders in libs and the root of the addon. if your addon needs
	# to include files in different places or a different set of files per platform
	# they can be specified here
	# ADDON_SOURCES =
	# ADDON_SOURCES = aubio.dll.a
	# ADDON_SOURCES += libaubio.a




	# some addons need resources to be copied to the bin/data folder of the project
	# specify here any files that need to be copied, you can use wildcards like * and ?
	
	#not working
	#ADDON_DATA =
	#ADDON_DATA += F:\openFrameworks\addons\ofxAubio\bin\libaubio-5.dll \data
	#ADDON_DATA += ..\..\..\addons\ofxAubio\aubio-0.4.6-win64\bin\libaubio-5.dll
	#ADDON_DATA += F:\openFrameworks\addons\ofxAubio\aubio-0.4.6-win64\bin\libaubio-5.dll
	



	##excludes

	# when parsing the file system looking for libraries exclude this for all or
	# a specific platform
	# ADDON_LIBS_EXCLUDE =
	
	# when parsing the file system looking for sources exclude this for all or
	# a specific platform
	
	# when parsing the file system looking for include paths exclude this for all or
	# a specific platform
    # ADDON_INCLUDES_EXCLUDE =

# linux:
	
# linux64:
	
# linuxarmv6l:
	
# linuxarmv7l:
	
# msys2:
	
# vs:#
# 	ADDON_LIBS =
# 	ADDON_LIBS += libs/opencv/lib/android/x86/libopencv_dnn.a
# 	ADDON_LIBS += libs/opencv/lib/android/x86/libopencv_photo.a
# 	ADDON_LIBS += libs/opencv/lib/android/x86/libopencv_stitching.a
# 	ADDON_LIBS += libs/opencv/lib/android/x86/libopencv_calib3d.a
		
# android/armeabi:	
	
# android/armeabi-v7a:	

# osx:
# 	ADDON_LDFLAGS = -F/Library/Frameworks -framework Accelerate
# 	ADDON_INCLUDES += /Library/Frameworks/Accelerate.framework/Headers
    
# ios:
