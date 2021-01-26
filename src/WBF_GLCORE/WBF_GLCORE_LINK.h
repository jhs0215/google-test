#pragma once

#ifndef __WBF_GLCORE_H__
#define __WBF_GLCORE_H__

#if !defined(_AFXDLL)
#error MFC Lib를 Shared Lib로 지정해야 합니다 !
#endif

#if (_MSC_VER == 1200)
#error vs6.0
#elif (_MSC_VER == 1400)
#error vs2005(8.0)
#elif (_MSC_VER == 1500)
#error vs2008(9.0)
#elif (_MSC_VER == 1600)
#error vs2010(10.0)
#elif (_MSC_VER == 1700)
#error vs2012(11.0)
#elif (_MSC_VER == 1800)
#error vs2013(12.0)
#elif (_MSC_VER == 1900)
#error vs2015(14.0)
#elif (_MSC_VER >= 1910 && _MSC_VER <= 1916) // vs2017(15.0)
	#ifndef _WIN64_
		#if defined(_DEBUG)
			#if defined(_AFXEXT)
				#define AUTOLIBNAME "..\\..\\lib\\v141\\debug\\x86\\WBF_GLCORE.lib"
			#else
				#define AUTOLIBNAME "..\\..\\lib\\v141\\debug\\x86\\WBF_GLCORE.lib"
			#endif
		#else
			#if defined(_AFXEXT)
				#define AUTOLIBNAME "..\\..\\lib\\v141\\release\\x86\\WBF_GLCORE.lib"
			#else
				#define AUTOLIBNAME "..\\..\\lib\\v141\\release\\x86\\WBF_GLCORE.lib"
			#endif
		#endif
	#else
		#if defined(_DEBUG)
			#if defined(_AFXEXT)
				#define AUTOLIBNAME "..\\..\\lib\\v141\\debug\\x64\\WBF_GLCORE.lib"
			#else
				#define AUTOLIBNAME "..\\..\\lib\\v141\\debug\\x64\\WBF_GLCORE.lib"
			#endif
		#else
			#if defined(_AFXEXT)
				#define AUTOLIBNAME "..\\..\\lib\\v141\\release\\x64\\WBF_GLCORE.lib"
			#else
				#define AUTOLIBNAME "..\\..\\lib\\v141\\release\\x64\\WBF_GLCORE.lib"
			#endif
		#endif
	#endif
#endif


// Perform autolink here:
#pragma message( "automatically link with (" AUTOLIBNAME ")")
#pragma comment(lib, AUTOLIBNAME)
#undef AUTOLIBNAME
#endif // End of __WBF_GLCORE_H__
