#if defined(__HEADERPRE_H__)
#error Export header file error. check following causes.
// ����:
// 1. HeaderPre.h�� HeaderPost.h ���̿� �ٸ� Export Header ������ ���Ե� ���
// 2. �ٸ� Export Header ������ ������ ��� �� ���Ͽ��� HeaderPost.h�� Include���� ���� ���
//    ã�� ���
//    Find���� Find What�� "HeaderP.*" �� �Է��ϰ� Regular Expression Check �Ҵ�.
//    �˻��� �� �߿��� "HeaderPre.h �� �ִ� ���� ã���� �ȴ�.
#endif

#define __HEADERPRE_H__

#if defined( __USE_DEF_FILE__) // Module Define File�� ��� �� ���
#error Module definition file can't be used this project

#else   // Module Define File�� ������� ���� ���

	#if defined(__WBF_BASE__)		// ���� Project�� ���ԵǴ� ���
		#define __MY_EXT_CLASS__		AFX_EXT_CLASS
		#define __MY_EXT_API__			AFX_EXT_API
		#define __MY_EXT_DATA__			AFX_EXT_DATA
	#else
		#if defined(_WINDLL)			// �ٸ� DLL Project�� ���ԵǴ� ���
			#define __MY_EXT_CLASS__	__declspec(dllimport)
			#define __MY_EXT_API__		__declspec(dllimport)
			#define __MY_EXT_DATA__		__declspec(dllimport)
		#else							// �ٸ� EXE Project�� ���ԵǴ� ���
			#define __MY_EXT_CLASS__	AFX_EXT_CLASS
			#define __MY_EXT_API__		AFX_EXT_API
			#define __MY_EXT_DATA__		AFX_EXT_DATA
		#endif
	#endif
#endif

